#include <base.hpp>
#include <output.hpp>
#include <serial.hpp>
#include <textDISP.hpp>
#include <keyboard.hpp>
#include <Multitasking.hpp>
#include <blockdev.hpp>
#include <elf.hpp>
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
    MTGosHAL::out << "a";
}
void task_b() {
  while(true)
    MTGosHAL::out << "b";
}
void task_c() {
  while(true)
    MTGosHAL::out << "c";
}
void task_d() {
  while(true)
    MTGosHAL::out << "d";
}
void main(void** files) {
  MTGosHAL::out << "Initializing Kernel!\n";
  Elf32_Ehdr** programs=(Elf32_Ehdr**)files;
  MTGosHAL::tasks.initTask(&pid_null);
  for(int i=0;programs[i];i++) {
    void(*start)()=(void(*)())load(programs[i]);
    if(!start)
      continue;
    MTGosHAL::tasks.initTask(start);
  }
}
