#if CHAPTER >= 7
//
// pmm.c -- Defines the functions related to physical memory management.
//          Written for JamesM's kernel development tutorials.
//

#include "pmm.h"
#include "vmm.h"
#include "common.h"

uint32_t pmm_stack_loc = PMM_STACK_ADDR;
uint32_t pmm_stack_max = PMM_STACK_ADDR;
uint32_t pmm_location;
char pmm_paging_active = 0;

void init_pmm (uint32_t start)
{
  // Ensure the initial page allocation location is page-aligned.
  pmm_location = (start + 0x1000) & PAGE_MASK;
}

uint32_t pmm_alloc_page ()
{
  if (pmm_paging_active)
  {
    // Quick sanity check.
    if (pmm_stack_loc == PMM_STACK_ADDR)
      panic ("Error:out of memory.");

    // Pop off the stack.
    pmm_stack_loc -= sizeof (uint32_t);
    uint32_t *stack = (uint32_t*)pmm_stack_loc;
  
    return *stack;
  }
  else
  {
    return pmm_location += 0x1000;
  }
}

void pmm_free_page (uint32_t p)
{
  // Ignore any page under "location", as it may contain important data initialised
  // at boot (like paging structures!)
  if (p < pmm_location) return;

  // If we've run out of space on the stack...
  if (pmm_stack_max <= pmm_stack_loc)
  {
    // Map the page we're currently freeing at the top of the free page stack.
    map (pmm_stack_max, p, PAGE_PRESENT | PAGE_WRITE);
    // Increase the free page stack's size by one page.
    pmm_stack_max += 4096;
  }
  else
  {
    // Else we have space on the stack, so push.
    uint32_t *stack = (uint32_t*)pmm_stack_loc;
    *stack = p;
    pmm_stack_loc += sizeof (uint32_t);
  }
}
#endif // CHAPTER >= 7
