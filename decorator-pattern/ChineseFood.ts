import { Food } from "./Food";
import { FoodDecorator } from "./FoodDecorator";

export class ChineseFood extends FoodDecorator {
    constructor(food: Food){
        super(food);
    }
    prepeareFood(): string {
        return super.prepeareFood() + " chinese sauce";
    }
    cost(): number {
        return super.cost() + 50;
    }
}