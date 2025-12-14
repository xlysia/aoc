const { start } = require('repl');
const { readInput, parseLines } = require('../../js/utils/readInput');

// Main function



async function main() {
    console.log('AoC 2025 day 7! Reading from input...\n');
    
    const input = await readInput(2025, 7);
    
    if (input !== null) {
        let lines = parseLines(input);
        
        W = lines[0].length;
        H = lines.length;

        function isSet(B,n){
            // Check if bit at position n is set
            return (B & (1n << BigInt(n))) !== 0n;
        }

        function turnOn(B,n){
            // To turn ON bit at position n
            return B | (1n << BigInt(n));
        }
        function turnOff(B,n){
            // To turn OFF bit at position n  
            return B & ~(1n << BigInt(n));
        }


        let partI = 0;
        let tachyon = 0n;
        tachyon = turnOn(tachyon, lines[0].indexOf('S')); // Turn on bit at start position

        for(let i = 1; i < H;i++){
            
            let nTachyon = 0n;
            for(let j = 0; j < W ; j++){
                if(!isSet(tachyon,j))continue;

                if(lines[i][j] !== '^'){
                    nTachyon = turnOn(nTachyon,j);
                    continue;
                }
                // Beam hits deflector - split into left and right
                if(j > 0) nTachyon = turnOn(nTachyon,j-1);
                if(j < W-1) nTachyon = turnOn(nTachyon,j+1);
                partI++;
            }
            tachyon = nTachyon;
            
        }

        console.log(`Part I - a tachyon beam a total of ${partI} times`);

        let partII = 1n;

        let tachyons = new Array(W).fill(0n);
        tachyons[lines[0].indexOf('S')] = 1n;

        for(let i = 1; i < H;i++){
            
            let nTachyon = new Array(W).fill(0n);
            for(let j = 0; j < W ; j++){

                if(tachyons[j] === 0n)continue;

                if(lines[i][j] !== '^'){
                    nTachyon[j] += tachyons[j];
                    continue;
                }
                // Beam hits deflector - split into left and right
                partII += BigInt(tachyons[j]); // Count the deflection once per beam
                
                if(j > 0){
                    nTachyon[j-1] += tachyons[j];
                }
                if(j < W-1){
                    nTachyon[j+1] += tachyons[j];
                } 
            }

            tachyons = nTachyon; // Fix: assign to tachyons, not tachyon
        }




        console.log(`Part II - a quantum tachyon beam a total of ${partII} times`);

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();