#include "Event.h"
#include "TimeoutEvent.h"
#include "Simulation.h"
#include "Process.h"
#include "CpuTask.h"
#include "StartCpuEvent.h"

TimeoutEvent::TimeoutEvent(int theTime, Process *process, Simulation *sim):Event(theTime,process,sim){
};

/**
 * Timeout触发后, 表明当前process的CpuTask并未完成 需要将当前CpuTask移动到work_queue中等待执行
**/
void TimeoutEvent::handleEvent(){
    Process* process = getProcess();
    if (sim->getCpuBusy()){
        /*表明当前cpu正在被使用 需要将自己塞入到cpu pending queue中*/
        CpuTask* old_task = dynamic_cast<CpuTask*>(process->currentTask());
        sim->submitCpuTask(old_task);
    } else {
        /*表明cpu没有被使用 需要根据是否有pending queue中是否有代执行的任务来决定*/
        CpuTask* task = dynamic_cast<CpuTask*>(sim->frontCpuTask());
        if (task){
            sim->popCpuTask();
            StartCpuEvent* event = new StartCpuEvent(sim->getClkTime(),task->getProcess(),sim);
            event->setStartTask(task);
            sim->submitEvent(event);
            CpuTask* old_task = dynamic_cast<CpuTask*>(process->currentTask());
            sim->submitCpuTask(old_task);
        } else {
            StartCpuEvent* event = new StartCpuEvent(sim->getClkTime(),process,sim);
            CpuTask* old_task = dynamic_cast<CpuTask*>(process->currentTask());
            event->setStartTask(old_task);
            sim->submitEvent(event);
        }
    }
    sim->LOG(sim->getClkTime(),getProcess()->getID(),"time out, need n units more");
}
