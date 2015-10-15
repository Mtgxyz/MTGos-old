#include <base.hpp>
#include <textDISP.hpp>
int x=0, y=0;
namespace MTGosHAL {
	auto Screen::putChar(char c) -> void {
		switch(c) {
			case '\n':
				x=0; y++;
				break;
			case '\r':
				x=0;
				
				break;
			case '\b':
				x--;
				if(x<0) x=0;
				putChar(' ');
				x--;
				if(x<0) x=0;
				break;
			case '\0':
				break;
			default:
				vmem[y*SCREEN_WIDTH+(x++)]=((uint16_t)fg) | ((uint16_t)bg) | ((uint8_t)c);
				if(x==SCREEN_WIDTH) {
					x=0; y++;
				}
				break;
		}
		if(y>SCREEN_HEIGHT)
			scroll();
	}	
	auto Screen::clrscr() -> void {
		for(int p=0; p<SCREEN_HEIGHT*SCREEN_WIDTH+SCREEN_WIDTH; p++)
			vmem[p]=((uint16_t)fg) | ((uint16_t)bg) | ((uint16_t)' ');
		x=y=0;
	}
	auto Screen::scroll() -> void {
		for(int p=0; p<SCREEN_HEIGHT*SCREEN_WIDTH; p++)
			vmem[p]=vmem[p+SCREEN_WIDTH];
		for(int p=SCREEN_HEIGHT*SCREEN_WIDTH; p<(SCREEN_HEIGHT+1)*SCREEN_WIDTH; p++)
			vmem[p]=((uint16_t)fg) | ((uint16_t)bg) | ((uint16_t)' ');
		y--;
	}
	template <>
	auto Screen::operator<<<FG_color>(FG_color fg) -> Screen &{
		this->fg=fg;
		return *this;
	}
	template <>
	auto Screen::operator<<<BG_color>(BG_color bg) -> Screen &{
		this->bg=bg;
		return *this;
	}
	auto Screen::setColor(FG_color fg) -> Screen &{
		this->fg=fg;
		return *this;
	}
	auto Screen::setColor(BG_color bg) -> Screen &{
		this->bg=bg;
		return *this;
	}
	auto Screen::setColor(FG_color fg, BG_color bg) -> Screen &{
		return (*this).setColor(fg).setColor(bg);
	}
}
