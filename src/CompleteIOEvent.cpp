#include "CompleteIOEvent.h"
#include "Process.h"
#include "Simulation.h"
#include "CpuTask.h"
#include "IOTask.h"
#include "StartCpuEvent.h"
#include "StartIOEvent.h"
#include "ExitEvent.h"

CompleteIOEvent::CompleteIOEvent(int theTime, Process* process, Simulation* sim):Event(theTime,process,sim){};

/**
 * 当IOTask执行完成后 需要判断当前process是否有其他cpu任务需要执行 同时将当前IO任务从io queue中移除
**/
void CompleteIOEvent::handleEvent(){
    sim->LOG(sim->getClkTime(),getProcess()->getID(),"complete IO");
    Process* process = getProcess();
    if (process->hasTask()){
        CpuTask* task = dynamic_cast<CpuTask*>(process->popTask());
        process->setCurrentTask(task);
        if(sim->getCpuBusy() || sim->frontCpuTask()){
            sim->submitCpuTask(task);
        } else {
            process->setCurrentTask(task);
            StartCpuEvent* event = new StartCpuEvent(sim->getClkTime(),getProcess(),sim);
            event->setStartTask(task);
            sim->submitEvent(event);
        }
    } else {
        //表明当前没有CPU任务 创建ExitEvent
        ExitEvent *event = new ExitEvent(sim->getClkTime(),getProcess(),sim);
        sim->submitEvent(event); 
    }
    
    IOTask* task = dynamic_cast<IOTask*>(sim->popIOTask());
    if (task) {
        StartIOEvent* event = new StartIOEvent(sim->getClkTime(),task->getProcess(),sim);
        event->setStartTask(task);
        sim->submitEvent(event);
    }
}
