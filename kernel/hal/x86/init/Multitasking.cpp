#include <base.hpp>
#include <textDISP.hpp>
#include <Multitasking.hpp>
#include <serial.hpp>
#include <blockdev.hpp>
auto schedule(struct cpu_state* cpu) -> struct cpu_state* {
    return MTGosHAL::tasks.schedule(cpu);
}
namespace MTGosHAL {

Multitasking::Multitasking(): current_task(-1), num_tasks(2)
{
  for(int i=0;i<32;i++) {
    if(i==2)
      continue;
    tss[i]=0;
  }
  tss[2]=0x10;
    task_states[0] = initTask(stack_a, user_stack_a, task_a);
    task_states[1] = initTask(stack_b, user_stack_b, task_b);
    if(!idt.request(0x20,::schedule)) {
        err << "Could not start multitasking\nFatal error; Kernel halted!\n";
        while(true);
            asm volatile("cli; hlt");
    }
}
auto Multitasking::initTask(uint8_t* stck, uint8_t* user_stck, void(* entry)()) -> struct cpu_state*
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
        0x18 | 0x03, //CS
        0x202, // EFLAGS
        (uint32_t) user_stck+4096, //ESP
        0x20 | 0x03 //SS
    };
    struct cpu_state* state = (struct cpu_state*)(stck+4096-sizeof(new_state));
    *state = new_state;
    return state;
}

auto Multitasking::task_a() -> void
{
    while(true) {
      char arr[513];
      arr[512]=0;
      disk.readSector(disk.getDriveNumByName("ATA0m"),0,(uint8_t*)arr);
      out << arr;
    }
}

auto Multitasking::task_b() -> void
{
  while(true) {
    char arr[513];
    arr[512]=0;
    disk.readSector(disk.getDriveNumByName("ATA0m"),1,(uint8_t*)arr);
    out << arr;
  }
}
auto Multitasking::schedule(struct cpu_state* cpu) -> struct cpu_state*
{
    if(current_task >= 0) {
        task_states[current_task] = cpu;
    }
    current_task++;
    current_task%= num_tasks;
    cpu=task_states[current_task];
    tss[1]=(uint32_t)(cpu+1);
    return cpu;
}

} // namespace MTGosHAL
