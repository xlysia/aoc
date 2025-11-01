const path = require('path');

const { readInput, parseLines } = require('../../js/utils/readInput');


function FFT(number, pattern){
    let n = number.length;
    let result = new Array(n);
    
    for(let i = 0; i < n; i++){
        let sum = 0;
        for(let j = 0; j < n; j++){
            let digit = parseInt(number[j]);
            
            let idx = Math.floor((j + 1) / (i + 1)) % 4;
            let p = pattern[idx];
            
            sum += digit * p;
        }
        
        // Keep only the ones digit
        result[i] = Math.abs(sum) % 10;
    }
    
    return result.join('');
}

// Main function
async function main() {
    console.log('AoC 2019 day 16! Reading from input...\n');
   // Flawed Frequency Transmission

    const input = await readInput(2019, 16);
    if (input !== null) {
        const originalInput = input.trim();
        let number = originalInput;

        const pattern = [0, 1, 0, -1];

        for(let i = 0 ; i < 100; i++){
            number = FFT(number, pattern);
        }
        
        console.log("Part I :", number.slice(0, 8));

        // Part II - Optimized for 10,000x repetition
        
        const offset = parseInt(originalInput.substring(0, 7));
        
        const fullMessage = originalInput.repeat(10000);
        const fullLength = fullMessage.length;
        
        if (offset > fullLength / 2) {
            
            let suffix = fullMessage.substring(offset);
            let digits = suffix.split('').map(d => parseInt(d));
                        
            for (let i = 0; i < 100; i++) {
                // For second half: each position is just cumulative sum from right to left
                let sum = 0;
                for (let j = digits.length - 1; j >= 0; j--) {
                    sum = (sum + digits[j]) % 10;
                    digits[j] = sum;
                }
            }
            
            console.log("Part II:", digits.slice(0, 8).join(''));
        } else {
            console.log("NO CLUE");
        }
    }
    return 0;
}

// Run the program
main();