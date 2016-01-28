#include <base.hpp>
#include <output.hpp>
#include <serial.hpp>
#include <textDISP.hpp>
#include <keyboard.hpp>
#include <Multitasking.h>
extern "C" void intr_stub_0(void);
namespace MTGosHAL {
	Serial debug;
	Screen out;
	Screen err;
	Keyboard in;
	Multitasking tasks;
	void main() {
		out << BG_color::BLACK << FG_color::WHITE << "Loading MTGos...\n";
		err << BG_color::BLACK << FG_color::RED;
		debug << "Hello debugger! This is MTGos v00r01\nThese logs are probably very long, so please redirect the output to a file.\n";
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

