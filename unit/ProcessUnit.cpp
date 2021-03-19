#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/PriorityQueue.h"
#include "../src/CpuTask.h"
#include "../src/Process.h"
#include "../src/ArrivalEvent.h"
#include "../src/TimeoutEvent.h"

class Simulation;
class Process;
class TimeoutEvent;
class ArrivalEvent;

TEST_CASE( "PriorityQueue are computed", "[PriorityQueue]" ) {
    PriorityQueue* queue = new PriorityQueue();
    Simulation* sim = nullptr;
    Process* process1 = new Process(1,sim);
    Process* process2 = new Process(2,sim);
    CpuTask* task1 = new CpuTask(10,process1,sim);
    queue->enqueue(task1);
    CpuTask* task2 = new CpuTask(5,process2,sim);
    queue->enqueue(task2);
    CpuTask* topTask = dynamic_cast<CpuTask*>(queue->getFront());
    REQUIRE(topTask->getProcess()->getID() == process2->getID());
}

TEST_CASE( "PriorityQueue are computed", "[PriorityQueue]" ) {
    PriorityQueue* queue = new PriorityQueue();
    Simulation* sim = nullptr;
    Process* process1 = new Process(2,sim);
    Process* process2 = new Process(1,sim);
    CpuTask* task1 = new CpuTask(5,process1,sim);
    queue->enqueue(task1);
    CpuTask* task2 = new CpuTask(5,process2,sim);
    queue->enqueue(task2);
    CpuTask* topTask = dynamic_cast<CpuTask*>(queue->getFront());
    REQUIRE(topTask->getProcess()->getID() == process2->getID());
}

TEST_CASE( "PriorityQueue are computed", "[PriorityQueue]" ) {
    PriorityQueue* queue = new PriorityQueue();
    Simulation* sim = nullptr;
    Process* process = new Process(1,sim);
    TimeoutEvent* event1 = new TimeoutEvent(10,process);
    queue->enqueue(event1);
    ArrivalEvent* event2 = new ArrivalEvent(10,process);
    queue->enqueue(event2);
    REQUIRE( typeif(queue->dequeue()) == typeid(class ArrivalEvent*));
}
