#include <mtgos.hpp>
static unsigned short* videomem = (unsigned short*) 0xb8000;
void temp() {
     int i;
    for (i = 0; i < 3; i++) {
        *videomem++ = (0x07 << 8) | ('0' + i);
    }
}
void main()
{
  char arr[4]="123";
  ScreenOut out=ScreenOut(false);
  int i;
  out.setColor(BGColor::BLUE, FGColor::YELLOW);
  for(;;) {
    out << arr;
  }
}
