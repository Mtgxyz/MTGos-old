#include <pmm.hpp>
//In this part, please remember that the address is split into 3 parts. Bitmap:
// AAAA AAAA ABBB BBBB BBBB CCCC CCCC CCCC
#define SPLIT1_FLAG 0xFF800000ul
#define SPLIT1_SHIFT(a) (a)<<23
#define SPLIT1_UNSHIFT(a) (a)>>23
#define SPLIT2_FLAG 0x007FF000ul
#define SPLIT2_SHIFT(a) (a)<<12
#define SPLIT2_UNSHIFT(a) ((a)<<23)&0x7FF
#define SPLIT3_FLAG 0x00000FFFul
#define SPLIT3_SHIFT(a) (a)
#define SPLIT3_UNSHIFT(a) (a)&0xFFF
namespace MTGosHAL {
PMM::PMM(): qdpmm() {
}
template <typename T>
auto PMM::markUsed(T * addr, uint32_t length) -> void {
  uint32_t add=(uint32_t)addr;
  uint32_t pagetid = SPLIT1_UNSHIFT(add);
  if(length > 256*1024*1024) //Maximum allocation limit is 256MB
    return;
  if(!pageTable[pagetid]) {
    void* temp;
    qdpmm >> temp;
    pageTable[pagetid]=(uint16_t*)temp;
    markUsed(pageTable[pagetid],1024); //Not a mistake
  }
  uint16_t counter=1;
  for(uint32_t curr_addr=add+length;curr_addr>=add;curr_addr-=0x1000) {
    pageTable[SPLIT1_UNSHIFT(curr_addr)][SPLIT2_UNSHIFT(curr_addr)]=counter++;
    qdpmm.markUsed((void*)curr_addr);
  }
}
auto PMM::init(struct multiboot_info* mb_info) -> void {
  qdpmm.init(mb_info);
  void *temp;
  qdpmm >> temp;
  pageTable=(uint16_t**)temp;
  markUsed(pageTable,1024);
  for(int i=0;i<4096;i++)
    pageTable[i]=nullptr;
}
}
