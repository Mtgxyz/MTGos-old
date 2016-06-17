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
	void main(int eax, struct multiboot_info* ebx) {
		//Init debug output
    new (&debug) Serial();
    debug << "Hello debugger! This is MTGos v00r01\nThese logs are probably very long, so please redirect the output to a file.\n";

    debug << "Init GDT\n";
    new (&gdt) GDT();
    gdt.setEntry(0, 0, 0, 0);
		gdt.setEntry(1, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
		gdt.setEntry(2, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
		gdt.setEntry(3, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
		gdt.setEntry(4, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
		gdt.setEntry(5, (uint32_t)tasks.tss, sizeof(tasks.tss), GDT_FLAG_RING3 | GDT_FLAG_TSS | GDT_FLAG_PRESENT);
		gdt.setEntry(6, 0, 0xfffff, GDT_FLAG_RING3 | GDT_FLAG_TSS | GDT_FLAG_PRESENT);
		gdt.apply();

    debug << "Init IDT\n";
    new (&idt) IDT();
    for(int i=0;i<256;i++) {
			idt.setEntry(i, (void *)((uint32_t)&intr_stub_0+i*16), SEG_KERNEL, IDT_INTERRUPT_GATE | IDT_SEG_32_BIT | IDT_RING_0 | IDT_USED);
		}
		idt.setEntry(48, (void *)((uint32_t)&intr_stub_0+768), SEG_KERNEL, IDT_TRAP_GATE | IDT_SEG_32_BIT | IDT_RING_3 | IDT_USED);
		idt.setEntry(8, (void *)((uint32_t)&intr_stub_0+128), SEG_DBL_FAULT, IDT_TASK_GATE | IDT_SEG_32_BIT | IDT_RING_0 | IDT_USED);
		idt.apply();
    asm volatile("ltr %%ax" : : "a"(5<<3));
    debug << "Init MM\n";
    new (&mm) PMM(ebx);

    debug << "Init Screen output\n";
    new (&out) Screen(ebx);
    new (&err) Screen(ebx);
		out << BG_color::BLACK << FG_color::WHITE << "Loading MTGos...\n";
		err << BG_color::BLACK << FG_color::RED;

    debug << "Init Keyboard\n";
    new (&in) Keyboard();

		debug << "Init Multitasking\n";
		new (&tasks) Multitasking();

    debug << "Init Disk\n";
    new (&disk) BlockDevice();

    debug << "Kernel initialized\n";
		if(eax!=0x2BADB002)
			err << "System wasn't loaded by a Multiboot-conformant launcher!\n";
    multiboot_mod_list *mods = (multiboot_mod_list*) ebx->mods_addr;
		progs=(void**)mm.alloc(4096);
    for(int i=0;i<1024;i++) {
      progs[i]=nullptr;
    }
		for(uint32_t i=0;i<(ebx->mods_count<1023?ebx->mods_count:1023);i++) { //Basically until MIN(ebx->mods_count, 1023), as we only support loading up to 1023 programs directly.
			progs[i]=(void*)(mods[i].mod_start);
			debug << "Found module!\n";
		}
		::main(progs);
    uint8_t buf[512];
    disk.readSector(disk.getDriveNumByName("ATA0m1"),0,buf);
    out << (char*)buf;
		sti();
		for(;;);
	}
}
typedef void (*constructor)();
typedef void (*destructor)();
extern "C" destructor start_dtors;
extern "C" destructor end_dtors;
extern "C" void init(int eax, struct multiboot_info* ebx) {
	MTGosHAL::main(eax, ebx);
	for(destructor* i = &start_dtors; i != &end_dtors; i++)
		(*i)();
}
extern "C" void __cxa_pure_virtual() {
	MTGosHAL::debug << "A pure virtual function just got called.\n";
}
