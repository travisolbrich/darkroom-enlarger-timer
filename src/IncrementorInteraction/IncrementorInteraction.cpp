#include "IncrementorInteraction.h"
#include <LiquidCrystal.h>
#include "Interval/Interval.h"
#include "ButtonConfiguration.h"

// StripCountIncrementorInteraction

StripCountIncrementorInteraction::StripCountIncrementorInteraction(LiquidCrystal& lcd,
                                                                   const ButtonConfiguration& buttonConfiguration):
    IncrementorInteraction<int>(lcd, buttonConfiguration)
{
    message = "Strips: ";
    suffix = "";
}

String StripCountIncrementorInteraction::formatString(int value)
{
    return String(value);
}

int StripCountIncrementorInteraction::increment(int value)
{
    if (value < 10)
    {
        return value + 1;
    }

    return value;
}

int StripCountIncrementorInteraction::decrement(int value)
{
    if (value > 1)
    {
        return value - 1;
    }

    return value;
}

// TimeIncrementorInteraction
TimeIncrementorInteraction::TimeIncrementorInteraction(LiquidCrystal& lcd,
                                                       const ButtonConfiguration& buttonConfiguration):
    IncrementorInteraction<double>(lcd, buttonConfiguration)
{
    message = "Time: ";
    suffix = "s";
}

String TimeIncrementorInteraction::formatString(double value)
{
    return String(value, 1);
}

double TimeIncrementorInteraction::increment(double value)
{
    // todo: should we set upper bound?
    return value * getTime(1);
}

double TimeIncrementorInteraction::decrement(double value)
{
    if (value > 1)
    {
        return value * getTime(-1);
    }
    return value;
}

// IntervalIncrementorInteraction

IntervalIncrementorInteraction::IntervalIncrementorInteraction(LiquidCrystal& lcd,
                                                               const ButtonConfiguration& buttonConfiguration):
    IncrementorInteraction<Interval>(lcd, buttonConfiguration)
{
    message = "Interval: ";
    suffix = " steps";
}

String IntervalIncrementorInteraction::formatString(Interval value)
{
    auto result = String(value.label);
    result.concat(": ");
    result.concat(value.fullLabel);

    return result;
}

Interval IntervalIncrementorInteraction::increment(Interval value)
{
    int i = getIntervalIndex(value);

    if (i < 3)
    {
        return intervals[i + 1];
    }

    return value;
}

Interval IntervalIncrementorInteraction::decrement(Interval value)
{
    int i = getIntervalIndex(value);

    if (i > 0)
    {
        return intervals[i - 1];
    }

    return value;
}
