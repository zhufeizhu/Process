#include "CpuTask.h"

#include "Simulation.h"
#include "CompleteCpuEvent.h"
#include "TimeoutEvent.h"
#include "StartCpuEvent.h"
#
CpuTask::CpuTask(int theTime, Process *theProcess, Simulation* sim, int remainTime):Event(theTime,theProcess,sim){
    work_time = 0;
    remain_time = remainTime;
};

/**
 * 当前时间片用尽或者任务执行完成 生成对应的event到event queue中
**/
void CpuTask::handleEvent(){
    if (remain_time == 0 ){
        
        CompleteCpuEvent* event = new CompleteCpuEvent(sim->getClkTime()+1,getProcess(),sim);
        sim->submitEvent(event);
    } else {
        /*表明时间片用完后还有任务未完成 此时出发timeout*/
        TimeoutEvent* event = new TimeoutEvent(sim->getClkTime()+1,getProcess(),sim);
        sim->submitEvent(event);
    }
}

void CpuTask::onUpdate(){
    //执行时间的更新
    work_time++;
    remain_time--;
}

int CpuTask::getWorkTime(){
    return work_time;
}

int CpuTask::getRemainTime(){
    return remain_time;
}
