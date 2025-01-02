#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int thread_ids[2] = { 1, 2 };

int count = 0;  // our mutable shared variable

void *thread_function(int *id);
pthread_mutex_t mutex; // decalre mutex

int main() {
    pthread_mutex_init(&mutex, NULL); // init mutex, must be before creating threads
	pthread_t threads[2];

	pthread_create(&threads[0], NULL, (void *)thread_function, &thread_ids[0]);
	pthread_create(&threads[1], NULL, (void *)thread_function, &thread_ids[1]);

	pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    pthread_mutex_destroy(&mutex); // destroy mutex, must be after joining threads

	printf("Total count: %d\n", count);
	return 0;
}

void *thread_function(int *id) {
	printf("Entered in thread: %d\n", *id);
	for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex); // lock/acquire
		count++;
        pthread_mutex_unlock(&mutex); // unlock/release
	}
}