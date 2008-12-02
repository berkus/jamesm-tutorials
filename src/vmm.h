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

typedef uint32_t page_directory_t;

// Sets up the environment, page directories etc and enables paging.
void init_vmm ();

// Changes address space.
void switch_page_directory (page_directory_t *pd);

void map (uint32_t va, uint32_t pa, uint32_t flags);

void unmap (uint32_t va);

#endif

