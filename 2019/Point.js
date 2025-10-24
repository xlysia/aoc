
class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
    
    // Manhattan distance to another point
    manhattanDistanceTo(other) {
        return Math.abs(this.x - other.x) + Math.abs(this.y - other.y);
    }
    
    // Euclidean distance to another point
    distanceTo(other) {
        return Math.sqrt((this.x - other.x) ** 2 + (this.y - other.y) ** 2);
    }
    
    // Add another point (vector addition)
    add(other) {
        return new Point(this.x + other.x, this.y + other.y);
    }
    
    // Subtract another point (vector subtraction)
    subtract(other) {
        return new Point(this.x - other.x, this.y - other.y);
    }
    
    // Check if equal to another point
    equals(other) {
        return this.x === other.x && this.y === other.y;
    }
    
    // Clone the point
    clone() {
        return new Point(this.x, this.y);
    }
    
    // Move by adding another point (modifies this point)
    move(other) {
        this.x += other.x;
        this.y += other.y;
        return this;
    }
    
    // String representation
    toString() {
        return `(${this.x}, ${this.y})`;
    }
}


// Export both the class and the simple function
module.exports = {
    Point
};