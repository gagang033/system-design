import { NotificationObserver } from "../observers/NotificationObserver";

export interface StockObservable {
    register(obj: NotificationObserver): void;
    
    unregister(obj: NotificationObserver): void;

    notifyAll(): void;

    addStock(newStock: number): void;

    getItemName(): string;
}