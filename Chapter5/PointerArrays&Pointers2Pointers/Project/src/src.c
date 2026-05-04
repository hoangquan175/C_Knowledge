/*
Exercises:
5-7. Rewrite readlines to store lines in an array supplied by main, 
rather than calling alloc to maintain storage. How much faster is the program?
*/
#include <stdio.h>
#include <string.h>
#include "header.h"

#define MAXLINES 1000 // maximum number of lines to be sorted
#define MAXLEN 1000 // maximum length of any input line

char *lineptr[MAXLINES]; // pointers to text lines
char linestor[MAXLINES * MAXLEN]; // storage for all lines

// readlines: read input lines into linestor, set pointers in lineptr, return number of lines read
int readlines(char *lineptr[], int maxlines, char *linestor) {
    int len, nlines = 0;
    char *p = linestor;
    char line[MAXLEN];
    while (fgets(line, MAXLEN, stdin) != NULL) {
        len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }
        if (nlines >= maxlines || p + len + 1 > linestor + MAXLINES * MAXLEN) {
            return -1; // too many lines or not enough storage
        }
        strcpy(p, line);
        lineptr[nlines++] = p;
        p += len + 1;
    }
    return nlines;
}
void writelines(char *lineptr[], int nlines) {
    // Implementation of writelines function to write lines from lineptr array
    for (int i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}
void qsort(char *lineptr[], int left, int right) {
    // Implementation of qsort function to sort lines in lineptr array
    if (left >= right) {
        return;
    }
    int pivot_index = (left + right) / 2;
    char *pivot = lineptr[pivot_index];
    // Swap pivot with leftmost element
    lineptr[pivot_index] = lineptr[left];
    lineptr[left] = pivot;
    int last = left;
    for (int i = left + 1; i <= right; i++) {
        if (strcmp(lineptr[i], pivot) < 0) {
            last++;
            // Swap lineptr[last] and lineptr[i]
            char *temp = lineptr[last];
            lineptr[last] = lineptr[i];
            lineptr[i] = temp;
        }
    }
    // Swap pivot back to its correct position
    char *temp = lineptr[left];
    lineptr[left] = lineptr[last];
    lineptr[last] = temp;
    // Recursively sort the partitions
    qsort(lineptr, left, last - 1);
    qsort(lineptr, last + 1, right);
}


int main() {
    int nlines; // number of input lines read
    if ((nlines = readlines(lineptr, MAXLINES, linestor)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}