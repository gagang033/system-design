import { Drive } from "./Drive";
import { Vehicle } from "./Vehicle";

export class NormalVehicle extends Vehicle {
    constructor(driveCapability: Drive) {
        super(driveCapability);
    }
    drive(): void {
        super.drive();
    }
}