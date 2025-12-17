const fs = require('fs');
const path = require('path');

// Simple utility functions to replace the missing utils
async function readInput(year, day) {
    try {
        const inputPath = path.join(__dirname, 'input.txt');
        if (fs.existsSync(inputPath)) {
            return fs.readFileSync(inputPath, 'utf8');
        }
        return null;
    } catch (err) {
        console.error('Error reading input:', err);
        return null;
    }
}

function parseLines(input) {
    return input.split('\n').filter(line => line.trim().length > 0);
}

// Parse pattern from [.##.] format to integer bitmap
function parsePattern(patternStr) {
    const match = patternStr.match(/\[([.#]+)\]/);
    if (!match) return null;
    
    const bits = match[1].split('').map(char => char === '#' ? 1 : 0);
    // Convert bit array to integer (leftmost bit is MSB)
    let bitmap = 0;
    for (let i = 0; i < bits.length; i++) {
        bitmap |= (bits[i] << (bits.length - 1 - i));
    }
    
    return bitmap;
}

// Parse buttons from (a,b) (c) format
function parseButtons(buttonsStr) {
    const buttonMatches = buttonsStr.match(/\(([^)]+)\)/g);
    if (!buttonMatches) return [];
    
    return buttonMatches.map(match => {
        const numbers = match.slice(1, -1).split(',').map(n => parseInt(n.trim()));
        return numbers;
    });
}

// Parse results from {a,b,c,d} format
function parseResults(resultsStr) {
    const match = resultsStr.match(/\{([^}]+)\}/);
    if (!match) return [];
    
    return match[1].split(',').map(n => parseInt(n.trim()));
}

// Convert button indices to bitmask for flipping
function buttonsToBitmask(buttonIndices, patternLength) {
    let mask = 0;
    for (const index of buttonIndices) {
        if (index < patternLength) {
            mask |= (1 << (patternLength - 1 - index));
        }
    }
    return mask;
}

// Find minimum button presses using BFS/DP
function findMinButtonPresses(targetPattern, buttons, patternLength) {
    const maxState = (1 << patternLength) - 1;
    const visited = new Array(maxState + 1).fill(false);
    const distance = new Array(maxState + 1).fill(Infinity);
    
    // Convert button arrays to bitmasks
    const buttonMasks = buttons.map(btn => buttonsToBitmask(btn, patternLength));
    
    // BFS starting from state 0
    const queue = [0];
    visited[0] = true;
    distance[0] = 0;
    
    while (queue.length > 0) {
        const currentState = queue.shift();
        
        // If we reached target, we found minimum path
        if (currentState === targetPattern) {
            return distance[currentState];
        }
        
        // Try each button
        for (const buttonMask of buttonMasks) {
            const nextState = currentState ^ buttonMask;
            
            if (!visited[nextState]) {
                visited[nextState] = true;
                distance[nextState] = distance[currentState] + 1;
                queue.push(nextState);
            }
        }
    }
    
    return -1; // Target unreachable
}

function findMinButtonPressesJoltage(targetPattern, buttons, patternLength) {
    // BFS implementation
    const target = targetPattern;
    
    // Pre-compute all button combinations grouped by parity pattern
    const buttonCombos = [];
    const n = buttons.length;
    for (let mask = 0; mask < (1 << n); mask++) {
        const combo = [];
        for (let i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                combo.push(buttons[i]);
            }
        }
        buttonCombos.push(combo);
    }
    
    // Group combos by their parity pattern
    const patternGroups = new Map();
    for (const combo of buttonCombos) {
        const joltage = new Array(target.length).fill(0);
        for (const button of combo) {
            for (const index of button) {
                if (index < joltage.length) joltage[index]++;
            }
        }
        const pattern = joltage.map(j => j % 2).join(',');
        if (!patternGroups.has(pattern)) patternGroups.set(pattern, []);
        patternGroups.get(pattern).push({combo, joltage});
    }
    
    // BFS with memoization to match recursive approach
    const memo = new Map();
    const queue = [target];
    
    while (queue.length > 0) {
        const state = queue.shift();
        const stateKey = state.join(',');
        
        // Skip if already computed
        if (memo.has(stateKey)) continue;
        
        // Base case: all zeros
        if (state.every(j => j === 0)) {
            memo.set(stateKey, 0);
            continue;
        }
        
        // Invalid case: negative values  
        if (state.some(j => j < 0)) {
            const result = state.reduce((sum, j) => sum + Math.abs(j), 0);
            memo.set(stateKey, result);
            continue;
        }
        
        // Find pattern and check if we have matching button combinations
        const pattern = state.map(j => j % 2).join(',');
        if (!patternGroups.has(pattern)) {
            const result = state.reduce((sum, j) => sum + j, 0);
            memo.set(stateKey, result);
            continue;
        }
        
        // Check if all dependencies are computed
        let allDepsReady = true;
        const nextStates = [];
        
        for (const {combo, joltage} of patternGroups.get(pattern)) {
            const newState = state.map((j, i) => Math.floor((j - joltage[i]) / 2));
            const newStateKey = newState.join(',');
            nextStates.push({newState, newStateKey, combo});
            
            if (!memo.has(newStateKey)) {
                allDepsReady = false;
                // Add dependency to queue if not already there
                if (!queue.some(s => s.join(',') === newStateKey)) {
                    queue.push(newState);
                }
            }
        }
        
        if (allDepsReady) {
            // Compute minimum cost using memoized results
            let minCost = Infinity;
            for (const {newStateKey, combo} of nextStates) {
                const currentCost = combo.length + 2 * memo.get(newStateKey);
                minCost = Math.min(minCost, currentCost);
            }
            memo.set(stateKey, minCost);
        } else {
            // Re-add to queue to compute later
            queue.push(state);
        }
    }
    
    const targetKey = target.join(',');
    return memo.has(targetKey) ? memo.get(targetKey) : -1;
}

// Parse a complete line
function parseLine(line) {
    const trimmed = line.trim();
    
    // Extract pattern [.##.]
    const patternMatch = trimmed.match(/\[([.#]+)\]/);
    const pattern = patternMatch ? parsePattern(patternMatch[0]) : null;
    const originalPattern = patternMatch ? patternMatch[1] : '';
    
    // Extract buttons (a,b) (c,d) etc.
    const buttonsSection = trimmed.substring(
        trimmed.indexOf(']') + 1,
        trimmed.indexOf('{')
    ).trim();
    const buttons = parseButtons(buttonsSection);
    
    // Extract results {a,b,c,d}
    const resultsMatch = trimmed.match(/\{([^}]+)\}/);
    const joltage = resultsMatch ? parseResults(resultsMatch[0]) : [];
    
    return {
        pattern,
        originalPattern,
        buttons,
        joltage
    };
}

// Solve a single machine
function solveMachine(machineData) {
    const pattern = machineData.pattern;
    const buttons = machineData.buttons;
    const patternLength = machineData.originalPattern.length;
    const joltage = machineData.joltage;
    
    const minPresses = findMinButtonPresses(pattern, buttons, patternLength);
    const minPressesJoltageBFS = findMinButtonPressesJoltage(joltage, buttons, patternLength);
    
    // console.log(`Pattern: ${machineData.originalPattern}`);
    // console.log(`  Bitmap: ${minPresses}`);
    // console.log(`  Joltage: ${minPressesJoltageBFS}`);
    
    return {
        pattern: pattern,
        originalPattern: machineData.originalPattern,
        minPresses: minPresses,
        minPressesJoltage: minPressesJoltageBFS,
        buttons: buttons,
        joltage: machineData.joltage
    };
}

// Main function
async function main() {
    console.log('AoC 2025 day 10! Reading from input...\n');
    
    const input = await readInput(2025, 10);
    
    if (input !== null) {
        let lines = parseLines(input);
        
        // Parse each line
        const parsedData = lines.map(line => parseLine(line));
        
        // Solve each machine
        const solutions = parsedData.map(data => solveMachine(data));
        
        const partI = solutions.reduce((sum, sol) => sum + (sol.minPresses >= 0 ? sol.minPresses : 0), 0);
        console.log(`\nPartI - Total minimum button presses: ${partI}`);
        const partII_BFS = solutions.reduce((sum, sol) => sum + (sol.minPressesJoltage >= 0 ? sol.minPressesJoltage : 0), 0);
        console.log(`PartII - Total minimum button presses for Joltage: ${partII_BFS}`);

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();