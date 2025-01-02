#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

    int n = argc - 1;
    int *arr = (int *)malloc(n * sizeof(int));

    // Convert command line arguments to integers and store in the array
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    // Create a child process
    pid_t child_pid = fork();

    if (child_pid == 0) {
        execl("./sort", "./sort", argv[1], argv[2], argv[3], (char *)NULL);
    } else if (child_pid > 0) {
      
        wait(NULL);

        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 == 0) {
                printf("%d is even\n", arr[i]);
            } else {
                printf("%d is odd\n", arr[i]);
            }
        }

        free(arr);
    }

    return 0;
}
