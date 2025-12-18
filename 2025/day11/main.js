const fs = require('fs');
const path = require('path');
const { readInput, parseLines } = require('../../js/utils/readInput');


// Main function
async function main() {
    console.log('AoC 2025 day 11! Reading from input...\n');
    
    const input = await readInput(2025, 11);
    
    if (input !== null) {
        
        let graph = new Map();
        // Parse input line in format "key: value"
        function parseLine(line){
            const trimmed = line.trim();
            const colonIndex = trimmed.indexOf(':');
            if (colonIndex === -1) {
                return null; // Invalid format
            }
            
            const key = trimmed.substring(0, colonIndex).trim();
            const values = trimmed.substring(colonIndex + 1).split(" ").map(x => x.trim()).filter(x => x.length > 0);
            
            if(!graph.has(key)) {
                graph.set(key, values);
            } else {
                graph.get(key).push(...values);
            }
        }
    
        function explore(key){
            // explore graph to find ALL paths to 'out'
            let res = 0;
            
            function dfs(currentKey) {
                if (currentKey === 'out') {
                    res++;
                    return;
                }
                graph.get(currentKey).forEach(element => {
                    dfs(element);
                });
            }
            
            dfs(key);            
            return res;
        }

        function explore2(key){
            // explore graph to find ALL paths to 'out' that pass through both DAC and FFT
            
            let memo = new Map();

            function dfs(currentKey, bDAC, bFFT) {
                
                // Create a unique memo key that includes the state
                const memoKey = `${currentKey},${bDAC},${bFFT}`;
                if(memo.has(memoKey)) return memo.get(memoKey);

                if (currentKey === 'out') {
                    const result = bDAC && bFFT ? 1 : 0;
                    memo.set(memoKey, result);
                    return result;
                }
                
                if(currentKey === 'dac'){
                    bDAC = true;
                }
                if(currentKey === 'fft'){
                    bFFT = true;
                }
                
                let res = 0;

                graph.get(currentKey).forEach(element => {
                    res += dfs(element, bDAC, bFFT);
                });

                memo.set(memoKey, res);
                return res;
            }
            
                      
            return dfs(key,false,false);
        }

        let lines = parseLines(input);
        
        // Parse each line
        lines.map(line => parseLine(line));
    
        let partI = explore("you");
        console.log(`PartI - Number of path ${partI}`);

        let partII = explore2("svr");
        console.log(`PartII - Number of path passing by DAC & FFT ${partII}`);
    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();