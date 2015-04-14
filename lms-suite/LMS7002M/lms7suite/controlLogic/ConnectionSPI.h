/**
@file   ConnectionSPI.h
@author Lime Microsystems (www.limemicro.com)
@brief  Class for data communications through SPI port
*/

#ifndef CONNECTION_SPI_PORT_H
#define CONNECTION_SPI_PORT_H

#ifndef __unix__
	#include "windows.h"
#endif

#include "IConnection.h"
#include <string>
#include <vector>

#include "spidev_interface.h"

class ConnectionSPI : public IConnection
{
public:
    static const int SPI_BUFFER_LENGTH = 1024; //max buffer size for data

	ConnectionSPI();
	~ConnectionSPI();

	bool Open();
	bool Open(unsigned i);
	void Close();
	bool IsOpen();
	int GetOpenedIndex();

	int Write(const unsigned char *buffer, int length, int timeout_ms = 0);
	int Read(unsigned char *buffer, int length, int timeout_ms = 0);

	std::vector<std::string> GetDeviceNames();
	int RefreshDeviceList();

    void *_spiHandle;
};
#endif
