/*
Exercises:
1-6. Verify that the expression getchar() != EOF is 0 or 1.  
1-7. Write a program to print the value of EOF.
*/
#include <stdio.h>

int main() {
    // Exercise 1-6
    int c = getchar();
    printf("getchar() != EOF: %d\n", c != EOF); 
    // Exercise 1-7
    printf("Value of EOF: %d\n", EOF); 
    return 0;
}