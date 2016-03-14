#include <string.h>
__attribute__((optimize(0))) void memmove(void* dst, void* src, uint32_t size) {
	uint8_t* from=(uint8_t*)src;
	uint8_t* to=(uint8_t*)dst;
	if((src<dst)&&((src+size)>dst)) {
		for(int i=size-1;i>=0;i--)
			to[i]=from[i]; //This would get optimized by gcc to memmove(dst, src, size); if optimizations are enabled.
	} else if(src != dst) {
		for(int i=0;i<size;i++)
			to[i]=from[i]; //This would get optimized by gcc to memmove(dst, src, size); if optimizations are enabled.
	}
}