#if CHAPTER >= 4
// 
// idt.h - Defines the interface for initialising the IDT.
//         Also defines needed structures.
//         Based on code from Bran's kernel development tutorials.
//         Rewritten for JamesM's kernel development tutorials.
//

#ifndef IDT_H
#define IDT_H

#include "common.h"

#if CHAPTER >= 5
// A few defines to make life a little easier
#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47
#endif // CHAPTER >= 5

// IDT initialisation function.
void init_idt ();

// This structure describes one interrupt gate.
typedef struct
{
  uint16_t base_lo;        // The lower 16 bits of the address to jump to.
  uint16_t sel;            // Kernel segment selector.
  uint8_t  always0;        // This must always be zero.
  uint8_t  flags;          // More flags. See documentation.
  uint16_t base_hi;        // The upper 16 bits of the address to jump to.
} __attribute__((packed)) idt_entry_t;

// A pointer structure used for informing the CPU about our IDT.
typedef struct
{
  uint16_t limit;
  uint32_t base;           // The address of the first element in our idt_entry_t array.
} __attribute__((packed)) idt_ptr_t;

// Structure containing register values when the CPU was interrupted.
typedef struct
{
  uint32_t ds;             // Data segment selector.
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
  uint32_t int_no, err_code; // Interrupt number and error code (if applicable).
  uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

// An interrupt handler. It is a pointer to a function which takes a pointer 
// to a structure containing register values.
typedef void (*interrupt_handler_t)(registers_t *);

// Allows us to register an interrupt handler.
void register_interrupt_handler (uint8_t n, interrupt_handler_t h);

// These extern directives let us access the addresses of our ASM ISR handlers.
extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr255();
#if CHAPTER >= 5
extern void irq0 ();
extern void irq1 ();
extern void irq2 ();
extern void irq3 ();
extern void irq4 ();
extern void irq5 ();
extern void irq6 ();
extern void irq7 ();
extern void irq8 ();
extern void irq9 ();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();
#endif // CHAPTER >= 5
#endif

#endif // CHAPTER >= 4
