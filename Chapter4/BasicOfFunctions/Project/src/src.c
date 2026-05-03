/*
Exercises:
4-1. Write the function strrindex(s,t) which returns the position of 
the rightmost occurrence of t in s, or -1 if there is none  
*/
#include <stdio.h>
#include "header.h"
#include <string.h>

// strrindex: return index of rightmost occurrence of t in s, -1 if none
int strrindex(char s[], char t[]) {
    int i, j, k;
    int len_t = strlen(t);
    for (i = strlen(s) - 1; i >= 0; i--) {
        for (j = i, k = len_t - 1; k >= 0 && j >= 0 && s[j] == t[k]; j--, k--);
        if (k < 0) {
            return j + 1; // Return the starting index of the rightmost occurrence  
        }
    }
    // If we reach here, t was not found in s
    return -1;
}

int main() {
    char s[] = "hello world";
    char t[] = "world";
    int index = strrindex(s, t);
    if (index != -1) {
        printf("The rightmost occurrence of '%s' in '%s' is at index: %d\n", t, s, index);
    } else {
        printf("'%s' not found in '%s'\n", t, s);
    }
    return 0;
}