// coding: utf-8
/* Copyright (c) 2013, Niklas Hauser
* All Rights Reserved.
*
* The file is released under the 2-clause BSD license.
* See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------

#ifndef LUMINET2_HARDWARE
#define LUMINET2_HARDWARE

#include <xpcc/architecture/platform.hpp>

using namespace xpcc::atmega;

// IO #########################################################################
// ATMEL ATMEGA328P
//                     +------------+
//     (P3/INT1) PD3  1|o           |24  PC1 (ADC1/A1)
//               PD4  2|            |23  PC0 (ADC0/A0)
//               GND  3|            |22  ADC7
//               VCC  4|            |21  GND
//               GND  5|            |20  AREF
//               VCC  6|            |19  ADC6
//       (XTAL1) PB6  7|            |18  AVCC
//       (XTAL2) PB7  8|            |17  PB5 (SCK)
//                     +------------+
//
//                     +------------+
//  (BLUE/OC0B) PD5   9|           o|32  PD2 (INT0/SRX)
// (GREEN/OC0A) PD6  10|            |31  PD1 (TXD)
//        (STX) PD7  11|            |30  PD0 (RXD)
//              PB0  12|            |29  PC6 (!RESET)
//   (RED/OC1A) PB1  13|            |28  PC5
//              PB2  14|            |27  PC4
//       (MOSI) PB3  15|            |26  PC3 (ADC3/LIGHT)
//       (MISO) PB4  16|            |25  PC2 (ADC2/A2)
//                     +------------+

// Color
typedef GpioOutputB1 RedLedPin;
typedef GpioOutputD6 GreenLedPin;
typedef GpioOutputD5 BlueLedPin;

// Analog
typedef GpioInputC0 A0;
typedef GpioInputC1 A1;
typedef GpioInputC2 A2;

// Interrupt
typedef GpioD2 Srx;
typedef GpioD7 ModeLed;
typedef GpioD3 ModePin;

// Leds
#include "leds.hpp"
RedLed redLed;
GreenLed greenLed;
BlueLed blueLed;

xpcc::ui::RgbLed colorLed(redLed, greenLed, blueLed);

enum class
ColorSpace
{
	RGB = 0,
	HSV = 1,
} colorSpace;

// Light sensor
typedef GpioInputC3 LightSensorPin;

uint16_t sensorData[4];
uint8_t adcMap[4] = {0, 1, 2, 3};
typedef xpcc::atmega::AnalogSensors< 4, 3, AdcInterrupt > sensors;

// COMMUNICATION ##############################################################

// Serial debug
#include <xpcc/io/iodevice_wrapper.hpp>
typedef Uart0 Uart;
xpcc::IODeviceWrapper<Uart> logger;

#include <xpcc/debug/logger.hpp>
xpcc::log::Logger xpcc::log::debug(logger);
xpcc::log::Logger xpcc::log::info(logger);
xpcc::log::Logger xpcc::log::warning(logger);
xpcc::log::Logger xpcc::log::error(logger);

#undef	XPCC_LOG_LEVEL
#define	XPCC_LOG_LEVEL xpcc::log::DEBUG


// TASKS ######################################################################
#include "tasks/task_input.hpp"
task::Input input;

#endif // LUMINET2_HARDWARE
