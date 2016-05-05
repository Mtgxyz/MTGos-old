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
	auto markUsed(void * addr) -> void;
public:
	PMM();
  template <typename T>
  auto markUsed(T * addr, uint32_t length) -> void;
  auto init(struct multiboot_info*) -> void;
  template <typename T>
  auto operator >> (T * &addr) -> QDPMM &; //alloc
  template <typename T>
  auto operator << (const T * addr) -> QDPMM &; //free
};
}
#endif
