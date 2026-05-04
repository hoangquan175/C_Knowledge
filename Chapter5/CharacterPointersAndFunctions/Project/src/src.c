/*
Exercises:
5-3. Write a pointer version of the function strcat that we showed in Chapter 2:
strcat(s,t) copies the string t to the end of s.
*/
#include <stdio.h>
#include "header.h"

// strcat: concatenate t to end of s; s must be big enough
void strcat(char *s, const char *t) {
    while (*s != '\0') { // Move s to the end of the string
        s++;
    }
    while (*t != '\0') { // Copy characters from t to s
        *s++ = *t++;
    }
    *s = '\0'; // Null-terminate the resulting string
}   

int main() {
    char s[100] = "Hello, ";
    char t[] = "world!";
    strcat(s, t);
    printf("%s\n", s); // Output: Hello, world! 
    return 0;
}