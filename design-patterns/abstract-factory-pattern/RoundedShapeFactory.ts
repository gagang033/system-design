import { RoundedRectangle } from "./RoundedRectangle";
import { RoundedSquare } from "./RoundedSquare";
import { Shape } from "./Shape";

export class RoundedShapeFactory {
    private _shapeMap: Record<string,Shape> = {
        "rectangle": new RoundedRectangle(),
        "square": new RoundedSquare()
    };
    getShape(shape: string): Shape | undefined {
        if(shape in this._shapeMap)
            return this._shapeMap[shape];
        return undefined;
    }
}