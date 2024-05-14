#pragma once

#include <LiquidCrystal.h>

#include "TestStrip/TestStrip.h"
#include "ButtonConfiguration.h"
#include "InteractionResult.h"

typedef void (*IncrementFunction)(TestStrip&);
typedef void (*DecrementFunction)(TestStrip&);
typedef String (*FormatFunction)(TestStrip&);

class IncrementorInteraction
{
public:
	IncrementorInteraction(LiquidCrystal& lcd, const ButtonConfiguration& buttonConfiguration,
	                       IncrementFunction increment, DecrementFunction decrement, FormatFunction formatString,
	                       const char* message);

	InteractionResult handleInteraction(TestStrip& testStrip);

protected:
	LiquidCrystal& lcd;

	ButtonConfiguration buttonConfiguration;

	IncrementFunction increment;
	DecrementFunction decrement;
	FormatFunction formatString;

	const char* message;

private:
	static bool isButtonPressed(int pin);;

	bool noButtonsPressed() const;;
};
