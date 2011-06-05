#if CHAPTER >= 9
//
// scheduler.h -- Defines functions and structures for preempting threads.
//                Written for JamesM's kernel development tutorials.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "common.h"
#include "thread.h"

typedef struct thread_list
{
  thread_t *thread;
  struct thread_list *next;
} thread_list_t;

void init_scheduler (thread_t *initial_thread);

void thread_is_ready (thread_t *t);

void thread_not_ready (thread_t *t);

void schedule ();

#endif
#endif
