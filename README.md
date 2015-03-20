# Control driver for LMS7002M dual transceiver

## The LMS7002M transceiver

The LMS7002M is Lime’s second-generation field programmable RF (FPRF) transceiver IC
with extended functionality to cover a greater range of frequencies and applications...
http://www.limemicro.com/products/field-programmable-rf-ics-lms7002m/

## Driver functionality

This project contains a C driver for control of the LMS7002M transceiver.
The driver provides user APIs for tuning frequencies, setting gains, setting filters,
setting sample rates, setting stream modes, configuring switches, and calibration.
Although this driver can select the streaming mode of the LMS7002M,
it does not directly interact with receive or transmit baseband data.

## Hardware independent

End applications may access the SPI bus for the LMS7002M in a variety of ways.
To ensure that the driver can talk to the LMS7002M independent of the hardware,
the caller provides the driver instance with SPI access callback functions.
These functions implement the hardware-dependent SPI register access routines.

## Licensing information

Use, modification and distribution is subject to the Apache License
Version 2.0. (See accompanying file LICENSE-2.0.txt or copy at
https://www.apache.org/licenses/LICENSE-2.0.txt)

## Project layout

* regs/ - LMS7002M register map and register header generator
* include/ - LMS7002M headers for C driver interface
* src/ - LMS7002M C sources for implementation details
* interfaces/ - example SPI interfaces for use in LMS7002M
* evb7/ - example SoapySDR wrapper using the LMS7002M C driver
* test/ - simple register access test using the LMS7002M C driver
