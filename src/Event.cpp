#include "Event.h"

#include <typeinfo>

#include "ArrivalEvent.h"
#include "TimeoutEvent.h"
#include "CpuTask.h"
#include "IOTask.h"
#include "Simulation.h"
#include "Process.h"
/**** Event implementation */

Event::Event(){};

Event::Event(int theTime, Process *theProcess, Simulation *theSim) 
	 :eventTime(theTime), process(theProcess), sim (theSim) {}


int Event::compareTo(ListItem *other){
	//首先比较event_time event_time较小着优先级较高
	Event* other_event = dynamic_cast<Event*>(other);
	if (this->getEventTime() < other_event->getEventTime()) {
		return 1;
	} else if (this->getEventTime() > other_event->getEventTime()){
		return -1;
	} else {
		//优先考虑特殊情况 TimeoutEvent对ArrivalEvent在时间相同的情况下优先级较高
		if(typeid(this) == typeid(class ArrivalEvent*) && typeid(other_event) == typeid(class TimeoutEvent *)){
			return 1;
		}

		if(typeid(other_event) == typeid(class ArrivalEvent *) && typeid(this) == typeid(class TimeoutEvent*)){
			return -1;
		}
		// 如果时间相同就比较process的id,较小者优先级较高
		if (this->getProcess()->getID() < other_event->getProcess()->getID()) {
			return 1;
		} else {
			return -1;
		}
	}
}

Process* Event::getProcess(){
	return process;
}

/**
 * 获取当前event开始的时间
**/
int Event::getEventTime(){
	return eventTime;
}

void Event::setEventTime(int time){
	eventTime = time;
}



