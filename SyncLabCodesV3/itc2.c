#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define TOTAL_CUSTOMERS 3
int customer_ids[TOTAL_CUSTOMERS] = { 1, 2, 3 };

void* customer(void* data);   // thread function that wait's on the condition
void* chef(void* data); // thread function that signals the condition, eventually notifying the other thread(s)

int food_amount = 0;

pthread_mutex_t mutex; // decalre mutex
pthread_cond_t  condition = PTHREAD_COND_INITIALIZER; // declare condition to wait on and signal to

int main() {
    pthread_mutex_init(&mutex, NULL); // init mutex, must be before creating threads

    pthread_t chef_thread;
    pthread_t customer_threads[TOTAL_CUSTOMERS];

    for (int i = 0; i < TOTAL_CUSTOMERS; i++)
        pthread_create(&customer_threads[i], NULL, (void*)customer, &customer_ids[i]);
    
    sleep(3);

    pthread_create(&chef_thread, NULL, (void *)chef, NULL);

    for (int i = 0; i < TOTAL_CUSTOMERS; i++)
        pthread_join(customer_threads[i], NULL);
    pthread_join(chef_thread, NULL);

    pthread_mutex_destroy(&mutex); // destroy mutex, must be after joining threads
    pthread_cond_destroy(&condition);

	return 0;
}

void* customer(void* data) {
    int id = *((int *)data);

    pthread_mutex_lock(&mutex);

    // int iter_count = 0;

    while(food_amount == 0) {
        printf("[CUSTOMER %d] I'm waiting for the food.\n", id);
        // unlock(mutex)
        pthread_cond_wait(&condition, &mutex);
        // lock(mutex)
        // iter_count++;
    }

    // printf("[CUSTOMER %d] iter_count = %d\n", id, iter_count);

    food_amount--;
    // sleep(1);
    printf("[CUSTOMER %d] I've ate mine, there are %d remaining.\n", id, food_amount);

    pthread_mutex_unlock(&mutex);
}

void* chef(void* data) {
    printf("[CHEF] I'm starting to cook.\n");

    sleep(2);
    pthread_mutex_lock(&mutex);
    food_amount = TOTAL_CUSTOMERS;
    pthread_mutex_unlock(&mutex);

    printf("[CHEF] I've finished cooking.\n");

    // pthread_cond_broadcast(&condition);
    for (int i = 0; i < TOTAL_CUSTOMERS; i++)
        pthread_cond_signal(&condition);
    
}