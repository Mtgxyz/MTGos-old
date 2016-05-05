#ifndef _PMM_HPP
#define _PMM_HPP
#include <qdpmm.hpp>
#include <stdint.h>
#include <multiboot.h>
namespace MTGosHAL {
class PMM {
private:
	uint16_t **pageTable;
  QDPMM qdpmm;
public:
	PMM();
  auto markUsed(const void * addr, uint32_t length) -> bool;
  auto init(struct multiboot_info*) -> void;
  auto operator >> (void * &addr) -> PMM &; //alloc
  auto operator << (const void * addr) -> PMM &; //free
  auto operator()(int pages) -> void*; //alloc_multipage
};
}
#endif
