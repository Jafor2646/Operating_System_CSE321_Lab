#include <stdio.h>
#include <stdbool.h>

#define n 5 // Number of processes
#define m 4 // Number of resources

void calculateNeed(int need[n][m], int max[n][m], int alloc[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

bool isSafe(int processes[n], int avail[m], int max[n][m], int alloc[n][m]) {
    int need[n][m];
    calculateNeed(need, max, alloc);

    bool finish[n];
    for (int i = 0; i < n; i++) {
        finish[i] = false;
    }

    int work[m];
    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }
                    finish[i] = true;
                    processes[count++] = i;
                    found = true;
                }
            }
        }
        if (!found) {
            return false; // System is not in a safe state
        }
    }

    return true; // System is in a safe state
}

void bankersAlgorithm(int alloc[n][m], int max[n][m], int avail[m]) {
    int processes[n];
    if (isSafe(processes, avail, max, alloc)) {
        printf("Safe here\n");
    } else {
        printf("Deadlock Ahead\n");
    }
}

int main() {
    int alloc[5][4] = {{0, 1, 0, 3},
                       {2, 0, 0, 0},
                       {3, 0, 2, 0},
                       {2, 1, 1, 5},
                       {0, 0, 2, 2}};

    int max[5][4] = {{6, 4, 3, 4},
                     {3, 2, 2, 1},
                     {9, 1, 2, 6},
                     {2, 2, 2, 8},
                     {4, 3, 3, 7}};

    int avail[4] = {3, 3, 2, 1};

    bankersAlgorithm(alloc, max, avail);

    return 0;
}
