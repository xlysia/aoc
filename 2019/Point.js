
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

class Point3D {
    constructor(x = 0, y = 0, z = 0) {
        this.x = x;
        this.y = y;
        this.z = z;
    }
    
    // Manhattan distance to another point
    manhattanDistanceTo(other) {
        return Math.abs(this.x - other.x) + Math.abs(this.y - other.y) + Math.abs(this.z - other.z);
    }
    
    // Euclidean distance to another point
    distanceTo(other) {
        return Math.sqrt((this.x - other.x) ** 2 + (this.y - other.y) ** 2 + (this.z - other.z) ** 2);
    }
    
    // Add another point (vector addition)
    add(other) {
        return new Point3D(this.x + other.x, this.y + other.y, this.z + other.z);
    }
    
    // Subtract another point (vector subtraction)
    subtract(other) {
        return new Point3D(this.x - other.x, this.y - other.y, this.z - other.z);
    }
    
    // Check if equal to another point
    equals(other) {
        return this.x === other.x && this.y === other.y && this.z === other.z;
    }
    
    // Clone the point
    clone() {
        return new Point3D(this.x, this.y, this.z);
    }
    
    // Move by adding another point (modifies this point)
    move(other) {
        this.x += other.x;
        this.y += other.y;
        this.z += other.z;
        return this;
    }
    
    // String representation
    toString() {
        return `(${this.x}, ${this.y}, ${this.z})`;
    }
}

// Export both classes
module.exports = {
    Point,
    Point3D
};