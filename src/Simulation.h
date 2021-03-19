#pragma once

#include <string>
#include <iostream>
#include <fstream>

class PriorityQueue;
class CPU;
class IO_DEVICE;
class IOTask;
class Process;
class CpuTask;
class ListItem;
class Queue;

using std::cout;
using std::string;
using std::ifstream;

class Simulation {
private:
	// you will need to add fields
	int cpu_time;
	Queue *cpu_queue; // cpu的等待队列
	Queue *io_queue;  // io的等待队列
	PriorityQueue *event_queue; //event的等待队列
    PriorityQueue *summary_queue; //总结的队列
	int clock_time;
	bool cpu_busy;
	CPU *cpu;
	IO_DEVICE *io_device;
	bool arrival;
    // including: Queues for CPU and IO, and priority queues for Events 	
public:
	Simulation();
    
    ~Simulation();

	// runSimulation -- start the simulation with the given filename.
	// Called by main.
	void runSimulation(char *fileName); 

	// summary -- print a summary of all the processes, as shown in the
	// assignment.  Called by main.
	void summary();
    
    void submitExitProcess(ListItem*);

	void submitCpuTask(ListItem *item);

	void submitIOTask(ListItem *item);

	void submitEvent(ListItem *item);

	ListItem* popIOTask();

	ListItem* popCpuTask();

	ListItem* popEvent();

	bool getCpuBusy();

	bool getIOBusy();

	void inline setCpuBusy(bool busy);

	void updateCpuTask();

	void updateIOTask();

	void runCpuTask(CpuTask* task);

	void runIOTask(IOTask* task);

	void update();

	Process* getNewProcess(ifstream &in, int &process_id);
	// you may need to add more methods

	int getClkTime();

	void LOG(int, int, string msg);

	void inline setCpuTime(int cpuTime){
		cpu_time = cpuTime;
	}

	int inline getCpuTime(){
		return cpu_time;
	}

	bool inline getArrival(){
		return arrival;
	}

	void inline setArrival(bool Arrival){
		arrival = Arrival;
	}
    
    int getBurstTime();
    
    ListItem* frontEvent();
    
    void clearCpu();
    
    void clearIO();
    
    ListItem* frontCpuTask();

	ListItem* frontIOTask();

};// class Simulation

class CPU{
private:
	CpuTask* task;
	int burst_time;
	bool busy;
	Simulation* sim;
public:
	CPU(Simulation* sim);

	bool inline isBusy(){
		return busy;
	}
    
    int inline getBurstTime(){
        return burst_time;
    }
    
	void runTask(CpuTask* task);

	void Update();
    
    void clear();
    
    void resetBurstTime();
};

class IO_DEVICE{
private:
	IOTask* task;
	bool busy;
	Simulation *sim;
public:
	IO_DEVICE(Simulation *sim);

	void runTask(IOTask* task);

	void Update();
    
    void clear();

	bool inline isBusy(){
		return busy;
	}
};

