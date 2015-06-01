
#include <stdio.h>
#include <math.h>
#include "utc2gmt.h"

#define SECONDS_PER_DAY         (60*60*24)
#define MILLISECONDS_PER_DAY	(1000 * SECONDS_PER_DAY)
#define DAYS_FROM_1970_TO_1984	((11*365) + (3*366))
#define TIME_T_1984_JAN_1       (DAYS_FROM_1970_TO_1984 * SECONDS_PER_DAY)

char *utctogmt(char *buff, signed long seconds, signed long fraction, signed long qflags)
{
    if (!buff)
        return NULL;

    signed long NOday, MS, year366, year365, year, month, day, remind_day;
    float f_MS;
    int h, m, s, SEC;

    if (seconds > TIME_T_1984_JAN_1)
    {
        NOday = (seconds - TIME_T_1984_JAN_1) / SECONDS_PER_DAY;
        SEC = ((seconds - TIME_T_1984_JAN_1) % SECONDS_PER_DAY);
    }
    else
    {
        NOday = seconds / SECONDS_PER_DAY;
        if (NOday == 0)
            NOday = 1;
        SEC = seconds % SECONDS_PER_DAY;
    }

    MS = fraction * 1000.0 / 0x01000000;
    f_MS = fraction * 1000.0 / 0x01000000;

    year366 = (NOday / (365 * 4));
    year365 = (NOday - (year366 * 366)) / 365;

    year = year365 + year366 + (seconds < TIME_T_1984_JAN_1) ? 1970 : 1984;

    remind_day = NOday - (year365 * 365 + year366 * 366);

    if (year % 4 == 0) {
        month = remind_day / (366 / 12);
        day = remind_day % (366 / 12);
    }
    else {
        month = (remind_day / (365 / 12));
        day = remind_day % (365 / 12);
        month++;

    }

    h = SEC / (60 * 60);
    m = (SEC - h*(60 * 60 ))/(60);
    s = (SEC - h*(60 * 60)) % (60);

    sprintf(buff, "%d-%d-%d %d:%d:%d.%.0f", year, month, day, h, m, s, ceil(f_MS));
    return buff;
}

