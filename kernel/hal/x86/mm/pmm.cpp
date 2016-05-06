#include <pmm.hpp>
#include <base.hpp>
//In this part, please remember that the address is split into 3 parts. Bitmap:
// AAAA AAAA ABBB BBBB BBBB CCCC CCCC CCCC
#define SPLIT1_FLAG 0xFF800000ul
#define SPLIT1_SHIFT(a) ((a)<<23)
#define SPLIT1_UNSHIFT(a) ((a)>>23)
#define SPLIT2_FLAG 0x007FF000ul
#define SPLIT2_SHIFT(a) ((a)<<12)
#define SPLIT2_UNSHIFT(a) (((a)<<23)&0x7FF)
#define SPLIT3_FLAG 0x00000FFFul
#define SPLIT3_SHIFT(a) ((a))
#define SPLIT3_UNSHIFT(a) ((a)&0xFFF)
extern "C" const int kernel_start;
extern "C" const int kernel_end; //those are voids actually
void *operator new(size_t size) {
	if(size>4096) {
    return MTGosHAL::mm(size/4096);
	}
	void *ptr;
	MTGosHAL::mm >> ptr;
	return ptr;
}
void *operator new[](size_t size)  {
  if(size>4096) {
    return MTGosHAL::mm(size/4096);
	}
	void *ptr;
	MTGosHAL::mm >> ptr;
	return ptr;
}
void operator delete(void* p) {
	MTGosHAL::mm << p;
}
void operator delete[](void* p) {
	MTGosHAL::mm << p;
}
void operator delete(void* p, size_t size) {
	MTGosHAL::mm << p;
}
void operator delete[](void* p, size_t size) {
	MTGosHAL::mm << p;
}
namespace MTGosHAL {
PMM::PMM(): qdpmm() {
}

auto PMM::markUsed(const void * addr, uint32_t length) -> bool {
  uint32_t add=(uint32_t)addr;
  uint32_t pagetid = SPLIT1_UNSHIFT(add);
  if(length > 256*1024*1024) //Maximum allocation limit is 256MB
    return false;
  if(!pageTable[pagetid]) {
    void* temp;
    qdpmm >> temp;
    pageTable[pagetid]=(uint16_t*)temp;
    for(int i=0;i<2048;i++)
      pageTable[pagetid][i]=0;
    markUsed(pageTable[pagetid],1024); //Not a mistake
  }
  //Check if used
  for(uint32_t curr_addr=add+length;curr_addr>=add;curr_addr-=0x1000) {
    if(pageTable[SPLIT1_UNSHIFT(curr_addr)][SPLIT2_UNSHIFT(curr_addr)])
      return false;
  }
  //Mark as used
  uint16_t counter=1;
  for(uint32_t curr_addr=add+length;curr_addr>=add;curr_addr-=0x1000) {
    pageTable[SPLIT1_UNSHIFT(curr_addr)][SPLIT2_UNSHIFT(curr_addr)]=counter++;
    qdpmm.markUsed((void*)curr_addr);
  }
  return true;
}

auto PMM::operator >> (void * &addr) -> PMM & {
  qdpmm >> addr;
  markUsed(addr,4096);
  return *this;
}
auto PMM::operator << (const void *addr) -> PMM & {
  uint32_t add=(uint32_t)addr;
  if(!pageTable[SPLIT1_UNSHIFT(add)])
    return *this; //Prevent nullptr derefs
  for(int i=0;i<pageTable[SPLIT1_UNSHIFT(add)][SPLIT2_UNSHIFT(add)];i++) {
    pageTable[SPLIT1_UNSHIFT(add+i*4096)][SPLIT2_UNSHIFT(add+i*4096)]=0;
    qdpmm << (void*)(add+i*4096);
  }
  return *this;
}
auto PMM::operator()(int pages) -> void* {
  //I want to get this working so:
  //TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
  // NEVER USE A BRUTE-FORCE ALGO TO ALLOC PAGES!
  //TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
  for(uint32_t i=0;i<(uint32_t)(-(pages*4096));i+=4096) {
    if(markUsed((void*)i,pages*4096))
      return (void*)i;
  }
  return nullptr;
}
auto PMM::init(struct multiboot_info* mb_info) -> void {
  qdpmm.init(mb_info);
  void *temp;
  qdpmm >> temp;
  pageTable=(uint16_t**)temp;
  for(int i=0;i<4096;i++)
    pageTable[i]=nullptr;
  markUsed(pageTable,4096);
  markUsed((void*)nullptr,4096);
  struct multiboot_mmap_entry* mmap = (struct multiboot_mmap_entry*) mb_info->mmap_addr;
	struct multiboot_mmap_entry* mmap_end = (struct multiboot_mmap_entry*) ((unsigned int) mb_info->mmap_addr + mb_info->mmap_length);
  while(mmap < mmap_end) {
    if(mmap->type != 1) {
      markUsed((void*)mmap->addr,mmap->len);
    }
    mmap++;
  }
  markUsed(&kernel_start,((uint32_t)&kernel_end)-((uint32_t)&kernel_start)); //Protect kernel)
  multiboot_mod_list *mods = (multiboot_mod_list*) mb_info->mods_addr;
	for(uint32_t i=0;i<mb_info->mods_count;i++) {
		markUsed((void*)((uint32_t)(&mods[i])&(~0xFFF)),4096); //Mark all of the module table as used
    markUsed((void*)mods[i].mod_start,mods[i].mod_end-mods[i].mod_start);
	}
}
}
