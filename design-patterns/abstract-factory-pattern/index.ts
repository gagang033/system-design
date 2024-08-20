import { AbstractFactory } from "./AbstractFactory";
import { Shape } from "./Shape";
import { ShapeFactory } from "./ShapeFactory";

const abtractFactory = new AbstractFactory();

const shapeFactory = abtractFactory.getShapeFactory(false); //not 

const shape1: Shape | undefined = shapeFactory.getShape("square");
if(shape1 === undefined){
    throw new Error("shape not found!!");
}
shape1.draw();

const roundedShapeFactory = abtractFactory.getShapeFactory(true); //rounded

const shape2: Shape | undefined = roundedShapeFactory.getShape("rectangle");
if(shape2 === undefined){
    throw new Error("shape not found!!");
}
shape2.draw();