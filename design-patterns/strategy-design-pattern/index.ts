import { LuxuryDrive } from "./LuxuryDrive";
import { LuxuryVehicle } from "./LuxuryVehicle";
import { NormalDrive } from "./NormalDrive";
import { SportsVehicle } from "./SportsVehicle";

const mersedes = new LuxuryVehicle(new LuxuryDrive());
mersedes.drive();

const audi = new SportsVehicle(new LuxuryDrive());
audi.drive();
       
const bmw = new LuxuryVehicle(new NormalDrive());
bmw.drive();