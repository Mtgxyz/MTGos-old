#include <base.hpp>
#include <textDISP.hpp>
#include <Multitasking.hpp>
namespace MTGosHAL {
    Task::Task(struct cpu_state* cpu): cpu_state(cpu), next(nullptr) {};
    //This is run every time this task is chosen by the scheduler
    auto Task::unpause() -> struct cpu_state* {
        return cpu_state;
    }
    //This is run every time the timer ticks and a task is running
    auto Task::pause(struct cpu_state* cpu) -> Task * {
        cpu_state=cpu;
        return next;
    }
    auto Task::addTask(Task* task) -> void {
        if(next)
            return next->addTask(task);
        next=task;
    }
    auto Task::hasNext() -> bool {
        return next!=nullptr;
    }
}
