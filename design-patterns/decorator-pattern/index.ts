import { ChineseFood } from "./ChineseFood";
import { NonVegFood } from "./NonVegFood";
import { VegFood } from "./VegFood";

const veg = new VegFood();
const nonVeg = new NonVegFood(new VegFood());
const chinese = new ChineseFood(new VegFood());
const chineseNonVeg = new ChineseFood(new NonVegFood(new VegFood()));

console.log(`veg food: ${veg.prepeareFood()}. Cost = ${veg.cost()}`);
console.log(`nonveg food: ${nonVeg.prepeareFood()}. Cost = ${nonVeg.cost()}`);
console.log(`chinese food: ${chinese.prepeareFood()}. Cost = ${chinese.cost()}`);
console.log(`nonveg chinese food: ${chineseNonVeg.prepeareFood()}. Cost = ${chineseNonVeg.cost()}`);
