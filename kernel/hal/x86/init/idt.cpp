#include <base.hpp>
#include <io.h>
#include <idt.hpp>
#include <serial.hpp>
#include <textDISP.hpp>
#include <vmm3.hpp>
auto syscall(uint32_t syscall_num, void* handle, void* args) -> void*;
extern void** progs;
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
	auto IDT::handle(struct cpu_state* cpu) -> struct cpu_state* {
    struct cpu_state* new_cpu=cpu;
		debug << "Interrupt 0x" << Base::HEXADECIMAL << (int) cpu->intr << " was raised.\n";
		if(cpu->intr<=0x1F) {
			err << "Exception 0x" << Base::HEXADECIMAL << (int) cpu->intr << "! Kernel halted!\n";
      err << "EAX = 0x" << (int)cpu->eax << " - EBX = 0x" << (int)cpu->ebx << "\n";
      err << "ECX = 0x" << (int)cpu->ecx << " - EDX = 0x" << (int)cpu->edx << "\n";
      err << "ESI = 0x" << (int)cpu->esi << " - EDI = 0x" << (int)cpu->edi << "\n";
      err << "SS:ESP = 0x" << (int)cpu->ss << ":0x" << (int)cpu->esp << " - SS:EBP = 0x" << (int)cpu->ss << ":0x" << (int)cpu->ebp << "\n";
      err << "CS:EIP = 0x" << (int)cpu->cs << ":0x" << (int)cpu->eip << " - INTR:ERR = 0x" << (int)cpu->intr << ":0x" << (int)cpu->error << "\n";
      err << "------ END OF REGISTER DUMP ------   ------ START OF PROGRAM LOADPOINTS ------\n";
      for(int i=0;i<1024;i++) {
        if(!progs[i])
          break;
        err << "0x" << (int)((uint32_t)progs[i]) << "; ";
      }
      err << "\n";
      uint16_t counter = 1193180 / 220; //Make an annoying beep
      outb(0x43, 0xB6);
      outb(0x42, (uint8_t)counter);
      outb(0x42, (uint8_t)(counter>>8));
      outb(0x61, inb(0x61) | 3);
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
				new_cpu=ivt[cpu->intr][i](new_cpu);
		}
    if(cpu->intr>=48)
      new_cpu->eax=(uint32_t)(::syscall(cpu->eax, (void*)(cpu->ebx), (void*)(cpu->esp)));
		return new_cpu;
	}
	auto IDT::request(uint8_t intr, struct cpu_state* (*handler)(struct cpu_state*)) -> bool {
		for(int i=0;i<16;i++) {
			if(ivt[intr][i])
				continue;
			ivt[intr][i]=handler;
			return true;
		}
		return false;
	}
}
extern "C" void* handleINT(void* cpu) {
	return (void*)MTGosHAL::idt.handle((MTGosHAL::cpu_state*)cpu);
}
