#ifndef _TEXTDISP_H
#define _TEXTDISP_H
#include <base.hpp>
#include <stdint.h>
#include <output.hpp>
#include <string.hpp>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 96
namespace MTGosHAL {
	enum class BG_color : uint32_t {
		BLACK=0x000000,
		BLUE=0x0000AA,
		GREEN=0x00AA00,
		CYAN=0x00AAAA,
		RED=0xAA0000,
		MAGENTA=0xAA00AA,
		BROWN=0xAA5500,
		LIGHT_GREY=0xAAAAAA,
		GREY=0x555555,
		LIGHT_BLUE=0x5555FF,
		LIGHT_GREEN=0x55FF55,
		LIGHT_CYAN=0x55FFFF,
		LIGHT_RED=0xFF5555,
		LIGHT_MAGENTA=0xFF55FF,
		YELLOW=0xFFFF55,
		WHITE=0xFFFFFF
	};
	enum class FG_color : uint32_t {
		BLACK=0x000000,
		BLUE=0x0000AA,
		GREEN=0x00AA00,
		CYAN=0x00AAAA,
		RED=0xAA0000,
		MAGENTA=0xAA00AA,
		BROWN=0xAA5500,
		LIGHT_GREY=0xAAAAAA,
		GREY=0x555555,
		LIGHT_BLUE=0x5555FF,
		LIGHT_GREEN=0x55FF55,
		LIGHT_CYAN=0x55FFFF,
		LIGHT_RED=0xFF5555,
		LIGHT_MAGENTA=0xFF55FF,
		YELLOW=0xFFFF55,
		WHITE=0xFFFFFF
	};

	class Screen {
		private:
			FG_color fg;
			BG_color bg;
			uint32_t* lfb;
			int base;
			auto putChar(char c) -> void;
		public:
			auto putChar(unsigned short c) -> void;
			auto puts(const char *s) -> void;
			auto puts(String &) -> void;
			Screen(): fg(FG_color::WHITE), bg(BG_color::BLACK), base(10) {
			}
			template <typename T>
			auto operator<< (T output) -> Screen & {
				puts(output);
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
	template <>
	auto Screen::operator<<<Base>(Base output) -> Screen &;
	template <>
	auto Screen::operator<<<int>(int output) -> Screen &;
	template <>
	auto Screen::operator<<<long int>(long int output) -> Screen &;
	template <>
	auto Screen::operator<<<char>(char output) -> Screen &;
	template <>
	auto Screen::operator<<<char*>(char* output) -> Screen &;
}
#endif
