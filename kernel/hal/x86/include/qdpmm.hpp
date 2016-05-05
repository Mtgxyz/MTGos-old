#ifndef _QDPMM_HPP
#define _QDPMM_HPP
#include <stdint.h>
#include <multiboot.h>
namespace MTGosHAL {
class QDPMM {
private:
	uint32_t bitmap[0x8000]; //Enough for 4 GB
protected:
public:
	QDPMM();
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
