#ifndef _GDT_HPP
#define _GDT_HPP
#include <stdint.h>
#define GDT_FLAG_DATASEG 0x02
#define GDT_FLAG_CODESEG 0x0a
#define GDT_FLAG_TSS     0x09

#define GDT_FLAG_SEGMENT 0x10
#define GDT_FLAG_RING0   0x00
#define GDT_FLAG_RING3   0x60
#define GDT_FLAG_PRESENT 0x80

#define GDT_FLAG_4K_GRAN 0x800
#define GDT_FLAG_32_BIT  0x400
#define GDT_FLAG_64_BIT  0x200
extern "C" void loadGDT(void * gdtpr);
namespace MTGosHAL {
	class GDT {
		private:
			uint64_t gdt[7];
			struct gdtp {
				uint16_t limit;
				void* pointer;
			} __attribute__((packed));
			struct gdtp fin;
		public:
			GDT();
			auto setEntry(int i, unsigned int base, unsigned int limit, int flags) -> void;
			auto apply() -> void;
	};
}
#endif
