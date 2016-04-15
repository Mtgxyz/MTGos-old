#include <base.hpp>
#include <output.hpp>
#include <serial.hpp>
#include <textDISP.hpp>
#include <gdt.hpp>
#include <idt.hpp>
#include <keyboard.hpp>
#include <Multitasking.hpp>
#include <multiboot.h>
#include <blockdev.hpp>
extern "C" void intr_stub_0(void);
void main();
namespace MTGosHAL {
	Serial debug;
	Screen out;
	Screen err;
	Keyboard in;
	IDT idt;
	GDT gdt;
	Multitasking tasks;
	BlockDevice disk;
	void main(int eax, struct multiboot_info* ebx) {
		out << BG_color::BLACK << FG_color::WHITE << "Loading MTGos...\n";
		err << BG_color::BLACK << FG_color::RED;
		if(eax!=0x2BADB002)
			err << "System wasn't loaded by a Multiboot-conformant launcher!\n";
		debug << "Hello debugger! This is MTGos v00r01\nThese logs are probably very long, so please redirect the output to a file.\n";
		gdt.setEntry(0, 0, 0, 0);
		gdt.setEntry(1, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
		gdt.setEntry(2, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
		gdt.setEntry(3, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
		gdt.setEntry(4, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
		gdt.setEntry(5, (uint32_t)tasks.tss, sizeof(tasks.tss), GDT_FLAG_RING3 | GDT_FLAG_TSS | GDT_FLAG_PRESENT);
		gdt.setEntry(6, 0, 0xfffff, GDT_FLAG_RING3 | GDT_FLAG_TSS | GDT_FLAG_PRESENT);
		gdt.apply();
		asm volatile("ltr %%ax" : : "a"(5<<3));
		debug << "We are now creating the IDT.\n";
		for(int i=0;i<256;i++) {
			idt.setEntry(i, (void *)((uint32_t)&intr_stub_0+i*16), SEG_KERNEL, IDT_INTERRUPT_GATE | IDT_SEG_32_BIT | IDT_RING_0 | IDT_USED);
		}
		idt.setEntry(48, (void *)((uint32_t)&intr_stub_0+768), SEG_KERNEL, IDT_TRAP_GATE | IDT_SEG_32_BIT | IDT_RING_0 | IDT_USED);
		idt.setEntry(8, (void *)((uint32_t)&intr_stub_0+128), SEG_DBL_FAULT, IDT_TASK_GATE | IDT_SEG_32_BIT | IDT_RING_0 | IDT_USED);
		idt.apply();
		::main();
		sti();
		for(;;);
	}
}
typedef void (*constructor)();
typedef void (*destructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" destructor start_dtors;
extern "C" destructor end_dtors;
extern "C" void init(int eax, struct multiboot_info* ebx) {
	for(constructor* i = &start_ctors; i != &end_ctors; ++i)
		(*i)();
	MTGosHAL::main(eax, ebx);
	for(destructor* i = &start_dtors; i != &end_dtors; i++)
		(*i)();
}
extern "C" void __cxa_pure_virtual() {
	MTGosHAL::debug << "A pure virtual function just got called.\n";
}
