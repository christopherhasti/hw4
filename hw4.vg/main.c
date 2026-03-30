// main.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "lawn.h"
#include "mole.h"
#include "mtq.h"
#include "threads.h"

// Producer thread function
static void *produce(void *a) {
    void **arg = a;
    Mtq q = (Mtq)arg[0];
    Lawn l = (Lawn)arg[1];
    
    // Place a newly created mole onto the safe queue
    mtq_tail_put(q, mole_new(l, 0, 0));
    return 0;
}

// Consumer thread function
static void *consume(void *a) {
    void **arg = a;
    Mtq q = (Mtq)arg[0];
    
    // Retrieve a mole from the queue and whack it
    Mole m = (Mole)mtq_head_get(q);
    mole_whack(m);
    return 0;
}

int main() {
    srandom(time(0));
    const int n = 10;
    
    Lawn lawn = lawn_new(0, 0);
    
    // Initialize queue with a capacity of 4 to introduce congestion 
    Mtq q = mtq_new(4); 

    // Package arguments to pass to threads
    void *args[2] = {q, lawn};

    // Launch n producer and n consumer threads
    pthread_t *producers = launch_threads(n, produce, args);
    pthread_t *consumers = launch_threads(n, consume, args);

    // Wait for all threads to finish their operations
    join_threads(n, producers);
    join_threads(n, consumers);

    // Free resources to ensure zero valgrind leaks
    mtq_free(q);
    lawn_free(lawn);
    
    return 0;
}