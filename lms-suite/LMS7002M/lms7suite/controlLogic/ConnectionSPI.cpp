/**
@file   ConnectionSPI.cpp
@author Lime Microsystems (www.limemicro.com)
@brief  Implementation of communications through SPI port
*/

#include "ConnectionSPI.h"
#include <fstream>
#include <sstream>
#include "string.h"
#ifdef __unix__
#include <errno.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#else
#include <windows.h>
#endif // LINUX
#include "MessageLog.h"
using namespace std;

/** @brief Initializes com port connection
*/
ConnectionSPI::ConnectionSPI()
{
    _spiHandle = NULL;
}

/** @brief When object is destroyed it closes it's opened SPI port
*/
ConnectionSPI::~ConnectionSPI()
{
	Close();
}

/** @brief Opens connection to first found chip
    @return true if device was opened
*/
bool ConnectionSPI::Open()
{
    _spiHandle = spidev_interface_open("/dev/spidev32766.0");
    return _spiHandle != NULL;
}

/** @brief Opens connection to selected chip
    @param index chip index in device list
    @return true if opened
*/
bool ConnectionSPI::Open(unsigned index)
{
    if (index > 0) return false;
    return this->Open();
}

/** @brief Closes connection to chip
*/
void ConnectionSPI::Close()
{
    if (_spiHandle != NULL) spidev_interface_close(_spiHandle);
}

/** @brief Returns whether chip is connected
    @return chip is connected
*/
bool ConnectionSPI::IsOpen()
{
    return _spiHandle != NULL;
}

int ConnectionSPI::GetOpenedIndex()
{
    return 0;
}

/** @brief Sends data through SPI port
    @param buffer data buffer to send
    @param length size of data buffer
    @return Number of bytes sent
*/
int ConnectionSPI::Write(const unsigned char *buffer, int length, int timeout_ms)
{
    return length;
}

/** @brief Reads data from SPI port
    @param buffer pointer to data buffer for receiving
    @param length number of bytes to read
    @return Number of bytes received
*/
int ConnectionSPI::Read(unsigned char *buffer, int length, int timeout_ms)
{
    return length;
}

/** @brief Finds all chips connected to com ports
    @return number of devices found
*/
int ConnectionSPI::RefreshDeviceList()
{
    return 1;
}

/** @brief Returns found devices names
    @return vector of device names
*/
vector<string> ConnectionSPI::GetDeviceNames()
{
    return vector<string>(1, "spidev");
}
