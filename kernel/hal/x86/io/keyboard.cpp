#include <base.hpp>
#include <output.hpp>
#include <serial.hpp>
#include <keyboard.hpp>
namespace MTGosHAL {
	auto Keyboard::getChar() -> char {
		char chr=buf[0];
		for(int i=0;i<15;i++) {
			buf[i]=buf[i+1];
		}
		buf[15]='\0';
		if(len)
			len--;			
		return chr;
	}
	auto Keyboard::sendCommand(uint8_t command) -> void {
		while((inb(0x64) & 0x2));
		outb(0x60, command);
	}
	auto Keyboard::handleIRQ1(struct cpu_state* cpu) -> void {
		debug << "Keyboard interrupt received.\nGot: 0x" << Base::HEXADECIMAL << (int) inb(0x60) << ".\n";
	}
	Keyboard::Keyboard(): shift(false), numlock(true), caps(false), scrollock(false) {
		if(!idt.request(0x21, (void(*)(struct cpu_state*))&MTGosHAL::Keyboard::handleIRQ1)) {
			debug << "Could not get an handler for IRQ1 (Keyboard)\n";
			return;
		}
		//Clear keyboard buffer
		while(inb(0x64) & 0x1) {
			inb(0x60);
		}
		sendCommand(0xF4); //Activate keyboard
		//Check for self-test being passed
		sendCommand(0x20);
		uint8_t ccb=inb(0x60);
		if(!(ccb&4)) {
			debug << "Keyboard didn't pass self-test!\nDeactivating IRQ1.\n";
			ccb &= ~1;
		} else {
			ccb |= 1;
		}
		sendCommand(0x60);
		outb(0x64, ccb);
	}
}
