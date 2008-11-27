//
// pmm.h -- Defines the functions related to physical memory management.
//          Written for JamesM's kernel development tutorials.
//

#ifndef PMM_H
#define PMM_H

#include "common.h"

void init_pmm ();

uint32_t pmm_alloc_page ();

void pmm_free_page ();


#endif
