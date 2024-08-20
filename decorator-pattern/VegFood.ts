import { Food } from "./Food";

export class VegFood implements Food {
    prepeareFood(): string {
        return "food";
    }
    cost(): number {
        return 100;
    }
    
}