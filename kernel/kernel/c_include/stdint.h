#ifndef __LP64__
typedef signed char            int8_t;
typedef signed short           int16_t;
typedef signed int             int32_t;
typedef signed long long int   int64_t;
typedef unsigned char          uint8_t;
typedef unsigned short         uint16_t;
typedef unsigned int           uint32_t;
typedef unsigned long long int uint64_t;
typedef unsigned int           uintptr_t;
typedef unsigned int           size_t;
#else
typedef signed char            int8_t;
typedef signed short           int16_t;
typedef signed int             int32_t;
typedef signed long int        int64_t;
typedef unsigned char          uint8_t;
typedef unsigned short         uint16_t;
typedef unsigned int           uint32_t;
typedef unsigned long int      uint64_t;
typedef unsigned long int      uintptr_t;
typedef unsigned long int      size_t;
#endif
