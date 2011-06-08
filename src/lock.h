//
// lock.h -- Declares functions and structures for the locking mechanism.
//           Written for JamesM's kernel development tutorials.
//

#include "common.h"
#include "thread.h"
#include "scheduler.h"

#define SPINLOCK_LOCKED 0
#define SPINLOCK_UNLOCKED 1

typedef uint32_t spinlock_t;

typedef struct semaphore
{
  uint32_t counter;
  spinlock_t lock;
  thread_list_t queue;
} semaphore_t;

void spinlock_lock (spinlock_t *lock);

void spinlock_unlock (spinlock_t *lock);

uint32_t spinlock_trylock (spinlock_t *lock);

void semaphore_init (semaphore_t *sem, uint32_t value);

void semaphore_destroy (semaphore_t *sem);

void semaphore_p (semaphore_t *sem);

void semaphore_v (semaphore_t *sem);