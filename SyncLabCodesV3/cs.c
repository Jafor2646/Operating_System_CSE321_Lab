#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int thread_ids[2] = { 1, 2 };

int count = 0;  // our mutable shared variable

void *thread_function(int *id);

int main() {
	pthread_t threads[2];
	pthread_create(&threads[0], NULL, (void *)thread_function, &thread_ids[0]);
	pthread_create(&threads[1], NULL, (void *)thread_function, &thread_ids[1]);

	pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

	printf("Total count: %d\n", count);
	return 0;
}

void *thread_function(int *id) {
	printf("Entered in thread: %d\n", *id);
	for (int i = 0; i < 100000; i++) {
		count++;
	}
}