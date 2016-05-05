#ifndef _PMM_HPP
#define _PMM_HPP
#include <stdint.h>
namespace MTGosHAL {
class PMM {
private:
	uint32_t bitmap[0x8000]; //Enough for 4 GB
public:
	template <typename T>
	auto markUsed(T * addr) -> void;
	auto init(struct multiboot_info*) -> void;
	template <typename T>
	auto operator >> (T * &addr) -> QDPMM &; //alloc
	template <typename T>
	auto operator << (const T * addr) -> QDPMM &; //free

};
}
#endif
