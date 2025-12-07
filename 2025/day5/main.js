const { readInput, parseLines } = require('../../js/utils/readInput');

// Main function

async function main() {
    console.log('AoC 2025 day 5! Reading from input...\n');
    
    const input = await readInput(2025, 5);
    
    if (input !== null) {

        let partI = 0;
        let partII = 0;

        [freshs, ingredients] = input.split('\n\n');

        freshs = parseLines(freshs).map(x => x.split('-').map(num => parseInt(num.trim())));
        ingredients = parseLines(ingredients).map(num => parseInt(num.trim()));


        function simpIntervals( intervals){
            if (intervals.length <= 1) return intervals;
            
            const sorted = intervals.slice().sort((a, b) => a[0] - b[0]);
            const merged = [sorted[0]];
            
            for (let i = 1; i < sorted.length; i++) {
                const current = sorted[i];
                const last = merged[merged.length - 1];
                
                // If current interval overlaps or is adjacent to the last merged interval
                if (current[0] <= last[1] + 1) {
                    last[1] = Math.max(last[1], current[1]);
                } else {
                    merged.push(current);
                }
            }
            
            return merged;
        }

        function isFresh(x){
            return freshs.some( ([min, max]) => x >= min && x <= max);
        }

        freshs = simpIntervals(freshs);

        ingredients.forEach(x => {
            partI += isFresh(x);
        });

        freshs.forEach(([min,max]) => {
            partII += max - min +1;
        });

        console.log(`Part I - Fresh ingredients on table  ${partI}`);
        console.log(`Part II - Fresh ingredients total ${partII}`);

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();