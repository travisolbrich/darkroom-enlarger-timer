#include "TestStripMenu.h"

#include "IncrementorInteraction/IncrementorInteraction.h"
#include "TestStrip/TestStrip.h"
#include "TestStripInteractions.h"

bool TestStripMenu::run(TestStrip &outTestStrip)
{

    IncrementorInteraction stripCountIncrementorInteraction(lcd, buttonConfiguration,
                                                            TestStripInteractions::incrementStripCount,
                                                            TestStripInteractions::decrementStripCount,
                                                            TestStripInteractions::formatStripCount,
                                                            "Strips:");

    IncrementorInteraction timeIncrementorInteraction(lcd, buttonConfiguration,
                                                      TestStripInteractions::incrementTime,
                                                      TestStripInteractions::decrementTime,
                                                      TestStripInteractions::formatTime,
                                                      "Time:");

    IncrementorInteraction intervalIncrementorInteraction(lcd, buttonConfiguration,
                                                          TestStripInteractions::incrementInterval,
                                                          TestStripInteractions::decrementInterval,
                                                          TestStripInteractions::formatInterval,
                                                          "Interval:");

    IncrementorInteraction *interactions[] = {
        &stripCountIncrementorInteraction,
        &timeIncrementorInteraction,
        &intervalIncrementorInteraction
    };

    int interactionStage = 0;

    while (interactionStage >= 0 && interactionStage < 3)
    {
        lcd.clear();

        outTestStrip.printTestStripFooter(lcd);

        InteractionResult interactionResult = interactions[interactionStage]->handleInteraction(outTestStrip);

        switch (interactionResult)
        {
        case InteractionResult::Back:
            interactionStage--;
            break;

        case InteractionResult::Continue:
            interactionStage++;
            break;

        case InteractionResult::MainMenu:
            return false;

        case InteractionResult::Done:
            return true;
        }
    }

    if (interactionStage < 0)
    {
        return false;
    }

    return true;

}
