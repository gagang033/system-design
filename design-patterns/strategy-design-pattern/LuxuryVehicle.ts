import { Drive } from "./Drive";
import { Vehicle } from "./Vehicle";

export class LuxuryVehicle extends Vehicle {
    constructor(driveCapability: Drive) {
        super(driveCapability);
    }
    drive(): void {
        super.drive();
    }
}