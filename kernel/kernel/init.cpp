#include <base.hpp>
#include <output.hpp>
#include <serial.hpp>
#include <textDISP.hpp>
#include <keyboard.hpp>
#include <Multitasking.h>
#include <blockdev.hpp>
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
void main() {
    MTGosHAL::out << "Initializing Kernel!\n";
    MTGosHAL::tasks.initTask(&pid_null);
    MTGosHAL::tasks.initTask(&task_a);
    MTGosHAL::tasks.initTask(&task_b);
    MTGosHAL::tasks.initTask(&task_c);
    MTGosHAL::tasks.initTask(&task_d);
}
