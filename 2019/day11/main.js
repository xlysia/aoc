const { patch } = require('simple-get');
const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');
const { IntcodeComputer } = require('../intCode');
const { Point } = require('../Point');
const { createCanvas } = require('canvas');
const fs = require('fs');

function getCurrentPanelColor(ctx, pos) {
    const pixel = ctx.getImageData(pos.x, pos.y, 1, 1).data;
    
    // Check if white panel (1) or black panel (0)
    if (pixel[0] === 255 && pixel[1] === 255 && pixel[2] === 255 ) {
        return 1; // White panel
    } else if (pixel[3] === 0){
        return 2;
    } else return 0;
}

function setCurrentPanelColor(ctx,pos,color){
    ctx.fillStyle = color === 1 ? 'white' : 'black';
    ctx.fillRect(pos.x, pos.y, 1, 1);
}

// Main function
async function main() {
    console.log('AoC 2019 day 11! Reading from input...\n');

    const input = await readInput(2019, 11);

    const dirs = [new Point(0,-1), new Point(1,0),new Point(0,1), new Point(-1,0)];
    let didx = 0;

    if (input !== null) {
        // Input is comma separated integers
        const numbers = parseCommaSeparatedInts(input);
        const computer = new IntcodeComputer(numbers.slice());
        computer.enlarge();
        computer.setInput([0]);
        
        const canvas = createCanvas(300, 300);

        const ctx = canvas.getContext('2d');
        ctx.fillStyle = 'rgba(0, 0, 0, 0)';
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        
        let partI = 0;
        let pos = new Point(150,150);

        while(!computer.halted){
            // run and paint
            const poscolor = getCurrentPanelColor(ctx,pos);
            computer.setInput([poscolor === 1 ? 1 : 0]);
            
            computer.run();
            let color = computer.getOutput();
            let turn = computer.getOutput();

            setCurrentPanelColor(ctx,pos,color);
            didx = (didx + 2*turn - 1 + 4)%4;
            pos.move(dirs[didx]);
            // Count if this panel was transparent (first time painted)
            if(poscolor === 2) partI++;
        }
        console.log('PartI : ', partI);

        // Save Part I image and wait for completion
        const out = fs.createWriteStream('partI.png');
        const stream = canvas.createPNGStream();
        stream.pipe(out);
        
        await new Promise((resolve) => {
            out.on('finish', () => {
                console.log('Saved as partI.png');
                resolve();
            });
        });

        // Now it's safe to clear and start Part II
        computer.reset(numbers.slice());
        computer.enlarge();
        computer.setInput([1]);
        let partII = 1;
        pos = new Point(150,150);
        didx = 0;

        ctx.clearRect(0, 0, canvas.width, canvas.height);
        setCurrentPanelColor(ctx,pos,1);
        while(!computer.halted){
            // run and paint
            const poscolor = getCurrentPanelColor(ctx,pos);
            computer.setInput([poscolor === 1 ? 1 : 0]);
            
            computer.run();
            let color = computer.getOutput();
            let turn = computer.getOutput();

            setCurrentPanelColor(ctx,pos,color);
            didx = (didx + 2*turn - 1 + 4)%4;
            pos.move(dirs[didx]);
        }
        const out2 = fs.createWriteStream('partII.png');
        const stream2 = canvas.createPNGStream();
        stream2.pipe(out2);
        out2.on('finish', () => console.log('Saved as partII.png'));

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();