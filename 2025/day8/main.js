const { start } = require('repl');
const { readInput, parseLines, parseCommaSeparatedInts } = require('../../js/utils/readInput');

// Main function



async function main() {
    console.log('AoC 2025 day 8! Reading from input...\n');
    
    const input = await readInput(2025, 8);
    
    if (input !== null) {
        let lines = parseLines(input);
        let boxes = lines.map(x => {
            let [x_val, y_val, z_val] = parseCommaSeparatedInts(x);
            return { x: x_val, y: y_val, z: z_val };
        });

        function dist2( A, B) {
            return (B.x-A.x)**2 +(B.y-A.y)**2 + (B.z-A.z)**2; 
        }

        let n = boxes.length;
        
        // Simple min-heap implementation
        class MinHeap {
            constructor() {
                this.heap = [];
            }
            
            push(item) {
                this.heap.push(item);
                this.bubbleUp(this.heap.length - 1);
            }
            
            pop() {
                if (this.heap.length === 0) return null;
                if (this.heap.length === 1) return this.heap.pop();
                
                let min = this.heap[0];
                this.heap[0] = this.heap.pop();
                this.bubbleDown(0);
                return min;
            }
            
            bubbleUp(index) {
                while (index > 0) {
                    let parentIndex = Math.floor((index - 1) / 2);
                    if (this.heap[index].dist >= this.heap[parentIndex].dist) break;
                    
                    [this.heap[index], this.heap[parentIndex]] = [this.heap[parentIndex], this.heap[index]];
                    index = parentIndex;
                }
            }
            
            bubbleDown(index) {
                while (true) {
                    let leftChild = 2 * index + 1;
                    let rightChild = 2 * index + 2;
                    let smallest = index;
                    
                    if (leftChild < this.heap.length && this.heap[leftChild].dist < this.heap[smallest].dist) {
                        smallest = leftChild;
                    }
                    if (rightChild < this.heap.length && this.heap[rightChild].dist < this.heap[smallest].dist) {
                        smallest = rightChild;
                    }
                    
                    if (smallest === index) break;
                    
                    [this.heap[index], this.heap[smallest]] = [this.heap[smallest], this.heap[index]];
                    index = smallest;
                }
            }
            
            isEmpty() {
                return this.heap.length === 0;
            }
        }
        
        // Union-Find for efficient cluster tracking
        class UnionFind {
            constructor(n) {
                this.parent = Array(n).fill().map((_, i) => i);
                this.rank = Array(n).fill(0);
                this.components = n;
            }
            
            find(x) {
                if (this.parent[x] !== x) {
                    this.parent[x] = this.find(this.parent[x]);
                }
                return this.parent[x];
            }
            
            union(x, y) {
                let rootX = this.find(x);
                let rootY = this.find(y);
                
                if (rootX !== rootY) {
                    if (this.rank[rootX] < this.rank[rootY]) {
                        this.parent[rootX] = rootY;
                    } else if (this.rank[rootX] > this.rank[rootY]) {
                        this.parent[rootY] = rootX;
                    } else {
                        this.parent[rootY] = rootX;
                        this.rank[rootX]++;
                    }
                    this.components--;
                    return true;
                }
                return false;
            }
        }
        
        // Create heap with all connections sorted by distance
        let heap = new MinHeap();
        for (let i = 0; i < n; i++) {
            for (let j = i + 1; j < n; j++) {
                heap.push({
                    i: i,
                    j: j,
                    dist: dist2(boxes[i], boxes[j])
                });
            }
        }
        
        let uf = new UnionFind(n);
        let merges = 0;
        let links = 0;
        // Process connections from heap until 1000 merges done
        while (!heap.isEmpty()) {
            let connection = heap.pop();
            
            // Try to merge these two boxes
            if(uf.union(connection.i, connection.j)){
                merges++;
            }
            
            links++;    
            if (links === 1000) {
                // Calculate cluster sizes
                let clusterSizes = new Map();
                for (let i = 0; i < n; i++) {
                    let root = uf.find(i);
                    clusterSizes.set(root, (clusterSizes.get(root) || 0) + 1);
                }
                
                // Sort clusters by size (descending) and get top 3
                let sizes = Array.from(clusterSizes.values()).sort((a, b) => b - a);
                let top3Sizes = sizes.slice(0, 3);

                let partI =  top3Sizes.length >= 3 ? top3Sizes[0] * top3Sizes[1] * top3Sizes[2] : 0;


                console.log(`Part I - Product of 3 largest clusters: ${partI}`);
            }

            if(merges === boxes.length-1){
                let partII = boxes[connection.i].x * boxes[connection.j].x;
                console.log(`Part II - Product of X last boxes to connect: ${partII}`);
                break;
            }
        }



    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();