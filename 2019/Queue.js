// Simple Queue implementation
class Queue {
    constructor() {
        this.items = [];
    }
    
    // Add to back of queue
    enqueue(item) {
        this.items.push(item);
    }
    
    // Remove from front of queue
    dequeue() {
        return this.items.shift();
    }
    
    // Check if empty
    isEmpty() {
        return this.items.length === 0;
    }
    
    // Get size
    size() {
        return this.items.length;
    }
    
    // Peek at front without removing
    front() {
        return this.items[0];
    }
}
