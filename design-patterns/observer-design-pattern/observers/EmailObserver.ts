import { NotificationObserver } from "./NotificationObserver";
import { StockObservable } from "../observables/StockObservable";

export class EmailObserver implements NotificationObserver {
    emailId: string = "";
    observable: StockObservable;

    constructor(emailId: string, observable: StockObservable) {
        this.emailId = emailId;
        this.observable = observable;
    }
    update(): void {
        this.sendEmail(this.emailId);
    }

    sendEmail(emailId: string): void {
        console.log(`email sent to: ${emailId} for ${this.observable.getItemName()}`);
    }

}