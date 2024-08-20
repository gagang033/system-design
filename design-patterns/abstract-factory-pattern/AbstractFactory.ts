import { RoundedShapeFactory } from "./RoundedShapeFactory"
import { ShapeFactory } from "./ShapeFactory"

export class AbstractFactory {
    getShapeFactory(isRounded: boolean): RoundedShapeFactory | ShapeFactory {
        return isRounded ? new RoundedShapeFactory() : new ShapeFactory();
    }
}