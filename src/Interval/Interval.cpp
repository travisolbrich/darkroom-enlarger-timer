#include "Interval.h"

#include "math.h"

// todo: perhaps "stop" makes more sense than "step"?
/* todo: probably no need to do this time to step conversion?
   simplify math by computing arbitrary time + increment as time * pow(2, increment / 12)
*/
double getTime(int step)
{
    double time = pow(2, (step / 12.0));

    return time;
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
        if (intervals[i].interval == interval.interval)
        {
            return i;
        }
    }

    return -1;
}