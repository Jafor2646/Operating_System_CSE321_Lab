#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
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
            if (p[i].priority > p[j].priority) {
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