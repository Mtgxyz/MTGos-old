#include <pmm.hpp>
#include <multiboot.h>
extern "C" const int kernel_start;
extern "C" const int kernel_end; //those are voids actually
namespace MTGosHAL {
PMM::PMM(struct multiboot_info * mb_info) {
	for(int i=0;i<0x8000;i++)
		bitmap[i]=0;
	struct multiboot_mmap_entry* mmap = (struct multiboot_mmap_entry*) mb_info->mmap_addr;
	struct multiboot_mmap_entry* mmap_end = (struct multiboot_mmap_entry*) ((unsigned int) mb_info->mmap_addr + mb_info->mmap_length);
	while (mmap < mmap_end) {
		if (mmap->type == 1) {
			// Der Speicherbereich ist frei, entsprechend markieren
			uintptr_t addr = mmap->addr;
			uintptr_t end_addr = addr + mmap->len;
			while (addr < end_addr) {
				*this << (void*) addr;
				addr += 0x1000;
			}
		}
	}
	mmap++;
	unsigned int addr = (unsigned int) &kernel_start;
	while(addr < (unsigned int) &kernel_end) {
		markUsed((void*)addr);
		addr+=0x1000;
	}
}
auto PMM::markUsed(void * addr) -> void {
	unsigned int address=(unsigned int)addr;
	address>>=12;
	int index=address>>5;
	int bit=1<<(address&0x1F);
	bitmap[index]&=~bit;
}
auto PMM::operator >> (void * &addr) -> PMM & {
	for(int i=0;i<0x8000;i++) {
		if(!bitmap[i])
			continue;
		for(int j=0;j<32;j++) {
			if(bitmap[i]&(1<<j)) {
				//We found a free page!
				bitmap[i]&=(1<<j);
				addr=(void*)(((i<<5)+j)<<12);
				return *this;
			}
		}
	}
	addr=nullptr;
	return *this;
}
auto PMM::operator << (const void * addr) -> PMM & {
	unsigned int address=(unsigned int)addr;
	address>>=12;
	int index=address>>5;
	int bit=1<<(address&0x1F);
	bitmap[index]|=bit;
	return *this;
}
}