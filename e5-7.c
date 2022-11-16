#include <stdio.h>

/* note that the array consists of chars to save space, since only small integers are stored */
static char daytab[2][13] = {
{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(void)
{

}

/* set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = ((year%4 == 0 && year%100 != 0) || year%400 == 0);
    /* remember the arithmetic value of a logical expression is either 1 or 0 */

    for(i=1; i<month; i++)
    {
        day += daytab[leap][i];
    }
    return day;
}

/* set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = ((year%4 == 0 && year%100 != 0) || year%400 == 0);

    for(i=1; yearday > daytab[leap][i]; i++)
    {
        yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = yearday;
}