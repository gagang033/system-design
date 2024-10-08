#include <bits/stdc++.h>
using namespace std;
enum TimeUnit
{
    SECOND,
    MINUTE,
    HOUR
};
enum TaskType
{
    NONE,
    FIXEDRATE,
    FIXEDDELAY
};
map<TimeUnit, long> delayMap;
long getCurrentTimeMillis()
{
    auto now = chrono::system_clock::now();

    // Convert to time since epoch (January 1, 1970) in milliseconds
    auto duration = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch());

    // Return the count of milliseconds
    return duration.count();
}
class ScheduledTask
{
private:
    function<void()> _task;
    TaskType _taskType;
    long _executionTime;
    TimeUnit _unit;
    long _delay = 0;

public:
    ScheduledTask(function<void()> task, TaskType taskType, long executionTime)
    {
        this->_task = task;
        this->_taskType = taskType;
        this->_executionTime = executionTime;
    }
    ScheduledTask(function<void()> task, TaskType taskType, long executionTime, TimeUnit unit, long delay)
    {
        this->_task = task;
        this->_taskType = taskType;
        this->_executionTime = executionTime;
        this->_delay = delay;
        this->_unit = unit;
    }

    void execute()
    {
        this->_task();
    }

    long executionTime()
    {
        return this->_executionTime;
    }

    TaskType taskType()
    {
        return this->_taskType;
    }

    long nextExecutionTime()
    {
        return _taskType == TaskType::FIXEDRATE ? this->_delay * delayMap[this->_unit] + _executionTime : this->_delay * delayMap[this->_unit] + getCurrentTimeMillis();
    }

    void executionTime(long executionTime)
    {
        this->_executionTime = executionTime;
    }
};
class Compare
{
public:
    bool operator()(ScheduledTask *a, ScheduledTask *b)
    {
        return a->executionTime() > b->executionTime();
    }
};
class ScheduledExecutorService
{
private:
    static ScheduledExecutorService *_scheduledExecutorService;
    static priority_queue<ScheduledTask *, vector<ScheduledTask *>, Compare> pq;
    ScheduledExecutorService() {}
    static mutex mtx;

public:
    static ScheduledExecutorService *getInstance()
    {
        if (ScheduledExecutorService::_scheduledExecutorService == nullptr)
        {
            mtx.lock();
            if (ScheduledExecutorService::_scheduledExecutorService == nullptr)
            {
                ScheduledExecutorService::_scheduledExecutorService = new ScheduledExecutorService();
            }
            mtx.unlock();
        }
        return ScheduledExecutorService::_scheduledExecutorService;
    }
    static void _execute()
    {
        if (ScheduledExecutorService::pq.empty())
        {
            this_thread::sleep_for(chrono::milliseconds(500));
            ScheduledExecutorService::_execute();
        }
        else
        {
            // cout<<ScheduledExecutorService::pq.top()->executionTime()<<endl;
            // cout<<ScheduledExecutorService::getCurrentTimeMillis()<<endl;
            while (!ScheduledExecutorService::pq.empty() && ScheduledExecutorService::pq.top()->executionTime() <= getCurrentTimeMillis())
            {
                ScheduledTask *sTask = ScheduledExecutorService::pq.top();
                // cout<<sTask->taskType()<<endl;
                ScheduledExecutorService::pq.pop();
                sTask->execute();
                if (sTask->taskType() == TaskType::FIXEDDELAY || sTask->taskType() == TaskType::FIXEDRATE)
                {
                    sTask->executionTime(sTask->nextExecutionTime());
                    ScheduledExecutorService::pq.push(sTask);
                }
            }
            this_thread::sleep_for(chrono::milliseconds(500));
            ScheduledExecutorService::_execute();
        }
    }

    /**
     * Creates and executes a one-shot action that becomes enabled after the given delay.
     */
    void schedule(function<void()> task, long delay, TimeUnit unit)
    {
        ScheduledTask *sTask = new ScheduledTask(task, TaskType::NONE, delay * delayMap[unit] + getCurrentTimeMillis());
        ScheduledExecutorService::pq.push(sTask);
    }

    /**
     * Creates and executes a periodic action that becomes enabled first after the given initial delay, and
     * subsequently with the given period; that is executions will commence after initialDelay then
     * initialDelay+period, then initialDelay + 2 * period, and so on.
     */
    void scheduleAtFixedRate(function<void()> task, long initialDelay, long period, TimeUnit unit)
    {
        ScheduledTask *sTask = new ScheduledTask(task, TaskType::FIXEDRATE, initialDelay * delayMap[unit] + getCurrentTimeMillis(), unit, period);
        ScheduledExecutorService::pq.push(sTask);
    }

    /*
     * Creates and executes a periodic action that becomes enabled first after the given initial delay, and
     * subsequently with the given delay between the termination of one execution and the commencement of the next.
     */
    void scheduleWithFixedDelay(function<void()> task, long initialDelay, long delay, TimeUnit unit)
    {
        ScheduledTask *sTask = new ScheduledTask(task, TaskType::FIXEDDELAY, initialDelay * delayMap[unit] + getCurrentTimeMillis(), unit, delay);
        ScheduledExecutorService::pq.push(sTask);
    }
};
void normalTask()
{
    cout << "normal hi with 1s delay" << endl;
}
void fixedRateTask()
{
    cout << "repeating gagan with 2s delay and then 3s" << endl;
}
void fixedDelayTask()
{
    cout << "repeating naveen with 1s delay and then 10s" << endl;
}
void scheduleTasks()
{
    ScheduledExecutorService *obj = ScheduledExecutorService::getInstance();
    obj->schedule(normalTask, 1, TimeUnit::SECOND);
    obj->scheduleAtFixedRate(fixedRateTask, 2, 3, TimeUnit::SECOND);
    obj->scheduleWithFixedDelay(fixedDelayTask, 1, 10, TimeUnit::SECOND);
}
priority_queue<ScheduledTask *, vector<ScheduledTask *>, Compare> ScheduledExecutorService::pq;
mutex ScheduledExecutorService::mtx;
ScheduledExecutorService *ScheduledExecutorService::_scheduledExecutorService = nullptr;
int main()
{
    delayMap[TimeUnit::SECOND] = 1000;
    delayMap[TimeUnit::MINUTE] = 60000;
    delayMap[TimeUnit::HOUR] = 3600000;
    thread t1(ScheduledExecutorService::_execute);
    thread t2(scheduleTasks);
    t1.join();
    t2.join();
    return 0;
}