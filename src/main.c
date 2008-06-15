// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "multiboot.h"

int main(struct multiboot *mboot_ptr, u32int initial_stack)
{
  return 0xdeadbeef;
}
