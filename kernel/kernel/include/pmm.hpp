#ifndef _PMM_HPP
#define _PMM_HPP
#include <stdint.h>
namespace MTGosHAL {
struct malloc_t {
  uint32_t len;
  malloc_t *last;
  malloc_t *next;
};
class PMM {
private:
  malloc_t *head;
public:
  PMM();
  auto alloc(uint32_t length) -> void *;
  auto free(void* ptr) -> bool;
  auto markUsed(const void * addr, uint32_t length) -> bool;
  auto operator >> (void * &addr) -> PMM &; //alloc
  auto operator << (const void * addr) -> PMM &; //free
  auto operator()(int pages) -> void*; //alloc_multipage
};
}
#endif
