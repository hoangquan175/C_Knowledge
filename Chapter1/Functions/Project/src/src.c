/*
Exercises:
1-15. Rewrite the temperature conversion program of Section 1.2 to use a function for conversion. 
*/
#include <stdio.h>
#include "header.h"

#define LOWER 0 // lower limit of temperature table
#define UPPER 300 // upper limit
#define STEP 20 // step size

// Function definitions for temperature conversion
float celsius_to_fahrenheit(float celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}
float fahrenheit_to_celsius(float fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

int main() {
    float celsius, fahrenheit;
    
    printf("Celsius to Fahrenheit:\n");
    printf("Celsius\tFahrenheit\n");
    for (celsius = LOWER; celsius <= UPPER; celsius += STEP) {
        fahrenheit = celsius_to_fahrenheit(celsius);
        printf("%7.0f\t%10.1f\n", celsius, fahrenheit);
    }

    printf("\nFahrenheit to Celsius:\n");
    printf("Fahrenheit\tCelsius\n");    
    for (fahrenheit = LOWER; fahrenheit <= UPPER; fahrenheit += STEP) {
        celsius = fahrenheit_to_celsius(fahrenheit);
        printf("%7.0f\t%10.1f\n", fahrenheit, celsius);
    }

    return 0;
}