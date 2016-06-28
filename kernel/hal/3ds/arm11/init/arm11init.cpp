//Notice: 0x1FFFFFF8 is a pointer to a function that is being executed by
//A11 SYS_CORE
//If it's zero, SYS_CORE is ready for a new task
#include <stdint.h>
#include <stdfnt.h>
void(**fpointer)(void)=(void(**)(void))0x1FFFFFF8;
void  __attribute__((naked)) arm11Stub(void)
{
    //Disable interrupts
    __asm(".word 0xF10C01C0");

    //Wait for the entry to be set
    while(*fpointer == &arm11Stub);

    //Jump to it
    (*fpointer)();
}
void mainRoutine() {
  *fpointer=nullptr;
  while(true) {
    if(!(*fpointer))
      continue;
    (*fpointer)();
    *fpointer=nullptr;
  }
}
unsigned int seed=0;
unsigned int random() {
  return seed=0x41C64E6D * seed + 0x00006073;
}
#define CALCXY_top(x,y) ((x)*240+240-(y))
void initScreen() {
  //top screen lfb size: 0x5dc00
  //bottom screen lfb size: 0x4b000
  //lfb locations: 0x18000000 (left 1)
  //lfb locations: 0x18060000 (left 2)
  //lfb locations: 0x180C0000 (right 1)
  //lfb locations: 0x18120000 (right 2)
  //lfb locations: 0x18180000 (bottom 1)
  //lfb locations: 0x181D0000 (bottom 2)
  unsigned int *fb_init=(unsigned int*)0x10400400;
  fb_init[0x70/4]&=~0x7;
  fb_init[0x170/4]&=~0x7;
  fb_init[0x68/4]=0x18000000; //Left eye
  fb_init[0x6C/4]=0x18060000; //Left eye
  fb_init[0x90/4]=960;
  fb_init[0x94/4]=0x180C0000; //Right eye
  fb_init[0x98/4]=0x18120000; //Right eye
  fb_init[0x168/4]=0x18180000;
  fb_init[0x16C/4]=0x181D0000;
  fb_init[0x190/4]=960;
  int *lfb=(int*)0x18060000;
  for(int bx=0;bx<32;bx++) {
    for(int by=0;by<8;by++) {
      for(int x=0;x<8;x++) {
        for(int y=0;y<8;y++) {
          if(font[bx+by*32][y]&(1<<x))
            lfb[CALCXY_top(bx*8+x,by*8+y)]=0xFFFFFF00;
          else
            lfb[CALCXY_top(bx*8+x,by*8+y)]=0x0;
        }
      }
    }
  }
  fb_init[0x78/4]=1;
}
