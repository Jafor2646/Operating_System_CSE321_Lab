#include <stdio.h>

int isPerfect(int num) {
    int sum = 1; 

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;
            if (i != num / i) {
                sum += num / i;
            }
        }
    }

    return (sum == num);
}

void printPerfectNumbers(int start, int end) {
    printf("Perfect numbers between %d and %d:\n", start, end);

    for (int i = start; i <= end; i++) {
        if (isPerfect(i)) {
            printf("%d\n", i);
        }
    }
}

int main() {
    int start, end;

    printf("Enter the starting number: ");
    scanf("%d", &start);

    printf("Enter the ending number: ");
    scanf("%d", &end);

    printPerfectNumbers(start, end);

    return 0;
}
