#include "StartCpuEvent.h"
#include "CpuTask.h"
#include "Process.h"
#include "Simulation.h"
#include "CompleteCpuEvent.h"

StartCpuEvent::StartCpuEvent(int theTime,Process *process,Simulation *sim):Event(theTime,process,sim){
}

/**
 * startCpuEvent需要将当前process加入到cpu的工作队列中 
**/
void StartCpuEvent::handleEvent(){
    /*将当前任务交给CPU执行*/
    CpuTask* task = getStartTask();
    int time = task->getRemainTime() - sim->getCpuTime();
    sim->runCpuTask(task);
    
    if (time > 0){
        sim->LOG(sim->getClkTime(),getProcess()->getID(),"begins Cpu burst ( will time out)" );
    } else {
        sim->LOG(sim->getClkTime(),getProcess()->getID(),"begin Cpu burst (will complete all)");
        if(task->getRemainTime() == 0){
            CompleteCpuEvent* event = new CompleteCpuEvent(sim->getClkTime(),getProcess(),sim);
            sim->submitEvent(event);
            sim->clearCpu();
        }
    }
    
};
