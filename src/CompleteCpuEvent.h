#pragma once
#include "Event.h"

class CompleteCpuEvent:public Event{
public:
    CompleteCpuEvent(int theTime, Process* process, Simulation* sim);
    void handleEvent();
};