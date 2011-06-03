// common.h -- Defines typedefs and some global functions.
//             From JamesM's kernel development tutorials.

#ifndef COMMON_H
#define COMMON_H

// Some standard typedefs, to standardise sizes across platforms.
// These typedefs are written for 32-bit X86.
typedef unsigned int   uint32_t;
typedef          int   int32_t;
typedef unsigned short uint16_t;
typedef          short int16_t;
typedef unsigned char  uint8_t;
typedef          char  int8_t;

#if CHAPTER >= 4
#include "printk.h"
#endif
#if CHAPTER >= 8
#include "panic.h"
#endif
#if CHAPTER >= 7
#include "heap.h"
#endif

#if CHAPTER >= 3
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
#endif // CHAPTER >= 3

#endif // COMMON_H
