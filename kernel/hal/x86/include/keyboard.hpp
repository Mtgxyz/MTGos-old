	#ifndef _KEYBOARD_HPP
#define _KEYBOARD_HPP
#include <stdint.h>
#include <input.hpp>
#include <io.h>
#include <idt.hpp>
namespace MTGosHAL {

	class Keyboard: public Input {
		private:

			//This kernel has a buffer of 16 chars
			char buf[16];
			int len;
			auto getChar() -> char;
			auto sendCommand(uint8_t command) -> void;
			bool numlock, capslock, scrolllock, response;
		public:
			auto handleIRQ1(struct cpu_state* cpu) -> struct cpu_state*;
			Keyboard();
	};
}
#endif // -Wno-pmf-conversions
