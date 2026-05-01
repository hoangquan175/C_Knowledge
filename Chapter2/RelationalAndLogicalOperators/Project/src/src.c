/*
Exercises:
2-2. Write a loop equivalent to the for loop above without using && or ||.
*/
#include <stdio.h>
#include "header.h"

#define MAXLINE 1000 // maximum input line length

// getline function to read a line of input and return its length
int getline(char s[], int lim) {
    int c, i;
    // The original loop condition is: i < lim - 1 && (c = getchar()) != EOF && c != '\n'
    // We can rewrite it without using && or || as follows:
    for (i = 0; i < lim - 1; i++) {
        c = getchar();
        if (c != EOF) {
            if (c != '\n') {
                s[i] = c; // Store the character in the array
            } else {
                s[i] = c; // Store the newline character
                i++; // Increment i to account for the newline
                break; // Exit the loop after storing the newline
            }
        }else{
            break; // Exit the loop if EOF is encountered
        }
    }
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}

int main() {
    // Assuming maximum line length is MAXLINE characters
    char line[MAXLINE];
    // To store the lenghth of the current line.
    int len;
    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > 80) {
            printf("%s", line); // Print the line if it's longer than 80 characters
        }
    }
    return 0;
}
