/*
Exercises:
5-8. There is no error checking in day_of_year or month_day. Remedy this deficiency.
*/
#include <stdio.h>
#include <string.h>
#include "header.h"

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

// is_leap_year: return 1 if year is a leap year, 0 otherwise
int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// day_of_year: set day of year from month & day
int day_of_year(int year, int month, int day) {
    if (year < 1 || month < 1 || month > 12 || day < 1 || day > daytab[is_leap_year(year)][month]) {
        return -1; // Return -1 to indicate an error
    }
    int leap = is_leap_year(year);
    for (int i = 1; i < month; i++) {
        day += daytab[leap][i];
    }
    return day;
}

// month_day: set month, day from day of year
void month_day(int year, int yearday, int *pmonth, int *pday) {
    if (year < 1 || yearday < 1 || yearday > (is_leap_year(year) ? 366 : 365)) {
        *pmonth = -1; // Set month to -1 to indicate an error
        *pday = -1;   // Set day to -1 to indicate an error
        return;
    }
    int leap = is_leap_year(year);
    int month = 1;
    while (yearday > daytab[leap][month]) {
        yearday -= daytab[leap][month];
        month++;
    }
    *pmonth = month;
    *pday = yearday;
}


int main() {
    // Test cases for day_of_year and month_day functions
    int year = 2020, month = 3, day = 1;
    int yearday = day_of_year(year, month, day);
    if (yearday != -1) {
        printf("Day of year for %d-%02d-%02d is: %d\n", year, month, day, yearday);
    } else {
        printf("Invalid date: %d-%02d-%02d\n", year, month, day);
    }

    return 0;
}