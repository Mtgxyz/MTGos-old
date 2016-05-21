#include <base.hpp>
#include <pmm.hpp>
#include <vmm3.hpp>
extern "C" const int kernel_start;
extern "C" const int kernel_end; //those are voids actually
void *operator new(size_t size) {
  return MTGosHAL::mm.alloc(size);
}
void *operator new[](size_t size)  {
  return MTGosHAL::mm.alloc(size);
}
void operator delete(void* p) {
	MTGosHAL::mm.free(p);
}
void operator delete[](void* p) {
	MTGosHAL::mm.free(p);
}
void operator delete(void* p, size_t size) {
	MTGosHAL::mm.free(p);
}
void operator delete[](void* p, size_t size) {
	MTGosHAL::mm.free(p);
}
namespace MTGosHAL {
PMM::PMM(): head(nullptr), pmm2() {}
auto PMM::init(struct multiboot_info* mb_info) -> void {
  pmm2.init(mb_info);
}
auto PMM::alloc(uint32_t length) -> void * {
  if(!head) {
    //Alloc space for head
    if(length+sizeof(malloc_t)<=4096) { //Small optimization. The routine for allocating more than one continuous page is terribly slow.
      void *tmp;
      pmm2 >> tmp;
      head=(malloc_t*)tmp;
    } else
      head=(malloc_t*)pmm2(((length+sizeof(malloc_t))>>12)+1);
    if(!head) //The alloc() didn't work! We're out of RAM!
      return nullptr;
    head->len=length;
    head->next=head->last=nullptr;
    malloc_t* tmp=head;
    tmp++;
    return (void*)tmp;
  }
  malloc_t* curr=head;
  malloc_t* last=nullptr;
  do {
    uint32_t loc=(uint32_t)curr+sizeof(malloc_t)+curr->len;
    if((loc+length+sizeof(malloc_t))<((loc&(~0xFFF))+4096)) {
      malloc_t *allocd=(malloc_t *)loc;
      allocd->len=length;
      allocd->last=curr;
      allocd->next=curr->next; //Set double linked list
      curr->next=allocd;
      if(allocd->next)
        allocd->next->last=allocd;
      malloc_t *tmp=allocd;
      tmp++;
      return (void*)tmp;
    }
    last=curr;
    curr=curr->next;
  } while(curr);
  malloc_t *allocd=nullptr;
  if(length+sizeof(malloc_t)<=4096) { //Small optimization. The routine for allocating more than one continuous page is terribly slow.
    void *tmp;
    pmm2 >> tmp;
    allocd=(malloc_t*)tmp;
  } else
    allocd=(malloc_t*)pmm2(((length+sizeof(malloc_t))>>12)+1);
  if(!allocd) //The alloc() didn't work! We're out of RAM!
    return nullptr;
  last->next=allocd;
  allocd->len=length;
  allocd->last=last;
  allocd->next=nullptr;
  malloc_t *tmp=allocd;
  tmp++;
  return (void*)tmp;
}
auto PMM::free(void* ptr) -> bool {
  if(!ptr)
    return false;
  malloc_t* curr=head;
  malloc_t* chk=(malloc_t*)ptr;
  chk--;
  do {
    if(curr==chk) {
      uint32_t start=((uint32_t)chk)&(~0xFFF);
      uint32_t end=start+0x1000;
      if((((uint32_t)(curr->last)<start)||((uint32_t)(curr->last)>=end))&&(((uint32_t)(curr->next)>=end)||((uint32_t)(curr->next)<start))) {
        pmm2 << (void*)start;
      }
      if(curr->last)
        curr->last->next=curr->next;
      else {
        head=curr->next;
      }
      if(curr->next)
        curr->next->last=curr->last;
      return true;
    }
    curr=curr->next;
  } while(curr);
  return false;
}
}
