#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

void *threadFunction(void *threadID) {
    int tid = *((int *)threadID);

    printf("thread-%d running\n", tid);


    printf("thread-%d closed\n", tid);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadIDs[NUM_THREADS];

    for (int i = 1; i <= NUM_THREADS; i++) {
        threadIDs[i-1] = i;
        int rc = pthread_create(&threads[i-1], NULL, threadFunction, (void *)&threadIDs[i-1]);

        if (rc) {
            fprintf(stderr, "Error: Unable to create thread %d\n", i);
            return 1;
        }

        pthread_join(threads[i-1], NULL);
    }

    pthread_exit(NULL);
    return 0;
}
