#ifndef _PMM3_HPP
#define _PMM3_HPP
#include <stdint.h>
#include <multiboot.h>
namespace MTGosHAL {
class PMM3 {
private:
	uint32_t bitmap[0x8000]; //Enough for 512 GB (2MB pages)
protected:
public:
	PMM3();
	auto markUsed(const void * addr) -> void;
	auto init(struct multiboot_info*) -> void;
	auto operator >> (void * &addr) -> PMM3 &; //alloc
	auto operator << (const void * addr) -> PMM3 &; //free
};
}
#endif
