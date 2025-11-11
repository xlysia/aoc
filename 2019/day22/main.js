const { error } = require('console');
const { readInput, parseLines } = require('../../js/utils/readInput');

async function main() {
    console.log('AoC 2019 day 22! Reading from input...\n');

    const input = await readInput(2019, 22);

    if (input !== null) {
        
        // Macro for proper modulo operation (handles negative numbers)
        const mod = (x, m) => ((x % m) + m) % m;
        
        let DECK_SIZE = 10007;

        const lines = parseLines(input);

        // Part I: Use linear transformation approach
        
        let a1 = 1; // coefficient  
        let b1 = 0; // offset
        
        for(let line of lines) {
            if(line === "deal into new stack") {
                // x -> -x - 1  =>  f(x) = -1*x + (-1)
                a1 = (-a1) % DECK_SIZE;
                b1 = (-b1 - 1) % DECK_SIZE;
            } else {
                let N = parseInt(line.split(' ').pop());
                let operation = line.split(' ')[0];
                
                if(operation === "deal") {
                    // deal with increment N: x -> N*x
                    a1 = (a1 * N) % DECK_SIZE;
                    b1 = (b1 * N) % DECK_SIZE;
                } else {
                    // cut N: x -> x - N
                    b1 = (b1 - N) % DECK_SIZE;
                }
            }
        }
        
        // Normalize to positive values
        a1 = mod(a1, DECK_SIZE);
        b1 = mod(b1, DECK_SIZE);
        
        // Apply transformation: f(2019) = a*2019 + b (mod DECK_SIZE)
        const partI = (a1 * 2019 + b1) % DECK_SIZE;

        console.log("PartI - Card 2019 is at position", partI );

        // Part II: What card ends up at position 2020?
        const DECK_SIZE_2 = 119315717514047n; //  is a prime
        const SHUFFLES = 101741582076661n;
        const TARGET_POSITION = 2020n;
                
        // Modular arithmetic functions for BigInt
        function modPow(base, exp, mod) {
            let result = 1n;
            base = base % mod;
            while (exp > 0n) {
                if (exp % 2n === 1n) result = (result * base) % mod;
                exp = exp / 2n;
                base = (base * base) % mod;
            }
            return result;
        }
        
        function modInverse(a, m) {
            // For prime modulus, use Fermat's little theorem: a^(m-1) = 1 (mod m)
            // So a^(-1) = a^(m-2) (mod m)
           
            return modPow(a, m - 2n, m);
        }
        
        // Convert shuffle operations to linear transformation: f(x) = ax + b (mod m)
        // This tracks where card x ends up after shuffling
        let a = 1n; // coefficient
        let b = 0n; // offset
        
        for(let line of lines) {
            if(line === "deal into new stack") {
                // x -> -x - 1  =>  f(x) = -1*x + (-1)
                a = mod(-a, DECK_SIZE_2);
                b = mod(-b - 1n, DECK_SIZE_2);
            } else {
                let N = BigInt(parseInt(line.split(' ').pop()));
                let operation = line.split(' ')[0];
                
                if(operation === "deal") {
                    // deal with increment N: x -> N*x
                    a = (a * N) % DECK_SIZE_2;
                    b = (b * N) % DECK_SIZE_2;
                } else {
                    // cut N: x -> x - N
                    b = mod(b - N, DECK_SIZE_2);
                }
            }
        }
        
        // Normalize to positive values (already handled above, but just to be sure)
        a = mod(a, DECK_SIZE_2);
        b = mod(b, DECK_SIZE_2);
                        
        // For multiple applications: f^n(x) = a^n * x + b * (a^n - 1) / (a - 1)
        const aPowN = modPow(a, SHUFFLES, DECK_SIZE_2);
        const aMinusOne = mod(a - 1n, DECK_SIZE_2);
        const aInv = modInverse(aMinusOne, DECK_SIZE_2);
        const aPowNMinusOne = mod(aPowN - 1n, DECK_SIZE_2);
        const bCoeff = (b * aPowNMinusOne % DECK_SIZE_2 * aInv) % DECK_SIZE_2;
                        
        // To find what card ends up at position 2020, we solve: aPowN * x + bCoeff = 2020
        // x = (2020 - bCoeff) / aPowN = (2020 - bCoeff) * aPowN^(-1)
        const aPowNInv = modInverse(aPowN, DECK_SIZE_2);        
        const targetMinusBCoeff = mod(TARGET_POSITION - bCoeff, DECK_SIZE_2);
        
        const partII = (targetMinusBCoeff * aPowNInv) % DECK_SIZE_2;
        
        console.log("PartII - Card at position 2020:", partII.toString());

    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();