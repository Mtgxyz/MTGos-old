#ifndef _PMM_HPP
#define _PMM_HPP
#include <pmm2.hpp>
#include <stdint.h>
#include <multiboot.h>
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
  PMM2 pmm2;
  PMM();
  auto init(struct multiboot_info*) -> void;
  auto alloc(uint32_t length) -> void *;
  auto free(void* ptr) -> bool;
};
}
#endif
