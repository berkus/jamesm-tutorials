#if CHAPTER >= 4
//
// idt.c - Initialises the GDT and IDT, and defines the 
//         default ISR and IRQ handler.
//         Based on code from Bran's kernel development tutorials.
//         Rewritten for JamesM's kernel development tutorials.
//

#include "common.h"
#include "idt.h"

// Lets us access our ASM functions from our C code.
extern void idt_flush(uint32_t);

// Internal function prototypes.
static void idt_set_gate(uint8_t,uint32_t,uint16_t,uint8_t);

// The IDT itself.
idt_entry_t idt_entries [256];
// Pointer structure to give to the CPU.
idt_ptr_t idt_ptr;
// Array of interrupt handler functions.
interrupt_handler_t interrupt_handlers [256];

// Initialisation routine - zeroes all the interrupt service routines, and
// initialises the IDT.
void init_idt ()
{
  // Zero all interrupt handlers initially.
  memset (&interrupt_handlers, 0, sizeof (interrupt_handler_t) * 256);

  // Just like the GDT, the IDT has a "limit" field that is set to the last valid byte in the IDT,
  // after adding in the start position (i.e. size-1).
  idt_ptr.limit = sizeof (idt_entry_t) * 256 - 1;
  idt_ptr.base  = (uint32_t) &idt_entries;

  // Zero the IDT to start with.
  memset (&idt_entries, 0, sizeof (idt_entry_t) * 255);

#if CHAPTER >= 5
  // Remap the irq table.
  outb (0x20, 0x11);
  outb (0xA0, 0x11);
  outb (0x21, 0x20);
  outb (0xA1, 0x28);
  outb (0x21, 0x04);
  outb (0xA1, 0x02);
  outb (0x21, 0x01);
  outb (0xA1, 0x01);
  outb (0x21, 0x0);
  outb (0xA1, 0x0);
#endif // CHAPTER >= 5

  // Set each gate in the IDT that we care about - that is:
  // 0-32:  Used by the CPU to report conditions, both normal and error.
  // 255:   Will be used later as a way to execute system calls.
  idt_set_gate ( 0, (uint32_t)isr0 , 0x08, 0x8E);
  idt_set_gate ( 1, (uint32_t)isr1 , 0x08, 0x8E);
  idt_set_gate ( 2, (uint32_t)isr2 , 0x08, 0x8E);
  idt_set_gate ( 3, (uint32_t)isr3 , 0x08, 0x8E);
  idt_set_gate ( 4, (uint32_t)isr4 , 0x08, 0x8E);
  idt_set_gate ( 5, (uint32_t)isr5 , 0x08, 0x8E);
  idt_set_gate ( 6, (uint32_t)isr6 , 0x08, 0x8E);
  idt_set_gate ( 7, (uint32_t)isr7 , 0x08, 0x8E);
  idt_set_gate ( 8, (uint32_t)isr8 , 0x08, 0x8E);
  idt_set_gate ( 9, (uint32_t)isr9 , 0x08, 0x8E);
  idt_set_gate (10, (uint32_t)isr10, 0x08, 0x8E);
  idt_set_gate (11, (uint32_t)isr11, 0x08, 0x8E);
  idt_set_gate (12, (uint32_t)isr12, 0x08, 0x8E);
  idt_set_gate (13, (uint32_t)isr13, 0x08, 0x8E);
  idt_set_gate (14, (uint32_t)isr14, 0x08, 0x8E);
  idt_set_gate (15, (uint32_t)isr15, 0x08, 0x8E);
  idt_set_gate (16, (uint32_t)isr16, 0x08, 0x8E);
  idt_set_gate (17, (uint32_t)isr17, 0x08, 0x8E);
  idt_set_gate (18, (uint32_t)isr18, 0x08, 0x8E);
  idt_set_gate (19, (uint32_t)isr19, 0x08, 0x8E);
  idt_set_gate (20, (uint32_t)isr20, 0x08, 0x8E);
  idt_set_gate (21, (uint32_t)isr21, 0x08, 0x8E);
  idt_set_gate (22, (uint32_t)isr22, 0x08, 0x8E);
  idt_set_gate (23, (uint32_t)isr23, 0x08, 0x8E);
  idt_set_gate (24, (uint32_t)isr24, 0x08, 0x8E);
  idt_set_gate (25, (uint32_t)isr25, 0x08, 0x8E);
  idt_set_gate (26, (uint32_t)isr26, 0x08, 0x8E);
  idt_set_gate (27, (uint32_t)isr27, 0x08, 0x8E);
  idt_set_gate (28, (uint32_t)isr28, 0x08, 0x8E);
  idt_set_gate (29, (uint32_t)isr29, 0x08, 0x8E);
  idt_set_gate (30, (uint32_t)isr30, 0x08, 0x8E);
  idt_set_gate (31, (uint32_t)isr31, 0x08, 0x8E);
#if CHAPTER >= 5
  idt_set_gate (32, (uint32_t)irq0, 0x08, 0x8E);
  idt_set_gate (33, (uint32_t)irq1, 0x08, 0x8E);
  idt_set_gate (34, (uint32_t)irq2, 0x08, 0x8E);
  idt_set_gate (35, (uint32_t)irq3, 0x08, 0x8E);
  idt_set_gate (36, (uint32_t)irq4, 0x08, 0x8E);
  idt_set_gate (37, (uint32_t)irq5, 0x08, 0x8E);
  idt_set_gate (38, (uint32_t)irq6, 0x08, 0x8E);
  idt_set_gate (39, (uint32_t)irq7, 0x08, 0x8E);
  idt_set_gate (40, (uint32_t)irq8, 0x08, 0x8E);
  idt_set_gate (41, (uint32_t)irq9, 0x08, 0x8E);
  idt_set_gate (42, (uint32_t)irq10, 0x08, 0x8E);
  idt_set_gate (43, (uint32_t)irq11, 0x08, 0x8E);
  idt_set_gate (44, (uint32_t)irq12, 0x08, 0x8E);
  idt_set_gate (45, (uint32_t)irq13, 0x08, 0x8E);
  idt_set_gate (46, (uint32_t)irq14, 0x08, 0x8E);
  idt_set_gate (47, (uint32_t)irq15, 0x08, 0x8E);
  idt_set_gate (255, (uint32_t)isr255, 0x08, 0x8E);
#endif

  // Tell the CPU about our new IDT.
  idt_flush ((uint32_t)&idt_ptr);
}

static void idt_set_gate (uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
  idt_entries[num].base_lo = base & 0xFFFF;
  idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

  idt_entries[num].sel     = sel;
  idt_entries[num].always0 = 0;
  // We must uncomment the OR below when we get to using user-mode.
  // It sets the interrupt gate's privilege level to 3.
  idt_entries[num].flags   = flags /* | 0x60 */;
}

// This gets called from our ASM interrupt handler stub.
void idt_handler (registers_t *regs)
{
  if (interrupt_handlers [regs->int_no])
    interrupt_handlers [regs->int_no] (regs);
  else
  {
    printk ("Unhandled interrupt: %d\n", regs->int_no);
#if CHAPTER >= 6
    panic ("Unhandled interrupt");
#endif // CHAPTER >= 6
  }
}

void register_interrupt_handler (uint8_t n, interrupt_handler_t h)
{
  interrupt_handlers [n] = h;
}

#if CHAPTER >= 5
// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t *regs)
{
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs->int_no >= 40)
    {
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    outb(0x20, 0x20);

    if (interrupt_handlers[regs->int_no] != 0)
      interrupt_handlers[regs->int_no] (regs);
}
#endif

#endif // CHAPTER >= 4
