const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');
const { IntcodeComputer } = require('../intCode');

// Simple permutation function
function getPermutations(array) {
    if (array.length === 0) return [[]];
    
    const result = [];
    for (let i = 0; i < array.length; i++) {
        const rest = [...array.slice(0, i), ...array.slice(i + 1)];
        const restPermutations = getPermutations(rest);
        for (const perm of restPermutations) {
            result.push([array[i], ...perm]);
        }
    }
    return result;
}

// Main function
async function main() {
    console.log('AoC 2019 day 7! Reading from input...\n');

    const input = await readInput(2019, 7);

    if (input !== null) {
        
        const numbers = parseCommaSeparatedInts(input);
        
        const computer1 = new IntcodeComputer(numbers.slice());

        let partI = 0;
        // Try all phase settings 0-4
        const phaseSettings = [0, 1, 2, 3, 4];
        const permutations = getPermutations(phaseSettings);
        for (const phases of permutations) {
            let inputSignal = 0;
            for (let i = 0; i < 5; i++) {
                computer1.reset(numbers.slice());
                computer1.setInput([phases[i], inputSignal]);
                computer1.run();
                inputSignal = computer1.getLastOutput();
            }
            if (inputSignal > partI) {
                partI = inputSignal;
            }
        }
        console.log('PartI:', partI);

        // Part II

       // const test = parseCommaSeparatedInts("3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5");
        const feedbackLoop = (phases, program) => {
            // Initialize 5 computers with the program
            const computers = phases.map(() => new IntcodeComputer(program));
            
            // Give each computer its phase setting (only once!)
            for (let i = 0; i < 5; i++) {
                computers[i].setInput([phases[i]]);
                computers[i].run(); // Run until it needs more input
            }
            
            let inputSignal = 0; // Initial signal to amp A
            let lastOutput = 0;
            let allHalted = false;
            
            while (!allHalted) {
                for (let i = 0; i < 5; i++) {
                    if (!computers[i].halted) {
                        // Add the signal to the computer's input
                        computers[i].input.push(inputSignal);
                        computers[i].waitingForInput = false;
                        
                        // Run until it produces output or halts
                        computers[i].run();
                        
                        // Get the output (should be the last output)
                        inputSignal = computers[i].getLastOutput();
                        
                        if (i === 4) { // Amp E's output
                            lastOutput = inputSignal;
                        }
                    }
                }
                
                // Check if all computers are halted
                allHalted = computers.every(comp => comp.halted);
            }
            return lastOutput;
        };
        let partII = 0;
        const phaseSettingsII = [5, 6, 7, 8, 9];
        const permutationsII = getPermutations(phaseSettingsII);
        for (const phases of permutationsII) {
            const output = feedbackLoop(phases, numbers);
            if (output > partII) {
                partII = output;
            }
        }
        console.log('PartII:', partII);

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();