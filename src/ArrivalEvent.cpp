#include "ArrivalEvent.h"
#include "Process.h"
#include "Simulation.h"
#include "CpuTask.h"
#include "StartCpuEvent.h"

ArrivalEvent::ArrivalEvent(int theTime, Process *theProcess, Simulation* sim):Event(theTime,theProcess,sim){
};

/**
 * arrivalEvent事件结束后应当将当前的process的StartCpu事件加入到eventQueue中
**/ 
void ArrivalEvent::handleEvent(){
    /*首先判断当前cpu是否在执行其他任务*/
    Process* process = getProcess();
    if (sim->getCpuBusy() ){
        CpuTask* task = dynamic_cast<CpuTask*>(process->popTask());
        process->setCurrentTask(task);
        sim->submitCpuTask(task);
        sim->LOG(sim->getClkTime(),getProcess()->getID(),"arrival in System: CPU is busy(process will be queued)");
    } else {
        /*表明当前cpu没有在执行其他任务 创建StartIOEvent*/
        CpuTask* task = dynamic_cast<CpuTask*>(process->popTask());
        process->setCurrentTask(task);
        StartCpuEvent* event = new StartCpuEvent(sim->getClkTime(),getProcess(),sim);
        event->setStartTask(task);
        sim->submitEvent(event);
        sim->LOG(sim->getClkTime(),getProcess()->getID(),"arrival in System: CPU is free(process begins execution)");
    }
}
