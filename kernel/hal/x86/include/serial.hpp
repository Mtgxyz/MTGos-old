#ifndef _SERIAL_HPP
#define _SERIAL_HPP
#include <output.hpp>
#include <input.hpp>
#include <textDISP.hpp>
#include <io.h>
#define SERIAL_IER 1
#define SERIAL_IIR 2
#define SERIAL_FCR 2
#define SERIAL_LCR 3
#define SERIAL_MCR 4
#define SERIAL_LSR 5
#define SERIAL_MSR 6
namespace MTGosHAL {
	class Serial: public Output, public Input {
		private:
			uint16_t port;
			uint64_t waittimes;
			uint64_t transmits;
			auto isTransmitEmpty() -> int;
			auto putChar(char chr) -> void;
			auto serial_received() -> int;
			auto getChar() -> char;
		public:
			Serial(uint32_t baud);
			auto debug() -> void;
	};
}

#endif
