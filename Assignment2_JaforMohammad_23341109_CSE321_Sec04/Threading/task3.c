#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

int calculateSum(const char *name) {
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        sum += (int)name[i];
    }
    return sum;
}

void *compareAndPrint(void *args) {
    int *values = (int *)args;

    if (values[0] == values[1] && values[1] == values[2]) {
        printf("Youreka\n");
    } else if (values[0] == values[1] || values[1] == values[2] || values[0] == values[2]) {
        printf("Miracle\n");
    } else {
        printf("Hasta la vista\n");
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[4];
    char names[3][MAX_NAME_LENGTH];

    for (int i = 0; i < 3; i++) {
        printf("Enter name %d: ", i + 1);
        scanf("%s", names[i]);
    }

    int values[3];
    for (int i = 0; i < 3; i++) {
        values[i] = calculateSum(names[i]);
        pthread_create(&threads[i], NULL, compareAndPrint, (void *)&values);
        pthread_join(threads[i], NULL);
    }

    pthread_create(&threads[3], NULL, compareAndPrint, (void *)&values);
    pthread_join(threads[3], NULL);

    return 0;
}
