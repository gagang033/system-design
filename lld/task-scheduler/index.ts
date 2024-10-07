import { ScheduledExecutorService } from "./ScheduledExecutorService";
import { TaskType, TimeUnit } from "./ScheduledTask";

const executor = ScheduledExecutorService.getInstance();

executor.schedule(() => console.log("hi at 200 ms from now"), (Date.now() + 200), TaskType.NONE);

executor.scheduleAtFixedRate(() => console.log("repeating gagan at 2000 ms from now and then every 10s"), (Date.now() + 2000), TaskType.FIXEDRATE, 10, TimeUnit.SECOND);

executor.scheduleAtFixedRate(() => console.log("repeating naveen at 1000 ms from now and then every 1 min"), (Date.now() + 1000), TaskType.FIXEDRATE, 1, TimeUnit.MINUTE);

