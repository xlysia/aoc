const { error } = require('console');
const { readInput, parseLines } = require('../../js/utils/readInput');

async function main() {
    console.log('AoC 2019 day 24! Reading from input...\n');

    const input = await readInput(2019, 24);

    if (input !== null) {
        
        const lines = parseLines(input);
        
        // Parse grid into a single integer bitmap (bit set for bug '#')
        let grid = 0;
        for (let y = 0; y < lines.length; y++) {
            for (let x = 0; x < lines[y].length; x++) {
                const pos = y * lines[0].length + x;
                if (lines[y][x] === '#') {
                    grid |= (1 << pos);
                }
            }
        }
        
        const WIDTH = lines[0].length;  // Usually 5
        const HEIGHT = lines.length;    // Usually 5
        
        console.log(`Grid parsed: ${WIDTH}x${HEIGHT}, bitmap: ${grid.toString(2).padStart(WIDTH * HEIGHT, '0')}`);
        
        // Function to compute neighbor sum value at given position using bitwise operations
        function getNeighborSum(bitmap, pos) {
            const x = pos % WIDTH;
            const y = Math.floor(pos / WIDTH);
            let sum = 0;
            
            // Check up
            if (y > 0) {
                const upPos = (y - 1) * WIDTH + x;
                sum += (bitmap >> upPos) & 1;
            }
            
            // Check down  
            if (y < HEIGHT - 1) {
                const downPos = (y + 1) * WIDTH + x;
                sum += (bitmap >> downPos) & 1;
            }
            
            // Check left
            if (x > 0) {
                const leftPos = y * WIDTH + (x - 1);
                sum += (bitmap >> leftPos) & 1;
            }
            
            // Check right
            if (x < WIDTH - 1) {
                const rightPos = y * WIDTH + (x + 1);
                sum += (bitmap >> rightPos) & 1;
            }
            
            return sum;
        }
        
        // Update function that applies the evolution rules
        function update(grid){
            let newgrid = grid;

            for(let i = 0; i < HEIGHT * WIDTH; i++){
                let sum = getNeighborSum(grid, i);
                let hasBug = (grid >> i) & 1;

                if(hasBug && sum !== 1) {
                    // Bug dies if not exactly 1 neighbor - clear the bit
                    newgrid &= ~(1 << i);
                } else if(!hasBug && (sum === 1 || sum === 2)) {
                    // Empty space becomes infested if 1 or 2 neighbors
                    newgrid |= (1 << i);
                }
                // Otherwise the position stays the same (no action needed)
            }
            
            return newgrid;
        }

        let memo = new Set();
        memo.add(grid);
        while(true){
            grid = update(grid);
            if(memo.has(grid)){
                console.log(`PartI : First grid to repeat ${grid}`);
                break;
            }
            memo.add(grid);
        }

        // Part II: Recursive grids with depth
        console.log("\n--- Part II: Recursive Evolution ---");
        
        // Use Map to store grids at different depths: depth -> bitmap
        let recursiveGrids = new Map();
        recursiveGrids.set(0, parseLines(input).reduce((bitmap, line, y) => {
            for (let x = 0; x < line.length; x++) {
                const pos = y * WIDTH + x;
                if (pos !== 12 && line[x] === '#') { // Skip center cell (position 12)
                    bitmap |= (1 << pos);
                }
            }
            return bitmap;
        }, 0));
        
        // Function to get neighbor count for recursive grids
        function getRecursiveNeighborSum(grids, depth, pos) {
            const x = pos % WIDTH;
            const y = Math.floor(pos / WIDTH);
            let sum = 0;
            
            // Skip center cell (it's the portal to inner level)
            if (pos === 12) return 0;
            
            const currentGrid = grids.get(depth) || 0;
            const outerGrid = grids.get(depth - 1) || 0;
            const innerGrid = grids.get(depth + 1) || 0;
            
            // Check each direction
            const directions = [
                { dx: 0, dy: -1 }, // up
                { dx: 0, dy: 1 },  // down
                { dx: -1, dy: 0 }, // left
                { dx: 1, dy: 0 }   // right
            ];
            
            for (const { dx, dy } of directions) {
                const nx = x + dx;
                const ny = y + dy;
                
                if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
                    const neighborPos = ny * WIDTH + nx;
                    
                    if (neighborPos === 12) {
                        // Looking at center - count appropriate edge of inner level
                        if (dx === 0 && dy === -1) {
                            // Looking up at center - count bottom row of inner grid
                            for (let i = 20; i < 25; i++) sum += (innerGrid >> i) & 1;
                        } else if (dx === 0 && dy === 1) {
                            // Looking down at center - count top row of inner grid  
                            for (let i = 0; i < 5; i++) sum += (innerGrid >> i) & 1;
                        } else if (dx === -1 && dy === 0) {
                            // Looking left at center - count right column of inner grid
                            for (let i = 4; i < 25; i += 5) sum += (innerGrid >> i) & 1;
                        } else if (dx === 1 && dy === 0) {
                            // Looking right at center - count left column of inner grid
                            for (let i = 0; i < 25; i += 5) sum += (innerGrid >> i) & 1;
                        }
                    } else {
                        // Normal neighbor in same level
                        sum += (currentGrid >> neighborPos) & 1;
                    }
                } else {
                    // Outside boundary - look at outer level
                    if (nx < 0) {
                        // Left edge - look at position 11 in outer level
                        sum += (outerGrid >> 11) & 1;
                    } else if (nx >= WIDTH) {
                        // Right edge - look at position 13 in outer level
                        sum += (outerGrid >> 13) & 1;
                    } else if (ny < 0) {
                        // Top edge - look at position 7 in outer level
                        sum += (outerGrid >> 7) & 1;
                    } else if (ny >= HEIGHT) {
                        // Bottom edge - look at position 17 in outer level
                        sum += (outerGrid >> 17) & 1;
                    }
                }
            }
            
            return sum;
        }
        
        // Recursive update function
        function updateRecursive(grids) {
            const newGrids = new Map();
            
            // Find range of depths we need to consider
            const depths = [...grids.keys()];
            const minDepth = Math.min(...depths) - 1;
            const maxDepth = Math.max(...depths) + 1;
            
            for (let depth = minDepth; depth <= maxDepth; depth++) {
                let newGrid = grids.get(depth) || 0;
                
                for (let i = 0; i < HEIGHT * WIDTH; i++) {
                    if (i === 12) continue; // Skip center cell
                    
                    const sum = getRecursiveNeighborSum(grids, depth, i);
                    const hasBug = ((grids.get(depth) || 0) >> i) & 1;
                    
                    if (hasBug && sum !== 1) {
                        // Bug dies if not exactly 1 neighbor
                        newGrid &= ~(1 << i);
                    } else if (!hasBug && (sum === 1 || sum === 2)) {
                        // Empty space becomes infested if 1 or 2 neighbors
                        newGrid |= (1 << i);
                    }
                }
                
                // Only store non-empty grids
                if (newGrid !== 0) {
                    newGrids.set(depth, newGrid);
                }
            }
            
            return newGrids;
        }
        
        // Simulate 200 minutes
        for (let minute = 0; minute < 200; minute++) {
            recursiveGrids = updateRecursive(recursiveGrids);
        }
        
        // Count total bugs
        let totalBugs = 0;
        for (const [depth, bitmap] of recursiveGrids) {
            for (let i = 0; i < 25; i++) {
                if (i !== 12) totalBugs += (bitmap >> i) & 1;
            }
        }
        
        console.log(`Part II: Total bugs after 200 minutes: ${totalBugs}`);

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();