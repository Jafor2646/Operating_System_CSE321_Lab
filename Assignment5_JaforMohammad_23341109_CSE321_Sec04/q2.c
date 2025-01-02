#include <stdio.h>
#include <stdbool.h>

#define n 6 // Number of processes
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

void safeSequence(int alloc[n][m], int max[n][m], int avail[m]) {
    int processes[n];
    if (isSafe(processes, avail, max, alloc)) {
        printf("Safe Sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d", processes[i]);
            if (i != n - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
    } else {
        printf("No safe sequence exists.\n");
    }
}

int main() {
    int alloc[6][4] = {{0, 1, 0, 3},
                       {2, 0, 0, 3},
                       {3, 0, 2, 0},
                       {2, 1, 1, 5},
                       {0, 0, 2, 2},
                       {1, 2, 3, 1}};

    int max[6][4] = {{6, 4, 3, 4},
                     {3, 2, 2, 4},
                     {9, 1, 2, 6},
                     {2, 2, 2, 8},
                     {4, 3, 3, 7},
                     {6, 2, 6, 5}};

    int avail[4] = {2, 2, 2, 1};

    safeSequence(alloc, max, avail);

    return 0;
}
