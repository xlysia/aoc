/**
 * Intcode Computer Implementation 
 */

class IntcodeComputer {
    constructor(program) {
        this.memory = [...program];
        this.pc = 0;
        this.inputptr = 0;
        this.outputptr = 0;
        this.input = [];
        this.output = [];
        this.halted = false;
        this.waitingForInput = false;
        this.base = 0;
    }

    // Run the program
    run() {
        this.halted = false;



        while (!this.halted && !this.waitingForInput) {

            this.step();
        }
        return this.memory[0];
    }

    enlarge(){
        // make sure memory is large enough
        while (this.memory.length < 10000) {
            this.memory.push(0);
        }
    }
    // Execute one instruction
    step() {
        if (this.halted) return;
        const instruction = this.memory[this.pc];
        const opcode = instruction % 100;

        const mode1 = Math.floor(instruction / 100) % 10;
        const mode2 = Math.floor(instruction / 1000) % 10;
        const mode3 = Math.floor(instruction / 10000) % 10;

        // Helper function to get parameter value based on mode
        const getParam = (paramNum, mode) => {
            const rawParam = this.memory[this.pc + paramNum];
            if(mode === 1) return rawParam; // Immediate mode
            if(mode === 2) return this.memory[this.base + rawParam] || 0; // Relative mode
            return this.memory[rawParam] || 0; // Position mode
        };

        // Helper function to get write address based on mode
        const getWriteAddr = (paramNum, mode) => {
            const rawParam = this.memory[this.pc + paramNum];
            if(mode === 2) return this.base + rawParam; // Relative mode
            return rawParam; // Position mode (mode 0 or 1, but writes are never immediate)
        };

        switch (opcode) {
            case 1: // Add
                {
                    const val1 = getParam(1, mode1);
                    const val2 = getParam(2, mode2);
                    const writeAddr = getWriteAddr(3, mode3);
                    this.memory[writeAddr] = val1 + val2;
                    this.pc += 4;
                }
                break;

            case 2: // Multiply
                {
                    const val1 = getParam(1, mode1);
                    const val2 = getParam(2, mode2);
                    const writeAddr = getWriteAddr(3, mode3);
                    this.memory[writeAddr] = val1 * val2;
                    this.pc += 4;
                }
                break;
                
            case 3: // Input
                {
                    if (this.inputptr >= this.input.length) {
                        this.waitingForInput = true;
                        return; 
                    }
                    const writeAddr = getWriteAddr(1, mode1);
                    this.memory[writeAddr] = this.input[this.inputptr];
                    this.inputptr++;
                    this.pc += 2;
                }
                break;
                
            case 4: // Output
                {
                    const val = getParam(1, mode1);
                    this.output.push(val);
                    this.pc += 2;
                }
                break;
            case 5:
            case 6: // Jump-if-true / Jump-if-false
                {
                    const val = getParam(1, mode1);
                    const target = getParam(2, mode2);
                    if ((opcode === 5 && val !== 0) || (opcode === 6 && val === 0)) {
                        this.pc = target;
                    } else {
                        this.pc += 3;
                    }
                }
                break;
            case 7: // Less than
            case 8: // Equals
                {   
                    const val1 = getParam(1, mode1);
                    const val2 = getParam(2, mode2);
                    const writeAddr = getWriteAddr(3, mode3);
                    if ((opcode === 7 && val1 < val2) || (opcode === 8 && val1 === val2)) {
                        this.memory[writeAddr] = 1;
                    } else {
                        this.memory[writeAddr] = 0;
                    }
                    this.pc += 4;
                }
                break;
            case 9:
                const val1 = getParam(1, mode1);
                this.base += val1;
                this.pc +=2;
                break;
            case 99: // Halt
                this.halted = true;
                break;

            default:
                throw new Error(`Unknown opcode: ${opcode} at position ${this.pc}`);
        }
    }

    get(idx) {
        return this.memory[idx];
    }

    // Reset the computer with a new program
    reset(program, options = {}) {
        this.memory = [...program];
        this.pc = 0;
        this.halted = false;
        this.output = [];
        this.outputptr = 0;
        this.base = 0;
    }

    setInput(input) {
        this.input = input;
        this.inputptr = 0;
        this.waitingForInput = false;
    }

    getLastOutput() {
        return this.output[this.output.length - 1] || 0;
    }

    getOutput(){
        return this.output[this.outputptr++] || 0;
    }
}

function Intcode(program, noun, verb) {
    const computer = new IntcodeComputer(program);
    computer.memory[1] = noun;
    computer.memory[2] = verb;
    computer.run();
    return computer.memory[0];
}

// Export both the class and the simple function
module.exports = {
    IntcodeComputer,
    Intcode
};
