// mtq.c
#include <stdlib.h>
#include <pthread.h>
#include "mtq.h"
#include "error.h"

struct MtqRep {
    Deq deq;
    int capacity;
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
};

Mtq mtq_new(int capacity) {
    Mtq q = malloc(sizeof(struct MtqRep));
    if (!q) ERROR("Failed to allocate memory for Mtq");

    q->deq = deq_new();
    q->capacity = capacity;
    
    // Initialize lock and condition variables
    if (pthread_mutex_init(&q->lock, NULL) != 0) ERROR("Failed to init mutex");
    if (pthread_cond_init(&q->not_empty, NULL) != 0) ERROR("Failed to init cv");
    if (pthread_cond_init(&q->not_full, NULL) != 0) ERROR("Failed to init cv");
    
    return q;
}

void mtq_free(Mtq q) {
    if (!q) return;
    
    // We pass 0 (NULL) as the second argument because the consumer threads 
    // already extract and free the Moles via mole_whack().
    deq_del(q->deq, 0); 
    
    // Destroy MT primitives
    pthread_mutex_destroy(&q->lock);
    pthread_cond_destroy(&q->not_empty);
    pthread_cond_destroy(&q->not_full);
    
    free(q);
}

void mtq_tail_put(Mtq q, void *data) {
    pthread_mutex_lock(&q->lock);
    
    // Wait if the queue has reached max capacity (0 = unbounded)
    while (q->capacity > 0 && deq_len(q->deq) >= q->capacity) {
        pthread_cond_wait(&q->not_full, &q->lock);
    }
    
    deq_tail_put(q->deq, data);
    
    // Signal consumers that the queue is no longer empty
    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->lock);
}

void *mtq_head_get(Mtq q) {
    pthread_mutex_lock(&q->lock);
    
    // Wait if the queue is entirely empty
    while (deq_len(q->deq) == 0) {
        pthread_cond_wait(&q->not_empty, &q->lock);
    }
    
    void *data = deq_head_get(q->deq);
    
    // Signal producers that the queue is no longer full
    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->lock);
    
    return data;
}