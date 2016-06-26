#include <string.h>
//Those pragmas are used to skip optimization for this function
#pragma GCC push_options
#pragma GCC optimize ("O0")
void memmove(void* dst, void* src, uint32_t size) {
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
void memcpy(void* dest, void* src, uint32_t size) {
	memmove(dest, src, size);
}
uint32_t strlen(const char* str) {
	uint32_t i=0;
	char* str2=(char*)((uintptr_t)str);
	while(*str2) {
		i++;
		str2++;
	}
	return i;
}
int strcmp(const char* str1, const char* str2) {
	uint32_t len1=strlen(str1);
	uint32_t len2=strlen(str2);
	if(len1>len2)
		return 1;
	else if (len1<len2)
		return -1;
	for(int i=0;i<len1;i++) {
		if(str1[i]!=str2[i])
			return str1[i]-str2[i];
	}
	return 0;
}
#pragma GCC pop_options
