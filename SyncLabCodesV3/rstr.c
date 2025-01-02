#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h> // this should be included

int food_plate = 0; // declare a variable to hold our "foods". 0 is an empty food plate.

void* chef(void* data);
void* customer(void* data);

sem_t semaphore; // decalre semaphore

int main() {
	int sempahore_value = 0; // init with an already waiting state
    sem_init(&semaphore, 0, sempahore_value); // init semaphore with a value, must be before creating threads

	pthread_t chef_thread;
    pthread_t customer_thread;

    pthread_create(&customer_thread, NULL, (void *)customer, NULL);
    pthread_create(&chef_thread,     NULL, (void *)chef,     NULL);

    pthread_join(customer_thread, NULL);
    pthread_join(chef_thread,     NULL);

    sem_destroy(&semaphore); // destroy semaphore, must be after joining threads

	return 0;
}

void* chef(void* data) {
    printf("[CHEF]: I'm starting to cook the meal.\n");

    sleep(2); // Cooking food takes time
    food_plate = 42; // after preparing the meal, store it on the plate

    printf("[CHEF]: I'm done with cooking the meal!!\n");

    sem_post(&semaphore); // Notify the customer that the meal is available
}

void* customer(void* data) {
    printf("[CUSTOMER]: I'm waiting for the meal to be available.\n");
    sem_wait(&semaphore); // Wait until the meal is available

    printf("[CUSTOMER]: I'm starting to eat the meal.\n");

    int meal_value = food_plate; // pick the food from the plate
    sleep(1); // Eating food also takes time

    if(meal_value == 0) {
        printf("[CUSTOMER]: Terrible! All I got is an empty plate!!\n");
    } else {
        printf("[CUSTOMER]: The meal was good, I've eaten %d!!\n", meal_value);
    }

    printf("[CUSTOMER]: I'm done with eating the meal.\n");
}