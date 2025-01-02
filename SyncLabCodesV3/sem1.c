#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h> // this should be included

#define THREADC 6
int thread_ids[THREADC] = { 1, 2, 3, 4, 5, 6 };

int count = 0; // our mutable shared variable

void *thread_function(int *id);
sem_t semaphore; // decalre semaphore

int main() {
	int sempahore_value = 1;
    sem_init(&semaphore, 0, sempahore_value); // init semaphore with a value, must be before creating threads

	pthread_t threads[THREADC];

	for (int i = 0; i < THREADC; i++)
		pthread_create(&threads[i], NULL, (void *)thread_function, &thread_ids[i]);

	for (int i = 0; i < THREADC; i++)
		pthread_join(threads[i], NULL);

    sem_destroy(&semaphore); // destroy semaphore, must be after joining threads

	printf("Total count: %d\n", count);
	return 0;
}

void *thread_function(int *id) {
	printf("Entered in thread: %d\n", *id);
	for (int i = 0; i < 100000; i++) {
        sem_wait(&semaphore); // wait
		count++;
        sem_post(&semaphore); // signal
	}
}