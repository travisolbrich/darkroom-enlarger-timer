#include "IncrementorInteraction.h"
#include <LiquidCrystal.h>
#include "Interval/Interval.h"
#include "ButtonConfiguration.h"

// StripCountIncrementorInteraction

StripCountIncrementorInteraction::StripCountIncrementorInteraction(LiquidCrystal &lcd,
                                                                   const ButtonConfiguration &buttonConfiguration):
    IncrementorInteraction(lcd, buttonConfiguration)
{
    message = "Strips: ";
    suffix = "";
}


String StripCountIncrementorInteraction::formatString(TestStrip& testStrip)
{
    return String(testStrip.stripCount);
}

void StripCountIncrementorInteraction::increment(TestStrip& testStrip)
{
    if (testStrip.stripCount < 10)
    {
        testStrip.stripCount++;
    }
}

void StripCountIncrementorInteraction::decrement(TestStrip& testStrip)
{
    if (testStrip.stripCount > 1)
    {
        testStrip.stripCount--;
    }
}

// TimeIncrementorInteraction
TimeIncrementorInteraction::TimeIncrementorInteraction(LiquidCrystal &lcd,
                                                       const ButtonConfiguration &buttonConfiguration):
    IncrementorInteraction(lcd, buttonConfiguration)
{
    message = "Time: ";
    suffix = "s";
}

String TimeIncrementorInteraction::formatString(TestStrip& testStrip)
{
    return String(testStrip.time, 1);
}

void TimeIncrementorInteraction::increment(TestStrip& testStrip)
{
    // todo: should we set upper bound?
    testStrip.time = testStrip.time * getTime(1);
}

void TimeIncrementorInteraction::decrement(TestStrip& testStrip)
{
    if (testStrip.time > 1)
    {
        testStrip.time = testStrip.time * getTime(-1);
    }
}

// IntervalIncrementorInteraction

IntervalIncrementorInteraction::IntervalIncrementorInteraction(LiquidCrystal &lcd,
                                                               const ButtonConfiguration &buttonConfiguration):
    IncrementorInteraction(lcd, buttonConfiguration)
{
    message = "Interval: ";
    suffix = " steps";
}

String IntervalIncrementorInteraction::formatString(TestStrip& testStrip)
{
    String result = String(testStrip.interval.label);
    result.concat(": ");
    result.concat(testStrip.interval.fullLabel);

    return result;
}

void IntervalIncrementorInteraction::increment(TestStrip& testStrip)
{
    int i = getIntervalIndex(testStrip.interval);

    if (i < 3)
    {
        testStrip.interval = intervals[i + 1];
    }
}

void IntervalIncrementorInteraction::decrement(TestStrip& testStrip)
{
    int i = getIntervalIndex(testStrip.interval);

    if (i > 0)
    {
        testStrip.interval = intervals[i - 1];
    }
}
