#ifndef __GENERAL_H_
#define __GENERAL_H_

int dayOfMonth(int day_of_year, int is_leap_year);

int dayOfYear(int day, int month, int is_leap_year);

int monthOfYear(int dayOfYear, int isLeapYear);

int getCurrentDayOfMonth(void);

int getCurrentDayOfYear(void);

int minOfDay(int hours, int minutes);

int hourOfDay(int totalMinutes);

int minOfDay(int totalMinutes);

#endif /* __GENERAL_H_ */
