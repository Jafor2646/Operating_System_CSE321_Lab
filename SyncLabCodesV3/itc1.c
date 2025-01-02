#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* i_will_wait(void* data);   // thread function that wait's on the condition
void* i_will_notify(void* data); // thread function that signals the condition, eventually notifying the other thread

int some_value = 0;

pthread_mutex_t mutex; // decalre mutex
pthread_cond_t  condition = PTHREAD_COND_INITIALIZER; // declare condition to wait on and signal to

int main() {
    pthread_mutex_init(&mutex, NULL); // init mutex, must be before creating threads
	pthread_t waiter;
    pthread_t notifier;

	pthread_create(&waiter,   NULL, (void *)i_will_wait,   NULL);
	pthread_create(&notifier, NULL, (void *)i_will_notify, NULL);

	pthread_join(waiter,   NULL);
    pthread_join(notifier, NULL);

    pthread_mutex_destroy(&mutex); // destroy mutex, must be after joining threads

	return 0;
}

void* i_will_wait(void* data) {
    printf("[WAITER] I'm going to waiting state until I have been notified.\n");

    pthread_mutex_lock(&mutex);

    // wait until the other threads notifies/signals me.
    pthread_cond_wait(&condition, &mutex); // Wait for condition variable COND to be signaled or broadcast.
    // MUTEX is assumed to be locked before.

    printf("[WAITER] I've been notified, the value I got is %d.\n", some_value);

    pthread_mutex_unlock(&mutex);
}

void* i_will_notify(void* data) {
    int sleep_time = 2;
    printf("[NOTIFER] I'm going to notify the other thread after %d second(s).\n", sleep_time);

    sleep(sleep_time); // I will sleep to simulate a processing delay
    some_value = 1984; // Literally 1984

    printf("[NOTIFER] Notifying right now.\n");

    pthread_cond_signal(&condition); // Wake up one thread waiting for condition variable
    // this eventually notifies the other thread
}