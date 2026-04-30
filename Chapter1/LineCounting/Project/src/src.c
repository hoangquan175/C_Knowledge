/*
Exercises:
1-10. Write a program to copy its input to its output, 
replacing each tab by \t, each backspace by \b, and each backslash by \\. 
This makes tabs and backspaces visible in an unambiguous way
*/
#include <stdio.h>

int main() {
    // Exercise 1-10
    int c;
    while ((c = getchar()) != EOF) {
        // Replace tabs with \t
        if (c == '\t') {
            printf("\\t");
        // Replace backspaces with \b
        } else if (c == '\b') {
            printf("\\b");
        // Replace backslashes with \\
        } else if (c == '\\') {
            printf("\\\\");
        // For all other characters, we simply print them as they are
        } else {
            putchar(c);
        }
    }   
    return 0;
}