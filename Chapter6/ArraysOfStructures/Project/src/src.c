/*
Exercises:
6-1. Our version of getword does not properly handle underscores, string constants, 
comments, or preprocessor control lines. Write a better version.
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "header.h"

// getword: get next word or character from input
int getword(char *word, int lim) {
    // Implementation of getword that handles underscores, string constants, comments, and preprocessor control lines
    // This is a placeholder implementation.
    int c;
    while ((c = getchar()) == ' ' || c == '\t') // Skip whitespace
        ;
    if (c == EOF) {
        return EOF;
    }
    if (c == '_' || isalpha(c)) { // Start of a word
        int i = 0;
        do {
            if (i < lim - 1) {
                word[i++] = c;
            }
            c = getchar();
        } while (c == '_' || isalnum(c)); // Continue until non-word character
        word[i] = '\0';
        return i; // Return the length of the word read
    }
    if (c == '"') { // Start of a string constant
        int i = 0;
        while ((c = getchar()) != '"' && c != EOF) { // Read until closing quote
            if (i < lim - 1) {
                word[i++] = c;
            }
        }
        word[i] = '\0';
        return i; // Return the length of the string constant read
    }
    if (c == '/') { // Possible start of a comment
        if ((c = getchar()) == '/') { // Single-line comment
            while ((c = getchar()) != '\n' && c != EOF) // Skip until end of line
                ;
            return getword(word, lim); // Get the next word after the comment
        } else if (c == '*') { // Multi-line comment
            while (1) {
                c = getchar();
                if (c == EOF) {
                    return EOF;
                }
                if (c == '*') {
                    if ((c = getchar()) == '/') { // End of multi-line comment
                        break;
                    }
                }
            }
            return getword(word, lim); // Get the next word after the comment
        } else {
            ungetc(c, stdin); // Not a comment, put the character back
            return '/'; // Return the '/' character
        }
    }
    if (c == '#') { // Preprocessor control line
        while ((c = getchar()) != '\n' && c != EOF) // Skip until end of line
            ;
        return getword(word, lim); // Get the next word after the preprocessor line
    }
    word[0] = c; // Return the non-word character
    word[1] = '\0';
    return 1; // Return the length of the character read
}

int main() {
    char word[100];
    // Read words from input and print them
    while (getword(word, sizeof(word)) != EOF) {
        printf("Read word: %s\n", word);
    }

    return 0;
}