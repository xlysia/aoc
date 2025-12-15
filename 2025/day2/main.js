const { readInput } = require('../../js/utils/readInput');

// Main function

function isValidID(id){
    // return false if  id is made only of some sequence of digits repeated twice
    const idStr = id.toString();
    const len = idStr.length;
    if(len % 2 !== 0) return true;
    const half = len / 2;
    const firstHalf = idStr.slice(0, half);
    const secondHalf = idStr.slice(half);
    return firstHalf !== secondHalf;
}

function isValidID2(id){
    const idStr = id.toString();
    const len = idStr.length;

    // Find all divisors efficiently
    const divisors = [];
    for(let i = 1; i * i <= len; i++){
        if(len % i === 0){
            divisors.push(i);
            if(i !== len / i && i !== len){
                divisors.push(len / i);
            }
        }
    }
    divisors.sort((a, b) => a - b);

    // Check divisors for repeated sequences
    let maxSeq = 1;
    for(const seqLen of divisors){
        if(seqLen === len) break; // Skip full length
        const seq = idStr.slice(0, seqLen);
        let repeated = true;
        for(let start = seqLen; start < len; start += seqLen){
            if(idStr.slice(start, start + seqLen) !== seq){
                repeated = false;
                break;
            }
        }
        if(repeated){
            return false;
        }
    }
    return true;
}

async function main() {
    console.log('AoC 2025 day 2! Reading from input...\n');
    
    const input = await readInput(2025, 2);
    
    if (input !== null) {
        // input format : int_min-int_max separated by ,
        const ranges = input.split(',').map(rangeStr => {
            const [minStr, maxStr] = rangeStr.split('-');
            return { min: parseInt(minStr), max: parseInt(maxStr) };
        });
        
        let partI = 0n;
        let partII = 0n;
        
        ranges.forEach(({min, max}) => {
            for(let id = min; id <= max; id++){
                if(!isValidID(id)){
                    partI += BigInt(id);
                }
                if(!isValidID2(id)){
                    partII += BigInt(id);
                }
            }
        })

        console.log('PartI:', partI.toString());
        console.log('PartII:', partII.toString());


    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();