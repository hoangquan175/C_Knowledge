/*
Exercises:
1-13. Write a program to print a histogram of the lengths of words in its input. 
It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging.
*/
#include <stdio.h>

int main() {
    int c, i;
    int word_length[20]; // Assuming maximum word length is 20
    int max_length = 0; // To keep track of the maximum word length
    int length = 0; // To count the length of the current word
    // Initialize word_length array
    for (i = 0; i < 20; i++) {
        word_length[i] = 0;
    }   
    // Read input and count word lengths
    while ((c = getchar()) != EOF) {
        // Reset length for the new word
        length = 0;
        // Count the length of the current word
        while (c != ' ' && c != '\t' && c != '\n' && c != EOF) {
            length++;
            c = getchar();
        }
        if (length > 0 && length < 20) {
            /*
            Increment the count for this word length. 
            Using length as index, so length 1 corresponds to index 1, etc.
            */
            word_length[length]++;
            if (length > max_length) {
                max_length = length; // Update maximum word length
            }
        }
    }
    // Print the histogram
    printf("Word Length Histogram:\n");
    printf("Length: Count(times)\n");
    for (i = 1; i <= max_length; i++) {
        printf("%2d:\t%2d ", i, word_length[i]);
        printf("\n");
    }   
    return 0;
}