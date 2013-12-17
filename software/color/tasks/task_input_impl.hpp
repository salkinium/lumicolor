// coding: utf-8
/* Copyright (c) 2013, Niklas Hauser
* All Rights Reserved.
*
* The file is released under the 2-clause BSD license.
* See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------
#ifndef TASK_INPUT_HPP
#	error	"Don't include this file directly, use 'task_input.hpp' instead!"
#endif

#include <stdlib.h>

#undef	XPCC_LOG_LEVEL
#define	XPCC_LOG_LEVEL xpcc::log::ERROR

task::Input::Input()
:	timer(20), modeTask()
{
	ModePin::setInput(Gpio::InputType::PullUp);

	LightSensorPin::setInput();
	A0::setInput();
	A1::setInput();
	A2::setInput();
}

bool
task::Input::update()
{
	modeTask.update();

	PT_BEGIN();

	while(true)
	{
		PT_WAIT_UNTIL(sensors::readSensors());

		colorSpace = static_cast<ColorSpace>(!ModePin::read());
		modeTask.setColorSpace(colorSpace);

		PT_WAIT_UNTIL(sensors::isNewDataAvailable());
		sensors::getData();

		if (colorSpace == ColorSpace::RGB)
		{
			rgb.red = 255 - (sensorData[0] / 4);
			rgb.green = 255 - (sensorData[1] / 4);
			rgb.blue = 255 - (sensorData[2] / 4);
			colorLed.setColor(rgb);
		}
		else
		{
			hsv.hue = 255 - (sensorData[0] / 4);
			hsv.saturation = 255 - (sensorData[1] / 4);
			hsv.value = 255 - (sensorData[2] / 4);
			colorLed.setColor(hsv);
		}

		PT_WAIT_UNTIL(timer.isExpired());
	}

	// return is included in PT_END();
	PT_END();
}
