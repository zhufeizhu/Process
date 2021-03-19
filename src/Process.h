#pragma once 

#include <string>

#include "ListItem.h"

class Simulation;
class Queue;
class ListItem;
class Event;

class Process: public ListItem{
private:
	int ID;
	Simulation* Sim;
	Queue *work_queue;
	int arrival_time;
    int exit_time;
    int work_time;
	ListItem* current_task;
public:
	Process(int id, Simulation *sim);
    ~Process();
	void Init(std::string str);
	bool hasTask();
	ListItem* popTask();
	ListItem* frontTask();
	ListItem* currentTask();
	void setCurrentTask(ListItem*);
    void setExitTime(int);
	int getID();
	int getArrivalTime();
    int getWaitingTime();
    int getExitTime();
    int compareTo(ListItem *other);
    
};// class process
