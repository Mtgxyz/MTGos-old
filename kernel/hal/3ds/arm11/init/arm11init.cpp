//Notice: 0x1FFFFFF8 is a pointer to a function that is being executed by
//A11 SYS_CORE
//If it's zero, SYS_CORE is ready for a new task
#include <stdint.h>
#include <textDISP.hpp>
extern "C" void initInterrupts();
void(**fpointer)(void*)=(void(**)(void*))0x1FFFFFF8;
void **farg = (void**)0x1FFFFFFC;
//Flags:
//0: Output from ARM11
//1: puts() lock
uint32_t *flags = (uint32_t*)0x1FFFFFF4;
namespace MTGosHAL {
void mainRoutine(void*) {
    *farg=nullptr;
    *fpointer=nullptr;
    while(true) {
        if(!(*fpointer))
            continue;
        (*fpointer)(*farg);
        *farg=nullptr;
        *fpointer=nullptr;
        *flags&=~1;
    }
}
void initScreen(void*) {
    //top screen lfb size: 0x5dc00
    //bottom screen lfb size: 0x4b000
    //lfb locations: 0x18000000 (left 1)
    //lfb locations: 0x18060000 (left 2)
    //lfb locations: 0x180C0000 (right 1)
    //lfb locations: 0x18120000 (right 2)
    //lfb locations: 0x18180000 (bottom 1)
    //lfb locations: 0x181D0000 (bottom 2)
    unsigned int *lfbs = (unsigned int*)0x18000000;
    for(int i=0;i<475136;i++)
        lfbs[i]=0;
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
}
void testSVC(void*) {
    initInterrupts();
    asm volatile("svc #1");
}
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
extern "C"  void handleINT11(uint32_t stack, uint32_t id) {
    MTGosHAL::Screen out;
    *flags|=1;
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
    *flags&=~1;
    if((id!=1)&&(id!=2)&&(id!=4))
        for(;;);
}
