#include <base.hpp>
#include <textDISP.hpp>
#include <string.h>
#include <stdfnt.h>
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
				for(int lx=0;lx<8;lx++) {
					for(int ly=0;ly<8;ly++) {
						if(font[(int)((uint8_t)c)][ly]&(1<<lx)) {
							lfb[(x*8+lx)+(y*8+ly)*1024]=0xFFFFFF;//static_cast<uint32_t>(fg);
						} else {
							lfb[(x*8+lx)+(y*8+ly)*1024]=0x000000;//static_cast<uint32_t>(bg);
						}
					}
				}
				x++;
				if(x==SCREEN_WIDTH) {
					x=0; y++;
				}
				break;
		}
		if(y>SCREEN_HEIGHT)
			scroll();
	}
	auto Screen::clrscr() -> void {
		for(int p=0;p<1024*786;p++) {
			lfb[p]=0x000000;//static_cast<uint32_t>(bg);
		}
		x=y=0;
	}
	auto Screen::scroll() -> void {
		for(int ly=0;ly<786-8;ly++) {
			for(int lx=0;lx<1024;lx++) {
				lfb[lx+ly*1024]=lfb[lx+(ly+8)*1024];
			}
		}
		for(int ly=786-8;ly<786;ly++) {
			for(int lx=0;lx<1024;lx++) {
				lfb[lx+ly*1024]=0x000000;//static_cast<uint32_t>(bg);
			}
		}
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
	auto Screen::init(struct multiboot_info* mb_info) -> void {
		lfb=(uint32_t*)((uint32_t)mb_info->framebuffer_addr);
		//clrscr();
		//Render '\001' character
		for(int tx=0;tx<16;tx++) {
			for(int ty=0;ty<16;ty++) {
				for(int x=0;x<8;x++) {
					for(int y=0;y<8;y++) {
						if(font[tx+ty*16][y]&(1<<x))
							lfb[(x+tx*8)+(y+ty*8)*1024]=0xFFFFFF;
					}
				}
			}
		}
	}
}
