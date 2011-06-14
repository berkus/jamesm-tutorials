#if CHAPTER >= 9
// 
// thread.h -- Declares functions and structures for multithreading.
//             Written for JamesM's kernel development tutorials.
//

#ifndef THREAD_H
#define THREAD_H

#include "common.h"

typedef struct
{
  uint32_t esp, ebp, ebx, esi, edi, eflags;
  uint32_t id;                  // Thread ID.
} thread_t;

thread_t *init_threading ();

thread_t *create_thread (int (*fn)(void*), void *arg, uint32_t *stack);

struct thread_list;

void switch_thread (struct thread_list *next);

#endif
#endif // CHAPTER >= 9
