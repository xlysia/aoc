const { readInput, parseLines } = require('../../js/utils/readInput');
const { Point } = require('../Point');
const fs = require('fs');
const { patch } = require('simple-get');

const dirs = [
    new Point(0, -1), // up
    new Point(1, 0),  // right
    new Point(0, 1),  // down
    new Point(-1, 0)  // left
];

function isKey(char) {
    return char >= 'a' && char <= 'z';
}

function isDoor(char) {
    return char >= 'A' && char <= 'Z';
}

function isWall(char) {
    return char === '#';
}

function isOpen(char) {
    return char === '.' || char === '@';
}

function isEntrance(char){
    return char === '@' || (char >= '0' && char < '4');
}

class GraphNode {
    constructor(pos, char) {
        this.pos = pos;
        this.char = char;
        this.reachable = new Map(); // Map<target_char, {distance, requiredKeys}>
    }
}

function buildGraph(map) {
    const WIDTH = map[0].length;
    const HEIGHT = map.length;
    const graph = new Map(); // Map<char, GraphNode>
    
    // Find all keys, doors, and start position
    const nodes = new Map(); // Map<pos_string, char>
    let nbkeys = 0;
    let nbdoors = 0;
    for (let y = 0; y < HEIGHT; y++) {
        for (let x = 0; x < WIDTH; x++) {
            const char = map[y][x];
            if(isKey(char))nbkeys++;
            if(isDoor(char))nbdoors++;
            
            if (isEntrance(char) || isKey(char) ){//|| isDoor(char)) {
                const pos = new Point(x, y);
                nodes.set(`${x},${y}`, char);
                graph.set(char, new GraphNode(pos, char));

            }
        }
    }
    console.log(`keys: ${nbkeys}, doors ${nbdoors}`);

    // For each node, find what it can reach using BFS
    for (const [nodeChar, node] of graph) {
        const reachable = bfsFromNode(map, node.pos, WIDTH, HEIGHT);
        node.reachable = reachable;
    }
    
    return graph;
}

function bfsFromNode(map, startPos, WIDTH, HEIGHT) {
    const reachable = new Map();
    const queue = [{pos: startPos, distance: 0, requiredKeys: new Set()}];
    const visited = new Set();
    visited.add(`${startPos.x},${startPos.y}`);
    
    while (queue.length > 0) {
        const {pos, distance, requiredKeys} = queue.shift();
        
        for (const dir of dirs) {
            const newPos = pos.clone().move(dir);
            const posKey = `${newPos.x},${newPos.y}`;
            
            // Check bounds
            if (newPos.x < 0 || newPos.x >= WIDTH || newPos.y < 0 || newPos.y >= HEIGHT) {
                continue;
            }
            
            // Skip if already visited
            if (visited.has(posKey)) {
                continue;
            }
            
            const char = map[newPos.y][newPos.x];
            
            // Skip walls
            if (isWall(char)) {
                continue;
            }
            
            visited.add(posKey);
            const newRequiredKeys = new Set(requiredKeys);
            
            // If it's a door, add required key
            if (isDoor(char)) {
                newRequiredKeys.add(char.toLowerCase());
            }
            
            // If it's a key (and not the starting position), record it as reachable
            if (isKey(char)) {
                reachable.set(char, {
                    distance: distance + 1,
                    requiredKeys: Array.from(newRequiredKeys)
                });
            }
            
            // Continue exploring (including through doors and keys)
            if (isOpen(char) || isKey(char) || isDoor(char)) {
                queue.push({
                    pos: newPos,
                    distance: distance + 1,
                    requiredKeys: newRequiredKeys
                });
            }
        }
    }
    
    return reachable;
}

// Memoization cache
const memo = new Map();

function dfs(graph, key, collectedKeys = new Set()){
    // Create state key for memoization
    const sortedKeys = Array.from(collectedKeys).sort().join('');
    const stateKey = `${key}-${sortedKeys}`;
    
    if(memo.has(stateKey)){
        return memo.get(stateKey);
    }
    
    // Base case: collected all keys
    const totalKeys = Array.from(graph.keys()).filter(k => k !== '@').length;
    if(collectedKeys.size === totalKeys){
        memo.set(stateKey, 0);
        return 0;
    }

    const node = graph.get(key);
    let mini = Infinity;
    
    for(let [char, info] of node.reachable){
        // Skip if already collected
        if(collectedKeys.has(char)) continue;
        
        // Check if we can reach (have required keys)
        let canGo = info.requiredKeys.every(x => collectedKeys.has(x));
        if(!canGo) continue;
        
        // Try collecting this key
        const newCollectedKeys = new Set(collectedKeys);
        newCollectedKeys.add(char);
        
        let s = info.distance + dfs(graph, char, newCollectedKeys);
        mini = Math.min(s, mini);
    }
    
    memo.set(stateKey, mini);
    return mini;
}

function dfs2(graph, keys, collectedKeys = new Set()){
    // Create state key for memoization
    const sortedKeys = Array.from(collectedKeys).sort().join('');
    const stateKey = `${keys.join('')}-${sortedKeys}`;
    
    if(memo.has(stateKey)){
        return memo.get(stateKey);
    }
    
    // Base case: collected all keys
    const totalKeys = Array.from(graph.keys()).filter(k => !isEntrance(k)).length;
    if(collectedKeys.size === totalKeys){
        memo.set(stateKey, 0);
        return 0;
    }

    let mini = Infinity;

    for(let i = 0; i < keys.length; i++){
        const key = keys[i];
        const node = graph.get(key);
        if(!node) continue;
        
        for(let [char, info] of node.reachable){
            // Skip if already collected
            if(collectedKeys.has(char)) continue;
            
            // Check if we can reach (have required keys)
            let canGo = info.requiredKeys.every(x => collectedKeys.has(x));
            if(!canGo) continue;
            
            // Try collecting this key - update robot position
            const newCollectedKeys = new Set(collectedKeys);
            newCollectedKeys.add(char);
            
            // Create new robot positions with robot i moved to char
            const newKeys = [...keys];
            newKeys[i] = char;
            
            let s = info.distance + dfs2(graph, newKeys, newCollectedKeys);
            mini = Math.min(s, mini);
        }
    }
    memo.set(stateKey, mini);
    return mini;
}

// Main function
async function main() {
    console.log('AoC 2019 day 18! Reading from input...\n');
    
    const input = await readInput(2019, 18);
    
    if (input !== null) {
        const map = parseLines(input).map(line => line.split(''));
        const WIDTH = map[0].length;
        const HEIGHT = map.length;

        // Build the graph
        console.log('Building graph...');
        const graph = buildGraph(map);
        const nbkeys = graph.size - 1; // -1 because @ is not a key
        
        console.log(`Graph has ${graph.size} nodes, ${nbkeys} keys to collect`);
        
        // Get shortest path to visit all...
        memo.clear(); // Clear memoization cache
        let partI = dfs(graph, "@", new Set());
        console.log("PartI - Shortest path to collect keys: ", partI);

        let start = graph.get('@');
        const origin = start.pos;

        // change pattern
        // ... ; .@. ; ...
        // to @#@ ; ### ; @#@
        map[origin.y - 1][origin.x - 1] = '0';
        map[origin.y - 1][origin.x] = '#';
        map[origin.y - 1][origin.x + 1] = '1'; 
        map[origin.y + 1][origin.x - 1] = '3';
        map[origin.y + 1][origin.x] = '#';
        map[origin.y + 1][origin.x + 1] = '2';

        map[origin.y ][origin.x - 1] = '#';
        map[origin.y ][origin.x] = '#';
        map[origin.y ][origin.x + 1] = '#'; 

        const graph2 = buildGraph(map);
        memo.clear();
        let partII = dfs2(graph2, ['0','1','2','3'], new Set());
        console.log("PartII - Shortest path to collect keys: ", partII);

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();