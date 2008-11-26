//
// gdt.c - Initialises the GDT and IDT, and defines the 
//         default ISR and IRQ handler.
//         Based on code from Bran's kernel development tutorials.
//         Rewritten for JamesM's kernel development tutorials.
//

#include "common.h"
#include "gdt.h"

// Lets us access our ASM functions from our C code.
extern void gdt_flush (uint32_t);

// Internal function prototypes.
static void gdt_set_gate (int32_t,uint32_t,uint32_t,uint8_t,uint8_t);

// The GDT itself.
gdt_entry_t gdt_entries [6];
// Pointer structure to give to the CPU.
gdt_ptr_t gdt_ptr;

void init_gdt ()
{
  // We have six entries in the GDT - two for kernel mode, two for user mode, the NULL descriptor,
  // and one for the TSS (task state segment)

  // The limit is the last valid byte from the start of the GDT - i.e. the size of the GDT - 1.
  gdt_ptr.limit = sizeof (gdt_entry_t) * 6 - 1;
  gdt_ptr.base = (uint32_t) &gdt_entries;

  gdt_set_gate (0, 0, 0, 0, 0);             // Null segment.
  gdt_set_gate (1, 0, 0xFFFFF, 0x9A, 0xCF); // Code segment.
  gdt_set_gate (2, 0, 0xFFFFF, 0x92, 0xCF); // Data segment.
  gdt_set_gate (3, 0, 0xFFFFF, 0xFA, 0xCF); // User mode code segment.

  // Inform the CPU about our GDT.
  gdt_flush ((uint32_t) &gdt_ptr);
}

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;
    
    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}
