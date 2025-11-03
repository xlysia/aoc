const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');
const { Point } = require('../Point');
const {IntcodeComputer} = require('../intCode');
const { createCanvas } = require('canvas');
const fs = require('fs');

const dirs = [
    new Point(0, -1), // up
    new Point(1, 0),  // right
    new Point(0, 1),  // down
    new Point(-1, 0)  // left
];

function setCurrentPanelColor(ctx,x,y,color){
    ctx.fillStyle = color;
    ctx.fillRect(x, y, 1, 1);
}

// Main function
async function main() {
    console.log('AoC 2019 day 19! Reading from input...\n');
    
    const input = await readInput(2019, 19);
    
    if (input !== null) {
        const numbers = parseCommaSeparatedInts(input);

        const WIDTH = 50;
        const HEIGHT = 50;

        const canvas = createCanvas(WIDTH, HEIGHT);
        const ctx = canvas.getContext('2d');
        ctx.fillStyle = 'rgba(0, 0, 0, 0)';
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        
        let partI = 0;

        function isInBeam(x, y) {
            const computer = new IntcodeComputer(numbers.slice());
            computer.enlarge();
            computer.setInput([x, y]);
            computer.run();
            return computer.getLastOutput() === 1;
        }


        for(let j = 0; j < HEIGHT;j++){
            for(let i = 0; i < WIDTH; i++){
                if(!isInBeam(i,j)) continue;
                setCurrentPanelColor(ctx,i,j, 'rgba(255,255,255,255)');
                partI++;
            }
        }

        // Save Part I image and wait for completion
        const out = fs.createWriteStream('partI.png');
        const stream = canvas.createPNGStream();
        stream.pipe(out);

        console.log("PartI - Beam impact on 50x50 grid :", partI);

        // Analyze Part I data to estimate beam angles
        let leftSlope = 0, rightSlope = 0;
        let leftSamples = [], rightSamples = [];
        
        for (let y = 10; y < HEIGHT; y++) {
            let leftEdge = -1, rightEdge = -1;
            
            for (let x = 0; x < WIDTH; x++) {
                if (isInBeam(x, y)) {
                    if (leftEdge === -1) leftEdge = x;
                    rightEdge = x;
                }
            }
            
            if (leftEdge !== -1) {
                leftSamples.push({ x: leftEdge, y: y });
                rightSamples.push({ x: rightEdge, y: y });
            }
        }
        
        // Calculate slopes using linear regression
        if (leftSamples.length > 1) {
            leftSlope = leftSamples[leftSamples.length - 1].x / leftSamples[leftSamples.length - 1].y;
            rightSlope = rightSamples[rightSamples.length - 1].x / rightSamples[rightSamples.length - 1].y;
        }
        
      //  console.log(`Estimated beam angles - Left slope: ${leftSlope.toFixed(4)}, Right slope: ${rightSlope.toFixed(4)}`);

        // Part II: Find 100x100 square that fits in beam
        
        function findBeamEdges(y) {
            
            // Estimate beam position using calculated slopes
            const estimatedLeft = Math.floor(leftSlope * y);
            const estimatedRight = Math.floor(rightSlope * y);
            

            const midInBeam = Math.floor((estimatedLeft + estimatedRight)/2);

            // Find left edge using binary search
            let left = Math.floor(estimatedLeft/2), right = midInBeam;
            while(left != right){
                const mid = Math.floor((left + right) / 2);
                if (isInBeam(mid, y)) {
                    right = mid; // Found beam, search left half
                } else {
                    left = mid + 1; // No beam, search right half
                }
            }
            const actualLeftEdge = left;
            
            // Find right edge using binary search
            left = midInBeam;
            right = estimatedRight * 2; 
            while(left != right){
                const mid = Math.floor((left + right + 1) / 2);
                if (isInBeam(mid, y)) {
                    left = mid; // Found beam, search right half
                } else {
                    right = mid - 1; // No beam, search left half
                }
            }
            const actualRightEdge = left;

            return { 
                left: actualLeftEdge, 
                right: actualRightEdge, 
                width: actualRightEdge - actualLeftEdge + 1 
            };
        }
        
        // Binary search for first Y where 100x100 square fits
        function canFitSquare(y) {
            const edges = findBeamEdges(y);
            if (edges.width < 100) return false;
            
            // Check if 100x100 square fits (top-left at edges.left, y-99)
            const topY = y - 99;
            const topLeftX = edges.left;
            const topRightX = edges.left + 99;
            
            // Verify the top-right corner is in beam
            return isInBeam(topRightX, topY);
        }
        
        let left = 99;
        let right = 2000;
        
        while (left < right) {
            const mid = Math.floor((left + right) / 2);
            if (canFitSquare(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        const finalY = left;
        const edges = findBeamEdges(finalY);
        const topY = finalY - 99;
        const topLeftX = edges.left;
        const result = topLeftX * 10000 + topY;
        
        console.log("Part II - Finding 100x100 square:", result);

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();