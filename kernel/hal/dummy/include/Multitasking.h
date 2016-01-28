#ifndef MULTITASKING_H
#define MULTITASKING_H
namespace MTGosHAL {

    class Multitasking
    {
        public:
            Multitasking();
            auto schedule(struct cpu_state* cpu) -> struct cpu_state*;
        protected:
        private:
            auto initTask(uint8_t* stck, void(*entry)()) -> struct cpu_state*;
            static auto task_a() -> void;
            static auto task_b() -> void;
            uint8_t stack_a[4096];
            uint8_t stack_b[4096];
            struct cpu_state* task_states[2];
            int current_task, num_tasks;
    };

} // namespace MTGosHAL

#endif // MULTITASKING_H
