/*
Exercises:
5-4. Write the function strend(s,t), which returns 1 
if the string t occurs at the end of the string s, and zero otherwise.
*/
#include <stdio.h>
#include "header.h"

// strend: return 1 if t occurs at the end of s, 0 otherwise
int strend(char *s, char *t) {
    char *s_end = s;
    char *t_end = t;

    // Move to the end of s
    while (*s_end != '\0') {
        s_end++;
    }

    // Move to the end of t
    while (*t_end != '\0') {
        t_end++;
    }

    // Compare characters from the ends
    while (t_end > t && s_end > s) {
        if (*t_end-- != *s_end--) {
            return 0; // t does not occur at the end of s
        }
    }

    // If we've reached the beginning of t, then t occurs at the end of s
    return (t_end == t);
} 

int main() {
    char s[100] = "Hello, world!";
    char t[] = "world!";
    if (strend(s, t)) {
        printf("'%s' occurs at the end of '%s'\n", t, s);
    } else {
        printf("'%s' does not occur at the end of '%s'\n", t, s);
    }
    return 0;
}