const { patch } = require('simple-get');
const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');
const { IntcodeComputer } = require('../intCode');
const { Point } = require('../Point');
const { createCanvas } = require('canvas');
const fs = require('fs');
const { Queue } = require('../Queue');

const TILES = {
    EMPTY: -1,
    WALL: 0,
    PATH: 1,
    OXYGEN: 2,
};

const TILE_COLORS = {
    [TILES.EMPTY]:'rgba(0, 0, 0, 0)',
    [TILES.WALL]: 'rgba(0, 0, 0, 255)',
    [TILES.PATH]: 'rgba(50, 50, 50, 255)',
    [TILES.OXYGEN]: 'rgba(0, 0, 200, 255)',
};

const dirs = {
    'N': new Point(0, -1),  // North (up)
    'E': new Point(1, 0),   // East (right) 
    'S': new Point(0, 1),   // South (down)
    'W': new Point(-1, 0)   // West (left)
};

const dirStr = ['N', 'S', 'W', 'E'];

// For Intcode movement commands (1=N, 2=S, 3=W, 4=E)
const intcodeDirs = {
    1: dirs['N'],  // North
    2: dirs['S'],  // South  
    3: dirs['W'],  // West
    4: dirs['E']   // East
}; 

const dir2intcode = {
    'N':1,
    'S':2,
    'W':3,
    'E':4
}

function getCurrentPanelColor(ctx, pos) {
    const pixel = ctx.getImageData(pos.x, pos.y, 1, 1).data;
    const [r, g, b, a] = pixel;
    
    // Compare against each tile color to find matching type
    for (const [tileType, colorString] of Object.entries(TILE_COLORS)) {
        // Parse rgba string to components
        const match = colorString.match(/rgba\((\d+),\s*(\d+),\s*(\d+),\s*(\d+)\)/);
        if (match) {
            const [, tr, tg, tb, ta] = match.map(Number);
            
            // Check if pixel matches this tile color
            if (r === tr && g === tg && b === tb && a === ta) {
                return parseInt(tileType);
            }
        }
    }
    
    // Default to EMPTY if no match found
    return TILES.EMPTY;
}

function setCurrentPanelColor(ctx,pos,color){
    ctx.fillStyle = color;
    ctx.fillRect(pos.x, pos.y, 1, 1);
}

function getNewTarget(ctx,pos){
    let queue = new Queue();
    let visited = new Set();
    
    queue.enqueue({path:'', coord: pos.clone()});
    visited.add(`${pos.x},${pos.y}`);
    
    while(!queue.isEmpty()){
        const { path, coord } = queue.dequeue();
        
        // Try each direction
        for(let [cmdNum, direction] of Object.entries(intcodeDirs)){
            let newCoord = coord.clone().move(direction);
            let coordKey = `${newCoord.x},${newCoord.y}`;
            
            if(visited.has(coordKey)) continue;
            visited.add(coordKey);
            
            let tileType = getCurrentPanelColor(ctx, newCoord);
            switch(tileType){
                case TILES.WALL: 
                    continue;
                case TILES.EMPTY:
                    // Found unexplored area - return path to get there
                    return path + dirStr[parseInt(cmdNum)-1];
                case TILES.OXYGEN:
                case TILES.PATH:
                    // Add to queue for further exploration
                    queue.enqueue({
                        path: path + dirStr[parseInt(cmdNum)-1], 
                        coord: newCoord
                    });
                    break;
            }
        }
    }
    
    return null; // No more unexplored areas
}

function explore(ctx,computer,pos){
    let target;
    let oxygen_coord = null;
    while((target = getNewTarget(ctx,pos)) != null){

        
        // Send commands to intcode computer for each character in path
        let lastResult;
        for(let direction of target){  // Like C++ range-based for loop!
            computer.setInput([dir2intcode[direction]]);
            computer.run();
            lastResult = computer.getLastOutput();
                        
            // Only move if we didn't hit a wall
            if(lastResult !== TILES.WALL) {
                pos.move(dirs[direction]);
            }
        }

        // Color the final position based on the last result
        if(lastResult !== undefined) {
            let colorPos = lastResult === TILES.WALL ? 
                pos.clone().move(dirs[target[target.length-1]]) : pos;
            setCurrentPanelColor(ctx, colorPos, TILE_COLORS[lastResult]);
            
            if(lastResult === TILES.OXYGEN){
                oxygen_coord =  pos.clone();
            }
        }
    }

    return oxygen_coord;
}

function bfs(ctx,from,to){
    let queue = new Queue();
    let visited = new Set();
    
    queue.enqueue({steps: 0, coord: from.clone()});
    visited.add(`${from.x},${from.y}`);
    
    let partI = null;
    let partII = 0;

    while(!queue.isEmpty()){
        const { steps, coord } = queue.dequeue();
        partII = Math.max(partII,steps);
        // Check current position
        let currentTile = getCurrentPanelColor(ctx, coord);
        if(coord.equals(to)) {
            partI = steps;
        }
        
        // Try each direction
        for(let [cmdNum, direction] of Object.entries(intcodeDirs)){
            let newCoord = coord.clone().move(direction);
            let coordKey = `${newCoord.x},${newCoord.y}`;
            
            if(visited.has(coordKey)) continue;
            visited.add(coordKey);
            
            let tileType = getCurrentPanelColor(ctx, newCoord);
            switch(tileType){
                case TILES.WALL: 
                case TILES.EMPTY:
                    continue;
                case TILES.OXYGEN:
                case TILES.PATH:
                    // Add to queue for further exploration
                    queue.enqueue({
                        steps: steps + 1, 
                        coord: newCoord
                    });
                    break;
            }
        }
    }
    
    return [partI, partII]; // Oxygen not found
}

// Main function
async function main() {
    console.log('AoC 2019 day 15! Reading from input...\n');

    const input = await readInput(2019, 15);

    if (input !== null) {
        // Input is comma separated integers
        const numbers = parseCommaSeparatedInts(input);
        const computer = new IntcodeComputer(numbers.slice());
        computer.enlarge();
        const canvas = createCanvas(300, 300);

        const ctx = canvas.getContext('2d');
        ctx.fillStyle = 'rgba(0, 0, 0, 0)';
        ctx.fillRect(0, 0, canvas.width, canvas.height);

        const startPos = new Point(canvas.width/2,canvas.height/2);
        let robotPos = startPos.clone();
        setCurrentPanelColor(ctx,robotPos,TILE_COLORS[TILES.PATH]);

        const oxygenPos =  explore(ctx,computer,robotPos);

        let [partI,partII] = bfs(ctx,oxygenPos,startPos);
        console.log('Part I (shortest steps to oxygen):', partI);
        console.log('Part II (Time to fill maze):', partII);

        // Save Part I image and wait for completion
        const out = fs.createWriteStream('partI.png');
        const stream = canvas.createPNGStream();
        stream.pipe(out);
        
        await new Promise((resolve) => {
            out.on('finish', () => {
                console.log('Saved as partI.png');
                resolve();
            });
        });

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();