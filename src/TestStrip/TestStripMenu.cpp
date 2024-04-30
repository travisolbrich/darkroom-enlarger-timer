#include "TestStripMenu.h"
#include <IncrementorInteraction/IncrementorInteraction.h>
#include "Interval/Interval.h"
#include "TestStrip/TestStrip.h"



bool TestStripMenu::run(TestStrip& outTestStrip)
{

    int strips = 8;
    int timeIdx = 0;
    int intervalIdx = 1;
    double testStripBaseTime = 8;
    Interval interval = intervals[intervalIdx];

    StripCountIncrementorInteraction stripCountIncrementorInteraction(lcd, buttonConfiguration, strips);
    TimeIncrementorInteraction timeIncrementorInteraction(lcd, buttonConfiguration, timeIdx, BASE_TIME);
    IntervalIncrementorInteraction intervalIncrementorInteraction(lcd, buttonConfiguration, intervalIdx);

    outTestStrip.stripCount = 8;
    outTestStrip.time = 8;
    outTestStrip.interval = interval;

    outTestStrip.printTestStripInfo(lcd);

    TestStripMenuStates state = STRIP_COUNT;

    while (state != DONE)
    {
        switch (state)
        {
        case STRIP_COUNT:
            strips = stripCountIncrementorInteraction.handleInteraction();

            if (strips == stripCountIncrementorInteraction.BACK_CODE)
            {
                return false;
            }

            state = TIME;
            break;

        case TIME:
            timeIdx = timeIncrementorInteraction.handleInteraction();

            if (timeIdx == timeIncrementorInteraction.BACK_CODE)
            {
                state = STRIP_COUNT;
                break;
            }


            state = INTERVAL_STEP;
            break;

        case INTERVAL_STEP:
            intervalIdx = intervalIncrementorInteraction.handleInteraction();

            if (intervalIdx == intervalIncrementorInteraction.BACK_CODE)
            {
                state = TIME;
                break;
            }

            state = DONE;
            break;

        case DONE:
            break;
        }

        lcd.clear();

        outTestStrip.stripCount = strips;
        outTestStrip.time = getTime(BASE_TIME, timeIdx);
        outTestStrip.interval = intervals[intervalIdx];

        outTestStrip.printTestStripInfo(lcd);
    }

    return true;
}
