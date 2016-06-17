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
    double st7;
		double st6;
		double st5;
		double st4;
		double st3;
		double st2;
		double st1;
		double st0;
		uint64_t   rax;
		uint64_t   rbx;
		uint64_t   rcx;
		uint64_t   rdx;
		uint64_t   rsi;
		uint64_t   rdi;
		uint64_t   rbp;
    uint64_t   r8;
    uint64_t   r9;
    uint64_t   r10;
    uint64_t   r11;
    uint64_t   r12;
    uint64_t   r13;
    uint64_t   r14;
    uint64_t   r15;

		uint64_t   intr;
		uint64_t   error;

		uint64_t   rip;
		uint64_t   cs;
		uint64_t   rflags;
		uint64_t   rsp;
		uint64_t   ss;
	};
	class IDT {
		private:
			unsigned __int128 idt[256];
			struct cpu_state* (*ivt[256][16])(struct cpu_state *);
			struct idtp {
				uint16_t limit;
				unsigned __int128* pointer;
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
