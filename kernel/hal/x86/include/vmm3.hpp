#include <pmm.hpp>
#include <multiboot.h>
#define virtualptr *
#define physicalptr *
// This is the class that activates paging and does general handling of pages
namespace MTGosHAL {
class VMM3 {
private:
  uint32_t **pd;
public:
  PMM pmm;
  VMM3();
  auto init(struct multiboot_info*) -> void;
  auto alloc(uint32_t length) -> void*;
  auto free(void* ptr) -> bool;
};
}
