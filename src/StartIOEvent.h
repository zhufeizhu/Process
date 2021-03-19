#pragma once
#include "Event.h"

class IOTask;

class StartIOEvent:public Event{
private:
    IOTask* task;
public:
    StartIOEvent(int theTime,Process* process, Simulation* sim);
    /**
     * startIOEvent需要将当前process加入到io的工作队列中 
    **/
    void handleEvent();
    
    void setStartTask(IOTask* task){
        this->task = task;
    }
    
    IOTask* getStartTask(){
        return task;
    }

};
