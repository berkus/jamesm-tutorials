#if CHAPTER >= 9
//
// scheduler.c -- Defines functions and structures for preempting threads.
//                Written for JamesM's kernel development tutorials.
//

#include "scheduler.h"

thread_list_t *ready_queue = 0;
thread_list_t *current_thread = 0;

void init_scheduler (thread_t *initial_thread)
{
  current_thread = (thread_list_t*) kmalloc (sizeof (thread_list_t*));
  current_thread->thread = initial_thread;
  current_thread->next = 0;
  ready_queue = 0;
}

void thread_is_ready (thread_t *t)
{
  // Create a new list item for the new thread.
  thread_list_t *item = (thread_list_t*) kmalloc (sizeof (thread_list_t*));
  item->thread = t;
  item->next = 0;

  if (!ready_queue)
  {
    // Special case if the ready queue is empty.
    ready_queue = item;
  }
  else
  {
    // Iterate through the ready queue to the end.
    thread_list_t *iterator = ready_queue;
    while (iterator->next)
      iterator = iterator->next;

    // Add the item.
    iterator->next = item;
  }
}

void thread_not_ready (thread_t *t)
{
  // Attempt to find the thread in the ready queue.
  thread_list_t *iterator = ready_queue;

  // Special case if the thread is first in the queue.
  if (iterator->thread == t)
  {
    ready_queue = iterator->next;
    kfree (iterator);
    return;
  }

  while (iterator->next)
  {
    if (iterator->next->thread == t)
    {
      thread_list_t *tmp = iterator->next;
      iterator->next = tmp->next;
      kfree (tmp);
    }
    iterator = iterator->next;
  }
}

void schedule ()
{
  if (!ready_queue) return;

  // Iterate through the ready queue to the end.
  thread_list_t *iterator = ready_queue;
  while (iterator->next)
    iterator = iterator->next;

  // Add the old thread to the end of the queue, and remove it from the start.
  iterator->next = current_thread;
  current_thread->next = 0;
  thread_list_t *new_thread = ready_queue;

  ready_queue = ready_queue->next;

  // Switch to the new thread.
  switch_thread (new_thread);
}
#endif // CHAPTER >= 9
