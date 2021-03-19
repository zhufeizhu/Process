#pragma once
#include "Event.h"

class ExitEvent:public Event{
public:
    ExitEvent(int theTime, Process *process, Simulation *sim);
    void handleEvent();
};