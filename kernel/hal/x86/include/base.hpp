#ifndef _BASE_HPP
#define _BASE_HPP
#include <stdint.h>
namespace MTGosHAL {
	class Output;
	class Input;
	class Serial;
	class Screen;
	class Keyboard;
	class GDT;
	class IDT;
	enum class BG_color: uint16_t;
	enum class FG_color: uint16_t;
	extern Serial debug;
	extern Screen out;
	extern Screen err;
	extern Keyboard in;
	extern GDT gdt;
	extern IDT idt;
}
#endif
