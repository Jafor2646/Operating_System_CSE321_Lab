#include <stdio.h>
#include <string.h>

int isPalindrome(const char *str){
    const char *start = str;
    const char *end = str + strlen(str) - 1;

    while (start < end){
        if (*start != *end) {
            return 0; 
        }
        start++;
        end--;
    }

    return 1; 
}
int main(){
    char input[100];
    printf("Enter a string: ");
    scanf("%s", input);
    if (isPalindrome(input)){
        printf("Palindrome.\n");
    } else {
        printf("Not Palindrome.\n");
    }
    return 0;
}