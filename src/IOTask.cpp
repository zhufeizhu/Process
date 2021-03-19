#include "IOTask.h"
#include "CompleteIOEvent.h"
#include "Simulation.h"

IOTask::IOTask(int theTime, Process *theProcess, Simulation* sim, int remainTime):Event(theTime,theProcess,sim){
    remain_time = remainTime;
    work_time = 0;
};

void IOTask::handleEvent(){
    CompleteIOEvent* event = new CompleteIOEvent(sim->getClkTime()+1,getProcess(),sim);
    sim->submitEvent(event);
}

int IOTask::getRemainTime(){
    return remain_time;
}

int IOTask::getWorkTime(){
    return work_time;
}

void IOTask::onUpdate(){
    work_time++;
    remain_time--;
}
