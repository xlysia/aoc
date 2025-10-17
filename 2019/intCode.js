/**
 * Intcode Computer Implementation 
 */

class IntcodeComputer {
    constructor(program) {
        this.memory = [...program];
        this.pc = 0;
        this.inputPointer = 0;
        this.halted = false;
    }

    // Run the program
    run() {
        while (!this.halted) {
            this.step();
        }
        return;
    }

    // Execute one instruction
    step() {
        if (this.halted) return;

        const instruction = this.memory[this.pc];
        const opcode = instruction;
        const mode1 = this.memory[this.pc+1];
        const mode2 = this.memory[this.pc+2];
        const mode3 = this.memory[this.pc+3];

        switch (opcode) {
            case 1: // Add
                {
                    this.memory[mode3] = this.memory[mode1] + this.memory[mode2];
                    this.pc += 4;
                }
                break;

            case 2: // Multiply
                {
                    this.memory[mode3] = this.memory[mode1] * this.memory[mode2];
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
