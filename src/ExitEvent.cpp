#include "ExitEvent.h"
#include "Simulation.h"
#include "Process.h"

ExitEvent::ExitEvent(int theTime, Process *process, Simulation *sim):Event(theTime,process,sim){};

    /**
     * process执行完所有的任务后执行Exit流程
    **/
void ExitEvent::handleEvent(){
    sim->LOG(sim->getClkTime(),getProcess()->getID(),"process finish all task and exit");
    Process* process = getProcess();
    process->setExitTime(sim->getClkTime());
    sim->submitExitProcess(process);
    return;
}
