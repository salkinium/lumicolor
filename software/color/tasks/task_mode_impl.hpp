// coding: utf-8
/* Copyright (c) 2013, Niklas Hauser
* All Rights Reserved.
*
* The file is released under the 2-clause BSD license.
* See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------
#ifndef TASK_MODE_HPP
#	error	"Don't include this file directly, use 'task_mode.hpp' instead!"
#endif

#include <stdlib.h>

#undef	XPCC_LOG_LEVEL
#define	XPCC_LOG_LEVEL xpcc::log::ERROR

task::Mode::Mode()
:	currentSpace(ColorSpace::RGB)
{
	ModeLed::setInput(Gpio::InputType::Floating);
}

void
task::Mode::setColorSpace(ColorSpace space)
{
	if (space != currentSpace)
	{
		currentSpace = space;
		this->restart();
	}
}

bool
task::Mode::update()
{
	PT_BEGIN();

	ModeLed::setOutput(static_cast<bool>(currentSpace));
	timeout.restart(1500);

	PT_WAIT_UNTIL(timeout.isExpired());

	ModeLed::setInput(Gpio::InputType::Floating);

	// return is included in PT_END();
	PT_END();
}
