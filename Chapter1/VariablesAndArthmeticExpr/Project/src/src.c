/* 
Exercises:
1-3. Modify the temperature conversion program to print a heading above the table. 
*/
#include <stdio.h>

// 1-3. Modify the temperature conversion program to print a heading above the table.
int main() {
    float fahr, celsius;
    int lower, upper, step;
    // lower limit of temperature scale
    lower = 0;
    // upper limit of temperature scale
    upper = 300;    
    // step size
    step = 20;      

    fahr = lower;
    // 1-3. Modify the temperature conversion program to print a heading above the table.
    printf("Fahrenheit\tCelsius\n");
    printf("----------\t-------\n");
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%3.0f\t\t%6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}