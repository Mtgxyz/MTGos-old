#include <base.hpp>
#include <pmm.hpp>
#include <stdint.h>
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

  auto PMM::alloc(size_t length) -> void * {
    if(!head) {
      //Alloc space for head
      if(length+sizeof(malloc_t)<=4096) { //Small optimization. The routine for allocating more than one continuous page is terribly slow.
        void *tmp;
        *this >> tmp;
        head=(malloc_t*)tmp;
      } else
        head=(malloc_t*)(*this)(((length+sizeof(malloc_t))>>12)+1);
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
      uintptr_t loc=(uintptr_t)curr+sizeof(malloc_t)+curr->len;
      if((loc+length+sizeof(malloc_t))<((loc&(~0xFFF))+4096) &&
         ((!curr->next) || (loc+length+sizeof(malloc_t))<((uintptr_t)(curr->next)))) {
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
      *this >> tmp;
      allocd=(malloc_t*)tmp;
    } else
      allocd=(malloc_t*)(*this)(((length+sizeof(malloc_t))>>12)+1);
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
        uintptr_t start=((uintptr_t)chk)&(~0xFFF);
        uintptr_t end=start+0x1000;
        if((((uintptr_t)(curr->last)<start)||((uintptr_t)(curr->last)>=end))&&(((uintptr_t)(curr->next)>=end)||((uintptr_t)(curr->next)<start))) {
          *this << (void*)start;
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
