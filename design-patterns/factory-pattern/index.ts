import { Shape } from "./Shape";
import { ShapeFactory } from "./ShapeFactory";

const shapeFactory = new ShapeFactory();

const shape: Shape | undefined = shapeFactory.getShape("square");
if(shape === undefined){
    throw new Error("shape not found!!");
}
shape.draw();