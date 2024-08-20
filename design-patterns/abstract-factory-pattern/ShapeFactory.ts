import { Rectangle } from "./Rectangle";
import { Shape } from "./Shape";
import { Square } from "./Square";

export class ShapeFactory {
    private _shapeMap: Record<string,Shape> = {
        "rectangle": new Rectangle(),
        "square": new Square()
    };
    getShape(shape: string): Shape | undefined {
        if(shape in this._shapeMap)
            return this._shapeMap[shape];
        return undefined;
    }
}