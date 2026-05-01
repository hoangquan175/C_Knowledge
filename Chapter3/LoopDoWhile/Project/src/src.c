/*
Exercises:
3-4. In a two's complement number system, our version of itoa does not handle the largest negative number, 
that is, the value of n equal to -(2^{wordsize-1}). 
Explain why not. Modify it to print that value correctly, regardless of the machine on which it runs.
Answer: In a two's complement number system, the largest negative number is represented as -(2^{wordsize-1}), 
which is one more than the largest positive number.
This means that when we try to convert this value to a string using the itoa function, 
we will encounter an overflow issue because the absolute value of this number cannot be 
represented in a signed integer type. To handle this case correctly, 
we can modify the itoa function to check for this specific value and return the string representation of it directly, 
instead of trying to convert it using the standard logic. 
This way, we can ensure that the function works correctly regardless of the machine's word size.  
*/
#include <stdio.h>
#include "header.h"

// itoa: convert n to characters in s
void itoa(int n, char s[]) {
    int i = 0, sign = n;
    unsigned int u; // Use unsigned to safely handle INT_MIN
    
    // Convert to unsigned to avoid overflow with negation
    if (n < 0) {
        u = -(unsigned int)n;
    } else {
        u = (unsigned int)n;
    }
    
    do {
        s[i++] = u % 10 + '0'; // Get next digit
    } while ((u /= 10) > 0); // Delete it
    
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    
    // Reverse the string (digits are in reverse order)
    for (int j = 0; j < i / 2; j++) {
        char temp = s[j];
        s[j] = s[i - 1 - j];
        s[i - 1 - j] = temp;
    }
}


int main() {
    int n = -2147483648; // Example of the largest negative number in a 32-bit signed integer
    char s[20]; // Buffer to hold the string representation of n
    itoa(n, s); // Convert n to a string
    printf("The string representation of %d is: %s\n", n, s);  
    return 0;
}