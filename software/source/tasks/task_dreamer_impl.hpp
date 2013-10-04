// coding: utf-8
/* Copyright (c) 2013, Niklas Hauser
* All Rights Reserved.
*
* The file is released under the 2-clause BSD license.
* See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------
#ifndef TASK_DREAMER_HPP
#	error	"Don't include this file directly, use 'task_dreamer.hpp' instead!"
#endif

#include <stdlib.h>

#undef	XPCC_LOG_LEVEL
#define	XPCC_LOG_LEVEL xpcc::log::ERROR

task::Dreamer::Dreamer()
:	timeout(3000), color(0,255,255)
{
}

bool
task::Dreamer::run()
{
	colorLed.run();

	PT_BEGIN();

	while(true)
	{
		color.hue = rand() % 256;
		colorLed.fadeTo(1000, color);
		timeout.restart(1000);

		PT_WAIT_UNTIL(timeout.isExpired());
	}

	// return is included in PT_END();
	PT_END();
}
