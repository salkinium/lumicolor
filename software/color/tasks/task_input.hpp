// coding: utf-8
/* Copyright (c) 2013, Niklas Hauser
* All Rights Reserved.
*
* The file is released under the 2-clause BSD license.
* See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------
#ifndef TASK_INPUT_HPP
#define TASK_INPUT_HPP

#include <xpcc/processing.hpp>
#include <xpcc/debug/logger.hpp>
#include <xpcc/ui/color.hpp>
#include "task_mode.hpp"

#include "../hardware.hpp"

namespace task
{

class Input : private xpcc::pt::Protothread
{
public:
	Input();

	bool
	update();

private:
	xpcc::PeriodicTimer<> timer;
	xpcc::color::Rgb rgb;
	xpcc::color::Hsv hsv;

	Mode modeTask;
};

} // namespace task

#include "task_input_impl.hpp"

#endif // TASK_INPUT_HPP
