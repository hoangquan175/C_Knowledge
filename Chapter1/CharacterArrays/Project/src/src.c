/*
Exercises:
1-17. Write a program to print all input lines that are longer than 80 characters.
*/
#include <stdio.h>

#define MAXLINE 1000 // maximum input line length

// getline function to read a line of input and return its length
int getline(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
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
