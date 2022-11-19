#include <stdio.h>

#define DAYS_IN_YEAR 365

/* note that the array consists of chars to save space, since only small integers are stored */
/* each row starts with 0 so that months can be accessed with traditional numbers 1 to 12 */
static char *daytab[2];
static char noleap[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char yesleap[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

/* Converts month and day into day of year (i.e. 1-365/366), and then vice-versa,
prompting the user for fresh input both times */
/* Modified to check for validity of dates, assumes valid input otherwise */
/* Rewritten to use pointers instead of indexing */
int main(void)
{
    int year, month, day, yearday;
    int *pmonth = &month;
    int *pday = &day;
    *daytab = noleap; // There may well have been a cleaner way to do this, but the book didn't
    *(daytab+1) = yesleap; // really specify how to init. pointer arrays beyond string constants

    /* Convert month/day to yearday */
    printf("Enter year: ");
    scanf("%d", &year);
    if(year<1)
    {
        printf("Invalid year\n");
        return 0;
    }
    printf("Enter month: ");
    scanf("%d", pmonth);
    printf("Enter day: ");
    scanf("%d", pday);

    yearday = day_of_year(year, month, day);
    if(yearday > 0)
    {
        printf("Day of year is %d\n", yearday);
    }

    /* Convert yearday to month/day */
    printf("Enter year: ");
    scanf("%d", &year);
    if(year<1)
    {
        printf("Invalid year\n");
        return 0;
    }
    printf("Enter day of year: ");
    scanf("%d", &yearday);

    month_day(year, yearday, pmonth, pday);
    if(month > 0)
    {
        printf("Month is %d, day is %d\n", month, day);
    }

    return 0;
}

/* set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = ((year%4 == 0 && year%100 != 0) || year%400 == 0);
    /* remember the arithmetic value of a logical expression is either 1 or 0 */
    if((month > 12) || (month < 1))
    {
        printf("Invalid month\n");
        return -1;
    }
    if((day > (*(daytab+leap))[month]) || (day < 1))
    {
        printf("Invalid day\n");
        return -1;
    }

    for(i=1; i<month; i++)
    {
        day += (*(daytab+leap))[i];
    }
    return day;
}

/* set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = ((year%4 == 0 && year%100 != 0) || year%400 == 0);
    if((yearday > (DAYS_IN_YEAR + leap)) || (yearday < 1)) // yearday is invalid
    {
        printf("Invalid day of year\n");
        *pmonth = -1;
        return;
    }

    for(i=1; yearday > (*(daytab+leap))[i]; i++)
    {
        yearday -= (*(daytab+leap))[i];
    }
    *pmonth = i;
    *pday = yearday;
}