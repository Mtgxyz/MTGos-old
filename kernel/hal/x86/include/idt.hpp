#ifndef _IDT_HPP
#define _IDT_HPP
#include <stdint.h>
#define IDT_INTERRUPT_GATE 0x06
#define IDT_TRAP_GATE      0x07
#define IDT_TASK_GATE      0x05
#define IDT_SEG_32_BIT     0x08
#define IDT_RING_0         0x00
#define IDT_RING_3         0x60
#define IDT_USED           0x80
#define SEG_KERNEL         0x08
#define SEG_USER           0x18 /*NEVER USE!!*/
#define SEG_DBL_FAULT      0x28 /*Only use for double fault handler!!*/
extern "C" {
	void loadIDT(void * ptr);
}

namespace MTGosHAL {
	struct cpu_state {
		uint32_t   eax;
		uint32_t   ebx;
		uint32_t   ecx;
		uint32_t   edx;
		uint32_t   esi;
		uint32_t   edi;
		uint32_t   ebp;

		uint32_t   intr;
		uint32_t   error;

		uint32_t   eip;
		uint32_t   cs;
		uint32_t   eflags;
		uint32_t   esp;
		uint32_t   ss;
	};
	class IDT {
		private:
			uint64_t idt[256];
			struct cpu_state* (*ivt[256][16])(struct cpu_state *);
			struct idtp {
				uint16_t limit;
				uint64_t* pointer;
			}__attribute__((packed));
			struct idtp idtptr;
		public:
			IDT();
			auto setEntry(int i, void* offset, uint16_t seg, uint8_t flags) -> void;
			auto apply() -> void;
			auto handle(struct cpu_state* cpu) -> struct cpu_state*;
			auto request(uint8_t intr, struct cpu_state* (*handler)(struct cpu_state*)) -> bool;
	};
}
#endif
