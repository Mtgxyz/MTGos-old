#include <base.hpp>
#include <textDISP.hpp>
#include <Multitasking.hpp>
#include <serial.hpp>
#include <blockdev.hpp>
#include <pmm.hpp>
auto schedule(struct cpu_state* cpu) -> struct cpu_state* {
    return MTGosHAL::tasks.schedule(cpu);
}
namespace MTGosHAL {

Multitasking::Multitasking(): curr_task(nullptr), first_task(nullptr)
{
  for(int i=0;i<32;i++) {
    if(i==2)
      continue;
    tss[i]=0;
  }
  tss[2]=0x10;
    //task_states[0] = initTask(stack_a, user_stack_a, task_a);
    //task_states[1] = initTask(stack_b, user_stack_b, task_b);
    if(!idt.request(0x20,::schedule)) {
        err << "Could not start multitasking\nFatal error; Kernel halted!\n";
        while(true)
          asm volatile("cli; hlt");
    }
}
auto Multitasking::initTask(void(* entry)()) -> struct cpu_state*
{
    void *tmp1, *tmp2;
    mm >> tmp1 >> tmp2;
    uint8_t *stack=(uint8_t*)tmp1, *user_stack=(uint8_t*)tmp2;
    struct cpu_state new_state = {
        0, //EAX
        0, //EBX
        0, //ECX
        0, //EDX
        0, //ESI
        0, //EDI
        0, //EBP
        0, //INTR
        0, //ERROR
        (uint32_t) entry, //EIP
        0x18 | 0x03, //CS
        0x202, // EFLAGS
        (uint32_t) user_stack+4096, //ESP
        0x20 | 0x03 //SS
    };
    struct cpu_state* state = (struct cpu_state*)(stack+4096-sizeof(new_state));
    *state = new_state;
    //Create new task class
    Task* task = new Task(state);
    if(first_task)
      first_task->addTask(task);
    else {
      first_task=task;
    }
    return state;
}
auto Multitasking::schedule(struct cpu_state* cpu) -> struct cpu_state*
{
  Task* next=nullptr;
  if(curr_task) {
    next=curr_task->pause(cpu);
  }
  if (!next) {
    next=first_task;
  }
  curr_task=next;
  return next->unpause();
}
Task::Task(struct cpu_state* cpu): cpu_state(cpu), next(nullptr) {};
//This is run every time this task is chosen by the scheduler
auto Task::unpause() -> struct cpu_state* {
  MTGosHAL::tasks.tss[1] = (uint32_t) (cpu_state + 1);
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
} // namespace MTGosHAL
