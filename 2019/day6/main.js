const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');

// Linked list node for orbit map
class Node {
    constructor(name) {
        this.name = name;
        this.parent = null;
        this.children = [];
    }
}

// Main function
async function main() {
    console.log('AoC 2019 day 6! Reading from input...\n');

    //const input ="1002,4,3,4,33";
    const input = await readInput(2019, 6);

    if (input !== null) {
        // Input contains orbits data each line is a direct orbit like "AAA)BBB"
        
        const lines = input.split('\n').map(line => line.trim()).filter(line => line.length > 0);

        // Build orbit map
        const nodes = new Map();

        for (const line of lines) {
            const [center, orbiter] = line.split(')').map(part => part.trim());
            if (!nodes.has(center)) {
                nodes.set(center, new Node(center));
            }
            if (!nodes.has(orbiter)) {
                nodes.set(orbiter, new Node(orbiter));
            }
            const parent = nodes.get(center);
            const child = nodes.get(orbiter);
            child.parent = parent;
            parent.children.push(child);
        }
        // Part I: Count total orbits
        let partI = 0;
        for (const node of nodes.values()) {
            let current = node;
            while (current.parent !== null) {
                partI++;
                current = current.parent;
            }
        }
        console.log('PartI:', partI);

        // Part II: Minimum orbital transfers between YOU and SAN
        // use queue for BFS
        const start = nodes.get('YOU').parent;
        const target = nodes.get('SAN').parent;
        const queue = [{ node: start, depth: 0 }];
        const visited = new Set();
        visited.add(start.name);
        let partII = -1;
        while (queue.length > 0) {
            const { node, depth } = queue.shift();
            if (node === target) {
                partII = depth;
                break;
            }
            const neighbors = [];
            if (node.parent !== null) {
                neighbors.push(node.parent);
            }
            for (const child of node.children) {
                if (!visited.has(child.name)) {
                    neighbors.push(child);
                }
            }
            for (const neighbor of neighbors) {
                if (!visited.has(neighbor.name)) {
                    visited.add(neighbor.name);
                    queue.push({ node: neighbor, depth: depth + 1 });
                }
            }
        }
        console.log('Part II:', partII);
    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();