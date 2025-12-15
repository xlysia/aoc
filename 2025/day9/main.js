const { start } = require('repl');
const { readInput, parseLines, parseCommaSeparatedInts } = require('../../js/utils/readInput');

// Main function



async function main() {
    console.log('AoC 2025 day 9! Reading from input...\n');
    
    const input = await readInput(2025, 9);
    
    if (input !== null) {
        let lines = parseLines(input);
        let sits = lines.map(x => {
            let [x_val, y_val] = parseCommaSeparatedInts(x);
            return { x: x_val, y: y_val };
        });

        function Area( A, B) {
            return (Math.abs(B.x-A.x)+1) * (Math.abs(B.y-A.y)+1);
        }

        let n = sits.length;
        
        let partI = 0;
        for (let i = 0; i < n; i++) {
            for (let j = i + 1; j < n; j++) {
                let area = Area(sits[i], sits[j]);
                if (area > partI) {
                    partI = area;
                }
            }
        }


        console.log(`Part I - Biggest Area ${partI}`);
        
        // Part II: Create perimeter segments by connecting consecutive tiles
        const perimeter = [];
        for (let i = 0; i < n; i++) {
            const tileA = sits[i];
            const tileB = sits[(i + 1) % n]; // wrap around
            
            const segment = {
                top: Math.min(tileA.y, tileB.y),
                bottom: Math.max(tileA.y, tileB.y),
                left: Math.min(tileA.x, tileB.x),
                right: Math.max(tileA.x, tileB.x)
            };
            perimeter.push(segment);
        }
        
        function rectangleHasIntruder(top, left, bottom, right) {
            // Check if any perimeter segment intersects the rectangle interior
            for (const segment of perimeter) {
                if (segment.top >= bottom) continue;
                if (segment.bottom <= top) continue;
                if (segment.left >= right) continue;
                if (segment.right <= left) continue;
                return true;
            }
            return false;
        }

        let partII = 0;
        
        // Find the biggest area without perimeter intrusion
        for (let i = 0; i < n; i++) {
            for (let j = i + 1; j < n; j++) {
                const tileA = sits[i];
                const tileB = sits[j];
                
                const top = Math.min(tileA.y, tileB.y);
                const bottom = Math.max(tileA.y, tileB.y);
                const left = Math.min(tileA.x, tileB.x);
                const right = Math.max(tileA.x, tileB.x);
                
                const area = Area(tileA, tileB);
                
                if (area <= partII) continue;
                
                if (rectangleHasIntruder(top, left, bottom, right)) continue;
                
                partII = area;
            }
        }

        console.log(`Part II - Biggest Area within Perimeter ${partII}`);

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();