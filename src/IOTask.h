#pragma once
#include "Event.h"

class IOTask:public Event{
private:
    int work_time;
    int remain_time;
public:
    IOTask(int theTime, Process *theProcess, Simulation* sim, int remainTime);

    void handleEvent();

    int getRemainTime();

    int getWorkTime();

    void onUpdate();
};