const fs = require('fs');
const path = require('path');
const { readInput, parseLines } = require('../../js/utils/readInput');

function parseInput(lines) {
    const presents = new Map();
    const tasks = [];
    let i = 0;
    
    // Parse presents
    while (i < lines.length) {
        const line = lines[i].trim();
        
        // Check if this is a present ID line (ends with :)
        if (line.includes(':') && !line.includes('x')) {
            const id = parseInt(line.replace(':', ''));
            
            // Read the 3x3 shape
            const shape = [];
            for (let row = 0; row < 3; row++) {
                i++;
                if (i < lines.length) {
                    shape.push(lines[i].trim());
                }
            }
            
            // Calculate shape mask and area
            const shapeMask = [];
            let area = 0;
            
            for (let row = 0; row < 3; row++) {
                const maskRow = [];
                for (let col = 0; col < 3; col++) {
                    const isPresent = shape[row] && shape[row][col] === '#';
                    maskRow.push(isPresent);
                    if (isPresent) area++;
                }
                shapeMask.push(maskRow);
            }
            
            presents.set(id, {
                id: id,
                shape: shape,
                shapeMask: shapeMask,
                area: area
            });
        } 
        // Check if this is a task line (WxH format)
        else if (line.includes('x') && line.includes(':')) {
            const [dimensions, numbersStr] = line.split(':');
            const [width, height] = dimensions.trim().split('x').map(n => parseInt(n));
            const presentCounts = numbersStr.trim().split(' ').map(n => parseInt(n));
            
            tasks.push({
                width: width,
                height: height,
                presentCounts: presentCounts
            });
        }
        
        i++;
    }
    
    return { presents, tasks };
}

// Main function
async function main() {
    console.log('AoC 2025 day 12! Reading from input...\n');
    
    const input = await readInput(2025, 12);
    
    if (input !== null) {

        let lines = parseLines(input);
        
        // Parse the input
        const { presents, tasks } = parseInput(lines);
        
        let partI = 0;
        tasks.forEach((task, index) => {
            let sum = 0;
            for(let i = 0; i < presents.size;i++){
                sum += task.presentCounts[i]*presents.get(i).area;
            }
            partI += task.height*task.width > sum;
        });
    

        console.log(`PartI - Can fit all the presents under ${partI} trees`);

        // Ok looks like just checking if it could fit in size is enough lol

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();