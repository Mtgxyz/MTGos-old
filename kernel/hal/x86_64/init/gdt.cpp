#include <base.hpp>
#include <gdt.hpp>
#include <serial.hpp>
namespace MTGosHAL {
    GDT::GDT() {
        gdt[0]=gdt[1]=gdt[2]=gdt[3]=gdt[4]=gdt[5]=gdt[6]=0x0ull;
    }
    auto GDT::setEntry(int i, unsigned int base, unsigned int limit, int flags) -> void {
        gdt[i] = limit & 0xffffLL;
        gdt[i] |= (base & 0xffffffLL) << 16;
        gdt[i] |= (flags & 0xffLL) << 40;
        gdt[i] |= ((limit >> 16) & 0xfLL) << 48;
        gdt[i] |= ((flags >> 8 )& 0xffLL) << 52;
        gdt[i] |= ((base >> 24) & 0xffLL) << 56;
    }
    auto GDT::apply() -> void {
        debug << "We are now trying to set our GDT. If the CPU triplefaults, something went wrong in MTGosHAL::GDT::apply() or loadGDT().\n";
        fin={(uint16_t)7*8-1, (void*)gdt};
        loadGDT((void*)(&fin));
    };
}
