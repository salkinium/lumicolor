// coding: utf-8
/* Copyright (c) 2013, Niklas Hauser
* All Rights Reserved.
*
* The file is released under the 2-clause BSD license.
* See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------
#ifndef TASK_DREAMER_HPP
#define TASK_DREAMER_HPP

#include <xpcc/processing/protothread.hpp>
#include <xpcc/processing/timeout.hpp>
#include <xpcc/debug/logger.hpp>
#include <xpcc/ui/color.hpp>

#include "../hardware.hpp"

namespace task
{

class Dreamer : private xpcc::pt::Protothread
{
public:
	Dreamer();

	bool
	run();

private:
	xpcc::Timeout<> timeout;
	xpcc::color::Hsv color;
};

} // namespace task

#include "task_dreamer_impl.hpp"

#endif // TASK_DREAMER_HPP
