const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');
const { IntcodeComputer } = require('../intCode');

// Main function
async function main() {
    console.log('AoC 2019 day 9! Reading from input...\n');

    const input = await readInput(2019, 9);

    if (input !== null) {
        
        const numbers = parseCommaSeparatedInts(input);
        
        const computer = new IntcodeComputer(numbers.slice());

        computer.setInput([1]);
        computer.enlarge();
        computer.run();
        let partI = computer.getLastOutput();
        console.log('PartI:', partI);

        computer.reset(numbers.slice());
        computer.setInput([2]);
        computer.enlarge();
        computer.run();
        let partII = computer.getLastOutput();
        console.log('PartII:', partII);

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();