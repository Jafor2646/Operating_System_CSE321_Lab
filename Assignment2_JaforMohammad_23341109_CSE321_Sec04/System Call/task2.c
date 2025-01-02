#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    pid_t child_pid, grandchild_pid;

    if ((child_pid = fork()) == 0) {
        printf("I am child\n");

        if ((grandchild_pid = fork()) == 0) {
            printf("I am grandchild\n");
        } else if (grandchild_pid > 0) {
            wait(NULL);
        }
    } else if (child_pid > 0) {
        wait(NULL);
        printf("I am parent\n");
    }

    return 0;
}
