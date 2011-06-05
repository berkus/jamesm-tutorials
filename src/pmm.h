#if CHAPTER >= 7
//
// pmm.h -- Defines the functions related to physical memory management.
//          Written for JamesM's kernel development tutorials.
//

#ifndef PMM_H
#define PMM_H

#include "common.h"

#define PMM_STACK_ADDR 0xFF000000

void init_pmm (uint32_t start);

uint32_t pmm_alloc_page ();

void pmm_free_page (uint32_t p);


#endif
#endif // CHAPTER >= 7
