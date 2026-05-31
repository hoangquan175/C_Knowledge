/*
Exercises:
7-6. Write a program to compare two files, printing the first line where they differ.
*/

#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char line1[1000], line2[1000];
    int line_number = 0;
    FILE *f1 = fopen("file1.txt", "r");
    if (f1 == NULL) {
        perror("fopen file1.txt");
        return 1;
    }
    FILE *f2 = fopen("file2.txt", "r");
    if (f2 == NULL) {
        perror("fopen file2.txt");
        fclose(f1);
        return 1;
    }

    char *r1, *r2;
    while (1) {
        r1 = fgets(line1, sizeof(line1), f1);
        r2 = fgets(line2, sizeof(line2), f2);

        if (r1 == NULL || r2 == NULL) {
            break;
        }

        line_number++;
        if (strcmp(line1, line2) != 0) {
            printf("Files differ at line %d:\n", line_number);
            printf("File 1: %s", line1);
            printf("File 2: %s", line2);
            fclose(f1);
            fclose(f2);
            return 0;
        }
    }

    /* Handle cases where one file has extra lines or both ended */
    if (r1 == NULL && r2 == NULL) {
        printf("Files are identical.\n");
    } else {
        /* One file ended earlier or a read error occurred */
        line_number++;
        printf("Files differ at line %d:\n", line_number);
        if (r1 == NULL) {
            printf("File 1: <EOF>\n");
        } else {
            printf("File 1: %s", line1);
        }
        if (r2 == NULL) {
            printf("File 2: <EOF>\n");
        } else {
            printf("File 2: %s", line2);
        }
    }

    fclose(f1);
    fclose(f2);
    return 0;
}

