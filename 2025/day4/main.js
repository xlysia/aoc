const { readInput, parseLines } = require('../../js/utils/readInput');

// Main function

async function main() {
    console.log('AoC 2025 day 4! Reading from input...\n');
    
    const input = await readInput(2025, 4);
    
    if (input !== null) {
        const grid = parseLines(input).map(x => x.split(''));
        const H = grid.length;
        const W = grid[0].length;

        // @ = roll . = empty

        function neighbourCount(x,y){
            if(grid[y][x] !== '@')return null;
            let res = -1;
            for( let i = x-1; i < x+2 ; i++){
                for( let j = y-1; j < y+2 ; j++){
                    if(i < 0 || i > W-1 || j < 0 || j > H -1)continue;

                    res+= grid[j][i] === '@';
                }
            }
            return res;
        }

        function searchRolls(bRemoveRoll){
            let res = 0;
            for(let i = 0; i < W;i++){
                for(let j = 0; j < H;j++){
                    if( grid[j][i] !== '@')continue;
                    if(neighbourCount(i,j)>3)continue;
                    if(bRemoveRoll)grid[j][i] = '.';
                    res ++;
                }
            }
            return res;
        }

        let partI = null;
        let partII = 0;
        while(true){

            let res = searchRolls(partI !== null);
            if(partI === null) partI = res;
            else partII += res;

            if(res === 0)break;



        }



        console.log(`Part I - accessible rolls count ${partI}`);
        console.log(`Part II - removed rolls count ${partII}`);

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();