#pragma once
#include "Event.h"

class TimeoutEvent:public Event{
public:
    TimeoutEvent(int theTime, Process *process, Simulation *sim);
    void handleEvent();
};