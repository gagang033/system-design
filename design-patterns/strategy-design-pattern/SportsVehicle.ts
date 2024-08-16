import { Drive } from "./Drive";
import { Vehicle } from "./Vehicle";

export class SportsVehicle extends Vehicle {
    constructor(driveCapability: Drive) {
        super(driveCapability);
    }
    drive(): void {
        super.drive();
    }
}