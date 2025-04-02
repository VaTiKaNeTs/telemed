#include "general.h"
#include <time.h>

/***********************************************************************************************/
int dayOfMonth(int day_of_year, int is_leap_year)
{
    int days_in_months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (is_leap_year)
    {
        days_in_months[1] = 29; // Февраль в високосный год
    }

    int month = 0;
    while (day_of_year > days_in_months[month])
    {
        day_of_year -= days_in_months[month];
        month++;
    }
    return day_of_year;
}

/***********************************************************************************************/
int dayOfYear(int day, int month, int is_leap_year) 
{
    int days_in_months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (is_leap_year) 
    {
        days_in_months[1] = 29;
    }

    int day_of_year = day;
    for (int i = 0; i < month - 1; i++) 
    {
        day_of_year += days_in_months[i];
    }
    return day_of_year;
}

/***********************************************************************************************/
int monthOfYear(int dayOfYear, int isLeapYear) 
{
    int daysInMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear) 
    {
        daysInMonths[1] = 29;
    }

    int month = 0;
    while (dayOfYear > daysInMonths[month]) 
    {
        dayOfYear -= daysInMonths[month];
        month++;
    }
    return month + 1;
}

/***********************************************************************************************/
int getCurrentDayOfMonth(void) 
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_mday;
}

/***********************************************************************************************/
int getCurrentDayOfYear(void)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_yday + 1; // tm_yday начинается с 0
}