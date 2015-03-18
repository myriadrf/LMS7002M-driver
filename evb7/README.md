# Example SoapySDR host wrapper for LMS7002M

We developed this example tandem with the LMS7002M driver for testing purposes.
This wrapper is also a good example of the LMS7002M driver in practical use.

## Hardware

This demo module is for use with a Microzed and carrier board.
The accompanying boot files for zynq are not yet included.

## Dependencies

First follow the build guide for SoapySDR:
https://github.com/pothosware/SoapySDR/wiki/BuildGuide

The evb7 module also requires two headers for the pothos zynq project
for communicating with the pothos zynq DMA kernel module.
If you are not actually using the Zynq DMA source and sink blocks,
it may be easiest to copy these two files to /usr/local/include
so that they can be found by the evb7 build system:

```
wget https://raw.githubusercontent.com/pothosware/pothos-zynq/master/driver/pothos_zynq_dma_driver.h
wget https://raw.githubusercontent.com/pothosware/pothos-zynq/master/kernel/pothos_zynq_dma_common.h
sudo mv pothos_zynq_dma_driver.h /usr/local/include/
sudo mv pothos_zynq_dma_common.h /usr/local/include/
```

## Build instructions

Configure, build, and install the evb7 module using CMake.
The build system will locate the install of SoapySDR.

```
cd evb7
mkdir build
cd build
cmake ../
make
sudo make install
```

## Load the kernel module

The Pothos Zynq DMA kernel module is used by the evb7 module to access streaming data in userspace.
This kernel module will need to be loaded into the kernel before the evb7 soapy module is usable.

First, build the kernel module using the Xilinx arm sdk and a cross compiled linux kernel from Xilinx:
https://github.com/pothosware/pothos-zynq/blob/master/kernel/README.md

Next, login to the Zynq board and load the DMA kernel module with insmod:

```
sudo insmod pothos_zynq_dma.ko
ls /dev/pothos_zynq_dma*
```

## A simple test

The following command should try to make an instance of the evb7 device:

```
SoapySDRUtil --make
```
