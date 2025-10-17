const fs = require('fs');
const path = require('path');
const { readInput } = require('../../js/utils/readInput');



// Main function
async function main() {
    console.log('AoC 2019 day 4! Reading from input...\n');

    const input = await readInput(2019, 4);

    if (input !== null) {
        // Input is 2 int separated by -
        const [min, max] = input.split('-').map(Number);

        let part1 = 0;
        let part2 = 0;

        for (let i = min; i <= max; i++) {
            const digits = String(i).split('').map(Number);
            let hasDouble = false;
            let hasExactDouble = false;
            let neverDecrease = true;

            for (let j = 1; j < digits.length; j++) {
                if (digits[j] === digits[j - 1]) {
                    hasDouble = true;
                    if (digits[j] !== digits[j + 1] && digits[j] !== digits[j - 2]) {
                        hasExactDouble = true;
                    }
                }
                if (digits[j] < digits[j - 1]) {
                    neverDecrease = false;
                    break;
                }
            }

            if (hasDouble && neverDecrease) {
                part1++;
            }
            if (hasExactDouble && neverDecrease) {
                part2++;
            }
        }

        console.log('Part I:', part1);
        console.log('Part II:', part2);
    }
    return 0;
}

// Run the program
main();