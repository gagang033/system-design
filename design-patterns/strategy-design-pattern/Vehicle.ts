import { Drive } from "./Drive";

export class Vehicle {
    private driveCapability: Drive;

    constructor(driveCapability: Drive) {
        this.driveCapability = driveCapability;
    }

    drive(): void {
        this.driveCapability.drive();
    }
}
