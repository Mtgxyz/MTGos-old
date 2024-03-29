#include <base.hpp>
#include <io.h>
#include <idt.hpp>
#include <serial.hpp>
#include <textDISP.hpp>
#include <pmm.hpp>
bool epicfail=false;
auto syscall(uint32_t syscall_num, void* handle, void* args) -> void*;
extern void** progs;
namespace MTGosHAL {
    auto startup() -> void;
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
        idt[i]=(uint16_t)((uint64_t)offset);
        idt[i]|=(unsigned __int128)(((uint64_t)offset)>>16)<<48;
        idt[i]|=((unsigned __int128)seg)<<16;
        idt[i]|=((unsigned __int128)flags)<<40;
    }
    auto IDT::apply() -> void {
        debug << "Now trying to load the IDT.\n";
        idtptr.limit=(uint16_t)(256*8-1);
        idtptr.pointer=(unsigned __int128*)&idt;
        loadIDT((void*)&idtptr);
    }
    auto IDT::handle(struct cpu_state* cpu) -> struct cpu_state* {
        struct cpu_state* new_cpu=cpu;
        debug << "Interrupt 0x" << Base::HEXADECIMAL << (int) cpu->intr << " was raised.\n";
        if(cpu->intr<=0x1F) {
            if(epicfail) {
                err << "While trying to output the stack another exception happened\n";
                while(1) {
                    asm volatile("cli; hlt");
                }
            }
            epicfail=true;
            err << "Exception 0x" << Base::HEXADECIMAL << (int) cpu->intr << "! Kernel halted!\n";
            err << "RAX = 0x" << (int)cpu->rax << " - RBX = 0x" << (int)cpu->rbx << "\n";
            err << "RCX = 0x" << (int)cpu->rcx << " - RDX = 0x" << (int)cpu->rdx << "\n";
            err << "RSI = 0x" << (int)cpu->rsi << " - RDI = 0x" << (int)cpu->rdi << "\n";
            err << "SS:RSP = 0x" << (int)cpu->ss << ":0x" << (int)cpu->rsp << " - SS:RBP = 0x" << (int)cpu->ss << ":0x" << (int)cpu->rbp << "\n";
            err << "CS:RIP = 0x" << (int)cpu->cs << ":0x" << (int)cpu->rip << " - INTR:ERR = 0x" << (int)cpu->intr << ":0x" << (int)cpu->error << "\n";
            err << "------ END OF REGISTER DUMP ------   ------ START OF PROGRAM LOADPOINTS ------\n";
            for(int i=0;i<1024;i++) {
                if(!progs[i])
                break;
                err << "0x" << (int)((uint64_t)progs[i]) << "; ";
            }
            err << "\n";
            uint16_t counter = 1193180 / 220; //Make an annoying beep
            outb(0x43, 0xB6);
            outb(0x42, (uint8_t)counter);
            outb(0x42, (uint8_t)(counter>>8));
            //outb(0x61, inb(0x61) | 3);
            err << "A detailled traceback is being output over the serial connector.\n";
            debug << "Outputting 32 stacks...\n";
            uint64_t *rsp=(uint64_t*)cpu->rsp;
            uint64_t *rbp=(uint64_t*)cpu->rbp;
            uint64_t *rip=(uint64_t*)cpu->rip;
            for(int i=0;i<32;i++) {
                if(!(rsp||rbp||rip))
                    break;
                if((int64_t)(rbp-rsp)<1)
                    break;
                debug << Base::HEXADECIMAL << "Execution at 0x" << (int64_t) rip << ":\n";
                debug << "Number of local variables: 0x" << (int64_t)(rbp-rsp)-1 << "\n";
                for(uintptr_t i=0;i<(uintptr_t)(rbp-rsp)-1;i++) {
                    debug << "0x"<< (int64_t)(i*8) << ": 0x" << (int64_t)rsp[i] << "\n";
                }
                rip=(uint64_t*)rbp[1];
                rsp=rbp;
                rbp=(uint64_t*)rbp[0];
            }
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
        if(cpu->intr==48)
            new_cpu->rax=(uint64_t)(::syscall(cpu->rax, (void*)(cpu->rbx), (void*)(cpu->rsp)));
            if(cpu->intr==49) {
                startup();
                for(int i=0;i<16;i++) {
                    if(ivt[0x20][i])
                        new_cpu=ivt[0x20][i](new_cpu);
                }
            }
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
