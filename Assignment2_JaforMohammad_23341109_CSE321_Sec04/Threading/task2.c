#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5
#define NUM_INTEGERS 5

void *printIntegers(void *threadID) {
    int tid = *((int *)threadID);

    for (int i = 1; i <= NUM_INTEGERS; i++) {
        printf("Thread %d prints %d\n", tid, tid * NUM_INTEGERS + i);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadIDs[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        threadIDs[i] = i;
        int rc = pthread_create(&threads[i], NULL, printIntegers, (void *)&threadIDs[i]);

        if (rc) {
            fprintf(stderr, "Error: Unable to create thread %d\n", i);
            return 1;
        }

        pthread_join(threads[i], NULL);
    }

    pthread_exit(NULL);
    return 0;
}
