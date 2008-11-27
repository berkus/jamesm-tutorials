//
// vmm.h -- Defines the interface for and structures relating to paging and virtual memory management.
//          Written for JamesM's kernel development tutorials.
//

#ifndef VMM_H
#define VMM_H

#include "common.h"

#define PAGE_DIR_VIRTUAL_ADDR   0xFFBFF000
#define PAGE_TABLE_VIRTUAL_ADDR 0xFFC00000
#define PAGE_DIR_IDX(x) ((uint32_t)x/1024)
#define PAGE_TABLE_IDX(x) ((uint32_t)x%1024)

#define PAGE_PRESENT   0x1
#define PAGE_WRITE     0x2
#define PAGE_USER      0x4
#define PAGE_MASK      0xFFFFF000

typedef struct
{
  uint32_t present     : 1;  // Page present in memory.
  uint32_t rw          : 1;  // Read-only if clear, read-write if set.
  uint32_t user        : 1;  // Supervisor level only if clear.
  uint32_t accessed    : 1;  // Has the page been accessed since last refresh?
  uint32_t dirty       : 1;  // Has the page been written to since last refresh?
  uint32_t unused      : 7;  // Amalgamation of unused and reserved bits.
  uint32_t frame       : 20; // Frame address (shifted right 12 bits).
} page_t;

typedef uint32_t page_directory_t;

// Sets up the environment, page directories etc and enables paging.
void initialise_vmm ();

// Changes address space.
void switch_page_directory (page_directory_t *pd);

void map (uint32_t va, uint32_t pa, uint32_t flags);

void unmap (uint32_t va);

#endif

