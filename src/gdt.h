#if CHAPTER >= 4
// 
// gdt.h - Defines the interface for initialising the GDT.
//         Also defines needed structures.
//         Based on code from Bran's kernel development tutorials.
//         Rewritten for JamesM's kernel development tutorials.
//

#ifndef GDT_H
#define GDT_H

#include "common.h"

// Initialisation function.
void init_gdt ();

// This structure contains the value of one GDT entry.
// We use the attribute "packed" to tell GCC not to change
// any of the alignment in the structure.
typedef struct
{
  uint16_t limit_low;     // The lower 16 bits of the limit.
  uint16_t base_low;      // The lower 16 bits of the base.
  uint8_t base_middle;    // The next 8 bits of the base.
  uint8_t access;         // Access flags, determines what ring this segment can be used in.
  uint8_t granularity;
  uint8_t base_high;      // The last 8 bits of the base.
} __attribute__((packed)) gdt_entry_t;

// This struct describes a GDT pointer. It points to the start of
// our array of GDT entries, and is in the format required by the
// lgdt instruction.
typedef struct
{
    uint16_t limit;       // The Global Descriptor Table limit.
    uint32_t base;        // The address of the first gdt_entry_t struct.
} __attribute__((packed)) gdt_ptr_t;

#endif

#endif // CHAPTER >= 4
