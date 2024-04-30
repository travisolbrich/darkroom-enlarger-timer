#include "TestStripMenu.h"
#include <IncrementorInteraction/IncrementorInteraction.h>
#include "Interval/Interval.h"
#include "TestStrip/TestStripUtil.h"

TestStripMenu::TestStripMenu(LiquidCrystal &lcd, ButtonConfiguration &buttonConfiguration) : lcd(lcd), buttonConfiguration(buttonConfiguration)
{
}

void TestStripMenu::run()
{
    menuExited = false;

    int strips = 8;
    int timeIdx = 0;
    int intervalIdx = 1;
    double testStripBaseTime = 8;
    Interval interval = intervals[intervalIdx];

    StripCountIncrementorInteraction stripCountIncrementorInteraction(lcd, buttonConfiguration, strips);
    TimeIncrementorInteraction timeIncrementorInteraction(lcd, buttonConfiguration, timeIdx, BASE_TIME);
    IntervalIncrementorInteraction intervalIncrementorInteraction(lcd, buttonConfiguration, intervalIdx);

    testStripConfiguration = {strips, testStripBaseTime, interval};
    TestStripUtil::printTestStripInfo(lcd, testStripConfiguration);

    TestStripMenuStates state = STRIP_COUNT;

    while (state != DONE)
    {
        switch (state)
        {
        case STRIP_COUNT:
            strips = stripCountIncrementorInteraction.handleInteraction();

            if (strips == stripCountIncrementorInteraction.BACK_CODE)
            {
                Serial.println("Back code received");
                menuExited = true;
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

        testStripConfiguration = {strips, testStripBaseTime, interval};
        TestStripUtil::printTestStripInfo(lcd, testStripConfiguration);
    }
}

bool TestStripMenu::wasMenuExited()
{
    return menuExited;
}

TestStripConfiguration TestStripMenu::getTestStripConfiguration()
{
    return testStripConfiguration;
}
