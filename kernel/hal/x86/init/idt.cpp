#include <base.hpp>
#include <io.h>
#include <idt.hpp>
#include <serial.hpp>
#include <textDISP.hpp>
namespace MTGosHAL {
	IDT::IDT() {
		//Init PIC
		outb(0x20, 0x11); //Init Master-PIC
		outb(0x21, 0x20); //Interrupt number for IRQ0
		outb(0x21, 0x04); //IRQ is the Slave
		outb(0x21, 0x01); //ICW 4
		outb(0xA0, 0x11); //Init Master-PIC
		outb(0xA1, 0x28); //Interrupt number for IRQ8
		outb(0xA1, 0x02); //IRQ is the Slave
		outb(0xA1, 0x01); //ICW 4
		//Activate IRQ's
		outb(0x21, 0x00);
		outb(0xA1, 0x00);
	}
	auto IDT::setEntry(int i, void* offset, uint16_t seg, uint8_t flags) -> void {
		idt[i]=(uint16_t)((uint32_t)offset);
		idt[i]|=(uint64_t)(((uint32_t)offset)>>16)<<48;
		idt[i]|=((uint64_t)seg)<<16;
		idt[i]|=((uint64_t)flags)<<40;
	}
	auto IDT::apply() -> void {
		debug << "Now trying to load the IDT.\n";
		idtptr.limit=(uint16_t)(256*8-1);
		idtptr.pointer=(uint64_t*)&idt;
		loadIDT((void*)&idtptr);
	}
	auto IDT::handle(struct cpu_state* cpu) -> void {
		debug << "Interrupt 0x" << Base::HEXADECIMAL << (int) cpu->intr << " was raised.\n";
		if(cpu->intr<=0x1F) {
			out << "Exception 0x" << Base::HEXADECIMAL << (int) cpu->intr << "! Kernel halted!\n";
			while(1) {
				asm volatile("cli; hlt");
			}
		} else if(cpu->intr >= 0x20 && cpu->intr <= 0x2F) {
			if(cpu->intr >= 0x28) {
				outb(0xA0, 0x20);
			}
			outb(0x20, 0x20);
			debug << "The IRQ " << Base::DECIMAL << (int) cpu->intr-0x20 << " was handled.\n";
			if(cpu->intr==0x20) {
				debug.debug();
			}
		}
		for(int i=0;i<16;i++) {
			if(ivt[cpu->intr][i])
				ivt[cpu->intr][i](cpu);
		}
	}
	auto IDT::request(uint8_t intr, void (*handler)(struct cpu_state*)) -> bool {
		for(int i=0;i<16;i++) {
			if(ivt[intr][i])
				continue;
			ivt[intr][i]=handler;
			return true;
		}
		return false;
	}
}
extern "C" void handleINT(struct cpu_state* cpu) {
	MTGosHAL::idt.handle(cpu);
}
