#ifndef _PMM_HPP
#define _PMM_HPP
#include <stdint.h>
namespace MTGosHAL {
class PMM {
private:
	uint32_t bitmap[0x8000]; //Enough for 4 GB
	auto markUsed(void * addr) -> void;
public:
	PMM();
	auto operator >> (void * &addr) -> PMM &; //alloc
	auto operator << (const void * addr) -> PMM &; //free
	auto operator()(int pages) -> void*; //alloc_multipage

};
}
#endif
