#include "TestStripMenu.h"
#include <IncrementorInteraction/IncrementorInteraction.h>
#include "Interval/Interval.h"
#include "TestStrip/TestStrip.h"



bool TestStripMenu::run(TestStrip& outTestStrip)
{
    int stripCount = outTestStrip.stripCount;
    int timeIdx = getStep(outTestStrip.time);
    int intervalIdx = getIntervalIndex(outTestStrip.interval);

    StripCountIncrementorInteraction stripCountIncrementorInteraction(lcd, buttonConfiguration, outTestStrip.stripCount);
    TimeIncrementorInteraction timeIncrementorInteraction(lcd, buttonConfiguration, timeIdx);
    IntervalIncrementorInteraction intervalIncrementorInteraction(lcd, buttonConfiguration, intervalIdx);

    outTestStrip.printTestStripInfo(lcd);

    TestStripMenuStates state = STRIP_COUNT;

    while (state != DONE)
    {
        switch (state)
        {
        case STRIP_COUNT:
            Serial.println("STRIP_COUNT");
            stripCount = stripCountIncrementorInteraction.handleInteraction();
            Serial.println(stripCount);
            if (stripCount == stripCountIncrementorInteraction.BACK_CODE)
            {
                return false;
            }

            outTestStrip.stripCount = stripCount;

            state = TIME;
            break;

        case TIME:
            Serial.println("TIME");
            timeIdx = timeIncrementorInteraction.handleInteraction();

            if (timeIdx == timeIncrementorInteraction.BACK_CODE)
            {
                state = STRIP_COUNT;
                break;
            }

            outTestStrip.time = getTime(timeIdx);

            state = INTERVAL_STEP;
            break;

        case INTERVAL_STEP:
            Serial.println("INTERVAL_STEP");
            intervalIdx = intervalIncrementorInteraction.handleInteraction();

            if (intervalIdx == intervalIncrementorInteraction.BACK_CODE)
            {
                state = TIME;
                break;
            }

            outTestStrip.interval = intervals[intervalIdx];

            state = DONE;
            break;

        case DONE:
            Serial.println("DONE");
            break;
        }

        lcd.clear();

        outTestStrip.printTestStripInfo(lcd);
    }

    return true;
}
