/*
Exercises:
4-2. Extend atof to handle scientific notation of the form 123.45e-6 where
a floating-point number may be followed by e or E and an optionally signed exponent.  
*/
#include <stdio.h>
#include <math.h>
#include "header.h"

// atof: convert string s to double, handling scientific notation
double atof(char s[]) {
    double val, power;
    int i, sign, exp_sign = 1, exponent = 0;

    // Skip whitespace
    for (i = 0; s[i] == ' ' || s[i] == '\t'; i++);

    // Handle optional sign
    // Determine the sign of the number and move past the sign character if present
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    // Convert integer part
    // Process the integer part of the number by iterating through the characters until a non-digit is encountered
    for (val = 0.0; s[i] >= '0' && s[i] <= '9'; i++)
        val = 10.0 * val + (s[i] - '0');

    // Convert fractional part
    // If a decimal point is encountered, process the fractional part by 
    // iterating through the characters and updating the value and power accordingly
    if (s[i] == '.') {
        i++;
        for (power = 1.0; s[i] >= '0' && s[i] <= '9'; i++) {
            val = 10.0 * val + (s[i] - '0');
            power *= 10.0;
        }
    }

    // Handle scientific notation
    // If an 'e' or 'E' is encountered, process the exponent part by determining the sign of 
    // the exponent and calculating its value
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        if (s[i] == '-') {
            exp_sign = -1;
            i++;
        } else if (s[i] == '+') {
            i++;
        }
        for (; s[i] >= '0' && s[i] <= '9'; i++)
            exponent = 10 * exponent + (s[i] - '0');
    }

    return sign * val / power * pow(10, exp_sign * exponent);
}

int main() {
    char s[] = "123.45e-6";
    double result = atof(s);
    printf("The value of '%s' is: %g\n", s, result);
    return 0;
}