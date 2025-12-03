const { readInput, parseLines } = require('../../js/utils/readInput');

// Main function

function findBiggestInt(line,n){
    // Stack-based approach to maintain order and maximize value
    let stack = [];
    let toRemove = line.length - n;  // How many digits we need to remove
    
    for(let i = 0; i < line.length; i++) {
        // Remove digits from stack if current digit is larger and we can still remove more
        while(stack.length > 0 && stack[stack.length - 1] < line[i] && toRemove > 0) {
            stack.pop();
            toRemove--;
        }
        stack.push(line[i]);
    }
    
    // If we still need to remove digits, remove from the end
    while(toRemove > 0) {
        stack.pop();
        toRemove--;
    }
    
    return BigInt(stack.slice(0, n).join(''));
}

async function main() {
    console.log('AoC 2025 day 3! Reading from input...\n');
    
    const input = await readInput(2025, 3);
    
    if (input !== null) {
        const lines = parseLines(input);
    
        let partI = 0n;
        let partII = 0n;
        
        lines.forEach((line, index) => {
            const result = findBiggestInt(line,2);
            partI += result;
            partII += findBiggestInt(line,12);
        });


        
        console.log('PartI:', partI);
        console.log('PartII:', partII);
        
    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();