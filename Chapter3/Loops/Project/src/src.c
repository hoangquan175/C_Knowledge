/*
Exercises:
3-3. Write a function expand(s1,s2) that expands shorthand notations 
like a-z in the string s1 into the equivalent complete list abc...xyz in s2. 
Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. 
Arrange that a leading or trailing - is taken literally.  
*/
#include <stdio.h>
#include "header.h"

// Function expand(s1,s2) that expands shorthand notations 
// like a-z in the string s1 into the equivalent complete list abc...xyz in s2. 
// Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. 
// Arrange that a leading or trailing - is taken literally.
int expand(char s1[], char s2[]) {
    int i = 1, j = 0; // Start from the second character of s1 to check for the '-' character

    if (s1[i] == '-' && i > 0 && s1[i + 1] != '\0' && ((s1[i - 1] >= 'a' && s1[i - 1] <= 'z' && s1[i + 1] >= 'a' && s1[i + 1] <= 'z') || (s1[i - 1] >= 'A' && s1[i - 1] <= 'Z' && s1[i + 1] >= 'A' && s1[i + 1] <= 'Z') || (s1[i - 1] >= '0' && s1[i - 1] <= '9' && s1[i + 1] >= '0' && s1[i + 1] <= '9'))) {
        char start = s1[i - 1];
        char end = s1[i + 1];
        for (char c = start; c <= end; c++) {
            s2[j++] = c;
        }
        i++; // Skip the next character since it's already processed
    } else {
        return 0;
    }
    s2[j] = '\0'; // Null-terminate the string
    return 1;
}


int main() {
    char s1[] = "0-9";
    char s2[100];
    if (expand(s1, s2)) {
        printf("Expanded string: %s\n", s2);
    } else {
        printf("No valid shorthand notation found in s1.\n");
    }   
    return 0;
}