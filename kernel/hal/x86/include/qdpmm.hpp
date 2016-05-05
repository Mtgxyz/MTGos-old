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
	auto markUsed(const void * addr) -> void;
	auto init(struct multiboot_info*) -> void;
	auto operator >> (void * &addr) -> QDPMM &; //alloc
	auto operator << (const void * addr) -> QDPMM &; //free
};
}
#endif
