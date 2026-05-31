/*
Exercises:
7-2. Write a program that will print arbitrary input in a sensible way. 
As a minimum, it should print non-graphic characters in octal or hexadecimal 
according to local custom, and break long text lines.
*/

#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(void) {
    // Define a variable to keep track of the current column for line breaking
    int c;
    int column = 0;
    // Define a constant for the maximum column width before breaking the line
    const int MAX_COLUMN = 80;

    // Read characters from standard input until EOF
    while ((c = getchar()) != EOF) {
        // If the character is printable, print it as is
        if (isprint(c)) {   
            putchar(c);
            column++;
        // If the character is not printable, print its hexadecimal representation
        } else {
            printf("\\x%02x", (unsigned char)c);
            column += 4; // Each non-printable character takes 4 columns in the output
        }
        
        // If the current column exceeds the maximum column width, print a newline and reset the column count
        if (column >= MAX_COLUMN) {
            putchar('\n');
            column = 0;
        }
    }

    return 0;
}

