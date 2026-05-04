/*
Exercises:
4-11. Modify getop so that it doesn't need to use ungetch. 
Hint: use an internal static variable.
*/
#include <stdio.h>
#include <stdlib.h> // Include stdlib.h for atof function
#include "header.h"
#include <ctype.h> // Include ctype.h for isdigit function

// Define constants for the calculator
#define MAXOP 100 // max size of operand or operator
#define NUMBER '0' // signal that a number was found
#define MAXVAL 100 // maximum depth of val stack

// Internal variables for stack implementation
int sp = 0; // next free stack position
double val[MAXVAL]; // value stack

// getop: get next character or numeric operand without using ungetch
int getop(char s[]) {
    static int lastc = 0; // buffered character from the previous call
    int i, c;

    if (lastc != 0) {
        c = lastc;
        lastc = 0;
    } else {
        c = getchar();
    }

    while (c == ' ' || c == '\t') {
        c = getchar();
    }

    if (c == EOF)
        return EOF;

    s[0] = c;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c;    /* not a number */

    i = 0;
    if (c == '-') {
        int next = getchar();
        if (!isdigit(next) && next != '.') {
            lastc = next;
            return '-';
        }
        s[++i] = next;
        c = next;
    }

    if (isdigit(c))    /* collect integer part */
        while (isdigit(s[++i] = c = getchar()))
            ;
    if (c == '.')      /* collect fraction part */
        while (isdigit(s[++i] = c = getchar()))
            ;

    s[i] = '\0';
    if (c != EOF)
        lastc = c;

    return NUMBER;
}

// push: push f onto value stack
void push(double f){
    // Implementation of push function to add a number to the stack
    // This is a placeholder - replace with actual stack implementation
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

// pop: pop and return top value from stack
double pop(void){
    // Implementation of pop function to remove and return the top number from the stack
    // This is a placeholder - replace with actual stack implementation
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

// reverse Polish calculator
int main() {
    int type;
    double op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            // Add modulus (%) operator handling
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push((int)pop() % (int)op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                if (sp > 0)
                    printf("\t%.8g\n", val[sp-1]);  // print top without popping
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}