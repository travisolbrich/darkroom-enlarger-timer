#include "TestStripMenu.h"
#include <IncrementorInteraction/IncrementorInteraction.h>
#include "Interval/Interval.h"
#include "TestStrip/TestStripUtil.h"

TestStripMenu::TestStripMenu(LiquidCrystal &lcd, ButtonConfiguration &buttonConfiguration) : lcd(lcd), buttonConfiguration(buttonConfiguration)
{
}

TestStripConfiguration TestStripMenu::run()
{
    int strips = 8;
    int timeIdx = 0;
    int intervalIdx = 1;
    double testStripBaseTime = 8;
    Interval interval = intervals[intervalIdx];

    StripCountIncrementorInteraction stripCountIncrementorInteraction(lcd, buttonConfiguration, strips);
    TimeIncrementorInteraction timeIncrementorInteraction(lcd, buttonConfiguration, timeIdx, BASE_TIME);
    IntervalIncrementorInteraction intervalIncrementorInteraction(lcd, buttonConfiguration, intervalIdx);

    TestStripConfiguration config = {strips, testStripBaseTime, interval};
    TestStripUtil::printTestStripInfo(lcd, config);

    TestStripMenuStates state = STRIP_COUNT;

    while (state != DONE)
    {
        switch (state)
        {
        case STRIP_COUNT:
            strips = stripCountIncrementorInteraction.handleInteraction();

            if (strips == stripCountIncrementorInteraction.BACK_CODE)
            {
                return;
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

            testStripBaseTime = getTime(BASE_TIME, timeIdx);

            state = INTERVAL_STEP;
            break;

        case INTERVAL_STEP:
            intervalIdx = intervalIncrementorInteraction.handleInteraction();

            if (intervalIdx == intervalIncrementorInteraction.BACK_CODE)
            {
                state = TIME;
                break;
            }

            interval = intervals[intervalIdx];
            state = DONE;
            break;

        case DONE:
            break;
        }

        lcd.clear();

        config = {strips, testStripBaseTime, interval};
        TestStripUtil::printTestStripInfo(lcd, config);
    }

    return config;
}
