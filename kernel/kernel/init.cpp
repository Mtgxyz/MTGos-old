#include <base.hpp>
#include <output.hpp>
#include <serial.hpp>
#include <textDISP.hpp>
#include <keyboard.hpp>
#include <Multitasking.hpp>
#include <blockdev.hpp>
#include <elf.hpp>
#include <pmm.hpp>
#include <partitions.hpp>
void * operator new (size_t, void * p)  { return p ; }
void * operator new[] (size_t, void * p)  { return p ; }
void operator delete (void *, void *)  { }
void operator delete[] (void *, void *)  { }
using namespace MTGosHAL;
void pid_null() {
    for(;;);
}
void task_a() {
    while(true)
        out << "a";
}
void task_b() {
    while(true)
        out << "b";
}
void task_c() {
    while(true)
        out << "c";
}
void task_d() {
    while(true)
        out << "d";
}
void main(void ** files, MTGosHAL::Serial &debug, MTGosHAL::PMM &mm, MTGosHAL::Screen &out,
    MTGosHAL::Screen &err, MTGosHAL::Keyboard &in, MTGosHAL::Multitasking &tasks, MTGosHAL::BlockDevice &disk) {
    out << "Initializing Kernel!\n";
    Elf32_Ehdr** programs=(Elf32_Ehdr**)files;
    tasks.initTask(&pid_null);
    for(int i=0;programs[i];i++) {
        void(*start)()=(void(*)())load(programs[i]);
        if(!start)
            continue;
        tasks.initTask(start);
    }
    out << "checking ata0 partitions...\n";
    MBR::MBR part(disk.getDriveNumByName("ATA0m"));
    out << "Partition 1: beg=" << (int32_t) part.getPartBeg(0) << " end=" << (int32_t)part.getPartEnd(0) << "\n";
    out << "Partition 2: beg=" << (int32_t)part.getPartBeg(1) << " end=" << (int32_t)part.getPartEnd(1) << "\n";
    out << "Partition 3: beg=" << (int32_t)part.getPartBeg(2) << " end=" << (int32_t)part.getPartEnd(2) << "\n";
    out << "Partition 4: beg=" << (int32_t)part.getPartBeg(3) << " end=" << (int32_t)part.getPartEnd(3) << "\n";
}
