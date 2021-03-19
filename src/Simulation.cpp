#include "Simulation.h"

#include <iomanip>
#include <streambuf>

#include "ArrivalEvent.h"
#include "CpuTask.h"
#include "IOTask.h"
#include "PriorityQueue.h"
#include "Queue.h"
#include "Process.h"

using std::ifstream;
using std::ios;
using std::setiosflags;
using std::setw;

Simulation::Simulation()
{
    cpu_queue = new Queue();
    io_queue = new Queue();
    cpu = new CPU(this);
    io_device = new IO_DEVICE(this);
    event_queue = new PriorityQueue();
    summary_queue = new PriorityQueue();
}

Simulation::~Simulation(){
    delete cpu_queue;
    delete io_queue;
    delete cpu;
    delete event_queue;
    delete summary_queue;
}

void Simulation::runSimulation(char *fileName)
{

    /*获取cpu时间*/
    int process_index = 1;
    ifstream in(fileName);
    string cpu_time_s;
    getline(in, cpu_time_s);
    setCpuTime(atoi(cpu_time_s.c_str()));

    //首先获取首个Process的信息
    Process *curProcess = getNewProcess(in, process_index);
    clock_time = curProcess->getArrivalTime();
    while (true && in.peek() != EOF)
    {
        Process *next = getNewProcess(in, process_index);
        if (next->getArrivalTime() > clock_time)
        {
            curProcess = next;
            break;
        }
    }
    while (true)
    {
        //首先判断当前时间要做的事情
        //1. 判断当前时间是否有新的process来
        if (clock_time == curProcess->getArrivalTime())
        {
            /*需要检测是否有新的process到来*/
            while (true && in.peek() != EOF)
            {
                Process *next = getNewProcess(in, process_index);
                if (next->getArrivalTime() > clock_time)
                {
                    curProcess = next;
                    break;
                }
            }
            /*标记当前有新到的process*/
            setArrival(true);
        }
        //2. 开始处理消息队列
        Event *event = NULL;
        while (true)
        {
            event = dynamic_cast<Event *>(frontEvent());
            if (!event || event->getEventTime() != clock_time)
            {
                break;
            }
            else
            {
                popEvent();
                event->handleEvent();
            }
        }

        //3.更新时钟
        update();

        setArrival(false);

        if (!getCpuBusy() && !getIOBusy() && cpu_queue->isEmpty() && io_queue->isEmpty() && event_queue->isEmpty() && in.peek() == EOF)
            break;
    }
    in.close();
}

/**
 * 判断当前cpu是否有任务在执行
**/
bool Simulation::getCpuBusy()
{
    return cpu->isBusy();
}

int Simulation::getBurstTime()
{
    return cpu->getBurstTime();
}

bool Simulation::getIOBusy()
{
    return io_device->isBusy();
}

/**
 * 设置当前cpu为空闲或忙碌 一般有任务在执行即为忙碌
**/
void inline Simulation::setCpuBusy(bool busy)
{
    cpu_busy = busy;
}

void Simulation::update()
{
    cpu->Update();
    io_device->Update();
    clock_time++;
    if (cpu->getBurstTime()  == 0 ){
        cpu->resetBurstTime();
    }
}

void Simulation::summary()
{
    cout << setiosflags(ios::right) << setw(15) << "Process" << setw(15) << "Arriaval" << setw(15) << "Exit" << setw(15) << "Wait\n";
    cout << setiosflags(ios::right) << setw(15) << "#" << setw(15) << "Time" << setw(15) << "Time" << setw(15) << "Time\n";
    for (int i = 0; i < 8; i++)
    {
        cout << "----------";
    }
    cout << "\n";
    while (!summary_queue->isEmpty())
    {
        Process *process = dynamic_cast<Process *>(summary_queue->dequeue());
        cout << setiosflags(ios::right) << setw(15) << process->getID() << setw(15) << process->getArrivalTime() << setw(15) << process->getExitTime() << setw(15) << process->getWaitingTime() << "\n";
    }
}

void Simulation::runCpuTask(CpuTask *task)
{
    cpu->runTask(task);
}

void Simulation::runIOTask(IOTask *task)
{
    io_device->runTask(task);
}

/**
 * 向simulation的cpu_queue提交任务 这里需要考虑优先队列
 * @param item:要提交的cpuEvent
**/
void Simulation::submitCpuTask(ListItem *item)
{
    cpu_queue->enqueue(item);
}

int Simulation::getClkTime()
{
    return clock_time;
}

/**
 * 向simulation的io_queue提交任务
 * @param item:要提交的IOEvent
**/
void Simulation::submitIOTask(ListItem *item)
{
    io_queue->enqueue(item);
}

/**
 *  完成某个CPU任务 并执行其handleEvent
**/
ListItem *Simulation::popCpuTask()
{
    return cpu_queue->dequeue();
}


ListItem* Simulation::frontCpuTask(){
    return cpu_queue->getFront();
}


ListItem* Simulation::frontIOTask(){
    return io_queue->getFront();
}

/**
 *  完成某个IO任务 并执行其handleEvent
**/
ListItem *Simulation::popIOTask()
{
    return io_queue->dequeue();
}

ListItem *Simulation::popEvent()
{
    return event_queue->dequeue();
}

ListItem *Simulation::frontEvent()
{
    return event_queue->getFront();
}

/**
 * 将event入队列 其中每个event对应一个需要处理的事件 
**/
void Simulation::submitEvent(ListItem *item)
{
    //将event入队列
    event_queue->enqueue(item);
}

void Simulation::LOG(int clk, int id, string msg)
{
    std::cout << "Time\t" << clk << ":Process\t" << id << "\t" << msg << std::endl;
}

Process *Simulation::getNewProcess(ifstream &in, int &process_id)
{
    if (!in)
    {
        return nullptr;
    }
    else
    {
        string line;
        getline(in, line);
        Process *process = new Process(process_id++, this);
        process->Init(line);
        return process;
    }
}

void Simulation::submitExitProcess(ListItem *item)
{
    summary_queue->enqueue(item);
}

CPU::CPU(Simulation *sim) : sim(sim)
{
    this->task = NULL;
    this->burst_time = 0;
    this->busy = false;
}

void CPU::resetBurstTime(){
    burst_time = sim->getBurstTime();
}

void CPU::Update()
{
    if (this->task && this->busy)
    {
        burst_time--;
        this->task->onUpdate();
        if (burst_time == 0)
        {
            /*同时调用CpuTask的handleEvent方法*/
            this->task->handleEvent();
            this->busy = false;
            this->task = NULL;
        }
        else if (task->getRemainTime() == 0)
        {
            /*表明当前cpu task完成了任务 调用handleEvent方法*/
            this->task->handleEvent();
            this->busy = false;
            this->task = NULL;
        }
    }
}

void CPU::clear(){
    this->task = NULL;
    this->busy = false;
};

void IO_DEVICE::clear(){
    this->task = NULL;
    this->busy = false;
};

void Simulation::clearCpu(){
    cpu->clear();
}

void Simulation::clearIO(){
    io_device->clear();
}

void CPU::runTask(CpuTask *task)
{
    /*仅在空闲时可以使用*/
    if (!busy)
    {
        this->task = task;
        burst_time = sim->getCpuTime();
        busy = true;
    }
}

IO_DEVICE::IO_DEVICE(Simulation *sim)
{
    task = NULL;
    busy = false;
    sim = sim;
}

void IO_DEVICE::Update()
{
    if (task && busy)
    {
        task->onUpdate();
        if (!task->getRemainTime())
        {
            task->handleEvent();
            busy = false;
            task = NULL;
        }
    }
}

void IO_DEVICE::runTask(IOTask *task)
{
    /*仅在空闲时可以使用*/
    if (!busy)
    {
        this->task = task;
        busy = true;
    }
}
