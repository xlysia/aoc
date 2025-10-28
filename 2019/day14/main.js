const { readInput, parseCommaSeparatedInts } = require('../../js/utils/readInput');

// Simple Queue implementation
class Queue {
    constructor() {
        this.items = [];
    }
    enqueue(item) { this.items.push(item); }
    dequeue() { return this.items.shift(); }
    isEmpty() { return this.items.length === 0; }
}

class Recipe {
    constructor(quantity, ingredients){
        this.produces = quantity;  // How much this recipe makes
        this.ingredients = [];     // What it needs

        for(let ingredient of ingredients.split(',').map(i => i.trim()).filter(i => i.length > 0)){
            const [n, name] = ingredient.split(' ').map(i => i.trim()).filter(i => i.length > 0);
            this.ingredients.push({chemical: name, needed: parseInt(n)});
        }
    }
}

function solver(recipes,target){
    let surplus = new Map(); // Track leftover chemicals
    let oreNeeded = 0;
    let queue = new Queue();
    // enqueue the requested amount of FUEL
    queue.enqueue({chemical: 'FUEL', needed: target});

    while (!queue.isEmpty()) {
        const { chemical, needed } = queue.dequeue();
        
        if (chemical === 'ORE') {
            oreNeeded += needed;
            continue;
        }

        // Check if we have surplus of this chemical
        const available = surplus.get(chemical) || 0;
        
        if (available >= needed) {
            // We have enough surplus
            surplus.set(chemical, available - needed);
            continue;
        }

        // We need to produce more
        const stillNeeded = needed - available;
        surplus.set(chemical, 0); // Used up all surplus

        const recipe = recipes.get(chemical);
        if (!recipe) {
            console.error(`No recipe found for ${chemical}`);
            continue;
        }

        // How many times do we need to run this recipe?
        const times = Math.ceil(stillNeeded / recipe.produces);
        
        // Add surplus from overproduction
        const produced = times * recipe.produces;
        const excess = produced - stillNeeded;
        surplus.set(chemical, (surplus.get(chemical) || 0) + excess);

        // Add ingredients to queue
        for (let ingredient of recipe.ingredients) {
            queue.enqueue({
                chemical: ingredient.chemical,
                needed: ingredient.needed * times
            });
        }
    }
    return oreNeeded;
}

// Main function
async function main() {
    console.log('AoC 2019 day 14! Reading from input...\n');
    
    const input = await readInput(2019, 14);
    
    if (input !== null) {
        
        const recipes = new Map();
        // 5 VJHF, 7 MNCFX, 9 VPVL, 37 CXFTF => 6 GNMV
        const lines = input.split('\n').map(line => line.trim()).filter(line => line.length > 0);

        for(let line of lines){
            const [ingredients, product] = line.split('=>').map(part => part.trim());
            const [q, pname] = product.split(' ').map(part => part.trim());
            recipes.set(pname, new Recipe(parseInt(q), ingredients));
        }

        // Find how many ORE for 1 FUEL
        let partI = solver(recipes,1);


        console.log(`Part I: ${partI} ORE needed for 1 FUEL`);

        // Part II: find maximum integer FUEL producible with 1 trillion ORE
        const ORE_TARGET = 1e12;

        let lo = 1;
        let hi = 10*ORE_TARGET/partI;

        while (lo < hi) {
            const mid = Math.floor((lo + hi + 1) / 2); // bias up to avoid infinite loop
            const requiredOre = solver(recipes, mid);
            if (requiredOre <= ORE_TARGET) {
                lo = mid; // mid is feasible
            } else {
                hi = mid - 1; // mid too large
            }
        }

        console.log(`Part II: ${lo} FUEL for 1T ORE`);



    } else {
        console.log('Failed to read input data');
    }
    return 0;
}

// Run the program
main();