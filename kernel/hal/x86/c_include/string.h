#ifndef _STRING_H
#define _STRING_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
void memmove(void* dst, void* src, uint32_t size);
uint32_t strlen(const char* str);
#ifdef __cplusplus
}
#endif
#endif
