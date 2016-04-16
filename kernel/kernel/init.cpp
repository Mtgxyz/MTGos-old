#include <base.hpp>
#include <output.hpp>
#include <serial.hpp>
#include <textDISP.hpp>
#include <keyboard.hpp>
#include <Multitasking.h>
#include <blockdev.hpp>
using namespace MTGosHAL;
void task_a() {
  MTGosHAL::out << "a";
}
void task_b() {
  MTGosHAL::out << "b";
}
void task_c() {
  MTGosHAL::out << "c";
}
void task_d() {
  MTGosHAL::out << "d";
}
void main() {
    MTGosHAL::out << "Initializing Kernel!\n";
    MTGosHAL::tasks.initTask(&task_a);
    MTGosHAL::tasks.initTask(&task_b);
    MTGosHAL::tasks.initTask(&task_c);
    MTGosHAL::tasks.initTask(&task_d);
}
