#include <base.hpp>
#include <serial.hpp>
namespace MTGosHAL {
	auto Serial::isTransmitEmpty() -> int {
		return 0;
	}
	auto Serial::putChar(char chr) -> void {
	}
	auto Serial::serial_received() -> int {
		return 0;
	}
	auto Serial::getChar() -> char {
		return '\0';
	}
	Serial::Serial(): works(true) {
	}
	auto Serial::debug() -> void {
	}
}
