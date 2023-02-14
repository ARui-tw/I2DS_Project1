// REF: https://stackoverflow.com/questions/5385777/implementing-a-fifo-mutex-in-pthreads

#include <pthread.h>

#define TICKET_LOCK_INITIALIZER { PTHREAD_COND_INITIALIZER, PTHREAD_MUTEX_INITIALIZER }

typedef struct ticket_lock {
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    unsigned long queue_head, queue_tail;
} ticket_lock_t;

void ticket_lock(ticket_lock_t *ticket);
void ticket_unlock(ticket_lock_t *ticket);