export class PriorityQueue<T> {
    private queue: T[] = [];
    private comparator: (a: T, b: T) => number;

    constructor(comparator: (a: T, b: T) => number) {
        this.comparator = comparator;
    }

    add(item: T) {
        this.queue.push(item);
        this.queue.sort(this.comparator); // Sorting based on the comparator
    }

    poll(): T | undefined {
        return this.queue.shift(); // Removes and returns the smallest (min) element
    }

    peek(): T | undefined {
        return this.queue[0]; // Returns the smallest element without removing it
    }

    isEmpty(): boolean {
        return this.queue.length === 0;
    }

    size(): number {
        return this.queue.length;
    }
}
