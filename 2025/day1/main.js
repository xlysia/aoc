const { readInput, parseLines } = require('../../js/utils/readInput');

// Main function
async function main() {
    console.log('AoC 2025 day 1! Reading from input...\n');
    
    const input = await readInput(2025, 1);
    
    if (input !== null) {
        // Input is comma separated integers
        const numbers = parseLines(input);
        
        var curr = 50;
        const mod = 100;  // 0-99 range means modulo 100
        // L10 => (curr - 10 + mod) % mod
        // R10 => (curr + 10) % mod
        var partI = 0;
        var partII = 0;
        numbers.forEach(change => {
            if (change.startsWith('L')) {
                const val = parseInt(change.slice(1));
                const next = (curr - val + mod * 1000) % mod;
                // Count times we pass through 0 going backwards
                const crosses = Math.floor(Math.abs(val) / mod);
                partII += crosses + (curr!=0&&(curr - (val%mod))<=0);
                curr = next;
            } else {
                const val = parseInt(change.slice(1));
                const next = (curr + val) % mod;
                // Count times we pass through 0 going forwards
                const crosses = Math.floor(Math.abs(val) / mod);
                partII += crosses + (curr!=0&&(curr + (val%mod))>=mod);
                curr = next;
            }
            partI += curr == 0;

           // console.log(`After change ${change} , cross:${partII}, position: ${curr}`);
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