const { readInput, parseGrid } = require('../../js/utils/readInput');
const { Point } = require('../Point');
const fs = require('fs');

const dirs = [
    new Point(0, -1), // up
    new Point(1, 0),  // right
    new Point(0, 1),  // down
    new Point(-1, 0)  // left
];

function isDoor(char) {
    return char >= 'A' && char <= 'Z';
}

function isWall(char) {
    return char === '#' || isEmpty(char);
}

function isOpen(char) {
    return char === '.';
}

function isEmpty(char){
    return char === ' ';
}

class Portal{
    constructor(label,A,B){
        this.label = label;
        this.A = A;
        this.B = B;
    }

    goThrough(pos){
        if(A.equals(pos))pos.move(B);
        else pos.move(A);
    }
};

function isVerticalPortal(map,i,j){
    return isDoor(map[i+1]?.[j]);
}

function isHorizontalPortal(map,i,j){
    return isDoor(map[i]?.[j+1]);
}

function findPortals(map){

    const portals = new Map();

    const WIDTH = map[0].length;
    const HEIGHT = map.length;

    for(i = 0; i < HEIGHT; i++){
        for(j = 0; j < WIDTH; j++){
            const c = map[i][j];
            if(isWall(c) || isOpen(c))continue;
            
            if(!isDoor(c))continue;
            
            // Find portal

            if(isVerticalPortal(map,i,j)){
                const label = map[i][j] + map[i+1][j];
                if(!portals.has(label))portals.set(label,new Portal(label,null,null));
                const p = portals.get(label);

                const pos = isOpen(map[i+2]?.[j])?new Point(j,i+2):new Point(j,i-1);
                if(!p.A)p.A = pos;
                else p.B = pos;
            }
            else if(isHorizontalPortal(map,i,j)){
                const label = map[i][j] + map[i][j+1];

                if(!portals.has(label))portals.set(label,new Portal(label,null,null));
                const p = portals.get(label);

                const pos = isOpen(map[i]?.[j+2])?new Point(j+2,i):new Point(j-1,i);
                if(!p.A)p.A = pos;
                else p.B = pos;
            }
            
        }
    }

    return portals;
}

// Main function
async function main() {
    console.log('AoC 2019 day 20! Reading from input...\n');
    
    const input = await readInput(2019, 20);
    
    if (input !== null) {
        const map = parseGrid(input);

        const portals = findPortals(map);
        console.log("Found ", portals.size ,"portals");
    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();