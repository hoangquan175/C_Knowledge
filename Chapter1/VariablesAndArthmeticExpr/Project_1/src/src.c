/* Exercises:
1-4. Write a program to print the corresponding Celsius to Fahrenheit table.  
1-5. Modify the temperature conversion program to print the table in reverse order, that is, from 300 degrees to 0.*/
#include <stdio.h>

/* 1-4. Write a program to print the corresponding Celsius to Fahrenheit table. */
int main() {
    float fahr, celsius;
    int lower, upper, step;
    // lower limit of temperature scale
    lower = 0;
    // upper limit of temperature scale
    upper = 300;    
    // step size
    step = 20;      

    // 1-5. Modify the temperature conversion program to print the table in reverse order, that is, from 300 degrees to 0.
    fahr = upper;
    // 1-4. Write a program to print the corresponding Celsius to Fahrenheit table.
    printf("Celsius\tFahrenheit\n");
    while (fahr >= lower) {
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%6.1f\t%3.0f\n", celsius, fahr);
        fahr = fahr - step;
    }
    return 0;
}