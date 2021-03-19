#pragma once
#include "Event.h"

class CpuTask: public Event{
private:
    bool init; //表明当前是否为Init
    int work_time; //记录当前CpuTask从首个StartCpu开始执行的时间
    int remain_time; //记录当前CpuTask剩余需要工作的时间
public:
    CpuTask(int theTime, Process *theProcess, Simulation* sim, int remainTime);

    /**
     * 当前时间片用尽或者任务执行完成 生成对应的event到event queue中
    **/
    void handleEvent();

    void onUpdate();

    int getWorkTime();

    int getRemainTime();
};