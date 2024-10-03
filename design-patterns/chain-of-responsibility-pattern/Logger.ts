export enum LogLevel {
    INFO,
    DEBUG,
    ERROR
};

export abstract class Logger {
    logger: Logger;
    constructor(nextLogger: Logger) {
        this.logger = nextLogger;
    }
    log(logLevel: LogLevel, msg: string): void {
        if (this.logger != null) {
            this.logger.log(logLevel, msg);
        }
    };
}