#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define MaxCrops 5
#define warehouseSize 5

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
char crops[warehouseSize] = {'R', 'W', 'P', 'S', 'M'};
char warehouse[warehouseSize] = {'N', 'N', 'N', 'N', 'N'};
pthread_mutex_t mutex;

void printWarehouse() {
    for (int i = 0; i < warehouseSize; i++) {
        printf("%c", warehouse[i]);
    }
    printf("\n");
}

void *Farmer(void *far) {
    int farmerNum = *((int *)far);

    while (1) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        printf("Farmer %d: Insert crops %c at %d\n", farmerNum, crops[farmerNum - 1], in);
        warehouse[in] = crops[farmerNum - 1];
        in = (in + 1) % warehouseSize;

        printWarehouse();

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1); 
    }
}

void *ShopOwner(void *sho) {
    int shopOwnerNum = *((int *)sho);

    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        printf("Shop owner %d: Remove crops %c from %d\n", shopOwnerNum, warehouse[out], out);
        warehouse[out] = 'N';
        out = (out + 1) % warehouseSize;

        printWarehouse();

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(1); 
    }
}

int main() {
    pthread_t Far[5], Sho[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, warehouseSize);
    sem_init(&full, 0, 0);

    int a[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        pthread_create(&Far[i], NULL, Farmer, (void *)&a[i]);
        pthread_create(&Sho[i], NULL, ShopOwner, (void *)&a[i]);
    }

    sleep(10);

    for (int i = 0; i < 5; i++) {
        pthread_cancel(Far[i]);
        pthread_cancel(Sho[i]);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
