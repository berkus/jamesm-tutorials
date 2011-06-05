#if CHAPTER >= 9
// 
// thread.c -- Defines functions and structures for multithreading.
//             Written for JamesM's kernel development tutorials.
//

#include "thread.h"

thread_t *current_thread;
uint32_t next_tid = 0;

static void thread_exit ();

thread_t *init_threading ()
{
  thread_t *thread = kmalloc (sizeof (thread_t));
  thread->id  = next_tid++;
  
  current_thread = thread;

  return thread;
}

thread_t *create_thread (int (*fn)(void*), void *arg, uint32_t *stack)
{
  thread_t *thread = kmalloc (sizeof (thread_t));
  memset (thread, 0, sizeof (thread_t));
  thread->id = next_tid++;
  
  *--stack = (uint32_t)arg;
  *--stack = (uint32_t)&thread_exit; // Fake return address.
  *--stack = (uint32_t)fn;
  *--stack = 0; // Fake EBP.
  thread->ebp = (uint32_t)stack;
  thread->esp = (uint32_t)stack;

  return thread;
}
#if 0
void switch_thread (thread_t *next)
{

    asm volatile ("mov %%esp, %0; mov %%ebp, %1" : "=r" (current_thread->esp), "=r"(current_thread->ebp));
  asm volatile ("mov %%ebp, %0" : "=r" (current_thread->ebp));
  asm volatile ("mov %%ebx, %0" : "=r" (current_thread->ebx));
  asm volatile ("mov %%esi, %0" : "=r" (current_thread->esi));
  asm volatile ("mov %%edi, %0" : "=r" (current_thread->edi));

  current_thread = next;

  asm volatile ("mov %0, %%edi" : : "r" (next->edi));
  asm volatile ("mov %0, %%esi" : : "r" (next->esi));
  asm volatile ("mov %0, %%ebx" : : "r" (next->ebx));
  asm volatile ("mov %0, %%esp" : : "r" (next->esp));
  asm volatile ("mov %0, %%ebp" : : "r" (next->ebp));
}
#endif
void thread_exit ()
{
  register uint32_t val asm ("eax");

  printk ("Thread exited with value %d\n", val);
  for (;;) ;
}
#endif // CHAPTER >= 9
