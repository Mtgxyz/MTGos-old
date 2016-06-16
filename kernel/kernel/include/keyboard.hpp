#ifndef _KEYBOARD_HPP
#define _KEYBOARD_HPP
#include <stdint.h>
#include <input.hpp>
namespace MTGosHAL {

	class Keyboard: public Input {
		private:

			//This kernel has a buffer of 16 chars
			char buf[16];
			int len;
			auto getChar() -> char;
		public:
			auto handleIRQ1(struct cpu_state* cpu) -> struct cpu_state*;
			Keyboard();
	};
}
#endif // -Wno-pmf-conversions
