#ifndef _PMM2_HPP
#define _PMM2_HPP
#include <pmm3.hpp>
#include <stdint.h>
#include <multiboot.h>
namespace MTGosHAL {
class PMM2 {
private:
	uint64_t *pageTable;
  PMM3 pmm3;
public:
	PMM2();
  auto markUsed(const void * addr, uint32_t length) -> bool;
  auto init(struct multiboot_info*) -> void;
  auto operator >> (void * &addr) -> PMM2 &; //alloc
  auto operator << (const void * addr) -> PMM2 &; //free
  auto operator()(int pages) -> void*; //alloc_multipage
};
}
#endif
