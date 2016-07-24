#include <mtgos.hpp>
extern "C" {
void * screenout_init(int err);
void * screenout_out(void* handle, const char *str);
void * screenout_clear(void* handle);
void * screenout_setcolor(void* handle, uint32_t BG, uint32_t FG);
void * screenout_destroy(void * handle);
}
ScreenOut::ScreenOut(bool err) {
    handle=screenout_init(err);
}
auto ScreenOut::operator<<(const char * str) -> ScreenOut & {
    screenout_out(handle, str);
    return *this;
}
auto ScreenOut::operator<<(int output) -> ScreenOut & {
    int base=10;
    const char* chars="0123456789ABCDEF";
    char buf[33];
    buf[32]='\0';
    char* ptr=buf+31;
    do {
        *(ptr--)=chars[output%base];
        output/=base;
    } while(output && (ptr!=buf));
    *this << ptr+1;
    return *this;
}
auto ScreenOut::clrscr() -> ScreenOut & {
    screenout_clear(handle);
    return *this;
}
auto ScreenOut::setColor(BGColor bg, FGColor fg) -> ScreenOut & {
    screenout_setcolor(handle, static_cast<uint32_t>(bg), static_cast<uint32_t>(fg));
    return *this;
}
ScreenOut::~ScreenOut() {
    handle=screenout_destroy(handle);
}
void main();
extern "C" void _start() {
    main();
    for(;;);
}
