/**
 * Intcode Computer Implementation 
 */

class IntcodeComputer {
    constructor(program) {
        this.memory = [...program];
        this.pc = 0;
        this.inputptr = 0;
        this.input = [];
        this.halted = false;
    }

    // Run the program
    run() {
        this.halted = false;

        // make sure memory is large enough
        // while (this.memory.length < 10000) {
        //     this.memory.push(0);
        // }

        while (!this.halted) {

            this.step();
        }
        return;
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
            return mode === 1 ? rawParam : this.memory[rawParam] || 0;
        };

        // Helper function to get write address (always position mode for writes)
        const getWriteAddr = (paramNum) => {
            return this.memory[this.pc + paramNum];
        };

        switch (opcode) {
            case 1: // Add
                {
                    const val1 = getParam(1, mode1);
                    const val2 = getParam(2, mode2);
                    const writeAddr = getWriteAddr(3);
                    this.memory[writeAddr] = val1 + val2;
                    this.pc += 4;
                }
                break;

            case 2: // Multiply
                {
                    const val1 = getParam(1, mode1);
                    const val2 = getParam(2, mode2);
                    const writeAddr = getWriteAddr(3);
                    this.memory[writeAddr] = val1 * val2;
                    this.pc += 4;
                }
                break;
                
            case 3: // Input
                {
                    if (this.inputptr >= this.input.length) {
                        throw new Error(`Input exhausted: need input at PC ${this.pc}`);
                    }
                    const writeAddr = getWriteAddr(1);
                    this.memory[writeAddr] = this.input[this.inputptr];
                    this.inputptr++;
                    this.pc += 2;
                }
                break;
                
            case 4: // Output
                {
                    const val = getParam(1, mode1);
                    console.log(val);
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
                    const writeAddr = getWriteAddr(3);
                    if ((opcode === 7 && val1 < val2) || (opcode === 8 && val1 === val2)) {
                        this.memory[writeAddr] = 1;
                    } else {
                        this.memory[writeAddr] = 0;
                    }
                    this.pc += 4;
                }
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
    }

    setInput(input) {
        this.input = input;
        this.inputptr = 0;
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
