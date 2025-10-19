const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');
const { IntcodeComputer } = require('../intCode');

// Main function
async function main() {
    console.log('AoC 2019 day 5! Reading from input...\n');

    //const input ="1002,4,3,4,33";
    const input = await readInput(2019, 5);

    if (input !== null) {
        // Input is comma separated integers
        
        const numbers = parseCommaSeparatedInts(input);
        
        console.log('PartI:');
        const computer1 = new IntcodeComputer(numbers.slice());
        computer1.setInput([1]);
        computer1.run();

        console.log('\nPartII:');
        computer1.reset(numbers.slice());
        computer1.setInput([5]);
        computer1.run();
    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();