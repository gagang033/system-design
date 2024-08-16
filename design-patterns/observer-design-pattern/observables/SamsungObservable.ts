import { NotificationObserver } from "../observers/NotificationObserver";
import { StockObservable } from "./StockObservable";

export class SamsungObservable implements StockObservable {
    stockCount: number = 0;
    observers: NotificationObserver[] = [];

    register(obj: NotificationObserver): void {
        this.observers.push(obj);
    }
    unregister(obj: NotificationObserver): void {
        const index = this.observers.indexOf(obj);
        if (index > -1) {
            this.observers.splice(index, 1);
        }
    }
    notifyAll(): void {
        for (const observer of this.observers) {
            observer.update();
        }
    }
    addStock(newStock: number): void {
        if (this.stockCount === 0) {
            this.notifyAll();
        }
        this.stockCount += newStock;
    }
    getItemName(): string {
        return "Samsung";
    }

}