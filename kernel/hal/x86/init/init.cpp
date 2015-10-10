#include <base.hpp>
#include <output.hpp>
#include <serial.hpp>
#include <textDISP.hpp>
namespace MTGosHAL {
	Serial* debug;
	Screen* out;
	Screen* err;
	void main() {
		Serial serialOUT(115200);
		Screen display;
		debug=&serialOUT;
		err=&display;
		out=&display;
		*out << BG_color::BLACK << FG_color::WHITE << "Loading MTGos...\n";
		*debug << "Hello debugger! This is MTGos version 0.0\nThese logs are probably very long, so please redirect the output to a file.\n";
		for(;;);
	}
}
extern "C" void init() {
	MTGosHAL::main();
}
extern "C" void __cxa_pure_virtual() {
	*MTGosHAL::debug << "A pure virtual function just got called.\n";
}

