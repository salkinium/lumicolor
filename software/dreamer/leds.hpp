// coding: utf-8
/* Copyright (c) 2013, Niklas Hauser
* All Rights Reserved.
*
* The file is part of the my thesis and is released under the 3-clause BSD
* license. See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------


#ifndef LEDS_HPP
#define LEDS_HPP

#include <xpcc/architecture/platform.hpp>
#include <xpcc/processing.hpp>
#include <xpcc/ui/led.hpp>
#include <xpcc/debug/logger.hpp>

void
initializeLeds()
{
	// Timer0 is used to fade the blue and green LEDs at 8bit resolution.
	// Fast PWM mode, inverting mode for both A and B compare outputs
	// Clear OC0X on Compare Match, set OC0X at Bottom
	TCCR0A = (1 << WGM01) | (1 << WGM00) |
			(1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0);
	// 8000kHz / 8 / 256 = 3.9kHz
	// Prescaler 64, enable Timer0
	TCCR0B = (1 << CS01);
	// No Interrupt required
	TIMSK0 = 0;

	// Timer1 is used to fade the red Led at 8bit resolution
	// Fast PWM mode, inverting mode for A compare outputs
	// Clear OC0X on Compare Match, set OC0X at Bottom
	TCCR1A = (1 << WGM12) | (1 << WGM10) |
			(1 << COM1A1) | (1 << COM1A0);
	// 8000kHz / 8 / 256 = 3.9kHz
	// Prescaler 8, enable Timer1
	TCCR1B = (1 << CS11);
	// No Interrupt required
	TIMSK1 = 0;

	// Timer2 is used to drive xpcc::Clock
	// CTC Mode
	TCCR2A = (1 << WGM21);
	// 8000kHz / 64 / 125 = 1kHz ~ 1ms
	// Prescaler 64, enable Timer2
	TCCR2B = (1 << CS22);
	// Enable Overflow Interrupt for xpcc::Clock
	TIMSK2 = (1 << OCIE2A);
	OCR2A = 125;
}

class RedLed : public xpcc::ui::Led
{
	xpcc::accessor::Flash<uint8_t> table;

	virtual void
	setValue(uint8_t brightness)
	{
		OCR1A = 255 - table[brightness];
	}

public:
	RedLed(const uint8_t* table=xpcc::ui::table8_256)
	:	Led(), table(table)
	{
	}
};

class GreenLed : public xpcc::ui::Led
{
	xpcc::accessor::Flash<uint8_t> table;

	virtual void
	setValue(uint8_t brightness)
	{
		OCR0A = 255 - table[brightness];
	}

public:
	GreenLed(const uint8_t* table=xpcc::ui::table8_256)
	:	Led(), table(table)
	{
	}
};

class BlueLed : public xpcc::ui::Led
{
	xpcc::accessor::Flash<uint8_t> table;

	virtual void
	setValue(uint8_t brightness)
	{
		OCR0B = 255 - table[brightness];
	}

public:
	BlueLed(const uint8_t* table=xpcc::ui::table8_256)
	:	Led(), table(table)
	{
	}
};



#endif // LEDS_HPP
