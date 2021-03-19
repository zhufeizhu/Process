#pragma once
#include "Event.h"

class CompleteIOEvent:public Event{
public:
    CompleteIOEvent(int theTime, Process* process, Simulation* sim);

    void handleEvent();
};