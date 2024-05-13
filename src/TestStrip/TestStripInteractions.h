#pragma once

#include "TestStrip/TestStrip.h"

namespace TestStripInteractions
{
	void incrementStripCount(TestStrip& testStrip);
	void decrementStripCount(TestStrip& testStrip);
	String formatStripCount(TestStrip& testStrip);

	void incrementTime(TestStrip& testStrip);
	void decrementTime(TestStrip& testStrip);
	String formatTime(TestStrip& testStrip);

	void incrementInterval(TestStrip& testStrip);
	void decrementInterval(TestStrip& testStrip);
	String formatInterval(TestStrip& testStrip);
} // namespace TestStripInteractions
