#ifndef _BASE_HPP
#define _BASE_HPP
#include <stdint.h>
void * operator new (size_t, void * p);
void * operator new[] (size_t, void * p);
void operator delete (void *, void *);
void operator delete[] (void *, void *);
namespace MTGosHAL {
	class Output;
	class Input;
	class Serial;
	class Screen;
	class Keyboard;
	class GDT;
	class IDT;
	class Multitasking;
	class BlockDevice;
	class Task;
	class PMM;
	enum class BG_color: uint32_t;
	enum class FG_color: uint32_t;
	extern Serial debug;
	extern Screen out;
	extern Screen err;
	extern Keyboard in;
	extern GDT gdt;
	extern IDT idt;
	extern Multitasking tasks;
	extern BlockDevice disk;
	extern PMM mm;
}
#endif
