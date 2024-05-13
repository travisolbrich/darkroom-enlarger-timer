#include "TestStripInteractions.h"

namespace TestStripInteractions {
    String formatStripCount(TestStrip& testStrip)
    {
        return String(testStrip.stripCount);
    }

    void incrementStripCount(TestStrip& testStrip)
    {
        if (testStrip.stripCount < 10)
        {
            testStrip.stripCount++;
        }
    }

    void decrementStripCount(TestStrip& testStrip)
    {
        if (testStrip.stripCount > 1)
        {
            testStrip.stripCount--;
        }
    }


    String formatTime(TestStrip& testStrip)
    {
        return String(testStrip.time, 1) + "s";
    }

    void incrementTime(TestStrip& testStrip)
    {
        // todo: should we set upper bound?
        testStrip.time = testStrip.time * getTime(1);
    }

    void decrementTime(TestStrip& testStrip)
    {
        if (testStrip.time > 1)
        {
            testStrip.time = testStrip.time * getTime(-1);
        }
    }


    String formatInterval(TestStrip& testStrip)
    {
        return String(testStrip.interval.label) + ": " + testStrip.interval.fullLabel;
    }

    void incrementInterval(TestStrip& testStrip)
    {
        int i = getIntervalIndex(testStrip.interval);

        if (i < 3)
        {
            testStrip.interval = intervals[i + 1];
        }
    }

    void decrementInterval(TestStrip& testStrip)
    {
        int i = getIntervalIndex(testStrip.interval);

        if (i > 0)
        {
            testStrip.interval = intervals[i - 1];
        }
    }
}