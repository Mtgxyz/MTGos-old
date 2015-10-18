#include <base.hpp>
#include <textDISP.hpp>
#include <Multitasking.h>
#include <serial.hpp>
auto schedule(struct cpu_state* cpu) -> struct cpu_state* {
    return MTGosHAL::tasks.schedule(cpu);
}
namespace MTGosHAL {

Multitasking::Multitasking(): current_task(-1), num_tasks(2)
{
    task_states[0] = initTask(stack_a, task_a);
    task_states[1] = initTask(stack_b, task_b);
    if(!idt.request(0x20,::schedule)) {
        err << "Could not start multitasking\nFatal error; Kernel halted!\n";
        while(true);
            asm volatile("cli; hlt");
    }
}
auto Multitasking::initTask(uint8_t* stck, void(* entry)()) -> struct cpu_state*
{
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
        0x08, //CS
        0x202, // EFLAGS
        (uint32_t) stck, //ESP
        0x10 //SS
    };
    struct cpu_state* state = (struct cpu_state*)(stck+4096-sizeof(new_state));
    *state = new_state;
    return state;
}

auto Multitasking::task_a() -> void
{
    while(true)
        out << "A";
}

auto Multitasking::task_b() -> void
{
    while(true)
        out << "B";
}
auto Multitasking::schedule(struct cpu_state* cpu) -> struct cpu_state*
{
    if(current_task >= 0) {
        task_states[current_task] = cpu;
    }
    current_task++;
    current_task%= num_tasks;
    cpu=task_states[current_task];
    return cpu;
}

} // namespace MTGosHAL
