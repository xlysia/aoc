const { readInput, parseLines } = require('../../js/utils/readInput');
const { Point } = require('../Point');


function getAngle(from, to) {
    const dx = to.x - from.x;
    const dy = to.y - from.y;
    
    // atan2 returns angle in radians (-π to π)
    let angle = Math.atan2(dx, -dy); // Note: swapped and negated dy for "up" start
    
    // Convert to 0-2π range (0 to 360 degrees)
    if (angle < 0) {
        angle += 2 * Math.PI;
    }
    
    return angle;
}

// Main function
async function main() {
    console.log('AoC 2019 day 10! Reading from input...\n');
    
    const input = await readInput(2019, 10);
    
    if (input !== null) {

        const lines = parseLines(input);
        // Asteroid map
        const asteroids = [];
        lines.forEach((line, y) => {
            [...line].forEach((char, x) => {
                if (char === '#') {
                    asteroids.push(new Point(x, y));
                }
            });
        });
        let partI = 0;
        let station = new Point(0,0);
        let dirs;
        for(let A of asteroids){
            const directions = new Map();

            for(let B of asteroids){
                if(B === A)continue;
                const angle = getAngle(A,B);
                if(directions.has(angle)){
                    let p = directions.get(angle);
                    if(A.distanceTo(p) < A.distanceTo(B))continue;
                    directions.set(angle,B);
                }else{
                    directions.set(angle,B);
                }
            }

            if(partI < directions.size){
                partI = directions.size;
                station = A;
                dirs = directions;
            }
            
        }

        console.log('PartI:',partI);

        // Get all asteroids visible from station, sorted by angle
        const visibleAsteroids = Array.from(dirs.entries())
            .sort((a, b) => a[0] - b[0]); // Sort by angle
        
        console.log('Part II',visibleAsteroids[199][1].x*100 + visibleAsteroids[199][1].y );
    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();