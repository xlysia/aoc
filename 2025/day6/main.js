const { readInput, parseLines } = require('../../js/utils/readInput');

// Main function

async function main() {
    console.log('AoC 2025 day 6! Reading from input...\n');
    
    const input = await readInput(2025, 6);
    
    if (input !== null) {
        let lines = parseLines(input);
        
        // For Part II, we need to work with the original character grid preserving spaces
        let charGrid = lines.map(line => line.split(''));


        let H = charGrid.length - 1;
        let W = charGrid[0].length;

        // Extract operations from last row
        let ops = charGrid[H].filter(char => char === '*' || char === '+');
        charGrid.pop();
        // For Part I: parse as before (removing spaces)
        let gridLines = lines.slice(0, -1).map(x => x.split(' ').filter(x => x.trim().length > 0));
        const grid = gridLines.map(row => row.map(x => BigInt(x)));
        const gridH = grid.length;
        const gridW = grid[0].length;

        let partI = 0n;
        let partII = 0n;

        // Part I calculation (as before)
        for(let j = 0; j < gridW ; j++){
            let op = ops[j];
            let res = op==='+'? 0n : 1n;
            for(let i = 0; i < gridH; i++){
                switch(op){
                    case '*': 
                        res*=grid[i][j];
                        break;
                    case '+':
                        res+= grid[i][j];
                        break;
                    default:
                        console.log("issue")
                }
            }
            partI += res;
        }

        // Part II - Read columns vertically from character grid, solve right-to-left
        // Find column positions where operations occur
        let o = ops.length-1;
        let op = ops[o];
        let curr = op === '+'?0n:1n;
        // Process from right to left
        for(let j = W-1; j >= 0 ; j--){
            
            // Form the vertical number from top to bottom for this column
            let verticalNumber = '';
            for(let i = 0; i < H; i++){ // exclude operation row
                let char = charGrid[i][j];
                if(char !== ' '){
                    verticalNumber += char;
                }
            }
            
            let num = 0n;
            if(verticalNumber != ''){
                num = BigInt(verticalNumber);
            }
            
            if(num === 0n){
                o -= 1;
                op = ops[o];
                partII += curr;
                curr = op === '+'?0n:1n;
                continue;
            }            

            switch(op){
                case '*': 
                    curr *= num
                    break;
                case '+':
                    curr += num;
                    break;
                default:
                    console.log("issue with operation:", op);
            }
        }

        o -= 1;
        op = ops[o];
        partII += curr;

        console.log(`Part I - sum of results ${partI}`);
        console.log(`Part II - grand total ${partII}`);

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();