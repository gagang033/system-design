export enum TimeUnit {
    SECOND,
    MINUTE,
    HOUR
};
export enum TaskType {
    NONE,
    FIXEDRATE,
    FIXEDDELAY
}
const delayMap: Record<TimeUnit, number> = {
    [TimeUnit.SECOND]: 1000,
    [TimeUnit.MINUTE]: 60000,
    [TimeUnit.HOUR]: 3600000
}
export class ScheduledTask {
    private _task: () => void;
    private _executionTime: number;
    private _unit: TimeUnit | undefined = undefined;
    private _delay: number | undefined = undefined;
    private _taskType: TaskType;

    constructor(task: () => void, executionTime: number, taskType: TaskType, delay?: number, unit?: TimeUnit) {
        this._task = task;
        this._executionTime = executionTime;
        this._taskType = taskType;
        this._delay = delay;
        this._unit = unit;
    }


    get taskType(): TaskType {
        return this._taskType;
    }

    get executionTime(): number {
        return this._executionTime;
    }

    get task(): () => void {
        return this._task;
    }

    get getNextExecutionTime(): number {
        return (this._executionTime*-1 + this._delay * delayMap[this._unit])*-1;
    }

    set executionTime(time: number) {
        this._executionTime = time;
    }

    get shouldReschedule(): boolean {
        return this._taskType !== TaskType.NONE;
    }
}