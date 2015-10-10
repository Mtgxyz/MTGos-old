#include <base.hpp>
#include <output.hpp>
#include <serial.hpp>
#include <textDISP.hpp>
#include <gdt.hpp>
namespace MTGosHAL {
	Serial* debug;
	Screen* out;
	Screen* err;
	void main() {
		Serial serialOUT(115200);
		Screen display;
		GDT gdt;
		debug=&serialOUT;
		err=&display;
		out=&display;
		*out << BG_color::BLACK << FG_color::WHITE << "Loading MTGos...\n";
		*debug << "Hello debugger! This is MTGos version 0.0\nThese logs are probably very long, so please redirect the output to a file.\n";
		gdt.setEntry(0, 0, 0, 0);
		gdt.setEntry(1, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
		gdt.setEntry(2, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
		gdt.setEntry(3, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
		gdt.setEntry(4, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
		gdt.setEntry(5, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_TSS     | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
		gdt.setEntry(6, 0, 0xfffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | GDT_FLAG_TSS     | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
		gdt.apply();
		for(;;);
	}
}
extern "C" void init() {
	MTGosHAL::main();
}
extern "C" void __cxa_pure_virtual() {
	*MTGosHAL::debug << "A pure virtual function just got called.\n";
}

