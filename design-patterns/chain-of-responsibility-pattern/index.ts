import { DebugLogger } from "./DebugLogger";
import { ErrorLogger } from "./ErorrLogger";
import { InfoLogger } from "./InfoLogger";
import { LogLevel } from "./Logger";

const logger = new InfoLogger(new DebugLogger(new ErrorLogger(null)));

logger.log(LogLevel.INFO,"info log");
logger.log(LogLevel.ERROR,"error log");