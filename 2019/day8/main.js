const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');
const { createCanvas } = require('canvas');
const fs = require('fs');

// Main function
async function main() {
    console.log('AoC 2019 day 8! Reading from input...\n');

    const input = await readInput(2019, 8);
    const W = 25;
    const H = 6;

    if (input !== null) {
        // Input is comma separated integers
        let nzeros = Infinity;
        let partI = 0;
        let partII = Array(W * H).fill('2');
        for (let i = 0; i < input.length; i += W*H) {
            const layer = input.slice(i, i + W*H);
            let z = 0;
            let o = 0;
            let t = 0;
            
            let idx = 0;

            for(let j = 0; j < layer.length;j++ ){
                const c = layer[j];
                z += c == '0';
                o += c == '1';
                t += c == '2';

                if(partII[j] == '2'){
                    partII[j] = c;
                }
                
            }

            if(z < nzeros){
                nzeros = z;
                partI = o*t;
            }
        }

        console.log('PartI : ', partI);

        const canvas = createCanvas(W, H);
        const ctx = canvas.getContext('2d');
        
        const imageData = ctx.createImageData(W, H);

        for (let y = 0; y < H; y++) {
            for (let x = 0; x < W; x++) {
                const index = (y * W + x) * 4;
                const pixel = partII[y * W + x];

                if (pixel === '0') {
                    // Black
                    imageData.data[index + 0] = 0;
                    imageData.data[index + 1] = 0;
                    imageData.data[index + 2] = 0;
                    imageData.data[index + 3] = 255;
                } else if (pixel === '1') {
                    // White
                    imageData.data[index + 0] = 255;
                    imageData.data[index + 1] = 255;
                    imageData.data[index + 2] = 255;
                    imageData.data[index + 3] = 255;
                } else if (pixel === '2') {
                    // Transparent
                    imageData.data[index + 0] = 0;
                    imageData.data[index + 1] = 0;
                    imageData.data[index + 2] = 0;
                    imageData.data[index + 3] = 0;
                }
            }
        }
        ctx.putImageData(imageData, 0, 0);

        const out = fs.createWriteStream('partII.png');
        const stream = canvas.createPNGStream();
        stream.pipe(out);
        out.on('finish', () => console.log('Saved as partII.png'));

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();