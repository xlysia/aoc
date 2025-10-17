const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');

function Intcode(program, noun, verb) {
    program[1] = noun;
    program[2] = verb;

    // for every 4number
    for (let i = 0; i < program.length; i += 4) {
        var opcode = program[i];
        var a = program[i + 1];
        var b = program[i + 2];
        var s = program[i + 3];

        switch (opcode) {
            case 1:
                program[s] = program[a] + program[b];
                break;
            case 2:
                program[s] = program[a] * program[b];
                break;
            case 99:
                return program[0];
            default:
                console.error('Unknown opcode:', opcode);
        }
    }
}

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