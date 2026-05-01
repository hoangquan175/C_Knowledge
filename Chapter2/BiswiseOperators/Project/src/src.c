/*
Exercises:
2-6. Write a function setbits(x,p,n,y) that returns x 
with the n bits that begin at position p set to the rightmost n bits of y, 
leaving the other bits of x unchanged.  
*/
#include <stdio.h>
#include "header.h"

// Function to set n bits of x starting at position p to the rightmost n bits of y, leaving the other bits of x unchanged
int setbits(int x, int p, int n, int y) {
    // Create a mask to clear the n bits at position p in x
    // (1 << n) - 1 : creates a mask with the rightmost n bits set to 1 (e.g., if n=3, it will be 0b111)
    // << (p - n + 1) : shifts the mask to the correct position (e.g., if p=5 and n=3, it will shift the mask to 0b11100000)
    int mask = ((1 << n) - 1) << (p - n + 1);
    // Clear the n bits at position p in x
    x &= ~mask;
    // Set the n bits at position p to the rightmost n bits of y
    // (y & ((1 << n) - 1)) : extracts the rightmost n bits of y (e.g., if y=0b101010 and n=3, it will be 0b010)
    // << (p - n + 1) : shifts the extracted bits to the correct position (e.g., if p=5 and n=3, it will shift the bits to 0b01000000)
    x |= (y & ((1 << n) - 1)) << (p - n + 1);
    return x;
}

int main() {
    int x = 112; // Binary: 1110000
    int p = 3;  // Position of the first bit to set
    int n = 2;  // Number of bits to set
    int y = 3;  // Binary: 11

    int result = setbits(x, p, n, y);
    printf("Result: %x\n", result);

    return 0;
}