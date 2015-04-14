/**
@file   ConnectionCOM.cpp
@author Lime Microsystems (www.limemicro.com)
@brief  Implementation of communications through COM port
*/

#include "ConnectionCOM.h"
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

const int COM_RETRY_INTERVAL = 20; //ms
const int COM_TOTAL_TIMEOUT = 300; //ms

/** @brief Initializes com port connection
*/
ConnectionCOM::ConnectionCOM()
{
    currentDeviceIndex = -1;
	connected = false;
	comPortList.clear();
	m_deviceNames.clear();
	m_connectionType = COM_PORT;
#ifndef __unix__
	hComm = INVALID_HANDLE_VALUE;
#else
    hComm = -1;
#endif
	comBaudrate = 9600;
}

/** @brief When object is destroyed it closes it's opened COM port
*/
ConnectionCOM::~ConnectionCOM()
{
	Close();
}

/** @brief Opens connection to first found chip
    @return true if device was opened
*/
bool ConnectionCOM::Open()
{
	bool opened = false;
	comPortList.clear();
	if(comPortList.size() == 0)
		FindAllComPorts();

	m_deviceNames.clear();
	if(m_deviceNames.size() == 0)
		RefreshDeviceList();

	for(unsigned int i=0; i<m_deviceNames.size(); i++)
	{
		if( Open(i) )
		{
			currentDeviceIndex = i;
			break;
		}
	}
	return opened;
}

/** @brief Opens connection to selected chip
    @param index chip index in device list
    @return true if opened
*/
bool ConnectionCOM::Open(unsigned index)
{
    unsigned int toOpen = index;
	Close();
	if(toOpen < m_deviceNames.size() && m_deviceNames.size() > 0 )
	{
		comPortName = m_deviceNames[toOpen];
		connected = Open(comPortName.c_str(), comBaudrate);
		if( connected )
		{
			currentDeviceIndex = toOpen;
			return connected;
		}
	}
	return false;
}

/** @brief Closes connection to chip
*/
void ConnectionCOM::Close()
{
    connected = false;
    currentDeviceIndex = -1;
#ifndef __unix__
	if (hComm != INVALID_HANDLE_VALUE)
	{
		SetCommTimeouts(hComm, &m_ctmoOld);
		CloseHandle(hComm);
	}
	hComm = INVALID_HANDLE_VALUE;
#else
    if( hComm >= 0)
    {
        close(hComm);
    }
    hComm = -1;
#endif
}

/** @brief Returns whether chip is connected
    @return chip is connected
*/
bool ConnectionCOM::IsOpen()
{
#ifndef __unix__
	if (hComm != INVALID_HANDLE_VALUE && TestConnectivity() )
		return true;
#else
    if( hComm != -1 && TestConnectivity() )
        return true;
#endif
    return false;
}

int ConnectionCOM::GetOpenedIndex()
{
    return currentDeviceIndex;
}

/** @brief Sends data through COM port
    @param buffer data buffer to send
    @param length size of data buffer
    @return Number of bytes sent
*/
int ConnectionCOM::Write(const unsigned char *buffer, int length, int timeout_ms)
{
    if(timeout_ms == 0)
    {
        timeout_ms = COM_TOTAL_TIMEOUT;
    }
    int retryCount = 0;
    const int maxRetries = (timeout_ms/COM_RETRY_INTERVAL) > 1 ? (timeout_ms/COM_RETRY_INTERVAL) : 1;
    bool status = false;
#ifndef __unix__
	unsigned long bytesWriten = 0;
	m_osWOverlap.InternalHigh = 0;

	for(int i = 0; i<maxRetries && status == false; ++i)
    {
        if (!WriteFile(hComm, buffer, length , &bytesWriten, NULL))
        {
            status = false;
        }
        else
            status = true;
        ++retryCount;
    }
#else
    long bytesWriten = 0;
    for(int i = 0; i<maxRetries && bytesWriten == 0; ++i)
    {
        bytesWriten = write(hComm, buffer, length);
        if(bytesWriten <= 0)
        {
            status = false;
        }
        else
            status = true;
        ++retryCount;
    }
#endif
    if(bytesWriten == length)
        status = true;

    stringstream ss;
	char ctemp[8];
    ss << "write(" << bytesWriten << "): ";
	for (unsigned i = 0; i < length; ++i)
	{
		sprintf(ctemp, "%02X ", buffer[i]);
		ss << ctemp;
	}
    ss << " - retries: " << retryCount-1 << endl;
    MessageLog::getInstance()->write(ss.str(), LOG_DATA);

	return bytesWriten;
}

/** @brief Reads data from COM port
    @param buffer pointer to data buffer for receiving
    @param length number of bytes to read
    @return Number of bytes received
*/
int ConnectionCOM::Read(unsigned char *buffer, int length, int timeout_ms)
{
    if(timeout_ms == 0)
    {
        timeout_ms = COM_TOTAL_TIMEOUT;
    }
    int retryCount = 0;
    const int maxRetries = (timeout_ms/COM_RETRY_INTERVAL) > 1 ? (timeout_ms/COM_RETRY_INTERVAL) : 1;
    bool status = false;

    memset(buffer, 0, length);
	long bytesReaded = 0;
	unsigned long totalBytesReaded = 0;
	char cRawData[COM_BUFFER_LENGTH];
	unsigned long bytesToRead = length;
	stringstream ss;

	memset(cRawData, '\0', sizeof(cRawData[0])*COM_BUFFER_LENGTH);

	for(int i=0; i<maxRetries && status == false; ++i)
    {
        memset(cRawData, '\0', sizeof(cRawData[0])*COM_BUFFER_LENGTH);
#ifndef __unix__

        DWORD bytesReceived = 0;
        if ( !ReadFile(hComm, cRawData, bytesToRead, &bytesReceived, NULL) )
        {
            status = false;
        }

        bytesReaded = bytesReceived;
#else
        bytesReaded = read(hComm, cRawData, bytesToRead);
        if(bytesReaded <= 0)
        {
            status = false;
        }
#endif
        retryCount++;

        for(int j=0; j<bytesReaded; ++j)
        {
            buffer[totalBytesReaded+j] = cRawData[j];
        }

        totalBytesReaded += bytesReaded;
        if(totalBytesReaded == bytesToRead)
            status = true;
    }

    ss << " read(" << totalBytesReaded << "): ";    
	char ctemp[8];    
	for (unsigned i = 0; i < totalBytesReaded; ++i)
	{
		sprintf(ctemp, "%02X ", buffer[i]);
		ss << ctemp;
	}
    ss << " - retries: " << retryCount-1 << endl;
    MessageLog::getInstance()->write(ss.str(), LOG_DATA);

	if(retryCount == maxRetries)
        MessageLog::getInstance()->write("COM PORT: read data timeout\n", LOG_WARNING);

    if(totalBytesReaded > length)
		MessageLog::getInstance()->write("COM PORT: read data corrupted, received length > requested length\n", LOG_ERROR);
	return totalBytesReaded;
}

/** @brief Searches for available COM ports and adds them to list
*/
void ConnectionCOM::FindAllComPorts()
{
    Close();
	comPortList.clear();
#ifndef __unix__
	HKEY hSERIALCOMM;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"),	0, KEY_QUERY_VALUE, &hSERIALCOMM) == ERROR_SUCCESS)
	{
		// Get the max value name and max value lengths
		DWORD dwMaxValueNameLen;
		DWORD dwMaxValueLen;
		DWORD dwQueryInfo = RegQueryInfoKey(hSERIALCOMM, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &dwMaxValueNameLen, &dwMaxValueLen, NULL, NULL);
		if (dwQueryInfo == ERROR_SUCCESS)
		{
			DWORD dwMaxValueNameSizeInChars = dwMaxValueNameLen + 1;
			// Include space for the NULL terminator
			DWORD dwMaxValueNameSizeInBytes = dwMaxValueNameSizeInChars*sizeof(TCHAR);
			DWORD dwMaxValueDataSizeInChars = dwMaxValueLen / sizeof(TCHAR) + 1;
			// Include space for the NULL terminator
			DWORD dwMaxValueDataSizeInBytes = dwMaxValueDataSizeInChars*sizeof(TCHAR);

			// Allocate some space for the value name and value data
			TCHAR* szValueName = new TCHAR[dwMaxValueNameSizeInChars];
			TCHAR* byValue = new TCHAR[dwMaxValueDataSizeInBytes];
			if (szValueName && byValue)
			{
				// Enumerate all the values underneath HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM
				DWORD dwIndex = 0;
				DWORD dwType;
				DWORD dwValueNameSize = dwMaxValueNameSizeInChars;
				DWORD dwDataSize = dwMaxValueDataSizeInBytes;
				memset(szValueName, 0, dwMaxValueNameSizeInBytes);
				memset(byValue, 0, dwMaxValueDataSizeInBytes);
				LONG nEnum = RegEnumValue(hSERIALCOMM, dwIndex, szValueName, &dwValueNameSize, NULL, &dwType, (LPBYTE)byValue, &dwDataSize);
				while (nEnum == ERROR_SUCCESS)
				{
					// If the value is of the correct type, then add it to the array
					if (dwType == REG_SZ)
					{
					    char portname[512];
						TCHAR* szPort = byValue;
						int nUserNameLenUnicode = lstrlen( szPort ); // Convert all UNICODE characters
						int nUserNameLen = WideCharToMultiByte( CP_ACP, // ANSI Code Page
                        0, // No special handling of unmapped chars
                        (LPCWSTR)szPort, // wide-character string to be converted
                        nUserNameLenUnicode,
                        NULL, 0, // No output buffer since we are calculating length
                        NULL, NULL ); // Unrepresented char replacement - Use Default
                        TCHAR* pszUserName = new TCHAR[ nUserNameLen ]; // nUserNameLen includes the NULL character
                        WideCharToMultiByte( CP_ACP, // ANSI Code Page
                        0, // No special handling of unmapped chars
						(LPCWSTR)szPort, // wide-character string to be converted
                        nUserNameLenUnicode,
                        portname,
                        nUserNameLen,
                        NULL, NULL ); // Unrepresented char replacement - Use Default
						portname[nUserNameLen] = 0;
						comPortList.push_back(portname);
					}
					// Prepare for the next time around
					dwValueNameSize = dwMaxValueNameSizeInChars;
					dwDataSize = dwMaxValueDataSizeInBytes;
					memset(szValueName, 0, dwMaxValueNameSizeInBytes);
					memset(byValue, 0, dwMaxValueDataSizeInBytes);
					++dwIndex;
					nEnum = RegEnumValue(hSERIALCOMM, dwIndex, szValueName,	&dwValueNameSize, NULL, &dwType, (LPBYTE)byValue, &dwDataSize);
				}
			}
			delete szValueName;
			delete byValue;
		}
		// Close the registry key now that we are finished with it
		RegCloseKey(hSERIALCOMM);

		if (dwQueryInfo != ERROR_SUCCESS)
			SetLastError(dwQueryInfo);
	}
#else
    char tempBuffer[256];
    string result = "";
#warning Currently searching only for ACM connections
    system( "ls /dev | grep ttyACM > /tmp/foundSerialPorts.txt");

    fstream fin;
    fin.open("/tmp/foundSerialPorts.txt", ios::in);
    while(!fin.eof())
    {
        fin.getline(tempBuffer, 256);
        result = "/dev/";
        result.append(tempBuffer);
        if( strlen(tempBuffer) > 3 ) //longer than tty
            comPortList.push_back(result);
    }
    fin.close();
#endif
}

/** @brief Opens COM port
    @param comName COM port name
    @param baudrate COM port baudrate
    @return 0 on success
*/
int ConnectionCOM::Open(const char *comName, int baudrate)
{
	Close();
	if (strlen(comName) == 0)
		return 0;

	int errorCode = 0;

#ifndef __unix__
	// Initialize Overlap structures
	m_osROverlap.Internal = 0;
	m_osROverlap.InternalHigh = 0;
	m_osROverlap.Offset = 0;
	m_osROverlap.OffsetHigh = 0;
	m_osROverlap.hEvent = CreateEvent(NULL, false, false, NULL);

	m_osWOverlap.Internal = 0;
	m_osWOverlap.InternalHigh = 0;
	m_osWOverlap.Offset = 0;
	m_osWOverlap.OffsetHigh = 0;
	m_osWOverlap.hEvent = CreateEvent(NULL, false, false, NULL);

	// Initialize DSB structure
	memset(&m_dcbCommPort, 0, sizeof(m_dcbCommPort));

	m_dcbCommPort.BaudRate = comBaudrate;
	m_dcbCommPort.fBinary = 1;
	m_dcbCommPort.fParity = 0;
	m_dcbCommPort.fOutxCtsFlow = 0;
	m_dcbCommPort.fOutxDsrFlow = 0;
	m_dcbCommPort.fDtrControl = 0;
	m_dcbCommPort.fDsrSensitivity = 0;
	m_dcbCommPort.fTXContinueOnXoff = 0;
	m_dcbCommPort.fOutX = 0;
	m_dcbCommPort.fInX = 0;
	m_dcbCommPort.fErrorChar = 0;
	m_dcbCommPort.fNull = 0;
	m_dcbCommPort.fRtsControl = 0;
	m_dcbCommPort.fAbortOnError = 0;
	m_dcbCommPort.fDummy2 = 0;
	// m_dcbCommPort.wReserved = 0;
	m_dcbCommPort.XonLim = 512;
	m_dcbCommPort.XoffLim = 512;
	m_dcbCommPort.ByteSize = 8;
	m_dcbCommPort.Parity = 0;
	m_dcbCommPort.StopBits = 0;
	//m_dcbCommPort.StopBits = 1;
	m_dcbCommPort.XonChar = 17;
	m_dcbCommPort.XoffChar = 19;
	m_dcbCommPort.ErrorChar = 0;
	m_dcbCommPort.EofChar = 26;
	m_dcbCommPort.EvtChar = 0;
	m_dcbCommPort.wReserved1 = 0;
	m_dcbCommPort.DCBlength = sizeof(DCB);

	// Initialize Timeout's
	m_ctmoNew.ReadIntervalTimeout = 50;
	m_ctmoNew.ReadTotalTimeoutMultiplier = 0;
	m_ctmoNew.ReadTotalTimeoutConstant = 100; // 1;
	m_ctmoNew.WriteTotalTimeoutMultiplier = 0;
	m_ctmoNew.WriteTotalTimeoutConstant = 100;

	// Open COM port
	string stmp;
	stmp = "\\\\.\\";
	stmp.append(comName);
	hComm = CreateFileA(stmp.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hComm != INVALID_HANDLE_VALUE)
	{
		// Set Events
		if (!SetCommMask(hComm, 0))
			errorCode = -1;

		// Set Timeouts
		GetCommTimeouts(hComm, &m_ctmoOld);
		if (!SetCommTimeouts(hComm, &m_ctmoNew))
			errorCode = -2;

		// Set DCB
		if (!SetCommState(hComm, &m_dcbCommPort))
			errorCode = -4;
	}
	else
	{
		errorCode = -8;
	};

	// Check the results
	if (errorCode != 0)
	{
		//unsigned long err = GetLastError();
		CloseHandle(hComm);
		hComm = INVALID_HANDLE_VALUE;
		return errorCode;
	}
	else
	{
		PurgeComm(hComm, PURGE_TXCLEAR | PURGE_RXCLEAR);
		return 1;
	}
#else
    hComm = open(comName, O_RDWR | O_NOCTTY | O_SYNC);
    if(hComm < 0)
    {
        return -8;
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if( tcgetattr(hComm, &tty) != 0)
    {
        return -8;
    }
    int speed = B9600;
    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN] = 0; // read non blocking
    tty.c_cc[VTIME] = 5; // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_cflag |= (CLOCAL | CREAD);

    if(tcsetattr(hComm, TCSANOW, &tty) != 0)
    {
        return -8;
    }
#endif
    return 1;
}

/** @brief Checks if chip is connected to currently open port
    @return chip is connected
*/
bool ConnectionCOM::TestConnectivity()
{
//currently set to always return true to show all com ports
    return true;
#ifndef __unix__
	if (hComm != INVALID_HANDLE_VALUE)
#else
    if( hComm >= 0)
#endif
	{
//	    unsigned char out[64];
//	    unsigned char in[64];
//	    memset(in, 0, 64);
//	    out[0] = CMD_GET_INFO;
//        SendData(out, 64);
//        ReadData(in, 64);
//        if(in[0] == CMD_GET_INFO && in[1] == 0x01)
//            return true;
//        else
//            return false;
	}
	return false;
}

/** @brief Finds all chips connected to com ports
    @return number of devices found
*/
int ConnectionCOM::RefreshDeviceList()
{
    int wasOpen = -1;
    string wasOpenName = "";
    if(IsOpen())
    {
        wasOpen = GetOpenedIndex();
        wasOpenName = comPortName;
    }
    Close();
    comPortList.clear();
	if(comPortList.size() == 0)
		FindAllComPorts();

	m_deviceNames.clear();
	string comName;
	for(unsigned int i=0; i<comPortList.size(); i++)
	{
	    comName = comPortList[i];
#ifndef __unix__
		if( Open(comName.c_str(), comBaudrate) > 0)
		{
			if( TestConnectivity() ) //if responds add it to device list
				m_deviceNames.push_back(comName);
		}
		Close();
#else
        m_deviceNames.push_back(comName);
#endif
	}
	if(wasOpen != -1)
    {
        for(unsigned i=0; i<m_deviceNames.size(); ++i)
            if(m_deviceNames[i] == wasOpenName)
            {
                Open(i);
                break;
            }
    }
	return m_deviceNames.size();
}

/** @brief Returns found devices names
    @return vector of device names
*/
vector<string> ConnectionCOM::GetDeviceNames()
{
    return m_deviceNames;
}

/** @brief Purges communication buffers
*/
void ConnectionCOM::ClearComm()
{
#ifndef __unix__
    PurgeComm(hComm, PURGE_TXCLEAR|PURGE_RXCLEAR);
#endif
}
