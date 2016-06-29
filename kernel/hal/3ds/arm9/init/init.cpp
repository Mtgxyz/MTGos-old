#include <textDISP.hpp>

void(**a11fpointer)(void*)=(void(**)(void*))0x1FFFFFF8;
void **a11farg = (void**)0x1FFFFFFC;
extern uint32_t *flags;
extern unsigned int _a9vectors_begin;
extern unsigned int _a9vectors_end;
extern unsigned int _a11vectors_begin;
extern unsigned int _a11vectors_end;
namespace MTGosHAL {
  void mainRoutine(void*);
  void initScreen(void*);
  void testSVC(void*);
  void main() {
    *a11farg = 0;
    *a11fpointer=&mainRoutine;
    while(*a11fpointer);
    *a11fpointer=&initScreen;
    while(*a11fpointer);
    unsigned int * output=(unsigned int*)0x08000000;
    Screen out;
    out << "Waiting for interrupt...\n";
    out << "Copying " << &_a9vectors_end-&_a9vectors_begin << " words...\n";
    for(int i=0;i<(&_a9vectors_end-&_a9vectors_begin);i++) {
      output[i]=(&_a9vectors_begin)[i];
    }
    asm volatile("svc #0\n");
    out << "Did it work?\nSetting up A11 interrupts\n";
    output=(unsigned int*)0x1FF80000;
    out << "Copying " << &_a11vectors_end-&_a11vectors_begin << " words...\n";
    for(int i=0;i<(&_a11vectors_end-&_a11vectors_begin);i++) {
      output[i]=(&_a11vectors_begin)[i];
    }
    out << "Done!\n";
    *a11fpointer=&testSVC;
    while(*a11fpointer);
    out << "Did it work?\n";
    for(;;);
  }
}
extern "C" void init() {
  MTGosHAL::main();
}
struct cpu_info {
  unsigned int pc;
  unsigned int r12;
  unsigned int r11;
  unsigned int r10;
  unsigned int r9;
  unsigned int r8;
  unsigned int r7;
  unsigned int r6;
  unsigned int r5;
  unsigned int r4;
  unsigned int r3;
  unsigned int r2;
  unsigned int r1;
  unsigned int retAddr;
};
extern "C" void handleINT9(uint32_t stack, uint32_t id) {
  MTGosHAL::Screen out;
  out << MTGosHAL::Base::HEXADECIMAL << MTGosHAL::FG_color::RED << "Interrupt! " << (int)stack << "-" << (int)id << "\n";
  struct cpu_info *cpu=(struct cpu_info*)stack;
  out << "handler addr " << (int) cpu->pc << "\n";
  out << "R1 " << (int) cpu->r1 << ", R2 " << (int)cpu->r2 << "\n";
  out << "R3 " << (int) cpu->r3 << ", R4 " << (int)cpu->r4 << "\n";
  out << "R5 " << (int) cpu->r5 << ", R6 " << (int)cpu->r6 << "\n";
  out << "R7 " << (int) cpu->r7 << ", R8 " << (int)cpu->r8 << "\n";
  out << "R9 " << (int) cpu->r9 << ", SL " << (int)cpu->r10 << "\n";
  out << "FP " << (int) cpu->r11 << ", IP " << (int)cpu->r12 << "\n";
  out << "SP " << (int) stack << ", PC " << (int)cpu->retAddr << "\n";
  if((id!=1)&&(id!=2)&&(id!=4))
    for(;;);
}
