#ifndef HEADER_H
#define HEADER_H

// Function declaration for day_of_year: convert month/day to day of year
int day_of_year(int year, int month, int day);
// Function declaration for month_day: convert day of year to month/day
void month_day(int year, int yearday, int *pmonth, int *pday);
// Function declaration for is_leap_year: check if a year is a leap year
int is_leap_year(int year);

#endif // HEADER_H
