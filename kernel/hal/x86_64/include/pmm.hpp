#ifndef _PMM_HPP
#define _PMM_HPP
#include <pmm2.hpp>
#include <stdint.h>
#include <multiboot.h>
namespace MTGosHAL {
struct malloc_t {
  size_t len;
  malloc_t *last;
  malloc_t *next;
};
class PMM {
private:
  malloc_t *head;
  PMM2 pmm2;
public:
  PMM();
  PMM(struct multiboot_info* mb_info): PMM() {init(mb_info);}
  auto init(struct multiboot_info*) -> void;
  auto alloc(size_t length) -> void *;
  auto free(void* ptr) -> bool;
  auto markUsed(const void * addr, uint64_t length) -> bool;
  auto operator >> (void * &addr) -> PMM &; //alloc
  auto operator << (const void * addr) -> PMM &; //free
  auto operator()(int pages) -> void*; //alloc_multipage
};
}
#endif
