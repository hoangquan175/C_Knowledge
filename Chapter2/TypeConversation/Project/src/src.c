/*
Exercises:
2-3. Write the function htoi(s), which converts a string of hexadecimal digits 
(including an optional 0x or 0X) into its equivalent integer value. 
The allowable digits are 0 through 9, a through f, and A through F.   
*/
#include <stdio.h>
#include "header.h"

// Function to convert a hexadecimal string to an integer
int htoi(char s[]) {
    int i = 0; // Index for iterating through the string
    int value = 0; // Variable to store the resulting integer value

    // Skip optional "0x" or "0X" prefix
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        i = 2; // Start processing from the character after the prefix
    }

    // Process each character in the string
    // the fomular is value = value * 16 + (current character's integer value)
    for (; s[i] != '\0'; i++) {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            value = value * 16 + (c - '0'); // Convert character to integer and accumulate
        } else if (c >= 'a' && c <= 'f') {
            value = value * 16 + (c - 'a' + 10); // Convert character to integer and accumulate
        } else if (c >= 'A' && c <= 'F') {
            value = value * 16 + (c - 'A' + 10); // Convert character to integer and accumulate
        } else {
            break; // Stop processing if an invalid character is encountered
        }
    }
    return value; // Return the resulting integer value
}


int main() {
    char hexString[] = "0x1a3F"; // Example hexadecimal string
    int result = htoi(hexString); // Convert the hexadecimal string to an integer
    printf("The integer value of %s is %d\n", hexString, result);
    return 0;
}