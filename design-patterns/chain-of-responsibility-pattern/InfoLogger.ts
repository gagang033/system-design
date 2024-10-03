import { Logger, LogLevel } from "./Logger";

export class InfoLogger extends Logger {
    constructor(nextLogger: Logger){
        super(nextLogger);
    }
    log(logLevel: LogLevel, msg: string): void {
        if(logLevel == LogLevel.INFO){
            console.log("INFO: ",msg);
            return;
        }
        super.log(logLevel,msg);
    }
    
}