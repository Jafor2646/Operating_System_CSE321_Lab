#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int remaining_tickets = 10;
pthread_mutex_t ticket_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ticket_sold_condition = PTHREAD_COND_INITIALIZER;
int current_person = 1;

void sell_ticket(int person_id) {
    pthread_mutex_lock(&ticket_mutex);

    while (person_id != current_person || remaining_tickets < 2) {
        pthread_cond_wait(&ticket_sold_condition, &ticket_mutex);
    }

    if (remaining_tickets >= 2) {
        printf("Person %d is purchasing a ticket.\n", current_person);
        remaining_tickets -= 2;
        printf("Tickets left: %d\n", remaining_tickets);
        printf("Person: %d, Purchase Done\n", current_person);
        current_person += 2;
    } else {
        printf("Person %d can not purchase.\n", current_person);
        printf("Tickets left: %d\n", remaining_tickets);
        printf("Person: %d, Purchase failed\n", current_person);
    }

    pthread_cond_broadcast(&ticket_sold_condition);
    pthread_mutex_unlock(&ticket_mutex);
}

void* sell_tickets(void* person_ptr) {
    int person_id = *(int*)person_ptr;

    pthread_mutex_lock(&ticket_mutex);
    sell_ticket(person_id);
    pthread_mutex_unlock(&ticket_mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[12];
    int persons[12];

    for (int i = 0; i < 12; i++) {
        persons[i] = i + 1;
        pthread_create(&threads[i], NULL, sell_tickets, &persons[i]);
    }

    for (int i = 0; i < 12; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
