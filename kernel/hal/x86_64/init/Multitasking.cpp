#include <base.hpp>
#include <textDISP.hpp>
#include <Multitasking.hpp>
#include <serial.hpp>
#include <blockdev.hpp>
#include <idt.hpp>
#include <pmm.hpp>
namespace MTGosHAL {
auto schedule(struct cpu_state* cpu) -> struct cpu_state* {
    return MTGosHAL::tasks.schedule(cpu);
}
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
    if(!idt.request(0x20,MTGosHAL::schedule)) {
        err << "Could not start multitasking\nFatal error; Kernel halted!\n";
        while(true)
          asm volatile("cli; hlt");
    }
}
auto Multitasking::initTask(void(* entry)()) -> struct cpu_state*
{
    void* tmp1, *tmp2;
    mm >> tmp1 >> tmp2;
    uint8_t *stack=(uint8_t*)tmp1, *user_stack=(uint8_t*)tmp2;
    struct cpu_state new_state = {
        0.0, //ST0
        0.0, //ST1
        0.0, //ST2
        0.0, //ST3
        0.0, //ST4
        0.0, //ST5
        0.0, //ST6
        0.0, //ST7
        0, //RAX
        0, //RBX
        0, //RCX
        0, //RDX
        0, //RSI
        0, //RDI
        0, //RBP
        0, //R8
        0, //R9
        0, //r10
        0, //r11
        0, //r12
        0, //r13
        0, //r14
        0, //r15
        0, //INTR
        0, //ERROR
        (uint64_t) entry, //RIP
        0x18 | 0x03, //CS
        0x202, // RFLAGS
        (uint64_t) user_stack+0x200000, //RSP
        0x20 | 0x03 //SS
    };
    struct cpu_state* state = (struct cpu_state*)(stack+0x200000-sizeof(new_state));
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
    struct cpu_state* cpu_state=next->unpause();
    MTGosHAL::tasks.tss[1] = (uint32_t) (uint64_t)(cpu_state + 1);
    return cpu_state;
}
} // namespace MTGosHAL
