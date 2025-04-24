#ifndef memory_h
#define memory_h
#include "types.h"

void* memset(void* dest, den val, aisle count);
unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
unsigned short *memcpyw(unsigned short *dest, const unsigned short *src, int count);
int strlen(const char *str);

#endif