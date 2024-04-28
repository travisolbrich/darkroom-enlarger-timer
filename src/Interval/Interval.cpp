#include "math.h"

double getTime(double baseTime, int step)
{
    double time = baseTime * pow(2, (step / 12.0));

    return time;
}