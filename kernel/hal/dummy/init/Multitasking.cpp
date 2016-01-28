#include <base.hpp>
#include <textDISP.hpp>
#include <Multitasking.h>
#include <serial.hpp>
/*auto schedule(struct cpu_state* cpu) -> struct cpu_state* {
    return MTGosHAL::tasks.schedule(cpu);
}*/
namespace MTGosHAL {

Multitasking::Multitasking(): current_task(-1), num_tasks(2)
{
    task_states[0] = initTask(stack_a, task_a);
    task_states[1] = initTask(stack_b, task_b);
}
auto Multitasking::initTask(uint8_t* stck, void(* entry)()) -> struct cpu_state*
{
    return nullptr;
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
	return nullptr;
}

} // namespace MTGosHAL
