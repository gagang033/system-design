//import PriorityQueue from 'priority-queue-typescript';
import { PriorityQueue } from './PriorityQueue';
import { ScheduledTask, TaskType, TimeUnit } from './ScheduledTask';
export class ScheduledExecutorService {
    private _queue: PriorityQueue<ScheduledTask>;
    taskComparator = (a: ScheduledTask, b: ScheduledTask): number => {
        return b.executionTime - a.executionTime;
      };
    constructor() {
        this._queue = new PriorityQueue<ScheduledTask>(this.taskComparator);
        this._execute();
    }

    private _execute = () => {
        if (this._queue.size() === 0) {
            setTimeout(() => {
                this._execute();
            }, 500);
        }
        else {
            while (this._queue.size() > 0 && this._queue.peek().executionTime*-1 <= Date.now()) {
                const scheduledTask: ScheduledTask = this._queue.poll();
                scheduledTask.task();
                //console.log(scheduledTask);
                if (scheduledTask.shouldReschedule) {
                    if (scheduledTask.taskType === TaskType.FIXEDRATE) {
                        const newTask: ScheduledTask = scheduledTask;
                        newTask.executionTime = scheduledTask.getNextExecutionTime;
                        //console.log(newTask);
                        this._queue.add(newTask);
                    }
                    else {
                        const newTask: ScheduledTask = scheduledTask;
                        newTask.executionTime = scheduledTask.getNextExecutionTime;
                        this._queue.add(newTask);
                    }
                }
            }
            setTimeout(() => {
                this._execute();
            }, 500);
        }
    }

    schedule = (task: () => void, executionTime: number, taskType: TaskType) => {
        const scheduledTask = new ScheduledTask(task, executionTime, taskType);
        //console.log(scheduledTask);
        this._queue.add(scheduledTask);
    }

    scheduleAtFixedRate = (task: () => void, executionTime: number, taskType: TaskType, delay: number, unit: TimeUnit) => {
        const scheduledTask = new ScheduledTask(task, executionTime, taskType, delay, unit);
        //console.log(scheduledTask);
        this._queue.add(scheduledTask);
    }

    schedulewithFixedDelay = (task: () => void, executionTime: number, taskType: TaskType, delay: number, unit: TimeUnit) => {
        const scheduledTask = new ScheduledTask(task, executionTime, taskType, delay, unit);
        this._queue.add(scheduledTask);
    }
}