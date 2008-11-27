// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "multiboot.h"
#include "common.h"
#include "monitor.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "vmm.h"

int main(multiboot_t *mboot_ptr)
{
  monitor_clear();

  init_gdt ();
  init_idt ();
  init_timer (20);
  init_pmm ();
  init_vmm ();

  printk ("Paging initialised.\n");

  printk ("Mapping page...\n");
  uint32_t addr = 0x900000;
  map (addr, 0x500000, PAGE_PRESENT|PAGE_WRITE);
  printk ("Accessing page...\n");

  volatile uint32_t *_addr  = (volatile uint32_t*)addr;
  *_addr = 0x567;
  printk ("*addr: %x\n", *_addr);

  printk ("Unmapping page...\n");
  unmap (addr);

  printk ("Trying to access again (should page fault)...\n");
  *_addr = 0x678;

  asm volatile ("sti");

  for (;;);
  
  return 0xdeadbeef;
}
