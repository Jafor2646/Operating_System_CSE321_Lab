#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("1. Parent process ID: %d\n", getpid());

    pid_t child_pid = fork();

    if (child_pid == 0) {

        printf("2. Child process ID: %d\n", getpid());

        for (int i = 0; i < 3; i++) {
            pid_t grandchild_pid = fork();

            if (grandchild_pid == 0) {
                printf("3. Grandchild process ID: %d\n", getpid());
                break; 
            }
        }

        for (int i = 0; i < 3; i++) {
            wait(NULL);
        }
    } else if (child_pid > 0) {

        wait(NULL);
    }

    return 0;
}
