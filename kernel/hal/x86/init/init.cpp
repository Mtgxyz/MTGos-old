#include <output.hpp>
#include <serial.hpp>
namespace MTGosHAL {
	Serial serialOUT(115200);
	void main() {
		serialOUT=Serial(115200);
		serialOUT << "This is the debug output of MTGos\n";
	}
}
extern "C" void init() {
	MTGosHAL::main();
}
extern "C" void __cxa_pure_virtual() {
	for(;;);
}

