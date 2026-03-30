// mtq.h
#ifndef MTQ_H
#define MTQ_H

// Assuming deq.h defines the MT-unsafe queue 'Deq' 
// from your earlier assignment.
#include "deq.h" 

typedef struct MtqRep *Mtq;

// Creates a new MT-safe queue. 0 capacity means unbounded.
Mtq mtq_new(int capacity);

// Frees the MT-safe queue and its resources
void mtq_free(Mtq q);

// Safely puts data at the tail of the queue
void mtq_tail_put(Mtq q, void *data);

// Safely gets data from the head of the queue
void *mtq_head_get(Mtq q);

#endif