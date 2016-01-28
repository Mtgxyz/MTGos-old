#include <base.hpp>
#include <output.hpp>
#include <serial.hpp>
#include <keyboard.hpp>
#include <keymap_DE.hpp>
auto handleIRQ(struct cpu_state* cpu) -> struct cpu_state* {
	return cpu;
}
namespace MTGosHAL {
	auto Keyboard::getChar() -> char {
		return '\0';
	}
	auto Keyboard::sendCommand(uint8_t command) -> void {
	}
	auto Keyboard::handleIRQ1(struct cpu_state* cpu) -> struct cpu_state* {
		return cpu;
	}
	Keyboard::Keyboard(): numlock(true), capslock(false), scrolllock(false), response(false) {
	}
}
