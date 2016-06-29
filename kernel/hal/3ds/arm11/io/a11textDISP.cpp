#include <base.hpp>
#include <textDISP.hpp>
#include <stdfnt.h>
int x=0, y=0;
extern uint32_t *flags;
namespace MTGosHAL {
   FG_color fg=FG_color::WHITE;
   BG_color bg=BG_color::BLACK;
   uint32_t* toplfb = (uint32_t*)0x18000000;
   uint32_t* bottomlfb = (uint32_t*)0x18180000;
   int base=10;

  void Screen::putChar(char c) {
    while(*flags&2); //to prevent garbage to be displayed when ARM9&ARM11 are trying to access it at the same time
    *flags|=2;
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
              if(y>=TOP_SCREEN_HEIGHT)
                bottomlfb[CALCXY(x*8+lx,(y-TOP_SCREEN_HEIGHT)*8+ly)]=__builtin_bswap32(static_cast<uint32_t>(fg));
              else
                toplfb[CALCXY(x*8+lx,(y)*8+ly)]=__builtin_bswap32(static_cast<uint32_t>(fg));
            } else {
              if(y>=TOP_SCREEN_HEIGHT)
                bottomlfb[CALCXY(x*8+lx,(y-TOP_SCREEN_HEIGHT)*8+ly)]=__builtin_bswap32(static_cast<uint32_t>(bg));
              else
                toplfb[CALCXY(x*8+lx,(y)*8+ly)]=__builtin_bswap32(static_cast<uint32_t>(bg));
            }
          }
        }
      x++;
      if(x==(y>=TOP_SCREEN_HEIGHT?BOTTOM_SCREEN_WIDTH:TOP_SCREEN_WIDTH)) {
        x=0;
        y++;
      }
      break;
    }
    if(y>=TOP_SCREEN_HEIGHT+BOTTOM_SCREEN_HEIGHT)
      scroll_impl();
    *flags&=~2; //Unlock
  }
  void Screen::clrscr_impl() {
    for(int p=0;p<400*240;p++)
      toplfb[p]=__builtin_bswap32(static_cast<uint32_t>(bg));
    for(int p=0;p<320*240;p++)
      bottomlfb[p]=__builtin_bswap32(static_cast<uint32_t>(bg));
  }
  void Screen::scroll_impl() {
    for(int ly=0;ly<240-8;ly++) {
      for(int lx=0;lx<400;lx++) {
        toplfb[CALCXY(lx,ly)]=toplfb[CALCXY(lx,ly+8)];
      }
    }
    for(int ly=0;ly<8;ly++) {
      for(int lx=0;lx<40;lx++) {
        toplfb[CALCXY(lx,ly+240-8)]=__builtin_bswap32(static_cast<uint32_t>(bg));
      }
      for(int lx=40;lx<360;lx++) {
        toplfb[CALCXY(lx,ly+240-8)]=bottomlfb[CALCXY(lx-40,ly)];
      }
      for(int lx=360;lx<400;lx++) {
        toplfb[CALCXY(lx,ly+240-8)]=__builtin_bswap32(static_cast<uint32_t>(bg));
      }
    }
    for(int ly=0;ly<240-8;ly++) {
      for(int lx=0;lx<320;lx++) {
        bottomlfb[CALCXY(lx,ly)]=bottomlfb[CALCXY(lx,ly+8)];
      }
    }
    for(int ly=240-8;ly<240;ly++) {
      for(int lx=0;lx<320;lx++) {
        bottomlfb[CALCXY(lx,ly)]=__builtin_bswap32(static_cast<uint32_t>(bg));
      }
    }
    y--;
  }
  auto Screen::a11puts(const char *s) -> void {
    int i=0;
    while(s[i])
      putChar(s[i]);
  }
}
