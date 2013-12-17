// coding: utf-8
#include "hardware.hpp"

#undef	XPCC_LOG_LEVEL
#define	XPCC_LOG_LEVEL xpcc::log::DEBUG

// system tick timer
ISR(TIMER2_COMPA_vect)
{
	xpcc::Clock::increment();
}

// main function \o/
int
main(void)
{
	// set the led pins
	initializeLeds();
	RedLedPin::setOutput(xpcc::Gpio::Low);
	GreenLedPin::setOutput(xpcc::Gpio::Low);
	BlueLedPin::setOutput(xpcc::Gpio::Low);

	AdcInterrupt::initialize(AdcInterrupt::Reference::ExternalARef,
			AdcInterrupt::Prescaler::Div4);
	sensors::initialize(adcMap, sensorData);

	GpioD0::connect(Uart::Rx);
	GpioD1::connect(Uart::Tx);
	Uart::initialize<Uart::B38400>();

	xpcc::atmega::enableInterrupts();
	XPCC_LOG_INFO << "\n\nRESTART\n\n";

	while(1)
	{
		input.update();
	}

	return 0;
}
