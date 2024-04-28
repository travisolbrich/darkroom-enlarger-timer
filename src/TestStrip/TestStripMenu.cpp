#include "TestStripMenu.h"
#include <IncrementorInteraction/IncrementorInteraction.h>
#include "Interval/Interval.h"

TestStripMenu::TestStripMenu(LiquidCrystal &lcd, ButtonConfiguration &buttonConfiguration) : lcd(lcd), buttonConfiguration(buttonConfiguration)
{
}

void TestStripMenu::printTestStripInfoLine(int strips)
{
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("#");
    lcd.print(strips);
}

void TestStripMenu::printTestStripInfoLine(int strips, double time)
{
    printTestStripInfoLine(strips);
    lcd.print(" ");
    lcd.print(String(time, 1));
    lcd.print("s ");
}

void TestStripMenu::printTestStripInfoLine(int strips, double time, Interval interval)
{
    printTestStripInfoLine(strips, time);
    lcd.print("+");
    lcd.print(interval.label);
}

TestStripConfiguration TestStripMenu::run()
{
    int strips = 8;
    int timeIdx = 0;
    int intervalIdx = 1;
    double testStripBaseTime = 0;
    Interval interval = intervals[0];

    StripCountIncrementorInteraction stripCountIncrementorInteraction(lcd, buttonConfiguration, strips);
    TimeIncrementorInteraction timeIncrementorInteraction(lcd, buttonConfiguration, timeIdx, BASE_TIME);
    IntervalIncrementorInteraction intervalIncrementorInteraction(lcd, buttonConfiguration, intervalIdx);

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
            printTestStripInfoLine(strips);
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
            printTestStripInfoLine(strips, testStripBaseTime);
            intervalIdx = intervalIncrementorInteraction.handleInteraction();

            if (intervalIdx == intervalIncrementorInteraction.BACK_CODE)
            {
                state = TIME;
                break;
            }

            interval = intervals[intervalIdx];
            state = DONE;
            break;
        }

        lcd.clear();
    }

    printTestStripInfoLine(strips, testStripBaseTime, interval);

    return {strips, testStripBaseTime, interval};
}
