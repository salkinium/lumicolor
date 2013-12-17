// coding: utf-8
/* Copyright (c) 2013, Niklas Hauser
* All Rights Reserved.
*
* The file is released under the 2-clause BSD license.
* See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------
#ifndef TASK_MODE_HPP
#define TASK_MODE_HPP

#include <xpcc/processing.hpp>

#include "../hardware.hpp"

namespace task
{

class Mode : private xpcc::pt::Protothread
{
public:
	Mode();

	void
	setColorSpace(ColorSpace space);

	bool
	update();

private:
	xpcc::Timeout<> timeout;
	ColorSpace currentSpace;
};

} // namespace task

#include "task_mode_impl.hpp"

#endif // TASK_MODE_HPP
