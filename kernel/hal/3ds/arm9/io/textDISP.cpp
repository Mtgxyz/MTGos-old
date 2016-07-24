#include <base.hpp>
#include <textDISP.hpp>
//Flags:
//0: Output from ARM11
//1: puts() lock
extern uint32_t *flags;
namespace MTGosHAL {
    auto Screen::puts(const char *s) -> void {

    void(**a11fpointer)(void*)=(void(**)(void*))0x1FFFFFF8;
    void **a11farg = (void**)0x1FFFFFFC;
    int i=0;
    while(s[i]) {
            if(*flags&1)
                putChar(s[i++]);
            else {
                while(*a11fpointer);
                *a11farg=(void*)((unsigned int)s[i++]);
                *a11fpointer=(void(*)(void*))&putChar;
            }
        }
    }
    auto Screen::clrscr() -> void {
        void(**a11fpointer)(void*)=(void(**)(void*))0x1FFFFFF8;
        while(*a11fpointer);
        *a11fpointer=(void(*)(void*))(clrscr_impl);
    }
    auto Screen::scroll() -> void {
        void(**a11fpointer)(void*)=(void(**)(void*))0x1FFFFFF8;
        while(*a11fpointer);
        *a11fpointer=(void(*)(void*))(scroll_impl);
    }
    template <>
    auto Screen::operator<<<FG_color>(FG_color fg) -> Screen &{
        fg=fg;
        return *this;
    }
    template <>
    auto Screen::operator<<<BG_color>(BG_color bg) -> Screen &{
        bg=bg;
        return *this;
    }
    auto Screen::setColor(FG_color fg) -> Screen &{
        fg=fg;
        return *this;
    }
    auto Screen::setColor(BG_color bg) -> Screen &{
        bg=bg;
        return *this;
    }
    auto Screen::setColor(FG_color fg, BG_color bg) -> Screen &{
        return (*this).setColor(fg).setColor(bg);
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
