// threads.c
#include <stdlib.h>
#include "threads.h"
#include "error.h"

pthread_t *launch_threads(int n, ThreadFunc func, void *arg) {
    // Allocate array to hold thread IDs
    pthread_t *threads = malloc(n * sizeof(pthread_t));
    if (!threads) ERROR("Failed to allocate memory for threads array");

    for (int i = 0; i < n; i++) {
        if (pthread_create(&threads[i], NULL, func, arg) != 0) {
            ERROR("pthread_create failed for thread %d", i);
        }
    }
    return threads;
}

void join_threads(int n, pthread_t *threads) {
    if (!threads) return;
    
    for (int i = 0; i < n; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            ERROR("pthread_join failed for thread %d", i);
        }
    }
    // Free the thread array to prevent valgrind leaks
    free(threads);
}