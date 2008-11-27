//
// pmm.c -- Defines the functions related to physical memory management.
//          Written for JamesM's kernel development tutorials.
//

#include "pmm.h"
#include "common.h"

uint32_t location = 0x200000;

void init_pmm ()
{
}

uint32_t pmm_alloc_page ()
{
  uint32_t l = location;
  location = (uint32_t)location + 0x1000;
  return l;
}

void pmm_free_page ()
{
}

