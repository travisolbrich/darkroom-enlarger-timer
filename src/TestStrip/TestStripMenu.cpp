#include "TestStripMenu.h"
#include <IncrementorInteraction/IncrementorInteraction.h>
#include "TestStrip/TestStrip.h"


bool TestStripMenu::run(TestStrip& outTestStrip)
{
    StripCountIncrementorInteraction stripCountIncrementorInteraction(lcd, buttonConfiguration);
    TimeIncrementorInteraction timeIncrementorInteraction(lcd, buttonConfiguration);
    IntervalIncrementorInteraction intervalIncrementorInteraction(lcd, buttonConfiguration);

    outTestStrip.printTestStripFooter(lcd);

    TestStripMenuStates state = STRIP_COUNT;

    while (state != DONE)
    {
        switch (state)
        {
        case STRIP_COUNT:
            Serial.println("STRIP_COUNT");

            if (!stripCountIncrementorInteraction.handleInteraction(outTestStrip.stripCount))
            {
                return false;
            }

            state = TIME;
            break;

        case TIME:
            Serial.println("TIME");

            if (!timeIncrementorInteraction.handleInteraction(outTestStrip.time))
            {
                state = STRIP_COUNT;
                break;
            }

            state = INTERVAL_STEP;
            break;

        case INTERVAL_STEP:
            Serial.println("INTERVAL_STEP");

            if (!intervalIncrementorInteraction.handleInteraction(outTestStrip.interval))
            {
                state = TIME;
                break;
            }

            state = DONE;
            break;

        case DONE:
            Serial.println("DONE");
            break;
        }

        lcd.clear();

        outTestStrip.printTestStripFooter(lcd);
    }

    return true;
}
