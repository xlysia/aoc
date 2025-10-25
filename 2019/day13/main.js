const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');
const { IntcodeComputer } = require('../intCode');
const { Point } = require('../Point'); 

// Tile types for the arcade game
const TILES = {
    EMPTY: 0,
    WALL: 1,
    BLOCK: 2,
    PADDLE: 3,
    BALL: 4
};

const TILE_CHARS = {
    [TILES.EMPTY]: ' ',
    [TILES.WALL]: '#',
    [TILES.BLOCK]: 'B',
    [TILES.PADDLE]: '═',
    [TILES.BALL]: '●'
};

// Create 2D array using Array()
function create2DArray(width, height, defaultValue = 0) {
    return Array(height).fill(null).map(() => Array(width).fill(defaultValue));
}

// Print the board
function printBoard(board) {
    for (let row of board) {
        let line = '';
        for (let cell of row) {
            line += TILE_CHARS[cell] || '?';
        }
        console.log(line);
    }
}

// Main function
async function main() {
    console.log('AoC 2019 day 13! Reading from input...\n');
    
    const input = await readInput(2019, 13);
    
    if (input !== null) {
        // Input is comma separated integers
        const numbers = parseCommaSeparatedInts(input);
        
        const arcade = new IntcodeComputer(numbers.slice());
        
        // Create a 2D array to represent the game board
        let board = create2DArray(100,100,TILES.EMPTY);
        let score = 0;
        let partI = 0;        
        // Run the arcade game and collect output
        arcade.run();
        
        // Process output in groups of 3 (x, y, tileId)
        let outputs = arcade.output;
        for (let i = 0; i < outputs.length; i += 3) {
            const x = outputs[i];
            const y = outputs[i + 1];
            const tileId = outputs[i + 2];
            
            if(x===-1 && y === 0){
                score = tileId;
            }else{
                if(board[y][x] === TILES.BLOCK)partI--;
                if(tileId == TILES.BLOCK)partI++;
                board[y][x] = tileId;
            }

        }
        
        
        // console.log('\nGame Board:');
        // printBoard(board);
        
        console.log(`PartI:`,partI);

        // Part II reset and rerun with memory 0 = 2
       // Create a 2D array to represent the game board

        score = 0;
        let partII = 0;
        let blocks = 0;
        let Ball = new Point(0,0);
        let Paddle = new Point(0,0);       
        // Run the arcade game and collect output
        arcade.reset(numbers.slice());
        
        arcade.memory[0] = 2; // Free game
        while(!arcade.halted){
            arcade.run();
            outputs = arcade.output;

            board = create2DArray(100,100,TILES.EMPTY);
            for (let i = 0; i < outputs.length; i += 3) {
                const x = outputs[i];
                const y = outputs[i + 1];
                const tileId = outputs[i + 2];
                
                if(x===-1 && y === 0){
                    score = tileId;
                }else{
                    if(board[y][x] === TILES.BLOCK)blocks--;
                    if(tileId == TILES.BLOCK)blocks++;
                    board[y][x] = tileId;
                    switch(tileId){
                        case TILES.BALL:
                            Ball = new Point(x,y);
                            break;
                        case TILES.BLOCK:
                            blocks++;
                            break;
                        case TILES.PADDLE:
                            Paddle = new Point(x,y);
                            break;
                    }
                }

            }
            arcade.clearOuput();
            if(arcade.waitingForInput){
                const move = Math.sign(Ball.x - Paddle.x);
                arcade.setInput([move]);
            }

            if(blocks === 0){
                console.log("GAME DONE");
            }

        }



        console.log("Part II : ", score);
    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();