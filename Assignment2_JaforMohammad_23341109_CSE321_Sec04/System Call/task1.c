#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char input[MAX_STRING_LENGTH];

    printf("Enter strings to write to the file (enter '-1' to stop):\n");

    while (1) {
        printf("Enter a string: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; 
        if (strcmp(input, "-1") == 0) {
            break;
        }

        fprintf(file, "%s\n", input);
    }

    fclose(file);

    printf("Strings have been written to the file.\n");

    return 0;
}
