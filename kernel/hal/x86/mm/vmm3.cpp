#include <vmm3.hpp>
#include <base.hpp>
extern "C" void enterPaging(uint32_t **pd);
namespace MTGosHAL {
VMM3::VMM3(): pmm() {
}
auto VMM3::init(struct multiboot_info* mb_info) -> void {
    pmm.init(mb_info);
    void* tmp;
    pmm >> tmp;
    pd=(uint32_t**)tmp;
    uint32_t ent=0x87;
    for(int i=0;i<1024;i++) {
        pd[i]=(uint32_t*)ent;
        ent+=0x1000*1024;
    }
    enterPaging(pd);
}
auto VMM3::alloc(uint32_t length) -> void* {
    return pmm.alloc(length);
}
auto VMM3::free(void* ptr) -> bool {
    return pmm.free(ptr);
}
}
