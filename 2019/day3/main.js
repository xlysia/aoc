// Simple Point class for easier coordinate handling
class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
    
    // Manhattan distance to another point
    manhattanDistanceTo(other) {
        return Math.abs(this.x - other.x) + Math.abs(this.y - other.y);
    }
    
    // Euclidean distance to another point
    distanceTo(other) {
        return Math.sqrt((this.x - other.x) ** 2 + (this.y - other.y) ** 2);
    }
    
    // Add another point (vector addition)
    add(other) {
        return new Point(this.x + other.x, this.y + other.y);
    }
    
    // Subtract another point (vector subtraction)
    subtract(other) {
        return new Point(this.x - other.x, this.y - other.y);
    }
    
    // Check if equal to another point
    equals(other) {
        return this.x === other.x && this.y === other.y;
    }
    
    // Clone the point
    clone() {
        return new Point(this.x, this.y);
    }
    
    // String representation
    toString() {
        return `(${this.x}, ${this.y})`;
    }
}

async function readInputFile() {
  try {
    // Fetch from local input.txt file
    const res = await fetch('./input.txt');

    if (!res.ok) {
      throw new Error(`HTTP error! Status: ${res.status}`);
    }

    const text = await res.text();
    return text.trim();
  } catch (error) {
    console.error('Error reading input.txt:', error.message);
    
    // Fallback to sample data if input.txt is not accessible
    console.log('Using fallback sample data...');
    return `R8,U5,L5,D3
U7,R6,D4,L4`;
  }
}

// Main function
async function main() {
    console.log('Hello World! Reading from input.txt...\n');
    
    const input = await readInputFile();

    if (input == null) {
        console.log('No input available');
        return;
    }

    // Process the input. For each lines comma separated instructions 1 direction can be (U, D, L, R) followed by number of steps

    const lines = input.split('\n').map(line => line.trim()).filter(line => line.length > 0);
    console.log(`Read ${lines.length} lines from input:\n`);
    lines.forEach((line, index) => {
        console.log(`Line ${index + 1}: ${line}`);
    });

    // We parse each line into instructions , they will create segments of the path , we want to store each segment as a start and end point and draw them
    const paths = lines.map(line => {
        const instructions = line.split(',').map(instr => instr.trim());
        const segments = [];
        let currentPos = new Point(0, 0);
        
        instructions.forEach(instr => {
            const direction = instr[0];
            const length = parseInt(instr.slice(1), 10);
            let nextPos = currentPos.clone();
            
            switch (direction) {
                case 'U': nextPos.y -= length; break;
                case 'D': nextPos.y += length; break;
                case 'L': nextPos.x -= length; break;
                case 'R': nextPos.x += length; break;
                default: console.error(`Unknown direction: ${direction}`);
            }
            
            segments.push({ 
                start: currentPos.clone(), 
                end: nextPos.clone(),
                length: currentPos.manhattanDistanceTo(nextPos)
            });
            currentPos = nextPos;
        });
        return segments;
    });

    // Function to check if two segments intersect and return the intersection point
    function getIntersection(segA, segB) { // its only vertical or horizontal segments
        const isSegAVertical = segA.start.x === segA.end.x;
        const isSegBVertical = segB.start.x === segB.end.x;
        
        if (isSegAVertical === isSegBVertical) {
            // Parallel lines (both vertical or both horizontal)
            return null;
        }
        
        let vertSeg, horizSeg;
        if (isSegAVertical) {
            vertSeg = segA;
            horizSeg = segB;
        } else {
            vertSeg = segB;
            horizSeg = segA;
        }

        // Check if the vertical segment is within the bounds of the horizontal segment
        const vertX = vertSeg.start.x;
        const horizY = horizSeg.start.y;
        const horizMinX = Math.min(horizSeg.start.x, horizSeg.end.x);
        const horizMaxX = Math.max(horizSeg.start.x, horizSeg.end.x);
        const vertMinY = Math.min(vertSeg.start.y, vertSeg.end.y);
        const vertMaxY = Math.max(vertSeg.start.y, vertSeg.end.y);
        
        if (vertX < horizMinX || vertX > horizMaxX || horizY < vertMinY || horizY > vertMaxY) {
            return null;
        }

        // If we reach here, we have an intersection
        return new Point(vertX, horizY);
    }   

    // Now we have all paths as arrays of segments
    // Draw on the display from index.html canvas id="display" it already exists in the html
    const canvas = document.getElementById('display');
    if (!canvas) {
        console.error('Canvas element with id "display" not found in the HTML.');
        return;
    }
    const ctx = canvas.getContext('2d');
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    
    // Calculate bounds to fit all paths on screen
    let minX = 0, maxX = 0, minY = 0, maxY = 0;
    paths.forEach(path => {
        path.forEach(segment => {
            minX = Math.min(minX, segment.start.x, segment.end.x);
            maxX = Math.max(maxX, segment.start.x, segment.end.x);
            minY = Math.min(minY, segment.start.y, segment.end.y);
            maxY = Math.max(maxY, segment.start.y, segment.end.y);
        });
    });
    
    // Calculate scale to fit the drawing in the canvas with padding
    const padding = 50;
    const scaleX = (canvas.width - 2 * padding) / (maxX - minX || 1);
    const scaleY = (canvas.height - 2 * padding) / (maxY - minY || 1);
    const scale = Math.min(scaleX, scaleY, 1); // Don't scale up, only down
    
    //console.log(`Bounds: (${minX}, ${minY}) to (${maxX}, ${maxY}), Scale: ${scale.toFixed(4)}`);
    
    // Set up transformation
    ctx.save();
    ctx.translate(canvas.width / 2, canvas.height / 2);
    ctx.scale(scale, scale);
    ctx.translate(-(minX + maxX) / 2, -(minY + maxY) / 2);
    
    // Draw origin point
    ctx.fillStyle = 'black';
    ctx.beginPath();
    ctx.arc(0, 0, 3 / scale, 0, 2 * Math.PI);
    ctx.fill();
    
    // Draw each path with different colors
    const colors = ['#ff4444', '#4444ff']; // Red and Blue for the two wires
    ctx.lineWidth = 2 / scale;
    
    for (let i = 0; i < paths.length; i++) {
        ctx.strokeStyle = colors[i % colors.length];
        ctx.beginPath();
        let isFirst = true;
        paths[i].forEach(segment => {
            if (isFirst) {
                ctx.moveTo(segment.start.x, segment.start.y);
                isFirst = false;
            }
            ctx.lineTo(segment.end.x, segment.end.y);
        });
        ctx.stroke();
    }
    


    // Look for intersections between paths and draw crosses
    const pathA = paths[0];
    const pathB = paths[1];
    const origin = new Point(0, 0);

    let partI = Infinity;
    let partII = Infinity;
    let L1 = 0;

    ctx.strokeStyle = 'red';
    ctx.lineWidth = 3 / scale;
    const crossSize = 8 / scale;

    // Check each segment of pathA against each segment of pathB
    pathA.forEach(segA => {
        let L2 = 0;
        pathB.forEach(segB => {
            const intersection = getIntersection(segA, segB);
            if (intersection && !intersection.equals(origin)) { // Skip origin
                const distance = intersection.manhattanDistanceTo(origin);
                
                // Draw cross at intersection
                ctx.beginPath();
                ctx.moveTo(intersection.x - crossSize, intersection.y - crossSize);
                ctx.lineTo(intersection.x + crossSize, intersection.y + crossSize);
                ctx.moveTo(intersection.x - crossSize, intersection.y + crossSize);
                ctx.lineTo(intersection.x + crossSize, intersection.y - crossSize);
                ctx.stroke();
                
                partI = Math.min(partI, distance);
                
                // Calculate steps to intersection for part II
                const stepsOnA = segA.start.manhattanDistanceTo(intersection);
                const stepsOnB = segB.start.manhattanDistanceTo(intersection);
                partII = Math.min(partII, L1 + L2 + stepsOnA + stepsOnB);
            }
            L2 += segB.length;
        });
        L1 += segA.length;
    });


    ctx.restore();

    console.log({ partI, partII });

    return 0;
}

// Run the program
main();