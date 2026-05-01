/*
Exercises:
1-12. Write a program that prints its input one word per line.   
*/
#include <stdio.h>

int main() {
    int c = 0;
    int in_word = 0;

    while ((c = getchar()) != EOF) {
        // Check if the character is a whitespace character (space, tab, or newline)
        if (c == ' ' || c == '\t' || c == '\n') {
            // If we were in a word, print a newline to end the current word
            if (in_word == 1) {
                putchar('\n');
                in_word = 0;
            }
        // If it's not a whitespace character, print it and mark that we are in a word
        } else {
            putchar(c);
            in_word = 1;
        }
    }
    return 0;
}