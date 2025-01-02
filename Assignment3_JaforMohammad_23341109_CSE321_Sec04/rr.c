#include <stdio.h>

struct process {
    int pid;
    int burst_time;
    int remaining_time;
    int completion_time;
};

int main() {
    FILE *fp;
    fp = fopen("rr_input.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    int t, quantum;
    fscanf(fp, "%d", &t);
    fscanf(fp, "%d", &quantum);
    const int n = t;
    struct process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        fscanf(fp, "%d", &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
    }

    fclose(fp);

    int time = 0;
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_time > 0) {
                if (p[i].remaining_time > quantum) {
                    time += quantum;
                    p[i].remaining_time -= quantum;
                } else {
                    time += p[i].remaining_time;
                    p[i].completion_time = time;
                    p[i].remaining_time = 0;
                    completed++;
                }
            }
        }
    }

    printf("PID\tBurst Time\tCompletion Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", p[i].pid, p[i].burst_time, p[i].completion_time);
    }

    return 0;
}
