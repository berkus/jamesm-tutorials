// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "multiboot.h"

int main(multiboot_t *mboot_ptr, uint32_t initial_stack)
{
  return 0xdeadbeef;
}
