#ifndef MULTITASKING_H
#define MULTITASKING_H
#include <idt.hpp>
namespace MTGosHAL {

    class Multitasking
    {
        public:
            Multitasking();
            auto schedule(struct cpu_state* cpu) -> struct cpu_state*;
            uint32_t tss[32];
        protected:
        private:
            auto initTask(uint8_t* stck, uint8_t* user_stck, void(*entry)()) -> struct cpu_state*;
            static auto task_a() -> void;
            static auto task_b() -> void;
            uint8_t stack_a[4096];
            uint8_t stack_b[4096];
            uint8_t user_stack_a[4096];
            uint8_t user_stack_b[4096];
            struct cpu_state* task_states[2];
            int current_task, num_tasks;
    };

} // namespace MTGosHAL

#endif // MULTITASKING_H
