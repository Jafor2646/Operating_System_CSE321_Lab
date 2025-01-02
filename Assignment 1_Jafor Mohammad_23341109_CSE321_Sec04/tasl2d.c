#include <stdio.h>
#include <string.h>

int isEmailUpdated(const char *email) {
    const char *newDomain = "sheba.xyz";
    char *atSymbol = strchr(email, '@'); 
    if (strcmp(atSymbol + 1, newDomain) == 0) {
        return 1; 
    } 
    return -1; 
}

int main() {
    char email[100];
    printf("Enter an email address: ");
    scanf("%s", email);

    int result = isEmailUpdated(email);

    if (result == 1) {
        printf("Email address is okay\n");
    } else if (result == -1) {
        printf("Email address is outdated\n");
    } 

    return 0;
}