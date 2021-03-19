#pragma once
#include "Event.h"

class ArrivalEvent:public Event{
private:
    int remain_time;
public:
    ArrivalEvent(int theTime, Process *theProcess, Simulation* sim);

    void handleEvent();
};