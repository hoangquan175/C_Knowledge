/*
Exercises:
2-5. Write the function any(s1,s2), which returns the first location in the string s1 where any character from the string s2 occurs,
 or -1 if s1 contains no characters from s2. 
(The standard library function strpbrk does the same job but returns a pointer to the location.) 
*/
#include <stdio.h>
#include "header.h"

// Function to return the first location in the string s1 where any character from the string s2 occurs
int any(char s1[], char s2[]) {
    int i, j;
    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                return i;
            }
        }
    }
    return -1;
}

int main() {
    char s1[] = "hello world";
    char s2[] = "aeiou";
    int result = any(s1, s2);
    if (result != -1) {
        printf("The first location in s1 where any character from s2 occurs is at index: %d\n", result);
    } else {
        printf("s1 contains no characters from s2.\n");
    }
    return 0;
}