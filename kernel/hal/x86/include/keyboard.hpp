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
			static auto handleIRQ1(struct cpu_state* cpu) -> void;
			bool shift, numlock, caps, scrollock;
		public:
			Keyboard();
	};
}
#endif // -Wno-pmf-conversions 
