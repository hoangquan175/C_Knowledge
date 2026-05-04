/*
Exercises:
5-5. Write version of the library function strncpy,strncat, and strncmp that operate on at most the first n characters of their argument strings.
For example, strncpy(s,t,n) copies at most n characters of t to s, and returns s.
*/
#include <stdio.h>
#include "header.h"

// strncpy: copy at most n characters of t to s; return s
char *strncpy(char *s, const char *t, size_t n) {
    char *s_start = s; // Keep the starting address of s to return later
    // Move s to the end of the string
    while (*s) {
        s++;
    }
    // Copy characters from t to s until we hit the null terminator or n characters
    while ((n-- ) && (*s++ = *t++))
        ;
    if (n == (size_t) - 1) { // If we copied n characters without hitting null terminator
        *s = '\0'; // Null-terminate the destination string
    }
    return s_start;
}

// strncat: concatenate at most n characters of t to end of s; return s
char *strncat(char *s, const char *t, size_t n) {
    char *s_start = s; // Keep the starting address of s to return later    
    while (*s) { // Move s to the end of the string
        s++;
    }
    while (n-- && (*s++ = *t++))
        ;
    if (n == (size_t)-1) { // If we concatenated n characters without hitting null terminator
        *s = '\0'; // Null-terminate the resulting string
    }
    return s_start;
}

// strncmp: compare at most n characters of s and t; return <0, 0, or >0
int strncmp(const char *s, const char *t, size_t n) {
    while (n-- && *s && (*s == *t)) {
        s++;
        t++;
    }
    if (n == (size_t)-1) { // If we compared n characters without finding a difference
        return 0; // Strings are equal up to n characters
    }
    return (unsigned char)*s - (unsigned char)*t; // Return difference of first non-matching character
}

int main() {
    char s[100] = "Hello, ";
    char t[] = "world!";
    printf("strncpy result: %s\n", strncpy(s, t, 5));
    printf("strncat result: %s\n", strncat(s, t, 5)); 
    if (strncmp(s, t, 5) == 0) {
        printf("First 5 characters of s and t are the same.\n");
    } else {
        printf("First 5 characters of s and t are different.\n");
    }
    return 0;
}