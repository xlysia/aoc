const path = require('path');

const { readInput, parseLines } = require('../../js/utils/readInput');
const { Point3D } = require('../Point');
const { sign } = require('crypto');

// Parse input lines like "<x=-13, y=-13, z=-13>"



class Moon{
    constructor(x, y, z) {
        this.pos = new Point3D(x,y,z);
        this.speed = new Point3D();
        
        // Store true initial state (position AND velocity)
        this.initialx = { pos: x, vel: 0 };
        this.initialy = { pos: y, vel: 0 };
        this.initialz = { pos: z, vel: 0 };
    }

    move(){
        this.pos.move(this.speed);
    }
    
    // Check if this moon is back to initial state for given axis
    isAxisAtInitialState(axis) {
        const initial = this[`initial${axis}`];
        return this.pos[axis] === initial.pos && this.speed[axis] === initial.vel;
    }
}

// GCD and LCM functions
function gcd(a, b) {
    return b === 0 ? a : gcd(b, a % b);
}

function lcm(a, b) {
    return (a * b) / gcd(a, b);
}


function parseMoonPositions(lines) {
    const moons = [];
    
    for (const line of lines) {
        // Use regex to extract x, y, z values
        const match = line.match(/<x=(-?\d+), y=(-?\d+), z=(-?\d+)>/);
        if (match) {
            const x = parseInt(match[1]);
            const y = parseInt(match[2]);
            const z = parseInt(match[3]);
            moons.push(new Moon(x, y, z));
        }
    }
    
    return moons;
}

// Main function
async function main() {
    console.log('AoC 2019 day 12! Reading from input...\n');
   
    const origin = new Point3D();
    const input = await readInput(2019, 12);
   // const input = "<x=-1, y=0, z=2>\n<x=2, y=-10, z=-7>\n<x=4, y=-8, z=8>\n<x=3, y=5, z=-1>"
    if (input !== null) {
        const lines = parseLines(input);
        const moons = parseMoonPositions(lines);
        
        let turn = 0;
        while(turn++ < 1000){
            for(let i = 0; i < moons.length;i++){
                for(let j = i+1; j < moons.length;j++){
                    // Apply gravity
                    const sx = Math.sign(moons[i].pos.x - moons[j].pos.x);
                    const sy = Math.sign(moons[i].pos.y - moons[j].pos.y);
                    const sz = Math.sign(moons[i].pos.z - moons[j].pos.z);

                    moons[i].speed.x -= sx;
                    moons[i].speed.y -= sy;
                    moons[i].speed.z -= sz;

                    moons[j].speed.x += sx;
                    moons[j].speed.y += sy;
                    moons[j].speed.z += sz;         
                }
            }

            for(let moon of moons){
                moon.move();
            }
        }

        // Get Total energy 
        let partI = 0;
        for(let moon of moons){
            const potential = Math.abs(moon.pos.x) + Math.abs(moon.pos.y) + Math.abs(moon.pos.z);
            const kinetic = Math.abs(moon.speed.x) + Math.abs(moon.speed.y) + Math.abs(moon.speed.z);
            partI += potential * kinetic;
        }
        console.log('Part I:', partI);

        // Part II: System-wide axis cycle detection (the correct approach)
        const systemMoons = parseMoonPositions(lines);
        let step = 0;
        let xCycle = null, yCycle = null, zCycle = null;
                
        while(++step && (!xCycle || !yCycle || !zCycle)){
            
            // Apply gravity
            for(let i = 0; i < systemMoons.length; i++) {
                for(let j = i + 1; j < systemMoons.length; j++) {
                    const sx = Math.sign(systemMoons[i].pos.x - systemMoons[j].pos.x);
                    const sy = Math.sign(systemMoons[i].pos.y - systemMoons[j].pos.y);
                    const sz = Math.sign(systemMoons[i].pos.z - systemMoons[j].pos.z);

                    systemMoons[i].speed.x -= sx;
                    systemMoons[i].speed.y -= sy;
                    systemMoons[i].speed.z -= sz;

                    systemMoons[j].speed.x += sx;
                    systemMoons[j].speed.y += sy;
                    systemMoons[j].speed.z += sz;
                }
            }
            
            // Move moons
            for(let moon of systemMoons) {
                moon.move();
            }

            // Check if ALL moons are back to initial state for each axis
            if(!xCycle && systemMoons.every(moon => moon.isAxisAtInitialState('x'))){
                xCycle = step;
            }
            if(!yCycle && systemMoons.every(moon => moon.isAxisAtInitialState('y'))){
                yCycle = step;
            }
            if(!zCycle && systemMoons.every(moon => moon.isAxisAtInitialState('z'))){
                zCycle = step;
            }

        }
        
        const partII = lcm(lcm(xCycle, yCycle), zCycle);
        console.log('Part II:', partII);
 
    }
    return 0;
}

// Run the program
main();