#include <base.hpp>
#include <serial.hpp>
namespace MTGosHAL {
	auto Serial::isTransmitEmpty() -> int {
		return inb(port+SERIAL_LSR)&0x20;
	}
	auto Serial::putChar(char chr) -> void {
		while(!isTransmitEmpty())
			waittimes++;
		outb(port, chr);
		transmits++;
	}
	auto Serial::serial_received() -> int {
		return inb(port+SERIAL_LSR)&1;
	}
	auto Serial::getChar() -> char {
		//We try 500 times to get a character
		int tries=500;
		while(!serial_received()) {
			tries--;
			waittimes++;
			if(!tries) {
				return '\0';
			}
		}
		transmits++;
		char chr = inb(port);
		if(chr!='\r')
			*this << chr;
		else
			*this << '\n';
		return chr;
	}
	Serial::Serial(uint32_t baud) {
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
	auto Serial::debug() -> void {
		if(getChar()) {
			*this << "The interactive debug shell was started.\n> ";
			*out << "The debug shell was started.\n";
			char buf[256];
			*out << buf << "\nDebug shell closed.\n";
			*this << "Unknown command. TODO\n";
		}
		uint64_t wt = waittimes;
		uint64_t tm = transmits;
		*this << "Transmit stats: " << (int32_t)wt << " times waited; " << (int32_t)tm << " bytes transferred.\n";
		waittimes=transmits=0;
	}
}
