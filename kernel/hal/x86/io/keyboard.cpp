#include <base.hpp>
#include <output.hpp>
#include <serial.hpp>
#include <keyboard.hpp>
#include <keymap_DE.hpp>
auto handleIRQ(struct cpu_state* cpu) -> void {
	return MTGosHAL::in.handleIRQ1(cpu);
}
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
		uint8_t keycode=0,scancode=inb(0x60);
		if(scancode==0xFA) {
			response=false;
			return;
		} else if(response && scancode == 0xFE) {
			sendCommand(0xED);
			outb(0x60, (scrolllock) + (numlock<<1) + (capslock<<2));
			return;
		}
		debug << "Keyboard interrupt received.\nGot: 0x" << Base::HEXADECIMAL << (int)scancode;
		bool break_code=false;
		static bool e0_code=false;
		static int e1_code=0;
		static uint16_t e1_prev=0;
		uint8_t tableID=0;
		if((scancode & 0x80 ) && (e1_code || (scancode != 0xE1)) && (e0_code || (scancode != 0xE0))) {
			break_code = true;
			scancode &= ~0x80;
		}
		if(e0_code) {
			if((scancode==0x2A) || (scancode = 0x36)) {
				e0_code = false;
				return;
			}
			keycode=keyboardKeycodes[1][scancode];
			e0_code=false;
		} else if (e1_code == 2) {
			e1_prev |= ((uint16_t) scancode << 8);
			//TODO. translate it, although I might not even use this code
			return;
		} else if (e1_code) {
			e1_prev = scancode;
			e1_code++;
			return;
		} else if (scancode == 0xE0) {
			e0_code = true;
			return;
		} else if (scancode == 0xE1) {
			e1_code = true;
			return;
		} else {
			keycode=keyboardKeycodes[0][scancode];
		}
		//Now put it into the keystate array
		if(break_code)
			keydowns[keycode]=false;
		else
			keydowns[keycode]=true;
		//0x2A 0x36 = Shift
		if(keydowns[0x2A] || keydowns[0x36])
			tableID^=1;
		//0x1D = Ctrl
		if(keydowns[0x1D])
			tableID^=2;
		//0x38 = Alt
		if(keydowns[0x38])
			tableID^=4;
		
		//0x45 = Numlock
		if(keycode==0x45)
			numlock=!numlock;
		//0x3A = CAPS
		if(keycode==0x3A)
			capslock=!capslock;
		//0x46 = Scrolllock
		if(keycode==0x46)
			scrolllock=!scrolllock;

		if(capslock)
			tableID^=1;
		//Correct the LEDs
		sendCommand(0xED);
		outb(0x60, (scrolllock) + (numlock<<1) + (capslock<<2));
		response=true;
		//Convert it into a char
		if(!break_code)
			out << keymap[tableID][keycode];
		debug << " -> 0x" << (int)keycode << ".\n";
	}
	Keyboard::Keyboard(): numlock(true), capslock(false), scrolllock(false), response(false) {
		if(!idt.request(0x21, (void(*)(struct cpu_state*))&handleIRQ)) {
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
		if((ccb&4)) {
			ccb &= ~1;
		} else {
			debug << "Keyboard didn't pass self-test!\nDeactivating IRQ1.\n";
			ccb |= 1;
		}
		sendCommand(0x60);
		outb(0x64, ccb);
	}
}
