const { patch } = require('simple-get');
const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');
const { IntcodeComputer } = require('../intCode');
const { Point } = require('../Point');
const { createCanvas } = require('canvas');
const fs = require('fs');

const TILES = {
    EMPTY: -1,
    SCAFFOLD: 35,
    PATH: 46,
    NEWLINE: 10,
    UP: 94,  // '^' 
    RIGHT: 62,  // '>' 
    DOWN: 118, // 'v'  
    LEFT: 60,  // '<' 
    TUMBLING: 88 ,
};

const TILE_COLORS = {
    [TILES.EMPTY]:'rgba(0, 0, 0, 0)',
    [TILES.SCAFFOLD]: 'rgba(0, 0, 0, 255)',
    [TILES.PATH]: 'rgba(50, 50, 50, 255)',
};

const char2dirIdx = {
    [TILES.UP]: 0,
    [TILES.RIGHT]: 1,
    [TILES.DOWN]: 2,
    [TILES.LEFT]: 3,
};

const dirs = [
    new Point(0,-1),
    new Point(1,0),
    new Point(0,1),
    new Point(-1,0)
];

const MAX_SIZE = 20;

class Robot extends Point{
    constructor(x = 0, y = 0, state = TILES.UP) {
        super(x, y);
        if(state === TILES.TUMBLING){
            this.didx = -1;
        }else{
            this.didx = char2dirIdx[state];
        }
        
        this.istumbling = state === TILES.TUMBLING;
        this.color = 'rgba(50, 50, 150, 255)'
        console.log("Robot initialized:",this);
    }
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

function generateFullPath(ctx, robot, WIDTH, HEIGHT) {
    const program = [];
    let currentPos = robot.clone();
    let currentDir = robot.didx;
        
    while (true) {
        // Try to move forward as much as possible
        let steps = 0;
        while (true) {
            const nextPos = currentPos.clone().move(dirs[currentDir]);
            
            // Check if next position is valid scaffold
            if (nextPos.x >= 0 && nextPos.x < WIDTH && 
                nextPos.y >= 0 && nextPos.y < HEIGHT) {
                const nextColor = getCurrentPanelColor(ctx, nextPos);
                if (nextColor === TILES.SCAFFOLD) {
                    currentPos = nextPos;
                    steps++;
                    continue;
                }
            }
            break; // Can't move forward anymore
        }
        
        // If we moved, add the step count
        if (steps > 0) {
            program.push(steps.toString());
        }
        
        // Try to turn left or right to find more scaffold
        let foundTurn = false;
        
        // Try turning right first
        const rightDir = (currentDir + 1) % 4;
        const rightPos = currentPos.clone().move(dirs[rightDir]);
        if (rightPos.x >= 0 && rightPos.x < WIDTH && 
            rightPos.y >= 0 && rightPos.y < HEIGHT) {
            const rightColor = getCurrentPanelColor(ctx, rightPos);
            if (rightColor === TILES.SCAFFOLD) {
                program.push('R');
                currentDir = rightDir;
                foundTurn = true;
            }
        }
        
        // If right didn't work, try left
        if (!foundTurn) {
            const leftDir = (currentDir + 3) % 4; // +3 is same as -1 mod 4
            const leftPos = currentPos.clone().move(dirs[leftDir]);
            if (leftPos.x >= 0 && leftPos.x < WIDTH && 
                leftPos.y >= 0 && leftPos.y < HEIGHT) {
                const leftColor = getCurrentPanelColor(ctx, leftPos);
                if (leftColor === TILES.SCAFFOLD) {
                    program.push('L');
                    currentDir = leftDir;
                    foundTurn = true;
                }
            }
        }

        if (!foundTurn) {
            break;
        }
    }
    
    return program;
}

class Routine{
    constructor(program){
        this.main = program;
        this.A = [];
        this.B = [];
        this.C = [];
        this.step = 0;
    }

    IsValid(){
        // Check all routines are <= 20 chars and we have all 3 subroutines
        const allRoutinesValid = [this.main,this.A,this.B,this.C].every(X => X.join(',').length <= MAX_SIZE);
        
        // Check main contains only A, B, C tokens
        const mainOnlyABC = this.main.every(token => ['A', 'B', 'C'].includes(token));
        
        return allRoutinesValid && mainOnlyABC && this.step === 3;
    }

    clone() {
        const newRoutine = new Routine([]);
        newRoutine.main = [...this.main];
        newRoutine.A = [...this.A];
        newRoutine.B = [...this.B]; 
        newRoutine.C = [...this.C];
        newRoutine.step = this.step;
        return newRoutine;
    }

    routineToASCII(routine) {
        const result = [];
        for (let i = 0; i < routine.length; i++) {
            const token = routine[i];
            // Convert each character of the token to ASCII
            for (let j = 0; j < token.length; j++) {
                result.push(token.charCodeAt(j));
            }
            if (i < routine.length - 1) {
                result.push(','.charCodeAt(0)); // 44
            }
        }
        return result;
    }

    toASCII(){
        const result = [];
        
        // Main routine + newline
        result.push(...this.routineToASCII(this.main));
        result.push(TILES.NEWLINE); // 10
        
        // Function A + newline  
        result.push(...this.routineToASCII(this.A));
        result.push(TILES.NEWLINE);
        
        // Function B + newline
        result.push(...this.routineToASCII(this.B));
        result.push(TILES.NEWLINE);
        
        // Function C + newline
        result.push(...this.routineToASCII(this.C));
        result.push(TILES.NEWLINE);
        
        // Video feed (n for no) + newline
        result.push('n'.charCodeAt(0)); // 110
        result.push(TILES.NEWLINE);
        
        return result;
    }
    
}

function dfs(routine) {
    // Base case: if we have all 3 routines (step = 3) and it's valid
    if (routine.step === 3) {
        return routine.IsValid() ? routine : null;
    }
    
    const routineNames = ['A', 'B', 'C'];
    const currentRoutineName = routineNames[routine.step];
    
    // Find first position that's not already assigned to A/B/C
    const firstUnassigned = routine.main.findIndex(token => 
        !['A', 'B', 'C'].includes(token)
    );
    
    if (firstUnassigned === -1) {
        return null;
    }

    let segmentSize = routine.main.slice(firstUnassigned).findIndex(token => 
        ['A', 'B', 'C'].includes(token)
    );

    if(segmentSize === -1){
        segmentSize = routine.main.length;
    }
    
    // Try different subsequence lengths starting from firstUnassigned
    for (let len = 2; len <= segmentSize; len+=2) {
        // Extract candidate subsequence
        const candidate = [];
        let pos = firstUnassigned;
        
        // Get 'len' unassigned tokens
        while (candidate.length < len && pos < routine.main.length) {
            candidate.push(routine.main[pos]);
            candidate.push(routine.main[pos+1]);
            pos+=2;
        }
        
        if (candidate.length !== len) continue;
        
        // Check if candidate routine is valid length
        if (candidate.join(',').length > MAX_SIZE) break;
        
        // Create new routine state
        const newRoutine = routine.clone();
        
        if (currentRoutineName === 'A') newRoutine.A = candidate;
        else if (currentRoutineName === 'B') newRoutine.B = candidate;
        else if (currentRoutineName === 'C') newRoutine.C = candidate;
        
        newRoutine.main = replaceSubsequence(newRoutine.main, candidate, currentRoutineName);
        newRoutine.step++;
        
        // Continue DFS
        const result = dfs(newRoutine);
        if (result) return result;
    }
    
    return null;
}

function replaceSubsequence(program, subsequence, replacement) {
    const S = subsequence.join(',');
    if (!S) return program.slice();

    // REGEX
    function escapeRegExp(str) {
        return str.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
    }

    const joined = program.join(',');
    const re = new RegExp(escapeRegExp(S), 'g'); // global replace
    const replaced = joined.replace(re, replacement);

    return replaced.split(',').filter(tok => tok.length > 0);
}

// Main function
async function main() {
    console.log('AoC 2019 day 17! Reading from input...\n');

    const input = await readInput(2019, 17);

    if (input !== null) {
        // Input is comma separated integers
        const numbers = parseCommaSeparatedInts(input);
        const cameras = new IntcodeComputer(numbers.slice());
        cameras.enlarge();
        cameras.run();
        const pixels = cameras.output;

        const WIDTH = pixels.findIndex(x => x === TILES.NEWLINE);
        const HEIGHT =  pixels.filter(x => x === TILES.NEWLINE).length;


        const canvas = createCanvas(WIDTH, HEIGHT);
        const ctx = canvas.getContext('2d');
        ctx.fillStyle = 'rgba(0, 0, 0, 0)';
        ctx.fillRect(0, 0, canvas.width, canvas.height);

        let cursor = new Point(0,0);
        let robot;

        for(let p of pixels){
            switch(p){
                case TILES.NEWLINE:
                    cursor.x = 0;
                    cursor.y ++;    
                    continue;
                case TILES.PATH:
                case TILES.SCAFFOLD:
                    setCurrentPanelColor(ctx,cursor,TILE_COLORS[p]);
                    cursor.x++;
                    break;
                default:
                    robot = new Robot(cursor.x,cursor.y, p);
                    setCurrentPanelColor(ctx,cursor,robot.color);
                    cursor.x++;
                    break;
            }
        }

        // Save Part I image and wait for completion
        const out = fs.createWriteStream('partI.png');
        const stream = canvas.createPNGStream();
        stream.pipe(out);
        
        let partI = 0;
        // Find Intersections of scaffold
        for(let i = 1; i < HEIGHT - 1;i++){
            for(let j = 1 ; j < WIDTH - 1;j++){
                cursor = new Point(j,i);
                
                // First check if center is a scaffold
                const centerColor = getCurrentPanelColor(ctx, cursor);
                if(centerColor !== TILES.SCAFFOLD) continue;
                
                // Then check all 4 neighbors are scaffolds
                const isIntersection = dirs.every(offset => {
                    const coord = cursor.clone().move(offset);
                    const color = getCurrentPanelColor(ctx, coord);
                    return color === TILES.SCAFFOLD;
                });

                // found intersection
                if(!isIntersection) continue;
                partI += i*j;
            }
        }

        console.log("Part I - Intersections value:", partI);

        await new Promise((resolve) => {
            out.on('finish', () => {
                console.log('Saved as partI.png');
                resolve();
            });
        });

        // Part II - Wake up the vacuum robot
        console.log("\n=== Part II - Vacuum Robot ===");
        
        // Change position 0 from 1 to 2 to wake up the robot
        const vacuumNumbers = [...numbers];
        vacuumNumbers[0] = 2;
        
        const vacuum = new IntcodeComputer(vacuumNumbers);
        vacuum.enlarge();
        
        // Pour l'instant, on lance juste pour voir ce que l'aspirateur demande
        vacuum.run();
        
        vacuum.clearOuput();
        
        const fullProgram = generateFullPath(ctx, robot, WIDTH, HEIGHT);

        console.log(fullProgram.join(','));

        console.log(`\nProgram length: ${fullProgram.length} commands`);

        let rawRoutine = new Routine(fullProgram);

        let routine = dfs(rawRoutine);

        if (routine) {
            console.log("\n✅ Found valid decomposition!");
            console.log("A:", routine.A.join(','), `(${routine.A.join(',').length} chars)`);
            console.log("B:", routine.B.join(','), `(${routine.B.join(',').length} chars)`);
            console.log("C:", routine.C.join(','), `(${routine.C.join(',').length} chars)`);
            console.log("Main:", routine.main.join(','), `(${routine.main.join(',').length} chars)`);

            vacuum.setInput(routine.toASCII());

            vacuum.run();
            
            let partII = vacuum.getLastOutput();

            console.log('PartII:',partII);

        } else {
            console.log("❌ No valid decomposition found");
        }

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();