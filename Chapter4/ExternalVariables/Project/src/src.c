/*
Exercises:
4-3 Given the basic framework, it's straightforward to extend the calculator. 
Add the modulus (%) operator and provisions for negative numbers.
4-9. Our getch and ungetch do not handle a pushed-back EOF correctly. 
Decide what their properties ought to be if an EOF is pushed back, then implement your design.
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
char buf[BUFSIZ]; // buffer for ungetch
int bufp = 0; // next free position in buf

// getch: get a (possibly pushed back) character
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
} 

// ungetch: push character back on input
void ungetch(int c) {
    // If EOF is pushed back, we can choose to ignore it or handle it in a specific way
    // For this implementation, we will ignore EOF and not push it back onto the buffer
    if (c == EOF) {
        return; // Ignore EOF
    }
    if (bufp < BUFSIZ) {
        buf[bufp++] = c;
    } else {
        printf("ungetch: too many characters\n");
    }
}

// getop: get next character or numeric operand
int getop(char s[]) {
    int i, c;
    
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c;    /* not a number */
    i = 0;
    if (c == '-') {
        if (!isdigit(c = getch()) && c != '.') {
            ungetch(c);
            return '-';
        }
        s[++i] = c;
    }
    if (isdigit(c))    /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')      /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
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