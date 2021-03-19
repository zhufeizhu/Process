
#include "Process.h"

#include <vector>

#include "Queue.h"
#include "Simulation.h"
#include "CpuTask.h"
#include "IOTask.h"
#include "ArrivalEvent.h"

Process::Process(int id, Simulation *sim):ID(id),Sim(sim){
    work_queue = new Queue();
    arrival_time = 0;
    work_time = 0;
    exit_time = 0;
}

Process::~Process(){
    delete work_queue;
}

ListItem* Process::popTask(){
	return work_queue->dequeue();
}

ListItem* Process::frontTask(){
    return work_queue->getFront();
}

int Process::getID(){
	return ID;
}

/**
 * 判断当前process中是否还有任务
 * @return true表示还有任务 false表示没有任务
**/
bool Process::hasTask(){
	return !work_queue->isEmpty();
}

ListItem* Process::currentTask(){
    return current_task;
}

void Process::setCurrentTask(ListItem* task){
    current_task = task;
}

typedef std::vector<std::string> StringList;

StringList splitstr(const std::string& str, char tag){
    StringList  li;
    std::string subStr;
 
    //遍历字符串，同时将i位置的字符放入到子串中，当遇到tag（需要切割的字符时）完成一次切割
    //遍历结束之后即可得到切割后的字符串数组
    for(size_t i = 0; i < str.length(); i++){
        if(tag == str[i]){//完成一次切
            if(!subStr.empty()){
                li.push_back(subStr);
                subStr.clear();
            }
        }
        else {//将i位置的字符放入子串
            subStr.push_back(str[i]);
        }
    }
 
    if(!subStr.empty()){ //剩余的子串作为最后的子字符串
        li.push_back(subStr);
    }
    return li;
}

std::vector<int> StringList2int(StringList ss){
	std::vector<int> vi;
	for(int i = 0; i < ss.size(); i++){
		std::string s = ss[i];
		int t = atoi(s.c_str());
		vi.push_back(t);
	}
	return vi;
}

/**
 * 解析当前process的任务流 并将其按照类型分为CpuEven和IOEvent 其中首个为CpuEvent直接插入到cpu_queue中
**/
void Process::Init(std::string str){
	StringList ss = splitstr(str,' ');
	std::vector<int> vi = StringList2int(ss);
    arrival_time = vi[0];
	//将当前process的arrival event入event队列
	ArrivalEvent *event = new ArrivalEvent(vi[0],this,Sim);
    Sim->submitEvent(event);
    /*构造当前process的任务队列*/
	for(int i = 1; i < vi.size(); i++) {
		if(vi[i] > 0) {
			//表明为CPU任务
			ListItem *cpu = new CpuTask(Sim->getClkTime(),this,Sim,vi[i]);
            work_time += vi[i];
			work_queue->enqueue(cpu);
		} else {
			//表明是IO任务
			ListItem *io = new IOTask(Sim->getClkTime(),this,Sim,vi[i]*(-1));
            work_time += vi[i]*(-1);
			work_queue->enqueue(io);
		}
	}
}

int Process::getArrivalTime(){
	return arrival_time;
}

void Process::setExitTime(int time){
    this->exit_time = time;
}

int Process::getWaitingTime(){
    return exit_time - arrival_time - work_time;
}

int Process::getExitTime(){
    return exit_time;
}

int Process::compareTo(ListItem *other){
    Process* otherProcess = dynamic_cast<Process*>(other);
    return otherProcess->getID() -  this->getID();
}
