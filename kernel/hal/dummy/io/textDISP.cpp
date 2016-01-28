#include <base.hpp>
#include <textDISP.hpp>
int x=0, y=0;
namespace MTGosHAL {
	auto Screen::putChar(char c) -> void {
	}	
	auto Screen::clrscr() -> void {
	}
	auto Screen::scroll() -> void {
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
