#include "CompleteCpuEvent.h"
#include "Process.h"
#include "CpuTask.h"
#include "StartIOEvent.h"
#include "StartCpuEvent.h"
#include "ExitEvent.h"
#include "Simulation.h"
#include "IOTask.h"

CompleteCpuEvent::CompleteCpuEvent(int theTime, Process* process, Simulation* sim):Event(theTime,process,sim){
};

/**
 * startCpuEvent需要将当前process加入到cpu的工作队列中 
**/
void CompleteCpuEvent::handleEvent(){
    /*根据当前cpu的时间片是否执行完来判断接下来的执行内容*/
    Process *process = getProcess();
    if (process->hasTask()){
        //表明当前还有IO任务 因此可能创建StartIO任务
        CpuTask* task = dynamic_cast<CpuTask*>(process->currentTask());
        if (sim->getBurstTime()){
            //修改当前正在执行的任务
            ListItem* new_task = process->popTask();
            process->setCurrentTask(new_task);
            if (sim->getIOBusy() || sim->frontIOTask()){
                sim->LOG(sim->getClkTime(),process->getID(),"complete CPU burst. Queueing for I/O");
                /*如果IO设备忙的话 就添加到等待队列中*/
                sim->submitIOTask(new_task);
            } else {
                /*否则就创建StartIOEvent*/
                StartIOEvent* event = new StartIOEvent(sim->getClkTime(),process,sim);
                event->setStartTask(dynamic_cast<IOTask*>(new_task));
                sim->submitEvent(event);
                sim->LOG(sim->getClkTime(),getProcess()->getID(),"complete CPU burst.");
            }
        } else {
            //表明时间片已经用完 需要等待下一个cpu时间片才可以创建startIO任务 因此将当前任务放到等待队列中
            CpuTask* task = dynamic_cast<CpuTask*>(process->currentTask());
            sim->submitCpuTask(task);
            sim->LOG(sim->getClkTime(),getProcess()->getID(),"complete CPU burst. waiting for next CPU burst to queue for I/O");
        }
    } else { 
        //表明当前没有I/O任务 创建ExitEvent
        sim->LOG(sim->getClkTime(),getProcess()->getID(),"complete CPU burst.");
        ExitEvent *event = new ExitEvent(sim->getClkTime(),getProcess(),sim);
        sim->submitEvent(event); 
    }
    
    /*切换当前需要执行的CPU任务 创建一个StartCpuEvent即可*/
    CpuTask* task = dynamic_cast<CpuTask*>(sim->popCpuTask());
    if (task){
        StartCpuEvent* event = new StartCpuEvent(sim->getClkTime(),task->getProcess(),sim);
        event->setStartTask(task);
        sim->submitEvent(event);
    }
};
