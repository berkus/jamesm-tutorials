// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "multiboot.h"
#include "common.h"
#include "monitor.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"

int main(multiboot_t *mboot_ptr)
{
  monitor_clear();
  printk ("Hello, world!\n");

  init_gdt ();
  init_idt ();
  init_timer (20);

  asm volatile ("sti");

  for (;;);
  
  return 0xdeadbeef;
}
