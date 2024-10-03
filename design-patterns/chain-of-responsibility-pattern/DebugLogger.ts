import { Logger, LogLevel } from "./Logger";

export class DebugLogger extends Logger {
    constructor(nextLogger: Logger){
        super(nextLogger);
    }
    log(logLevel: LogLevel, msg: string): void {
        if(logLevel == LogLevel.DEBUG){
            console.log("INFO: ",msg);
            return;
        }
        super.log(logLevel,msg);
    }
    
}