const { error } = require('console');
const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');
const { IntcodeComputer } = require('../intCode');
const { Queue } = require('../Queue');

async function main() {
    console.log('AoC 2019 day 23! Reading from input...\n');

    const input = await readInput(2019, 23);

    if (input !== null) {
        const numbers = parseCommaSeparatedInts(input);
        
        class Computer{
            constructor(numbers, address){
                this.NIC = new IntcodeComputer(numbers.slice());
                this.queue = new Queue();
                this.address = address;
                this.idle = false;
                this.NIC.enlarge();
                // Initialize with network address
                this.NIC.setInput([address]);
            }
            
            step() {
                // If queue is empty but computer is waiting for input, provide -1
                if (this.queue.isEmpty() && this.NIC.waitingForInput) {
                    this.NIC.setInput([-1]);
                    this.idle = true;
                } else if (!this.queue.isEmpty()) {
                    // Get X, Y from queue
                    const x = this.queue.dequeue();
                    const y = this.queue.dequeue();
                    this.NIC.setInput([x,y]);
                    this.idle = false;
                }
                
                // Run until output, waiting for input, or halt
                this.NIC.run();
                
                // Check for output packets
                const packets = [];
                while (this.NIC.output.length >= 3) {
                    const dest = this.NIC.output.shift();
                    const x = this.NIC.output.shift();
                    const y = this.NIC.output.shift();
                    packets.push({ dest, x, y });
                }
                
                return packets;
            }
            
            addPacket(x, y) {
                this.queue.enqueue(x);
                this.queue.enqueue(y);
            }
        };

        // Create array of 50 computers (addresses 0-49)
        const computers = [];
        for (let i = 0; i < 50; i++) {
            computers.push(new Computer(numbers, i));
        }

        console.log("Created network of 50 computers");

        // Part I: Find the first packet sent to address 255
        let partI = null;
        let partII = null;
        let NATpacket = null;

        while (true) {
            let anyPackets = false;
            
            for (let i = 0; i < 50; i++) {
                const packets = computers[i].step();
                
                if (packets.length > 0) {
                    anyPackets = true;
                }
                
                for (const packet of packets) {
                    if (packet.dest === 255) {
                        if (partI === null) {
                            partI = packet.y;
                            console.log(`Part I: First packet to address 255 has Y value ${partI}`);
                        } 
                        NATpacket = { x: packet.x, y: packet.y };
                    } else if (packet.dest >= 0 && packet.dest < 50) {
                        computers[packet.dest].addPacket(packet.x, packet.y);
                    }
                }
            }
            
            // Check if network is idle (no packets produced and all computers idle)
            let allIdle = computers.every(c => c.idle);
            
            if (!anyPackets && allIdle && NATpacket !== null) {
                //console.log("Network idle, NAT sending packet:", NATpacket);
                computers[0].addPacket(NATpacket.x, NATpacket.y);
                
                if (partII === NATpacket.y) {
                    console.log(`Part II: NAT sent duplicate Y value ${partII}`);
                    break;
                }
                partII = NATpacket.y;
            }
        }

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();