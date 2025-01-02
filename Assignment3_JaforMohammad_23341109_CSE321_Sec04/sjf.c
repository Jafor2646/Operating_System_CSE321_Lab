#include <stdio.h>


struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void swap(struct process *a, struct process *b) {
    struct process temp = *a;
    *a = *b;
    *b = temp;
}

void sort(struct process *p, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].burst_time > p[j].burst_time) {
                swap(&p[i], &p[j]);
            }
        }
    }
}

void calculate_times(struct process *p, int n) {
    p[0].waiting_time = 0;
    p[0].turnaround_time = p[0].burst_time;
    p[0].completion_time = p[0].turnaround_time + p[0].arrival_time;

    for (int i = 1; i < n; i++) {
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
        p[i].completion_time = p[i].turnaround_time + p[i].arrival_time;
    }
}

void print_table(struct process *p, int n) {
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time, p[i].completion_time);
    }
}

int main() {
    FILE *fp;
    fp = fopen("sjf_input.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    int t;
    fscanf(fp, "%d", &t);
    const int n = t;
    struct process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        fscanf(fp, "%d", &p[i].arrival_time);
    }

    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d", &p[i].burst_time);
    }

    fclose(fp);

    sort(p, n);
    calculate_times(p, n);
    print_table(p, n);

    return 0;
}
