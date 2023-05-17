#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 2

// Global variables
int counter = 0;
sem_t mutex;

void *threadFunction(void *threadId) {
    int tid = *(int *)threadId;

    printf("Thread %d: Waiting to enter the critical section...\n", tid);

    // Acquire the semaphore
    sem_wait(&mutex);

    printf("Thread %d: Entered the critical section.\n", tid);

    // Critical section
    for (int i = 0; i < 100000; i++) {
        counter++;
    }

    printf("Thread %d: Counter value after increment: %d\n", tid, counter);

    printf("Thread %d: Exiting the critical section.\n", tid);

    // Release the semaphore
    sem_post(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadIds[NUM_THREADS];

    // Initialize the semaphore
    if (sem_init(&mutex, 0, 1) != 0) {
        fprintf(stderr, "Failed to initialize semaphore.\n");
        return 1;
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threadIds[i] = i;
        if (pthread_create(&threads[i], NULL, threadFunction, &threadIds[i]) != 0) {
            fprintf(stderr, "Failed to create thread %d.\n", i);
            return 1;
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Failed to join thread %d.\n", i);
            return 1;
        }
    }

    // Destroy the semaphore
    sem_destroy(&mutex);

    return 0;
}
