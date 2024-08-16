import { NotificationObserver } from "./NotificationObserver";
import { StockObservable } from "../observables/StockObservable";

export class SmsObserver implements NotificationObserver {
    phoneNumber: number;
    observable: StockObservable;

    constructor(mobile: number, observable: StockObservable) {
        this.phoneNumber = mobile;
        this.observable = observable;
    }
    update(): void {
        this.sendEmail(this.phoneNumber);
    }

    sendEmail(phoneNumber: number): void {
        console.log(`sms sent to: ${phoneNumber} for ${this.observable.getItemName()}`);
    }

}