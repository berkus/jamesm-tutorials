//
// lock.c -- Defines functions and structures for the locking mechanism.
//           Written for JamesM's kernel development tutorials.
//

#include "lock.h"
#include "common.h"

extern uint32_t compare_and_swap (spinlock_t *, uint32_t, uint32_t);

void spinlock_lock (spinlock_t *lock)
{
  while (compare_and_swap (lock, SPINLOCK_LOCKED, SPINLOCK_UNLOCKED) == SPINLOCK_LOCKED);
  return 0;
}

void spinlock_unlock (spinlock_t *lock)
{
  compare_and_swap (lock, SPINLOCK_UNLOCKED, SPINLOCK_LOCKED);
  return 0;
}

uint32_t spinlock_trylock (spinlock_t *lock)
{
  return compare_and_swap (lock, SPINLOCK_UNLOCKED, SPINLOCK_LOCKED);
}

void semaphore_init (semaphore_t *sem, uint32_t value)
{
  sem->counter = value;
  sem->lock = SPINLOCK_UNLOCKED;
  thread_list_t queue = 0;
}

void semaphore_destroy (semaphore_t *sem)
{
  if(sem->queue != 0)
    panic("Trying to destroy active semaphore!");
  else
    kfree(sem);
}

void semaphore_p (semaphore_t *sem)
{
  spinlock_lock (sem->lock);

  if(sem->counter > 0)
    sem->counter--;
  else
  {
    if (sem->queue == 0)
    {
      sem->queue = (thread_list_t *) kmalloc (sizeof(thread_list_t *));
      sem->queue->thread = current_thread;
      sem->queue->next = 0;
    }
    else
    {
      thread_list_t current = sem->queue;
      while (current->next)
        current = current->next;
      current->next = (thread_list_t *) kmalloc (sizeof(thread_list_t *));
      current->next->thread = current_thread;
      current->next->next = 0;
    }
  }
  spinlock_unlock (sem->lock);
  thread_not_ready (current_thread);
  schedule ();
}

void semaphore_v (semaphore_t *sem) {
  spinlock_lock (sem->lock);

  if (sem->counter >= 0 && sem->queue == 0))
    sem->counter++;
  else
  {
    thread_is_ready (sem->queue->thread);
    sem->queue = sem->queue->next;
    schedule ();
  }
  
  spinlock_unlock (sem->lock);
}