/**
@file	ConnectionManager.h
@brief	Handles data writing and reading to chip
@author	Lime Microsystems
*/

#include "ConnectionManager.h"
#include <iostream>
#include <stdio.h>

#include "../CommonUtilities.h"
#include "ConnectionCOM.h"
#include "ConnectionUSB.h"
#include "MessageLog.h"
#include <sstream>
#include "RegistersMap.h"
#include <string.h>

using namespace std;

/** @brief Returns most repeated value, if all different returns first one
*/
unsigned char bestOfThree(const unsigned char A, const unsigned char B, const unsigned char C)
{
    if(A == B || A == C)
        return A;
    else if(B == C)
        return B;
    return A;
}

/** @brief Handles incoming messages
    @param msg message about event
*/
void ConnectionManager::HandleMessage(const LMS_Message &msg)
{

}

/** @brief Creates connection interfaces, determines system endianness for forming 16 bit values
*/
ConnectionManager::ConnectionManager(bool onlyUSB) : activeControlPort(NULL)
{
	mOpenedDevice = -1;
    regMap = NULL;
    m_currentDeviceType = LMS_DEV_UNKNOWN;
	m_testWriting = false;
    m_tripleCheckRead = false;
    m_system_big_endian = true;
    unsigned int endian_test = 0x11000044;
    unsigned char *p_byte;
    p_byte = (unsigned char*)&endian_test;
    if(p_byte[0] == 0x11 && p_byte[3] == 0x44) // little endian
        m_system_big_endian = false;
    else if(p_byte[0] == 0x44 && p_byte[3] == 0x11) // big endian
        m_system_big_endian = true;
    else
        MessageLog::getInstance()->write("Cannot determine system endiannes. Using big endian", LOG_ERROR);
    if(onlyUSB == false)
    {
        m_connections[COM_PORT] = new ConnectionCOM();
        MessageLog::getInstance()->write("COM connection supported\n", LOG_INFO);
    }
    m_connections[USB_PORT] = new ConnectionUSB();
    MessageLog::getInstance()->write("USB connection supported\n", LOG_INFO);
}

/** @brief Destroys connection interfaces
*/
ConnectionManager::~ConnectionManager()
{
	for (auto iter = m_connections.begin(); iter != m_connections.end(); ++iter)	
		delete iter->second;	
}

/** @brief Returns whether control device is opened
    @return true if opened
*/
bool ConnectionManager::IsOpen()
{
	return activeControlPort ? activeControlPort->IsOpen() : false;
}

/** @brief Connects to first found chip
    @return true is connection was made
*/
bool ConnectionManager::Open()
{
	return Open(0);
}

/** @brief Closes connection to chip
*/
void ConnectionManager::Close()
{
	if (activeControlPort)
	{
		activeControlPort->Close();
		Notify(LMS_Message(MSG_BOARD_DISCONNECTED, "", 0, 0));
	}
	m_currentDeviceType = LMS_DEV_UNKNOWN;
	mOpenedDevice = -1;        
}

/** @brief Finds all currently connected devices and forms device list
@return number of devices found
*/
int ConnectionManager::RefreshDeviceList()
{
	mDeviceList.clear();
	mDevices.clear();
	DeviceInfo dev;
	for (auto iter = m_connections.begin(); iter != m_connections.end(); ++iter)
	{
		vector<string> names;
		IConnection *port = iter->second;
		if (port->RefreshDeviceList() > 0)
		{
			names = port->GetDeviceNames();
			for (unsigned i = 0; i<names.size(); ++i)
			{
				dev.name = names[i];
				dev.port = iter->first;
				dev.portIndex = i;
				mDevices.push_back(dev);
			}
		}
	}
	for (unsigned i = 0; i<mDevices.size(); ++i)
		mDeviceList.push_back(mDevices[i].name);
	return mDevices.size();
}

/** @brief Sends given data to chip
    @param cmd LMS chip command
    @param data data buffer to send
    @param length size of data in bytes
    @return Command status

    Forms packet header and sends given data buffer to chip.
    When using CMD_LMS7002_WR the data buffer should be pointer to array of unsigned shorts.
 */
int ConnectionManager::SendData(eCMD_LMS cmd, const unsigned char* data, long length)
{
    if(!IsOpen())
        return STATUS_UNDEFINED;

    const int maxDataLen = cMAX_CONTROL_PACKET_SIZE-cPACKET_HEADER_SIZE;
    long sendLen;

    int status = STATUS_UNDEFINED;
    unsigned char buffer[cMAX_CONTROL_PACKET_SIZE];
    memset(buffer, 0, cMAX_CONTROL_PACKET_SIZE);

    const unsigned char* pdata_start = data;

    stringstream msg;
    bool hasErrors = false;

    while( length > 0)
    {
        sendLen = length < maxDataLen ? length : maxDataLen;

        if( MakeAndSendPacket(cmd, pdata_start, sendLen) )
        {
            long readLen = cMAX_CONTROL_PACKET_SIZE;
            status = ReadData(buffer, readLen);
            if(status == STATUS_ERROR_CMD || readLen == 0)
                break;

            //check if data has been written correctly
            if(cmd == CMD_LMS7002_WR && m_testWriting)
            {
                unsigned long bToRead = sendLen;
                unsigned short writeBuffer[32];
                unsigned short readbackBuffer[32];
                memset(writeBuffer, 0, 64);
                memset(readbackBuffer, 0, 64);
                int rdBufPos = 0;
                unsigned short addr = 0;
                for(unsigned i=0; i<sendLen/sizeof(unsigned short); i+=2)
                {
                    addr = ((unsigned short*)pdata_start)[i];
                    writeBuffer[rdBufPos++] = addr;
                }
                SendReadData(CMD_LMS7002_RD, (unsigned char*)writeBuffer, sendLen/2, (unsigned char*)readbackBuffer, bToRead);

                unsigned short *writtenShorts = (unsigned short*)pdata_start;
                unsigned short *readShorts = (unsigned short*)readbackBuffer;

                for(int i=0; i<sendLen/2; i+=2)
                {
                    if(writtenShorts[i+1] != readShorts[i+1])
                    {
                        if(hasErrors == false)
                            msg << "Written data don't match readback data:\n";
                        hasErrors = true;
                        msg << "at 0x" << int2hex(writtenShorts[i], 2) << " Wr: 0x" << int2hex(writtenShorts[i+1], 2) << "  Rd: 0x" << int2hex(readShorts[i+1], 2) << endl;
                    }
                }
            }
        }
        else
        {
            status = STATUS_ERROR_CMD;
            break;
        }
        pdata_start += sendLen;
        length -= sendLen;
    }
    if(hasErrors)
    {
        MessageLog::getInstance()->write(msg.str().c_str(), LOG_ERROR);
        Notify( LMS_Message(MSG_ERROR, msg.str().c_str(), 0, 0));
    }
    return status;
}

/** @brief Creates and sends packet buffer according to given command and data buffers
    @param cmd LMS chip command
    @param data data buffer to send
    @param length size of data in bytes
    @return true if success

    When using CMD_LMS7002_WR the data buffer should be pointer to array of unsigned shorts.
*/
int ConnectionManager::MakeAndSendPacket( eCMD_LMS cmd, const unsigned char *data, long length)
{
    const int maxDataLen = cMAX_CONTROL_PACKET_SIZE-cPACKET_HEADER_SIZE;
    if(length > maxDataLen)
    {
        MessageLog::getInstance()->write("MakeAndSendPacket : Packet larger than 64 bytes, truncating to 64 bytes." , LOG_WARNING);
        length = maxDataLen;
    }

    long sendLen;
    unsigned char buffer[cMAX_CONTROL_PACKET_SIZE];
    memset(buffer, 0, cMAX_CONTROL_PACKET_SIZE);

    sendLen = length < maxDataLen ? length : maxDataLen;
    memcpy(&buffer[8], data, sendLen);
    unsigned char temp;
    if(activeControlPort)
    {
        buffer[0] = cmd;
        //buffer[1] = 0; //Status
        // buffer[3-7] reserved
        switch( cmd )
        {
        case CMD_SI5351_WR:
        case CMD_SI5356_WR:
            buffer[2] = sendLen/2; //data block pairs(address,value)
            break;
        case CMD_SI5351_RD:
        case CMD_SI5356_RD:
            buffer[2] = sendLen; //data blocks(address)
            break;
        case CMD_ADF4002_WR:
            buffer[2] = sendLen/3; //data block(3xByte)
            break;
        case CMD_LMS7002_WR:
            buffer[2] = sendLen/4; //data block pairs(address,value)
            if(m_system_big_endian)
                for(int i=8; i<cMAX_CONTROL_PACKET_SIZE; i+=2)
                {
                    temp = buffer[i];
                    buffer[i] = buffer[i+1];
                    buffer[i+1] = temp;
                }
            break;
        case CMD_LMS7002_RD:
            buffer[2] = sendLen/2; //data blocks(address)
            if(m_system_big_endian)
                for(int i=8; i<cMAX_CONTROL_PACKET_SIZE; i+=2)
                {
                    temp = buffer[i];
                    buffer[i] = buffer[i+1];
                    buffer[i+1] = temp;
                }
            break;
        case CMD_PROG_MCU:
        case CMD_LMS7002_RST:
        case CMD_GET_INFO:
        case 0x2A:
        case 0x2B:
            buffer[2] = 1;
            break;
        case CMD_GPIO_WR:
        case CMD_GPIO_RD:
            buffer[2] = 2;
            break;
        default:
            MessageLog::getInstance()->write("Sending packet with unrecognized command\n", LOG_WARNING);
        }

        if( activeControlPort->Write(buffer, cMAX_CONTROL_PACKET_SIZE) > 0 )
            return true;
        else
            return false;
    }
    return false;
}

/** @brief Receives data from chip
    @param data array for incoming data
    @param length number of bytes to receive, this variable will be changed to actual number of bytes returned
    @return Command status
    Receives incoming data from chip and places it to given array.
*/
int ConnectionManager::ReadData(unsigned char* data, long& length)
{
    if(length > cMAX_CONTROL_PACKET_SIZE-cPACKET_HEADER_SIZE)
    {
        length = cMAX_CONTROL_PACKET_SIZE-cPACKET_HEADER_SIZE;
    }
    int status = STATUS_UNDEFINED;
    unsigned char buffer[cMAX_CONTROL_PACKET_SIZE];
    int bytesReceived;

    if(activeControlPort)
    {
        memset(buffer, 0, cMAX_CONTROL_PACKET_SIZE);
        bytesReceived = activeControlPort->Read(buffer, cMAX_CONTROL_PACKET_SIZE);
        if(bytesReceived > 0)
        {
            status = buffer[1];
            length = length > bytesReceived-cPACKET_HEADER_SIZE ? bytesReceived-cPACKET_HEADER_SIZE : length;
            if(bytesReceived-cPACKET_HEADER_SIZE <= 0)
                length = 0;
        }
        else
        {
            status = STATUS_UNDEFINED;
            length = 0;
        }
        memcpy(data, &buffer[8], length);
    }
    return status;
}

/** @brief Sends given data to chip and reads incoming data
    @param cmd LMS chip command
    @param outData data buffer to send
    @param oLength number of bytes in outData
    @param inData received data
    @param iLength number of bytes to receive
    @return Command status

    When using CMD_LMS7002_WR or CMD_LMS7002_RD commands the data buffers should be pointers to array of unsigned shorts.
*/
int ConnectionManager::SendReadData( eCMD_LMS cmd, const unsigned char *outData, unsigned long oLength, unsigned char *inData, unsigned long &iLength)
{
    if(!IsOpen())
        return STATUS_UNDEFINED;

    const int readCount = m_tripleCheckRead ? 3 : 1;
    const unsigned int maxDataLen = cMAX_CONTROL_PACKET_SIZE-cPACKET_HEADER_SIZE;
    unsigned char outBuffer[maxDataLen];
    unsigned char inBuffer[3][maxDataLen];
    for(int i=0; i<readCount; ++i)
        memset(inBuffer[i], 0, maxDataLen);

    int status = STATUS_UNDEFINED;

    unsigned int outBufPos = 0;
    unsigned int inDataPos = 0;

    unsigned char bestByte = 0;

    for(unsigned int i=0; i<oLength; ++i)
    {
        outBuffer[outBufPos++] = outData[i];
        if(outBufPos >= maxDataLen || (cmd == CMD_LMS7002_RD && outBufPos>=28) || outBufPos == oLength || i==oLength-1)
        {
            for(int i=0; i<readCount; ++i)
            {
                if(MakeAndSendPacket(cmd, outBuffer, outBufPos))
                {
                    long readLen = 64;
                    status = ReadData(inBuffer[i], readLen);
                    if(status != STATUS_COMPLETED_CMD)
                    {
                        stringstream ss;
                        ss << "Board response: ";
                        switch(status)
                        {
                        case STATUS_UNKNOWN_CMD:
                            ss << "unknown command";
                            break;
                        case STATUS_BUSY_CMD:
                            ss << "command execution not finished";
                            break;
                        case STATUS_MANY_BLOCKS_CMD:
                            ss << "too many blocks in packet";
                            break;
                        case STATUS_ERROR_CMD:
                            ss << "error occurred during command execution";
                            break;
                        case STATUS_WRONG_ORDER_CMD:
                            ss << "command packets received in wrong order";
                            break;
                        default:
                            ss << "no response";
                            break;
                        }
                        Notify(LMS_Message(MSG_WARNING, ss.str(), 0, 0));
                        return status;
                    }

                    if(cmd == CMD_LMS7002_RD)
                    {
                        unsigned char temp;
                        if(m_system_big_endian)
                            for(unsigned int j=0; j<outBufPos*2 && j<cMAX_CONTROL_PACKET_SIZE; j+=2)
                            {
                                temp = inBuffer[i][j];
                                inBuffer[i][j] = inBuffer[i][j+1];
                                inBuffer[i][j+1] = temp;
                            }
                    }
                }
            }

            for(unsigned int b=0; b<outBufPos*2 && b<cMAX_CONTROL_PACKET_SIZE; ++b)
            {
                if(m_tripleCheckRead)
                    bestByte = bestOfThree(inBuffer[0][b],inBuffer[1][b], inBuffer[2][b]);
                else
                    bestByte = inBuffer[0][b];
                inData[inDataPos++] = bestByte;
            }
            if(inDataPos > iLength)
            {
                return status;
            }
            outBufPos = 0;
        }
    }
    return status;
}

/** @brief Creates connection to selected receiver
    @param i receiver index from list
    @return true if success
*/
int ConnectionManager::Open(unsigned i)
{
    if(i >= mDevices.size())
        return 0;

    if(activeControlPort)
        activeControlPort->Close();
    switch(mDevices[i].port)
    {
    case COM_PORT:
        //delete activeControlPort;
        activeControlPort = m_connections[COM_PORT];
        break;
    case USB_PORT:
        //delete activeControlPort;
		activeControlPort = m_connections[USB_PORT];
        break;
//    case SPI_PORT:
//        activeControlPort = new ConnectionSPI();
//        break;
    default:
        return 0;
    }
    mOpenedDevice = -1;
    if( i < mDevices.size() )
    {
        if( activeControlPort->Open(mDevices[i].portIndex) )
        {			
            mOpenedDevice = i;			
			unsigned char outbuffer[56];
			unsigned char inbuffer[56];
			memset(outbuffer, 0, 56);
			memset(inbuffer, 0, 56);
			unsigned long readLen = 4;
			SendReadData(CMD_GET_INFO, outbuffer, 4, inbuffer, readLen);
			if (inbuffer[1] < LMS_DEV_COUNT)
				m_currentDeviceType = (eLMS_DEV)inbuffer[1];
			else
				m_currentDeviceType = LMS_DEV_UNKNOWN;
			Notify(LMS_Message(MSG_BOARD_CONNECTED, mDevices[i].name, 0, 0));
            return 1;
        }
    }
    return 0;
}

/** @brief Writes given data to one chip register
    @param addr_reg register address 16 bits
    @param data_reg register value 16 bits
    @return command status
*/
int ConnectionManager:: mSPI_write(unsigned short addr_reg, unsigned short data_reg)
{
    unsigned short Byte_array[2];
    Byte_array[0] = addr_reg;
    Byte_array[1] = data_reg;

    if (IsOpen()==true)
        return SendData(CMD_LMS7002_WR, (unsigned char*)Byte_array, 4);
    return STATUS_UNDEFINED;
}

/** @brief Reads one register value from chip
    @param addr_reg register address 16 bits
    @return register value 16 bits
*/
unsigned short ConnectionManager:: mSPI_read(unsigned short addr_reg)
{
	int ret=0;
	unsigned short tempi=0x0000;

	unsigned short Out_array[1];
	unsigned short In_array[100];
	unsigned long retint = 4;
	Out_array[0] = addr_reg;

    for (int i=0;i<100;i++)
        In_array[i]=0x00;

    if (IsOpen()==true)
    {
    ret = SendReadData(CMD_LMS7002_RD, (unsigned char*)Out_array, 2,(unsigned char*)In_array, retint);
    if ( (ret == STATUS_COMPLETED_CMD ) )
        tempi=In_array[1];
    }
    return tempi;
}

/** @brief Writes given data to chip without any modifications
    @param buf data buffer to write
    @param len length of data buffer
    @return true if success
*/
bool ConnectionManager::Port_write_direct(const unsigned char *buf, const long len)
{
    if(activeControlPort)
    {
        unsigned long bytesSent = activeControlPort->Write(buf, len);
        if(bytesSent > 0)
            return true;
    }
    else
        MessageLog::getInstance()->write("Connection port not opened\n", LOG_WARNING);
    return false;
}

/** @brief Tries to read any incoming data and puts it to given buffer
    @param buf buffer for received data, must be big enough to store len bytes
    @param len number of bytes to read, after procedure it will be changed to actual number of bytes received
    @param true if success
*/
bool ConnectionManager::Port_read_direct(unsigned char *buf, long &len)
{
    unsigned char *inBuffers = new unsigned char[len];
    int bytesReceived;

    if(activeControlPort)
    {
        bytesReceived = activeControlPort->Read(inBuffers, len);
        memcpy(buf, inBuffers, bytesReceived);
		delete []inBuffers;
        return true;
    }
    else
        MessageLog::getInstance()->write("Connection port not opened\n", LOG_WARNING);
	delete[]inBuffers;
    return false;
}

/** @brief Enables or Disables triple checking of received data
*/
void ConnectionManager::EnableTrippleReadChecking(bool checkMultipleReads)
{
    m_tripleCheckRead = checkMultipleReads;
}

void ConnectionManager::EnableTestWrittenData(bool enabled)
{
    m_testWriting = enabled;
}

/** @brief Returns connected board type
*/
eLMS_DEV ConnectionManager::GetConnectedDeviceType()
{
    return m_currentDeviceType;
}

void ConnectionManager::AssignRegistersMap(const RegistersMap* p_regMap)
{
    regMap = p_regMap;
}

/**
    @brief Start asynchronous data reading.
    @param buffer where to put received data
    @param length number of bytes to read.
    @return context handle
*/
int ConnectionManager::BeginDataReading(char *buffer, long length)
{
    return activeControlPort->BeginDataReading(buffer, length);
}
/**
    @brief Blocks until data is received or set number of milliseconds have passed.
    @param contextHandle handle returned by BeginDataReading()
    @param timeout_ms number of milliseconds to wait
    @return 1-data received, 0-data not received
*/
int ConnectionManager::WaitForReading(int contextHandle, unsigned int timeout_ms)
{
    return activeControlPort->WaitForReading(contextHandle, timeout_ms);
}
/**
    @brief Finished asynchronous data reading.
    @param buffer where to put received data
    @param length number of bytes to read, will be changed to actual number of bytes received
    @param contextHandle context handle returned by BeginDataReading()
    @return received data length
*/
int ConnectionManager::FinishDataReading(char *buffer, long &length, int contextHandle)
{
    return activeControlPort->FinishDataReading(buffer, length, contextHandle);
}

/**
	@brief Aborts reading operations
*/
void ConnectionManager::AbortReading()
{
	activeControlPort->AbortReading();
}

/**
    @brief Start asynchronous data sending.
    @param buffer data buffer to be sent
    @param length number of bytes to send.
    @return context handle
*/
int ConnectionManager::BeginDataSending(const char *buffer, long length)
{
    return activeControlPort->BeginDataSending(buffer, length);
}
/**
    @brief Blocks until data is sent or set number of miliseconds have passed.
    @param contextHandle handle returned by BeginDataReading()
    @param timeout_ms number of miliseconds to wait
    @return 1-data sent, 0-data not sent
*/
int ConnectionManager::WaitForSending(int contextHandle, unsigned int timeout_ms)
{
    return activeControlPort->WaitForSending(contextHandle, timeout_ms);
}
/**
    @brief Finished asynchronous data sending.
    @param buffer where to put received data
    @param length number of bytes to send, will be changed to actual number of bytes sent
    @param contextHandle context handle returned by BeginDataReading()
    @return sent data length
*/
int ConnectionManager::FinishDataSending(const char *buffer, long &length, int contextHandle)
{
    return activeControlPort->FinishDataSending(buffer, length, contextHandle);
}

/**
	@brief Aborts sending operations
*/
void ConnectionManager::AbortSending()
{
	activeControlPort->AbortSending();
}

/** @brief Returns currently opened connection index
*/
int ConnectionManager::GetOpenedIndex()
{
	return mOpenedDevice;
}

string ConnectionManager::GetConnectedDeviceName()
{
	if (mOpenedDevice >= 0 && mOpenedDevice < mDevices.size())
		return mDevices[mOpenedDevice].name;
	else
		return "";
}
