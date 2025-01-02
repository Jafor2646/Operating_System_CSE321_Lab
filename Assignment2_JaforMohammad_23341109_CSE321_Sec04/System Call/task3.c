#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int a, b, c;
    int processCount = 1; 
    a = fork();
    processCount++;

    if (a == 0) {
        printf("First child process (PID=%d)\n", getpid());

        if (getpid() % 2 != 0) {
            b = fork();
            processCount++;

            if (b == 0) {
                printf("Second child process (PID=%d)\n", getpid());
            }
        }
    }

    c = fork();
    processCount++;

    if (c == 0) {
        printf("Third child process (PID=%d)\n", getpid());
    } else {
        for (int i = 0; i < 2; i++) {
            wait(NULL);
        }
        printf("Number of processes created: %d\n", processCount);
    }

    return 0;
}
