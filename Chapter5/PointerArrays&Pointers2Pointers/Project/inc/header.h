#ifndef HEADER_H
#define HEADER_H

// Function declaration for readlines: read input lines into supplied storage, return number of lines read
int readlines(char *lineptr[], int maxlines, char *linestor);
// Function declaration for writelines: write lines from lineptr array
void writelines(char *lineptr[], int nlines);
// Function declaration for qsort: sort lines in lineptr array
void qsort(char *lineptr[], int left, int right);

#endif // HEADER_H
