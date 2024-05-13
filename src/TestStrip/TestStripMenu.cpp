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
    InteractionResult interactionResult = InteractionResult::Continue;

    while (state != DONE)
    {
        switch (state)
        {
        case STRIP_COUNT:
            Serial.println("STRIP_COUNT");

            interactionResult = stripCountIncrementorInteraction.handleInteraction(outTestStrip);

            if (interactionResult == InteractionResult::Back || interactionResult == InteractionResult::MainMenu)
            {
                return false;
            }
            if (interactionResult == InteractionResult::Done)
            {
                state = DONE;
                break;
            }

            state = TIME;
            break;

        case TIME:
            Serial.println("TIME");

            interactionResult = timeIncrementorInteraction.handleInteraction(outTestStrip);

            if (interactionResult == InteractionResult::Back)
            {
                state = STRIP_COUNT;
                break;
            }

            if (interactionResult == InteractionResult::MainMenu)
            {
                return false;
            }

            if (interactionResult == InteractionResult::Done)
            {
                state = DONE;
                break;
            }

            state = INTERVAL_STEP;
            break;

        case INTERVAL_STEP:
            Serial.println("INTERVAL_STEP");

            interactionResult = intervalIncrementorInteraction.handleInteraction(outTestStrip);

            if (interactionResult == InteractionResult::Back)
            {
                state = TIME;
                break;
            }

            if (interactionResult == InteractionResult::MainMenu)
            {
                return false;
            }

            if (interactionResult == InteractionResult::Done)
            {
                state = DONE;
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
