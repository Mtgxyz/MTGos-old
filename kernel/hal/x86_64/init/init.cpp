#include <base.hpp>
#include <output.hpp>
#include <serial.hpp>
#include <textDISP.hpp>
#include <keyboard.hpp>
#include <Multitasking.hpp>
#include <multiboot.h>
#include <blockdev.hpp>
#include <gdt.hpp>
#include <idt.hpp>
#include <pmm.hpp>
extern "C" void intr_stub_0(void);
void main(void ** programs, MTGosHAL::Serial debug, MTGosHAL::PMM mm, MTGosHAL::Screen out,
    MTGosHAL::Screen err, MTGosHAL::Keyboard in, MTGosHAL::Multitasking tasks, MTGosHAL::BlockDevice disk);
void** progs;
namespace MTGosHAL {
    Serial debug;
    GDT gdt;
    IDT idt;
    PMM mm;
    Screen out;
    Screen err;
    Keyboard in;
    Multitasking tasks;
    BlockDevice disk;
    struct multiboot_info* ebx;
    void main(long eax, struct multiboot_info* mb, uint64_t**** pt) {
        ebx=mb;
        new (&debug) Serial();
        debug << "Hello debugger! This is MTGos v00r01\nThese logs are probably very long, so please redirect the output to a file.\n";
        debug << "Init Screen output\n";
        new (&out) Screen(ebx);
        new (&err) Screen(ebx);
        out << BG_color::BLACK << FG_color::WHITE << "Loading MTGos...\n";
        err << BG_color::BLACK << FG_color::RED;
        debug << "Init GDT\n";
        new (&gdt) GDT();
        gdt.setEntry(0, 0, 0, 0);
        gdt.setEntry(1, 0, 0, GDT_FLAG_PRESENT | GDT_FLAG_64_BIT | GDT_FLAG_4K_GRAN | GDT_FLAG_RING0 | GDT_FLAG_SEGMENT | GDT_FLAG_CODESEG);
        gdt.setEntry(2, 0, 0, GDT_FLAG_PRESENT | GDT_FLAG_32_BIT | GDT_FLAG_4K_GRAN | GDT_FLAG_RING0 | GDT_FLAG_SEGMENT | GDT_FLAG_DATASEG);
        gdt.setEntry(3, 0, 0, GDT_FLAG_PRESENT | GDT_FLAG_64_BIT | GDT_FLAG_4K_GRAN | GDT_FLAG_RING3 | GDT_FLAG_SEGMENT | GDT_FLAG_CODESEG);
        gdt.setEntry(4, 0, 0, GDT_FLAG_PRESENT | GDT_FLAG_32_BIT | GDT_FLAG_4K_GRAN | GDT_FLAG_RING3 | GDT_FLAG_SEGMENT | GDT_FLAG_DATASEG);
        gdt.setEntry(5, (uint64_t)tasks.tss, sizeof(tasks.tss), GDT_FLAG_RING0 | GDT_FLAG_TSS | GDT_FLAG_PRESENT);
        gdt.setEntry(6, 0, 0, GDT_FLAG_RING3 | GDT_FLAG_TSS | GDT_FLAG_PRESENT);
        gdt.apply();

        debug << "Init IDT\n";
        new (&idt) IDT();
        for(int i=0;i<256;i++) {
            idt.setEntry(i, (void *)((uint64_t)&intr_stub_0+i*32), SEG_KERNEL, IDT_INTERRUPT_GATE | IDT_SEG_32_BIT | IDT_RING_0 | IDT_USED);
        }
        idt.setEntry(48, (void *)((uint64_t)&intr_stub_0+768*2), SEG_KERNEL, IDT_TRAP_GATE | IDT_SEG_32_BIT | IDT_RING_3 | IDT_USED);
        idt.setEntry(8, (void *)((uint64_t)&intr_stub_0+128*2), SEG_DBL_FAULT, IDT_TASK_GATE | IDT_SEG_32_BIT | IDT_RING_0 | IDT_USED);
        idt.apply();
        asm volatile("int $49"); // Finish loading GDT
  }
  auto startup() -> void {
        //asm volatile("ltr %%ax" : : "a"(5<<3));
        
        out << "Init MM\n";
        new (&mm) PMM(ebx);


        out << "Init Keyboard\n";
        new (&in) Keyboard();

        out << "Init Multitasking\n";
        new (&tasks) Multitasking();

        out << "Init blockdev\n";
        new (&disk) BlockDevice();
        out << "Kernel initialized\n";
        multiboot_mod_list *mods = (multiboot_mod_list*) (uint64_t)(ebx->mods_addr);
        progs=(void**)mm.alloc(8192);
        for(int i=0;i<1024;i++) {
            progs[i]=nullptr;
        }
        for(uint32_t i=0;i<(ebx->mods_count<1023?ebx->mods_count:1023);i++) { //Basically until MIN(ebx->mods_count, 1023), as we only support loading up to 1023 programs directly.
            progs[i]=(void*)((uint64_t)mods[i].mod_start);
            out << "Found module!\n";
        }
        ::main(progs, debug, mm, out, err, in, tasks, disk);

  }
}
typedef void (*constructor)();
typedef void (*destructor)();
extern "C" destructor start_dtors;
extern "C" destructor end_dtors;
extern "C" void init(int eax, struct multiboot_info* ebx, uint64_t**** ecx) {
    MTGosHAL::main(eax, ebx,ecx);
    for(destructor* i = &start_dtors; i != &end_dtors; i++)
        (*i)();
}
extern "C" void __cxa_pure_virtual() {
    MTGosHAL::debug << "A pure virtual function just got called.\n";
}
