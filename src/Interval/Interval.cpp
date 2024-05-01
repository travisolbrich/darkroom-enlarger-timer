#include "Interval.h"

#include "math.h"

double getTime(int numTwelthStops)
{
    return pow(2, (numTwelthStops / 12.0));
}

int getStep(double time)
{
    double step = log(time) / log(2.0) * 12;
    return round(step);
}

// given interval, return index in intervals[]
int getIntervalIndex(const Interval interval)
{
    for (int i = 0; i < sizeof(intervals) / sizeof(Interval); i++)
    {
        if (intervals[i].divisor == interval.divisor)
        {
            return i;
        }
    }

    return -1;
}