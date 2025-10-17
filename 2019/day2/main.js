const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');
const { Intcode } = require('../intCode');

// Main function
async function main() {
    console.log('AoC 2019 day 2! Reading from input...\n');
    
    const input = await readInput(2019, 2);
    
    if (input !== null) {
        // Input is comma separated integers
        const numbers = parseCommaSeparatedInts(input);
        
        console.log('PartI:', Intcode(numbers.slice(), 12, 2));

        for (let noun = 0; noun <= 99; noun++) {
            for (let verb = 0; verb <= 99; verb++) {
                const result = Intcode(numbers.slice(), noun, verb);
                if (result === 19690720) {
                    console.log('PartII:', 100 * noun + verb);
                    return 0;
                }
            }
        }
        console.log('No solution found for Part II');
    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();