/*
Exercises:
3-2. Write a function escape(s,t) that converts characters like newline and tab into visible 
escape sequences like \n and \t as it copies the string t to s.Use a switch. 
Write a function for the other direction as well, converting escape sequences into 
the real characters.  
*/
#include <stdio.h>
#include "header.h"
#include <string.h>

// Function to convert characters like newline and tab into visible escape sequences 
// like \n and \t as it copies the string t to s
void escape(char s[], char t[]) {
    int i, j;
    for (i = 0, j = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
            // Convert newline into visible escape sequence \n
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            // Convert tab into visible escape sequence \t
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            // For other characters, copy them as they are
            default:
                s[j++] = t[i];
                break;
        }
    }
    s[j] = '\0'; // Null-terminate the string
}

int main() {
    char t[] = "Hello\tWorld\nThis is a test.";
    char s[100]; // Assuming the escaped string will not exceed 100 characters
    escape(s, t);
    printf("Original string: %s\n", t);
    printf("Escaped string: %s\n", s);  
    return 0;
}