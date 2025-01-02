#include <stdio.h>
#include <string.h>

int has_lowercase(const char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (islower(password[i])) {
            return 1;
        }
    }
    return 0;
}

int has_uppercase(const char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) {
            return 1;
        }
    }
    return 0;
}

int has_digit(const char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (isdigit(password[i])) {
            return 1;
        }
    }
    return 0;
}

int has_special(const char *password) {
    char special_characters[] = "_,$,#,@";
    for (int i = 0; password[i] != '\0'; i++) {
        for (int j = 0; special_characters[j] != '\0'; j++) {
            if (password[i] == special_characters[j]) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    char password[100];
    printf("Enter the password: ");
    scanf("%s", password);

    int lowercase = has_lowercase(password);
    int uppercase = has_uppercase(password);
    int digit = has_digit(password);
    int special = has_special(password);

    if (!lowercase) {
        printf("Lowercase character missing, ");
    }
    if (!uppercase) {
        printf("Uppercase character missing,");
    }
    if (!digit) {
        printf("Digit missing, ");
    }
    if (!special) {
        printf("Special character missing\n");
    }

    if (lowercase && uppercase && digit && special) {
        printf("OK\n");
    }

    return 0;
}