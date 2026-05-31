/*
Exercises:
7-5. Rewirte the postfix calculator of Chapter 4 to use scanf and/or sscanf to do the input and number conversion.
*/

#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char input[100];
    double stack[100];
    int top = 0;
    while (fgets(input, sizeof(input), stdin)) {
        char *token = strtok(input, " \t\n");
        while (token) {
            if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
                stack[top++] = atof(token);
            } else if (strcmp(token, "+") == 0) {
                if (top < 2) {
                    fprintf(stderr, "Error: not enough operands for +\n");
                    return 1;
                }
                double b = stack[--top];
                double a = stack[--top];
                stack[top++] = a + b;
            } else if (strcmp(token, "-") == 0) {
                if (top < 2) {
                    fprintf(stderr, "Error: not enough operands for -\n");
                    return 1;
                }
                double b = stack[--top];
                double a = stack[--top];
                stack[top++] = a - b;
            } else if (strcmp(token, "*") == 0) {
                if (top < 2) {
                    fprintf(stderr, "Error: not enough operands for *\n");
                    return 1;
                }
                double b = stack[--top];
                double a = stack[--top];
                stack[top++] = a * b;
            } else if (strcmp(token, "/") == 0) {
                if (top < 2) {
                    fprintf(stderr, "Error: not enough operands for /\n");
                    return 1;
                }
                double b = stack[--top];
                double a = stack[--top];
                if (b == 0) {
                    fprintf(stderr, "Error: division by zero\n");
                    return 1;
                }
                stack[top++] = a / b;
            } else {
                fprintf(stderr, "Error: unknown token \"%s\"\n", token);
                return 1;
            }
            token = strtok(NULL, " \t\n");
        }
    }
    if (top == 1) {
        printf("Result: %f\n", stack[0]);
    } else if (top > 1) {
        fprintf(stderr, "Error: too many operands left on stack\n");
        return 1;
    } else {
        fprintf(stderr, "Error: no result on stack\n");
        return 1;
    }

    return 0;
}

