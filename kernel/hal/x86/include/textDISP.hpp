#ifndef _TEXTDISP_H
#define _TEXTDISP_H
#include <stdint.h>
#include <output.hpp>
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
namespace MTGosHAL {
	enum class BG_color : uint16_t {
		BLACK=0x0000,
		BLUE=0x1000,
		GREEN=0x2000,
		CYAN=0x3000,
		RED=0x4000,
		MAGENTA=0x5000,
		BROWN=0x6000,
		LIGHT_GREY=0x7000,
		GREY=0x8000,
		LIGHT_BLUE=0x9000,
		LIGHT_GREEN=0xA000,
		LIGHT_CYAN=0xB000,
		LIGHT_RED=0xC000,
		LIGHT_MAGENTA=0xD000,
		YELLOW=0xE000,
		WHITE=0xF000
	};
	enum class FG_color : uint16_t {
		BLACK=0x000,
		BLUE=0x100,
		GREEN=0x200,
		CYAN=0x300,
		RED=0x400,
		MAGENTA=0x500,
		BROWN=0x600,
		LIGHT_GREY=0x700,
		GREY=0x800,
		LIGHT_BLUE=0x900,
		LIGHT_GREEN=0xA00,
		LIGHT_CYAN=0xB00,
		LIGHT_RED=0xC00,
		LIGHT_MAGENTA=0xD00,
		YELLOW=0xE00,
		WHITE=0xF00
	};
	class Screen: public Output {
		private:
			FG_color fg;
			BG_color bg;
			uint16_t* vmem=(uint16_t*)0xB8000;
			auto putChar(char c) -> void;
		public:
			Screen(): fg(FG_color::WHITE), bg(BG_color::BLACK) {
				clrscr();
			}
			template <typename T>
			auto operator<< (T output) -> Screen & {
				Output::operator<<<T>(output);
				return *this;
			}
			auto clrscr() -> void;
			auto scroll() -> void;
			auto setColor(FG_color fg) -> Screen &;
			auto setColor(BG_color bg) -> Screen &;
			auto setColor(FG_color fg, BG_color bg) -> Screen &;
	};
	template <>
	auto Screen::operator<<<FG_color>(FG_color fg) -> Screen &;
	template <>
	auto Screen::operator<<<BG_color>(BG_color bg) -> Screen &;
}
#endif
