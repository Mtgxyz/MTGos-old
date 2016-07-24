#include <pmm2.hpp>
#include <base.hpp>
//In this part, please remember that the address is split into 2 parts. Bitmap:
// AAA AAAA AAAA AAAA AAAB BBBB BBBB BBBB BBBB BBBB
#define SPLIT1_FLAG 0x3ffff00000ull
#define SPLIT1_SHIFT(a) ((a)<<20)
#define SPLIT1_UNSHIFT(a) ((a)>>20)
#define SPLIT2_FLAG 0xFFFFFull
#define SPLIT2_SHIFT(a) ((a))
#define SPLIT2_UNSHIFT(a) ((a)&SPLIT2_FLAG)

extern "C" const int kernel_start;
extern "C" const int kernel_end; //those are voids actually

namespace MTGosHAL {
PMM2::PMM2(): pmm3() {
}
auto PMM2::markUsed(const void * addr, uint32_t length) -> bool {
    if(length<0x200000)
        length=0x200000;
    uintptr_t add=(uintptr_t)addr;
    uint64_t pagetid = SPLIT1_UNSHIFT(add);

    //Check if used
    for(uintptr_t curr_addr=add+length;curr_addr>add;curr_addr-=0x200000) {
        if(pageTable[SPLIT1_UNSHIFT(curr_addr)])
        return false;
    }
    //Mark as used
    uint64_t counter=1;
    for(uintptr_t curr_addr=add+length;curr_addr>add;curr_addr-=0x200000) {
        pageTable[SPLIT1_UNSHIFT(curr_addr)]=counter++;
        pmm3.markUsed((void*)curr_addr);
    }
    return true;
}
auto PMM2::operator >> (void * &addr) -> PMM2 & {
    pmm3 >> addr;
    markUsed(addr,0x200000);
    return *this;
}
auto PMM2::operator << (const void *addr) -> PMM2 & {
    uint64_t add=(uint64_t)addr;
    for(uint64_t i=0;i<pageTable[SPLIT1_UNSHIFT(add)];i++) {
        pageTable[SPLIT1_UNSHIFT(add+i*0x200000)]=0;
        pmm3 << (void*)(add+i*0x200000);
    }
    return *this;
}
auto PMM2::operator()(int pages) -> void* {
    //I want to get this working so:
    //TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
    // NEVER USE A BRUTE-FORCE ALGO TO ALLOC PAGES!
    //TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
    for(uint64_t i=0;i<(uint64_t)(-(pages*0x200000));i+=0x200000) {
        if(markUsed((void*)i,pages*0x200000))
        return (void*)i;
    }
    return nullptr;
}
auto PMM2::init(struct multiboot_info* mb_info) -> void {
    pmm3.init(mb_info);
    void *temp;
    pmm3 >> temp;
    pageTable=(uint64_t*)temp;
    for(int i=0;i<0x80000;i++)
        pageTable[i]=0;
    markUsed(pageTable,0x200000);
    markUsed((void*)nullptr,0x200000);
    struct multiboot_mmap_entry* mmap = (struct multiboot_mmap_entry*) (uintptr_t)(mb_info->mmap_addr);
    struct multiboot_mmap_entry* mmap_end = (struct multiboot_mmap_entry*) ((uintptr_t) mb_info->mmap_addr + mb_info->mmap_length);
    while(mmap < mmap_end) {
        if(mmap->type != 1) {
        markUsed((void*)mmap->addr,mmap->len);
        }
        mmap++;
    }
    markUsed(&kernel_start,((uintptr_t)&kernel_end)-((uintptr_t)&kernel_start)); //Protect kernel)
    multiboot_mod_list *mods = (multiboot_mod_list*) (uintptr_t)(mb_info->mods_addr);
    for(uint32_t i=0;i<mb_info->mods_count;i++) {
        markUsed((void*)((uintptr_t)(&mods[i])&(~0xFFF)),4096); //Mark all of the module table as used
        markUsed((void*)(uintptr_t)(mods[i].mod_start),mods[i].mod_end-mods[i].mod_start);
    }
}
}
