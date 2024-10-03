import { Logger, LogLevel } from "./Logger";

export class ErrorLogger extends Logger {
    constructor(nextLogger: Logger){
        super(nextLogger);
    }
    log(logLevel: LogLevel, msg: string): void {
        if(logLevel == LogLevel.ERROR){
            console.log("INFO: ",msg);
            return;
        }
        super.log(logLevel,msg);
    }
    
}