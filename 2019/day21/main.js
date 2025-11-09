const { error } = require('console');
const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');
const { IntcodeComputer } = require('../intCode');

// Main function
async function main() {
    console.log('AoC 2019 day 21! Reading from input...\n');

    const input = await readInput(2019, 21);

    if (input !== null) {
        
        const numbers = parseCommaSeparatedInts(input);
        
        const computer = new IntcodeComputer(numbers.slice());
        computer.enlarge();

        let partI = 0;

        computer.run();
        if(computer.waitingForInput){
            let output = computer.getAllOutputs();
            console.log(output.map(x => String.fromCharCode(x)).join(''));

            let prog =
            [
                'NOT A J',
                'NOT B T',
                'OR T J',
                'NOT C T',
                'OR T J',
                'AND D J',
                'WALK'
            ];      
            
            // Convert program to ASCII codes and add newline at the end
            const programString = prog.join('\n') + '\n';
            const asciiCodes = programString.split('').map(char => char.charCodeAt(0));
            computer.setInput(asciiCodes);
        }

        computer.run();
        
        // Get final output
        let finalOutput = computer.getAllOutputs();
        console.log("Final output:", finalOutput);
        
        // Check if we got a number (success) or ASCII (failure)
        let lastOutput = finalOutput[finalOutput.length - 1];
        if (lastOutput > 127) {
            partI = lastOutput;
        } else {
            console.log("Failed:");
            console.log(finalOutput.map(x => String.fromCharCode(x)).join(''));
        }
        console.log("PartI - Hull damage reported", partI);

        computer.reset(numbers.slice());
        computer.enlarge();
        
        computer.run();
        if(computer.waitingForInput){
            let output = computer.getAllOutputs();
            console.log(output.map(x => String.fromCharCode(x)).join(''));

            let prog =
            [
                'NOT A J',
                'NOT B T',
                'OR T J',
                'NOT C T',
                'OR T J',
                'AND D J',
                'NOT E T',
                'NOT T T',
                'OR H T',
                'AND T J',
                'RUN'
            ];  // Likebefore but also check if we don't jump too early
            
            // Convert program to ASCII codes and add newline at the end
            const programString = prog.join('\n') + '\n';
            const asciiCodes = programString.split('').map(char => char.charCodeAt(0));
            computer.setInput(asciiCodes);
        }

        computer.run();
        let partII = 0;
        finalOutput = computer.getAllOutputs();
        console.log("Final output:", finalOutput);
        // Check if we got a number (success) or ASCII (failure)
        lastOutput = finalOutput[finalOutput.length - 1];
        if (lastOutput > 127) {
            partII = lastOutput;
        } else {
            console.log("Failed:");
            console.log(finalOutput.map(x => String.fromCharCode(x)).join(''));
        }

        console.log("PartII - Hull damage reported", partII);



    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();