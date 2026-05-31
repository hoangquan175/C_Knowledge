/*
Exercises:
7-1. Write a program that converts uppercase to lowercase or lowercase to uppercase, 
depending on the name it is invoked with, as found in argv[0].
*/

#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    // Determine the program's name and set the conversion mode based on it
    const char *progname = argc > 0 ? argv[0] : "";
    const char *basename = strrchr(progname, '/');
    basename = basename ? basename + 1 : progname;
    // Flags to indicate conversion mode
    int convert_to_lower = 0;
    int convert_to_upper = 0;

    // Check the program's name to determine the conversion mode
    if (strstr(basename, "lower") != NULL || strstr(basename, "tolower") != NULL) {
        convert_to_lower = 1;
    // If the program's name contains "upper" or "toupper", set the flag to convert to uppercase
    } else if (strstr(basename, "upper") != NULL || strstr(basename, "toupper") != NULL) {
        convert_to_upper = 1;
    } else if (argc > 1) {
        if (strstr(argv[1], "lower") != NULL || strstr(argv[1], "tolower") != NULL) {
            convert_to_lower = 1;
        } else if (strstr(argv[1], "upper") != NULL || strstr(argv[1], "toupper") != NULL) {
            convert_to_upper = 1;
        }
    }

    if (!convert_to_lower && !convert_to_upper) {
        fprintf(stderr, "Usage: invoke program as upper or lower\n");
        return 1;
    }

    int c;
    // Read characters from standard input, convert them according to the mode, and write to standard output
    while ((c = getchar()) != EOF) {
        // If the convert_to_lower flag is set, convert the character to lowercase; 
        // if the convert_to_upper flag is set, convert it to uppercase
        if (convert_to_lower) {
            c = tolower((unsigned char)c);
        } else if (convert_to_upper) {
            c = toupper((unsigned char)c);
        }
        putchar(c);
    }

    return 0;
}
