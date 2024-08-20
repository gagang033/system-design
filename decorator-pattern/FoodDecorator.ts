import { Food } from "./Food";

export class FoodDecorator implements Food {
    newFood: Food;
    constructor(newFood: Food){
        this.newFood = newFood;
    }
    prepeareFood(): string {
        return this.newFood.prepeareFood();
    }
    cost(): number {
        return this.newFood.cost();
    }
    
}