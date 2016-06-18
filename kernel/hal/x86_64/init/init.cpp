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
void main(void ** programs);
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
  void main(long eax, struct multiboot_info* ebx, uint64_t**** pt) {
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
		gdt.setEntry(1, 0, 0, 0x298);
		gdt.setEntry(2, 0, 0, 0x292);
		gdt.setEntry(3, 0, 0, 0x2F8);
		gdt.setEntry(4, 0, 0, 0x2F2);
		gdt.setEntry(5, (uint64_t)tasks.tss, sizeof(tasks.tss), GDT_FLAG_RING3 | GDT_FLAG_TSS | GDT_FLAG_PRESENT);
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
    asm volatile("ltr %%ax" : : "a"(5<<3));

    debug << "Init MM\n";
    new (&mm) PMM(ebx);


    debug << "Init Keyboard\n";
    new (&in) Keyboard();
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
