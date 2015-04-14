/**
@file	ConnectionManager.h
@author Lime Microsystems
@brief Header for ConnectionManager.cpp
*/

#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include "LMS7002M_Commands.h"
#include "IConnection.h"
#include <string>
#include <map>
#include <vector>
#include "SignalHandler.h"

class RegistersMap;
/** @brief Handles communication with device. Data writing and reading is NOT
    thread safe
*/
class ConnectionManager : public SignalHandler
{
public:
	struct DeviceInfo
	{
		std::string name;
		eConnectionType port;
		int portIndex;
	};
    static const int cMAX_CONTROL_PACKET_SIZE = 64;
    static const int cPACKET_HEADER_SIZE = 8;

    virtual void HandleMessage(const LMS_Message &msg);

	ConnectionManager(bool onlyUSB);
	~ConnectionManager();
	bool IsOpen();
	bool Open();
	int Open(unsigned i);
	void Close();
	int RefreshDeviceList();
	int GetOpenedIndex();
	std::vector<std::string> GetDeviceList(){ return mDeviceList; };

    int SendData( eCMD_LMS cmd, const unsigned char *data, long length);
	int SendReadData( eCMD_LMS cmd, const unsigned char *outData, unsigned long oLength, unsigned char *inData, unsigned long &iLength);

	unsigned short mSPI_read(unsigned short addr_reg);
	int mSPI_write(unsigned short addr_reg, unsigned short data_reg);

	bool Port_write_direct(const unsigned char *buf, const long len);
	bool Port_read_direct(unsigned char *buf, long &len);

	void EnableTrippleReadChecking(bool checkMultipleReads);
	bool GetTriplleReadCheckingState() { return m_tripleCheckRead; };
	
	void EnableTestWrittenData(bool enabled);

	eLMS_DEV GetConnectedDeviceType();
	string GetConnectedDeviceName();

	void AssignRegistersMap(const RegistersMap* regMap);

	int BeginDataReading(char *buffer, long length);
	int WaitForReading(int contextHandle, unsigned int timeout_ms);
	int FinishDataReading(char *buffer, long &length, int contextHandle);
	void AbortReading();

    int BeginDataSending(const char *buffer, long length);
	int WaitForSending(int contextHandle, unsigned int timeout_ms);
	int FinishDataSending(const char *buffer, long &length, int contextHandle);
	void AbortSending();

protected:
    const RegistersMap* regMap;
    eLMS_DEV m_currentDeviceType;

    int MakeAndSendPacket( eCMD_LMS cmd, const unsigned char *data, long length);
    int ReadData(unsigned char *data, long &length);

	/// Port used for communication.
	IConnection *activeControlPort;	
	std::vector<DeviceInfo> mDevices;
	std::vector<std::string> mDeviceList;
	int mOpenedDevice;
	std::map<eConnectionType, IConnection*> m_connections;
	bool m_system_big_endian;
	bool m_tripleCheckRead;
	bool m_testWriting;
};

#endif
