#ifndef _SERIAL_HPP
#define _SERIAL_HPP
#include <output.hpp>
#include <io.h>
#define SERIAL_IER 1
#define SERIAL_IIR 2
#define SERIAL_FCR 2
#define SERIAL_LCR 3
#define SERIAL_MCR 4
#define SERIAL_LSR 5
#define SERIAL_MSR 6
namespace MTGosHAL {
	class Serial: public Output {
		private:
			uint16_t port;
			auto isTransmitEmpty() -> int {
				return inb(port+SERIAL_LSR)&0x20;
			}
			auto putChar(char chr) -> void {
				while(!isTransmitEmpty());
				outb(port, chr);
			}
			auto puts(const char* s) -> void {
				int i=0;
				while(s[i]!='\0')
					putChar(s[i++]);
			}
		public:
			Serial(uint32_t baud) {
				port=*((uint16_t*)0x0400);
				union {
					uint8_t b[2];
					uint16_t w;
				} divisor;
				divisor.w = 115200/baud;
				//Turn off interrupts
				outb(port+SERIAL_IER, 0x00);
				//Set DLAB-bit
				outb(port+SERIAL_LCR, 0x80);
				//Set baud divisor
				outb(port, divisor.b[0]);
				outb(port+1, divisor.b[1]);
				//Set bit count, parity and reset DLAB 
				outb(port+SERIAL_LCR, 3);
				//Finish init
				outb(port+SERIAL_FCR, 0xC7);
				outb(port+SERIAL_MCR, 0x0B);
			}
	};
}

#endif
