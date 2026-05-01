/*
Exercises:
1-11. How would you test the word count program? What kinds of input are most likely to uncover bugs if there are any?  
Answer: To test the word count program, I would use a variety of input cases, including:
- Empty input.
- Input with only whitespace: This would test if the program correctly identifies that there are no words.
- Input with multiple words separated by single spaces: This would test if the program correctly counts words in a simple case.
- Input with multiple words separated by multiple spaces: This would test if the program correctly ignores extra spaces and counts only the actual words.
- Input with tabs and newlines: This would test if the program correctly counts words when they are separated by tabs and newlines, in addition to spaces.
- Input with very long lines or words.
*/
#include <stdio.h>

#define IN 1
#define OUT 0

//count words, lines, characters in input
int main() {
    int c, nl = 0, nw = 0, nc = 0, state = OUT;
    
    while ((c = getchar()) != EOF) {
        ++nc; // count characters
        if (c == '\n') {
            ++nl; // count lines
        }      
        if (c == ' ' || c == '\t' || c == '\n') {
            state = OUT; // end of a word
        } else if (state == OUT) {
            state = IN; // start of a new word
            ++nw; // count words
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
    return 0;
}