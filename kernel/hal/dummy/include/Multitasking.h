#ifndef MULTITASKING_H
#define MULTITASKING_H
namespace MTGosHAL {

  class Multitasking
  {
      public:
          Multitasking();
          auto schedule(struct cpu_state* cpu) -> struct cpu_state*;
          auto initTask(void(*entry)()) -> struct cpu_state*;
          uint32_t tss[32];
      protected:
      private:
          static auto task_a() -> void;
          static auto task_b() -> void;
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
  };

} // namespace MTGosHAL

#endif // MULTITASKING_H
