#include <base.hpp>
#include <textDISP.hpp>
#include <string.h>
#include <stdfnt.h>
namespace MTGosHAL {
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
