#pragma once
#include "Event.h"

class CpuTask;

class StartCpuEvent:public Event{
private:
    CpuTask* task;
public:
    StartCpuEvent(int theTime,Process *process,Simulation *sim);

    /**
     * startCpuEvent需要将当前process加入到cpu的工作队列中 
    **/
    void handleEvent();
    
    inline void setStartTask(CpuTask* task){
        this->task = task;
    };
    
    inline CpuTask* getStartTask(){
        return task;
    };
};
