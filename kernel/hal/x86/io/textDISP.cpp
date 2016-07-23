#include <base.hpp>
#include <textDISP.hpp>
#include <string.h>
#include <stdfnt.h>
#include <base.hpp>
#include <textDISP.hpp>
#include <string.h>
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
				for(int lx=0;lx<16;lx++) {
					for(int ly=0;ly<16;ly++) {
						if(font[(int)((uint8_t)c)][ly]&(1<<(16-lx))) {
							lfb[(x*16+lx)+(y*16+ly)*1024]=0xFFFFFF;//static_cast<uint32_t>(fg);
						} else {
							lfb[(x*16+lx)+(y*16+ly)*1024]=0x000000;//static_cast<uint32_t>(bg);
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
		for(int ly=0;ly<786-16;ly++) {
			for(int lx=0;lx<1024;lx++) {
				lfb[lx+ly*1024]=lfb[lx+(ly+16)*1024];
			}
		}
		for(int ly=786-16;ly<786;ly++) {
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
		lfb=(uint32_t*)((uintptr_t)mb_info->framebuffer_addr);
		//Load font
		multiboot_mod_list *mods = (multiboot_mod_list*) mb_info->mods_addr;
		for(int i=0;i<65536;i++)
			for(int j=0;j<16;j++)
				font[i][j]=0;
		for(uint32_t i=0;i<mb_info->mods_count;i++) {
			fontfile* font=(fontfile*)(mods[i].mod_start);
			if((font->magic[0]!='F')||(font->magic[1]!='O')||(font->magic[2]!='N')||(font->magic[3]!='T')) //Is it a font file?
				continue;
			charmap* map=(charmap*)((char*)font+font->charmap_off);
			charwidth* width=(charwidth*)((char*)font+font->charwidth_off);
			CHR8* chr_begin=(CHR8*)((char*)font+font->chr_off);
			uint32_t hwcount=0;
			for(uint32_t i=0;i<font->no_char;i++) {
				uint16_t char_num=map[i].charnumber;
				bool wide_char=width[i].width==0x10;
				if(wide_char) {
					CHR16* chr=(CHR16*)((char*)(&chr_begin[hwcount]));
					for(int j=0;j<16;j++)
						::font[i][j]=chr->rows[j];
					hwcount+=2;
				} else {
					for(int j=0;j<16;j++)
						::font[i][j]=(uint16_t)(((uint16_t)chr_begin[hwcount].rows[j])<<8);
					hwcount++;
				}
			}
		}
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
	auto Screen::puts(const char* s) -> void {
		int i=0;
		while(s[i]!='\0')
			putChar(s[i++]);
	}
	template <>
	auto Screen::operator<<<Base>(Base output) -> Screen & {
		base=static_cast<int>(output);
		return *this;
	}
	template <>
	auto Screen::operator<<<int>(int op) -> Screen & {
		uintptr_t output=op;
		const char* chars="0123456789ABCDEF";
		char buf[33];
		buf[32]='\0';
		char* ptr=buf+31;
		do {
			*(ptr--)=chars[output%base];
			output/=base;
		} while(output && (ptr!=buf));
		puts(ptr+1);
		return *this;
	}
	template <>
	auto Screen::operator<<<long int>(long int op) -> Screen & {
		uint64_t output=op;
		const char* chars="0123456789ABCDEF";
		char buf[65];
		buf[64]='\0';
		char* ptr=buf+63;
		do {
			*(ptr--)=chars[output%base];
			output/=base;
		} while(output && (ptr!=buf));
		puts(ptr+1);
		return *this;
	}
	template <>
	auto Screen::operator<<<char>(char output) -> Screen & {
		putChar(output);
		return *this;
	}
	template <>
	auto Screen::operator<<<char*>(char* output) -> Screen & {
		puts(output);
		return *this;
	}
}
