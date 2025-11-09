const { readInput, parseGrid } = require('../../js/utils/readInput');
const { Point } = require('../Point');
const { Queue } = require('../Queue');
const fs = require('fs');

const dirs = [
    new Point(0, -1), // up
    new Point(1, 0),  // right
    new Point(0, 1),  // down
    new Point(-1, 0)  // left
];

function isDoor(char) {
    return char >= 'A' && char <= 'Z';
}

function isWall(char) {
    return char === '#' || isEmpty(char);
}

function isOpen(char) {
    return char === '.';
}

function isEmpty(char){
    return char === ' ';
}

class Portal{
    constructor(label,A,B){
        this.label = label;
        this.A = A;
        this.B = B;
    }

    goThrough(pos){
        if(A.equals(pos))pos.move(B);
        else pos.move(A);
    }
};

function isVerticalPortal(map,i,j){
    return isDoor(map[i+1]?.[j]);
}

function isHorizontalPortal(map,i,j){
    return isDoor(map[i]?.[j+1]);
}

function findPortals(map){

    const portals = new Map();
    const portals_ = new Map();

    const WIDTH = map[0].length;
    const HEIGHT = map.length;

    for(i = 0; i < HEIGHT; i++){
        for(j = 0; j < WIDTH; j++){
            const c = map[i][j];
            if(isWall(c) || isOpen(c))continue;
            
            if(!isDoor(c))continue;
            
            // Find portal

            if(isVerticalPortal(map,i,j)){
                const label = map[i][j] + map[i+1][j];
                if(!portals.has(label))portals.set(label,new Portal(label,null,null));
                const p = portals.get(label);

                const pos = isOpen(map[i+2]?.[j])?new Point(j,i+2):new Point(j,i-1);
                if(!p.A)p.A = pos;
                else{
                    p.B = pos;
                    portals_.set(`${p.B.x},${p.B.y}`, p.A);
                    portals_.set(`${p.A.x},${p.A.y}`, p.B);
                } 
            }
            else if(isHorizontalPortal(map,i,j)){
                const label = map[i][j] + map[i][j+1];

                if(!portals.has(label))portals.set(label,new Portal(label,null,null));
                const p = portals.get(label);

                const pos = isOpen(map[i]?.[j+2])?new Point(j+2,i):new Point(j-1,i);
                if(!p.A)p.A = pos;
                else{
                    p.B = pos;
                    portals_.set(`${p.B.x},${p.B.y}`, p.A);
                    portals_.set(`${p.A.x},${p.A.y}`, p.B);
                } 
            }
            
        }
    }

    return [portals,portals_];
}

function isOuterPortal(pos, WIDTH, HEIGHT) {
    // A portal is "outer" if it's on the absolute boundary of the maze
    // Based on typical AoC maze structure
    return pos.x <= 3 || pos.x >= WIDTH - 4 || 
           pos.y <= 3 || pos.y >= HEIGHT - 4;
}

function bfs(map , portals, from , to){
    let queue = new Queue();
    let visited = new Set();

    queue.enqueue({steps: 0, coord: from});
    visited.add(`${from.x},${from.y}`);

    while(!queue.isEmpty()){
        const { steps, coord } = queue.dequeue();

        if(coord.equals(to)) {
            return steps;
        }

        // Check for portal teleportation
        const coordKey = `${coord.x},${coord.y}`;
        if(portals.has(coordKey)){
            let newCoord = portals.get(coordKey).clone();
            let newCoordKey = `${newCoord.x},${newCoord.y}`;
           
            if(!visited.has(newCoordKey)) {
                visited.add(newCoordKey);
                queue.enqueue({
                    steps: steps + 1, 
                    coord: newCoord
                });
            }
        }

        // Try each direction
        for(let direction of dirs){
            let newCoord = coord.clone().move(direction);
            let coordKey = `${newCoord.x},${newCoord.y}`;
            
            let _char = map[newCoord.y][newCoord.x];

            if(isOpen(_char)){
                if(visited.has(coordKey)) continue;
                visited.add(coordKey);
                
                queue.enqueue({
                    steps: steps + 1, 
                    coord: newCoord
                });
            }
        }
    }
    return -1;
}

function bfsRecursive(map, portals, from, to) {
    const WIDTH = map[0].length;
    const HEIGHT = map.length;
    
    let queue = new Queue();
    let visited = new Set();

    queue.enqueue({steps: 0, coord: from, level: 0});
    visited.add(`${from.x},${from.y},0`);

    while(!queue.isEmpty()){
        const { steps, coord, level } = queue.dequeue();

        // Can only reach ZZ at level 0
        if(coord.equals(to) && level === 0) {
            return steps;
        }

        const coordKey = `${coord.x},${coord.y}`;
        if(portals.has(coordKey)){
            const newCoord = portals.get(coordKey);
            
            if(newCoord) {
                const isOuter = isOuterPortal(coord, WIDTH, HEIGHT);
                
                let newLevel;
                if(isOuter) {
                    newLevel = level - 1; 
                    if(newLevel < 0) {
                        // Can't go above level 0, skip this portal
                    } else {
                        const newCoordKey = `${newCoord.x},${newCoord.y},${newLevel}`;
                        if(!visited.has(newCoordKey)) {
                            visited.add(newCoordKey);
                            queue.enqueue({
                                steps: steps + 1,
                                coord: newCoord.clone(),
                                level: newLevel
                            });
                        }
                    }
                } else {
                    newLevel = level + 1; // Inner portal goes down one level
                    const newCoordKey = `${newCoord.x},${newCoord.y},${newLevel}`;
                    if(!visited.has(newCoordKey)) {
                        visited.add(newCoordKey);
                        queue.enqueue({
                            steps: steps + 1,
                            coord: newCoord.clone(),
                            level: newLevel
                        });
                    }
                }
            }
        }

        // Try each direction
        for(let direction of dirs){
            let newCoord = coord.clone().move(direction);
            let coordKey = `${newCoord.x},${newCoord.y},${level}`;
            
            let _char = map[newCoord.y][newCoord.x];

            if(isOpen(_char)){
                if(visited.has(coordKey)) continue;
                visited.add(coordKey);
                
                queue.enqueue({
                    steps: steps + 1, 
                    coord: newCoord,
                    level: level
                });
            }
        }
    }
    return -1;
}

// Main function
async function main() {
    console.log('AoC 2019 day 20! Reading from input...\n');
    
    const input = await readInput(2019, 20);
    
    if (input !== null) {
        const map = parseGrid(input);

        const [portals,portals_] = findPortals(map);
        console.log("Found ", portals.size ,"portals");

        let from = portals.get('AA').A.clone();
        let to = portals.get('ZZ').A.clone();

        let partI = bfs(map, portals_, from ,to);
        console.log("PartI - Shortest path length: ", partI);
        
        // Part II - Recursive maze
        let partII = bfsRecursive(map, portals_, from, to);
        console.log("PartII - Shortest path in recursive maze: ", partII);
    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();