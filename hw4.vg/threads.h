// threads.h
#ifndef THREADS_H
#define THREADS_H
#include <pthread.h>

typedef void *(*ThreadFunc)(void *);

// Launches n threads running the given function
pthread_t *launch_threads(int n, ThreadFunc func, void *arg);

// Waits for n threads to complete and frees the thread array
void join_threads(int n, pthread_t *threads);

#endif