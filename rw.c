#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

// Shared data
int sharedData = 0;
int readerCount = 0;

// Synchronization variables
sem_t mutex;
sem_t rwMutex;

void *readerFunction(void *readerId) {
    int tid = *(int *)readerId;

    // Entering the reader process
    sem_wait(&mutex);
    readerCount++;
    if (readerCount == 1) {
        sem_wait(&rwMutex); // First reader locks the resource
    }
    sem_post(&mutex);

    // Reading the shared data
    printf("Reader %d: Reading shared data: %d\n", tid, sharedData);

    // Exiting the reader process
    sem_wait(&mutex);
    readerCount--;
    if (readerCount == 0) {
        sem_post(&rwMutex); // Last reader unlocks the resource
    }
    sem_post(&mutex);

    pthread_exit(NULL);
}

void *writerFunction(void *writerId) {
    int tid = *(int *)writerId;

    // Entering the writer process
    sem_wait(&rwMutex);

    // Modifying the shared data
    sharedData = tid + 1;
    printf("Writer %d: Writing shared data: %d\n", tid, sharedData);

    // Exiting the writer process
    sem_post(&rwMutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t readerThreads[NUM_READERS];
    pthread_t writerThreads[NUM_WRITERS];
    int readerIds[NUM_READERS];
    int writerIds[NUM_WRITERS];

    // Initialize the semaphores
    if (sem_init(&mutex, 0, 1) != 0 || sem_init(&rwMutex, 0, 1) != 0) {
        fprintf(stderr, "Failed to initialize semaphores.\n");
        return 1;
    }

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        readerIds[i] = i + 1;
        if (pthread_create(&readerThreads[i], NULL, readerFunction, &readerIds[i]) != 0) {
            fprintf(stderr, "Failed to create reader thread %d.\n", i + 1);
            return 1;
        }
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writerIds[i] = i + 1;
        if (pthread_create(&writerThreads[i], NULL, writerFunction, &writerIds[i]) != 0) {
            fprintf(stderr, "Failed to create writer thread %d.\n", i + 1);
            return 1;
        }
    }

    // Join reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        if (pthread_join(readerThreads[i], NULL) != 0) {
            fprintf(stderr, "Failed to join reader thread %d.\n", i + 1);
            return 1;
        }
    }

    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        if (pthread_join(writerThreads[i], NULL) != 0) {
            fprintf(stderr, "Failed to join writer thread %d.\n", i + 1);
            return 1;
        }
    }

    // Destroy the
}
