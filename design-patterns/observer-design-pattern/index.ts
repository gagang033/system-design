import { EmailObserver } from "./observers/EmailObserver";
import { IphoneObservable } from "./observables/IphoneObservable";
import { SamsungObservable } from "./observables/SamsungObservable";
import { SmsObserver } from "./observers/SmsObserver";

const iphoneObservable: IphoneObservable = new IphoneObservable();
const samsungObservable: SamsungObservable = new SamsungObservable();

const observer1 = new EmailObserver("abc@email.com",iphoneObservable);
const observer2 = new EmailObserver("def@email.com",samsungObservable);
const observer3 = new SmsObserver(123,iphoneObservable);

iphoneObservable.register(observer1);
iphoneObservable.register(observer3);
samsungObservable.register(observer2);

iphoneObservable.addStock(10);
samsungObservable.addStock(5);
