#ifndef MULTITASKING_H
#define MULTITASKING_H
#include <cpu_state.h>
namespace MTGosHAL {

  class Multitasking
  {
      public:
          Multitasking();
          auto schedule(struct cpu_state* cpu) -> struct cpu_state*;
          auto initTask(void(*entry)()) -> struct cpu_state*;
      protected:
      private:
          Task* first_task;
          Task* curr_task;
  };
  class Task
  {
  private:
    struct cpu_state* cpu_state;
    Task* next;
  public:
    Task(struct cpu_state*);
    auto unpause() -> struct cpu_state*;
    auto pause(struct cpu_state*) -> Task *;
    auto addTask(Task*) -> void;
    auto hasNext() -> bool;
  };

} // namespace MTGosHAL

#endif // MULTITASKING_H
