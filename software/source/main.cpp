// coding: utf-8
#include "hardware.hpp"

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
	RedLedPin::setOutput();
	GreenLedPin::setOutput();
	BlueLedPin::setOutput();

	LightSensorPin::setInput();

	// set up the oversampling of the photosensitive diode
	AdcInterrupt::initialize(AdcInterrupt::Reference::ExternalARef, AdcInterrupt::Prescaler::Div32);
	lightSensor::initialize(adcMap, &lightSensorData);

	GpioD0::connect(Uart::Rx);
	GpioD1::connect(Uart::Tx);
	Uart::initialize<Uart::B115200>();

	xpcc::atmega::enableInterrupts();
	XPCC_LOG_INFO << "\n\nRESTART\n\n";

	while(1)
	{
		dreamer.run();
	}

	return 0;
}
