// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "multiboot.h"
#include "common.h"
#include "monitor.h"
#include "gdt.h"
#include "idt.h"

static void int_3_handler (registers_t *regs)
{
  printk ("Interrupt 3 received!\n");
}

int main(multiboot_t *mboot_ptr)
{
  monitor_clear();
  printk ("Hello, world!\n");

  init_gdt ();
  init_idt ();
  
  register_interrupt_handler (3, &int_3_handler);

  asm volatile("int $0x3");
  asm volatile("int $0x4");
  
  return 0xdeadbeef;
}
