/*
Exercises:
4-13. Write a recursive version of the function reverse(s), which reverses the string s in place. 
*/
#include <stdio.h>
#include "header.h"
#include <string.h>

// reverse: reverse the string s in place
void reverse(char s[]) {
    int len = strlen(s);
    reverse_helper(s, 0, len - 1);
}

// Helper function for reverse
void reverse_helper(char s[], int start, int end) {
    if (start >= end) {
        return;
    }
    // Swap characters at start and end
    char temp = s[start];
    s[start] = s[end];
    s[end] = temp;
    // Recursively reverse the remaining substring
    reverse_helper(s, start + 1, end - 1);
}

int main() {
    char s[] = "hello world";
    reverse(s);
    printf("Reversed string: %s\n", s);
    return 0;
}