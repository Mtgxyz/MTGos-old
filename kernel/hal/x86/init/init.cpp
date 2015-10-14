#include <base.hpp>
#include <output.hpp>
#include <serial.hpp>
#include <textDISP.hpp>
#include <gdt.hpp>
#include <idt.hpp>
#include <keyboard.hpp>
extern "C" void intr_stub_0(void);
namespace MTGosHAL {
	Serial debug;
	Screen out;
	Screen err;
	Keyboard in;
	IDT idt;
	GDT gdt;
	void main() {
		out << BG_color::BLACK << FG_color::WHITE << "Loading MTGos...\n";
		err << BG_color::BLACK << FG_color::RED;
		debug << "Hello debugger! This is MTGos version 0.0\nThese logs are probably very long, so please redirect the output to a file.\n";
		gdt.setEntry(0, 0, 0, 0);
		gdt.setEntry(1, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
		gdt.setEntry(2, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
		gdt.setEntry(3, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
		gdt.setEntry(4, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
		gdt.setEntry(5, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_TSS     | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
		gdt.setEntry(6, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_TSS     | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
		gdt.apply();
		debug << "We are now creating the IDT.\n";
		for(int i=0;i<256;i++) {
			idt.setEntry(i, (void *)((uint32_t)&intr_stub_0+i*16), SEG_KERNEL, IDT_INTERRUPT_GATE | IDT_SEG_32_BIT | IDT_RING_0 | IDT_USED);
		}
		idt.setEntry(48, (void *)((uint32_t)&intr_stub_0+768), SEG_KERNEL, IDT_TRAP_GATE | IDT_SEG_32_BIT | IDT_RING_0 | IDT_USED);
		idt.setEntry(8, (void *)((uint32_t)&intr_stub_0+128), SEG_DBL_FAULT, IDT_TASK_GATE | IDT_SEG_32_BIT | IDT_RING_0 | IDT_USED);
		idt.apply();
		sti();
		for(;;);
	}
}
typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void init() {
	for(constructor* i = &start_ctors; i != &end_ctors; ++i)
		(*i)();
	MTGosHAL::main();
}
extern "C" void __cxa_pure_virtual() {
	MTGosHAL::debug << "A pure virtual function just got called.\n";
}

