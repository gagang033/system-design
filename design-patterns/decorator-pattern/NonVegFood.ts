import { Food } from "./Food";
import { FoodDecorator } from "./FoodDecorator";

export class NonVegFood extends FoodDecorator {
    constructor(food: Food){
        super(food);
    }
    prepeareFood(): string {
        return super.prepeareFood() + " with chicken curry";
    }
    cost(): number {
        return super.cost() + 150;
    }
}