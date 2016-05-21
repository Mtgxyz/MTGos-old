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
#include <pmm.hpp>
extern "C" void intr_stub_0(void);
void main(void ** programs);
namespace MTGosHAL {
	Serial debug;
	Screen out;
	Screen err;
	Keyboard in;
	IDT idt;
	GDT gdt;
	Multitasking tasks;
	BlockDevice disk;
	PMM mm;
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
		mm.init(ebx);
    debug << "Now tesing the PMM... Allocating 1 byte\n";
    char* tmp=(char*)mm.alloc(1);
    debug << "Allocating another byte\n";
    char* tmp2=(char*)mm.alloc(1);
    tmp2[0]='A';
    debug << "Freeing the first byte...\n";
    mm.free((void*)tmp);
    debug << "Allocating 14 bytes... \n";
    tmp=(char*)mm.alloc(14);
    debug << "Changing the last byte... \n";
    tmp[13]='B';
    debug << "Changing if the second byte has changed...\n";
    if(tmp2[0]=='B') {
      err << "The allocate function is broken.\n";
      debug << "The allocate function is broken.\n";
    } else {
      debug << "The allocate function works!\n";
    }
    debug << "Freeing up both pointers.";
    mm.free((void*)tmp);
    mm.free((void*)tmp2);
    multiboot_mod_list *mods = (multiboot_mod_list*) ebx->mods_addr;
		void** progs=(void**)mm.alloc(4096);
		uint32_t i;
		for(i=0;i<(ebx->mods_count<1023?ebx->mods_count:1023);i++) { //Basically until MIN(ebx->mods_count, 1023), as we only support loading up to 1023 programs directly.
			progs[i]=(void*)(mods[i].mod_start);
			debug << "Found module!\n";
		}
		i++;
		progs[i]=nullptr;
		::main(progs);
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
