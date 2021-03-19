#include "StartIOEvent.h"
#include "Process.h"
#include "IOTask.h"
#include "Simulation.h"

StartIOEvent::StartIOEvent(int theTime, Process* process, Simulation* sim):Event(theTime,process,sim){}

void StartIOEvent::handleEvent(){
    /*当前任务交给IO执行*/
    IOTask* task = getStartTask();
    sim->runIOTask(task);
    sim->LOG(sim->getClkTime(),getProcess()->getID(),"begis I/O burst");
};
