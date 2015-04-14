/**
@file	LMS7002_MainControl.cpp
@author	Lime Microsystems
@brief	main class for controlling LMS7002 chip
*/

#include "LMS7002_MainControl.h"
#include "ConnectionManager.h"
#include "RegistersMap.h"
#include "Si5351C.h"
#include "ADF_module.h"
#include "MCU_BD.h"
#include "MessageLog.h"
#include "CoefficientFileParser.h"
#include "../CommonUtilities.h"
#include <math.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "iniParser.h"
using namespace std;

/** @brief Handles incoming messages
    @param msg message about event
*/
void LMS7002_MainControl::HandleMessage(const LMS_Message &msg)
{
    //just relay all incoming messages to main control listeners
    switch(msg.type)
    {
        case MSG_BOARD_CONNECTED:
            if(m_firstConnect)
            {
                ResetChip();
                eLMS_DEV boardType = getSerPort()->GetConnectedDeviceType();
                if( boardType == LMS_DEV_SOCKETBOARD || boardType == LMS_DEV_EVB7V2 )
                    DownloadGPIOStates();
                UploadAll();
                m_firstConnect = false;
            }
            SetParam(MIMO_SISO, 0);
        default:
            Notify(msg);
    }
}

/** @brief Creates and initializes control modules and registers map
*/
LMS7002_MainControl::LMS7002_MainControl() : m_device(new ConnectionManager(false))
{
    for(int i=0; i<8; ++i)
        ((unsigned short*)&mDC_REG)[i] = 0x7fff;
    m_firstConnect = true;
    gpioStates.resize(56, 0);
    algorithms = new Algorithms(this);
    //default reference frequency
    m_referenceFreqNCO_Tx_MHz = 30.72;
    m_referenceFreqNCO_Rx_MHz = 30.72;
    m_RefFreqSXR_MHz = 30.72;
    m_RefFreqSXT_MHz = 30.72;
    m_RefFreqCGEN_MHz = 30.72;
    m_freqSXR_MHz=1950;
    m_freqSXT_MHz=2140;
    m_freqCGEN_MHz=61.44;
    memset(m_FCWfreq_MHz, 0, sizeof(double)*16*2*2);
    memset(m_PHO, 0, sizeof(int)*16*2*2);
    m_registersMap = new RegistersMap(m_device);
    m_device->AssignRegistersMap(m_registersMap);
    m_si5351c = new Si5351C();
    m_ADF = new ADF_module();
    m_MCU_BD = new MCU_BD();
    Initialize();

    //register to messages from connection manager
    m_device->RegisterForNotifications(this);
}

/** @brief Initializes control modules
*/
void LMS7002_MainControl::Initialize()
{
    m_si5351c->Initialize(m_device);
    m_ADF->Initialize(m_device);
    m_MCU_BD->Initialize(m_device);

    //add GFIR coefficients to registers map
    short tempCoeffcients[120];
    memset(tempCoeffcients,0,120*sizeof(unsigned short));
    int prevChannel = GetConfigChannel();
    bool configAll = m_registersMap->GetConfigAll();
    SelectConfigChannel(0, false);
    LoadGFIRCoefficients(tempCoeffcients, 40, 1, false);
    LoadGFIRCoefficients(tempCoeffcients, 40, 2, false);
    LoadGFIRCoefficients(tempCoeffcients, 120,3, false);
    LoadGFIRCoefficients(tempCoeffcients, 40, 1, true);
    LoadGFIRCoefficients(tempCoeffcients, 40, 2, true);
    LoadGFIRCoefficients(tempCoeffcients, 120,3, true);
    SelectConfigChannel(1, false);
    LoadGFIRCoefficients(tempCoeffcients, 40, 1, false);
    LoadGFIRCoefficients(tempCoeffcients, 40, 2, false);
    LoadGFIRCoefficients(tempCoeffcients, 120,3, false);
    LoadGFIRCoefficients(tempCoeffcients, 40, 1, true);
    LoadGFIRCoefficients(tempCoeffcients, 40, 2, true);
    LoadGFIRCoefficients(tempCoeffcients, 120,3, true);
    SelectConfigChannel(prevChannel, configAll);

    MessageLog::getInstance()->write("LMS7002 Main control initialized\n");
}

/** @brief Deletes all control modules
*/
LMS7002_MainControl::~LMS7002_MainControl()
{
    m_device->UnregisterFromNotifications(this);
    delete algorithms;
    delete m_device;
    delete m_si5351c;
    delete m_MCU_BD;
}

/** @brief Loads register values from file
    @param filename file to load
    @return true if success
*/
bool LMS7002_MainControl::LoadFromFile(const string filename)
{
    bool status = false;
    bool loadFromBinary = false;
    char temp[128];
    ifstream fin;
    fin.open(filename.c_str(), ios::in | ios::binary);

    memset(temp,0,128);
    fin.read( temp, 7);
    if(strcmp(temp, "LMS7002") == 0) //check if file type is binary
        loadFromBinary = true;

    if(loadFromBinary)
    {
        fin.seekg(0, ios::beg); // reset to file beginning
        status = m_registersMap->LoadFromStream(fin);
        fin.read(temp, 12);
        if(strcmp(temp, "SXR_freq_MHz") == 0)
        {
            fin.read( (char*)&m_freqSXR_MHz, sizeof(m_freqSXR_MHz));
            fin.read(temp, 12);
            fin.read( (char*)&m_freqSXT_MHz, sizeof(m_freqSXT_MHz));
        }
    }
    fin.close();

    if(!loadFromBinary)
    {
        bool autoUploadState = GetAutoUpload();
        SetAutoUpload(false);
        iniParser parser;
        parser.Open(filename.c_str());
        parser.SelectSection("FILE INFO");
        string type = "";
        type = parser.Get("type", "undefined");
        stringstream ss;
        if(type != "LMS7002 configuration")
        {
            ss << "File " << filename << " not recognized" << endl;
            MessageLog::getInstance()->write(ss.str(), LOG_WARNING);
            return false;
        }

        int fileVersion = 0;
        fileVersion = parser.Get("version", 0);

        if(fileVersion == 1)
        {
            map<string, string>::iterator pairs;
            parser.SelectSection("LMS7002 registers ch.A");
            map<string, string> regValues = parser.GetCurrentSection();

            unsigned short addr = 0;
            unsigned short value = 0;
            m_registersMap->SelectConfigChannel(0, false);
            for(pairs = regValues.begin(); pairs != regValues.end(); ++pairs)
            {
                sscanf(pairs->first.c_str(), "%hx", &addr);
                sscanf(pairs->second.c_str(), "%hx", &value);
                m_registersMap->SetRegisterValue(addr, value);
            }
            parser.SelectSection("LMS7002 registers ch.B");
            regValues.clear();
            regValues = parser.GetCurrentSection();

            m_registersMap->SelectConfigChannel(1, false);
            for(pairs = regValues.begin(); pairs != regValues.end(); ++pairs)
            {
                sscanf(pairs->first.c_str(), "%hx", &addr);
                sscanf(pairs->second.c_str(), "%hx", &value);
                m_registersMap->SetRegisterValue(addr, value);
            }

            parser.SelectSection("Frequencies");
            m_freqSXR_MHz = parser.Get("SXR frequency MHz", 2.14);
            Notify(LMS_Message(MSG_RX_FREQUENCY_CHANGED, "", m_freqSXR_MHz*1000, 0));
            m_freqSXT_MHz = parser.Get("SXT frequency MHz", 2.14);
            Notify(LMS_Message(MSG_TX_FREQUENCY_CHANGED, "", m_freqSXT_MHz*1000, 0));
            m_freqCGEN_MHz = parser.Get("CGEN frequency MHz", 61.44);

            parser.SelectSection("Reference clocks");
            m_RefFreqSXR_MHz = parser.Get("SXR reference frequency MHz", 30.72);
            m_RefFreqSXT_MHz = parser.Get("SXT reference frequency MHz", 30.72);
            m_RefFreqCGEN_MHz = parser.Get("CGEN reference frequency MHz", 30.72);
            m_referenceFreqNCO_Rx_MHz = parser.Get("RxNCO MHz", 30.72);
            m_referenceFreqNCO_Tx_MHz = parser.Get("TxNCO MHz", 30.72);

            char ctemp[80];
            char secNames[][80] = {"NCO Tx ch.A", "NCO Tx ch.B", "NCO Rx ch.A", "NCO Rx ch.B"};
            for(int j=0; j<4; ++j)
            {
                parser.SelectSection(secNames[j]);
                for(int i=0; i<16; ++i)
                {
                    sprintf(ctemp, "FCW%02i", i);
                    m_FCWfreq_MHz[i][j%2][j/2] = parser.Get(ctemp, 0.0);
                    sprintf(ctemp, "PHO%02i", i);
                    m_PHO[i][j%2][j/2] = parser.Get(ctemp, 0);
                }
            }

            parser.SelectSection("gpio_states");
            {
                char ctemp[64];
                string cvalue;
                for(int i=0; i<56; ++i)
                {
                    sprintf(ctemp, "gpio_states_%02i", i);
                    cvalue = parser.Get(ctemp, "0x00");
                    int value = 0;
                    sscanf(cvalue.c_str(), "%x", &value);
                    gpioStates[i] = value;
                }
            }

            parser.SelectSection("TSG_DC_REG");
            mDC_REG[0][0][0] = hex2int(parser.Get("TSG_DC_REG_I_A_TXTSP", "0x7fff"));
            mDC_REG[1][0][0] = hex2int(parser.Get("TSG_DC_REG_Q_A_TXTSP", "0x7fff"));
            mDC_REG[0][1][0] = hex2int(parser.Get("TSG_DC_REG_I_B_TXTSP", "0x7fff"));
            mDC_REG[1][1][0] = hex2int(parser.Get("TSG_DC_REG_Q_B_TXTSP", "0x7fff"));
            mDC_REG[0][0][1] = hex2int(parser.Get("TSG_DC_REG_I_A_RXTSP", "0x7fff"));
            mDC_REG[1][0][1] = hex2int(parser.Get("TSG_DC_REG_Q_A_RXTSP", "0x7fff"));
            mDC_REG[0][1][1] = hex2int(parser.Get("TSG_DC_REG_I_B_RXTSP", "0x7fff"));
            mDC_REG[1][1][1] = hex2int(parser.Get("TSG_DC_REG_Q_B_RXTSP", "0x7fff"));
        }

        SetAutoUpload(autoUploadState);
        status = true;
    }

    return status;
}

/** @brief Saves register values to file
    @param filename file to save into
    @param binary binary or text file
    @return true if success
*/
bool LMS7002_MainControl::SaveToFile(const string filename, bool binary)
{
    bool status = false;
    if(binary)
    {
        status = m_registersMap->SaveToFile(filename);
        ofstream fout;
        fout.open(filename.c_str(), ios::out | ios::binary);
        m_registersMap->SaveToStream(fout);
        fout.seekp(0, ios_base::end);
        fout.write("SXR_freq_MHz", 12);
        fout.write( (const char*)&m_freqSXR_MHz, sizeof(m_freqSXR_MHz));
        fout.write("SXT_freq_MHz", 12);
        fout.write( (const char*)&m_freqSXT_MHz, sizeof(m_freqSXT_MHz));

        fout.close();
    }
    else
    {
        iniParser parser;
        parser.SelectSection("FILE INFO");
        parser.Set("type", "LMS7002 configuration");
        parser.Set("version", 1);

        map<unsigned short, unsigned short>::iterator pairs;
        parser.SelectSection("LMS7002 registers ch.A");
        map<unsigned short, unsigned short> regValues = m_registersMap->GetRegistersValues(0);

        char addr[80];
        char value[80];

        for(pairs = regValues.begin(); pairs != regValues.end(); ++pairs)
        {
            sprintf(addr, "0x%04X", pairs->first);
            sprintf(value, "0x%04X", pairs->second);
            parser.Set(addr,value);
        }

        parser.SelectSection("LMS7002 registers ch.B");
        regValues.clear();
        regValues = m_registersMap->GetRegistersValues(1);

        for(pairs = regValues.begin(); pairs != regValues.end(); ++pairs)
        {
            sprintf(addr, "0x%04X", pairs->first);
            sprintf(value, "0x%04X", pairs->second);
            parser.Set(addr,value);
        }

        parser.SelectSection("Frequencies");
        parser.Set("SXR frequency MHz", m_freqSXR_MHz);
        parser.Set("SXT frequency MHz", m_freqSXT_MHz);
        parser.Set("CGEN frequency MHz", m_freqCGEN_MHz);

        parser.SelectSection("Reference clocks");
        parser.Set("SXT reference frequency MHz", m_RefFreqSXT_MHz);
        parser.Set("SXR reference frequency MHz", m_RefFreqSXR_MHz);
        parser.Set("CGEN reference frequency MHz", m_RefFreqCGEN_MHz);
        parser.Set("RxNCO MHz", m_referenceFreqNCO_Rx_MHz);
        parser.Set("TxNCO MHz", m_referenceFreqNCO_Tx_MHz);

        char ctemp[80];
        char secNames[][80] = {"NCO Tx ch.A", "NCO Tx ch.B", "NCO Rx ch.A", "NCO Rx ch.B"};
        for(int j=0; j<4; ++j)
        {
            parser.SelectSection(secNames[j]);
            for(int i=0; i<16; ++i)
            {
                sprintf(ctemp, "FCW%02i", i);
                parser.Set(ctemp, m_FCWfreq_MHz[i][j%2][j/2]);
                sprintf(ctemp, "PHO%02i", i);
                parser.Set(ctemp, m_PHO[i][j%2][j/2]);
            }
        }

        parser.SelectSection("gpio_states");
        for(int i=0; i<56; ++i)
        {
            sprintf(ctemp, "gpio_states_%02i", i);
            sprintf(value, "0x%02X", gpioStates[i]);
            parser.Set(ctemp, value);
        }
        parser.SelectSection("TSG_DC_REG");
        parser.Set("TSG_DC_REG_I_A_TXTSP", short2hex(mDC_REG[0][0][0]).c_str());
        parser.Set("TSG_DC_REG_Q_A_TXTSP", short2hex(mDC_REG[1][0][0]).c_str());
        parser.Set("TSG_DC_REG_I_B_TXTSP", short2hex(mDC_REG[0][1][0]).c_str());
        parser.Set("TSG_DC_REG_Q_B_TXTSP", short2hex(mDC_REG[1][1][0]).c_str());
        parser.Set("TSG_DC_REG_I_A_RXTSP", short2hex(mDC_REG[0][0][1]).c_str());
        parser.Set("TSG_DC_REG_Q_A_RXTSP", short2hex(mDC_REG[1][0][1]).c_str());
        parser.Set("TSG_DC_REG_I_B_RXTSP", short2hex(mDC_REG[0][1][1]).c_str());
        parser.Set("TSG_DC_REG_Q_B_RXTSP", short2hex(mDC_REG[1][1][1]).c_str());

        parser.Save(filename.c_str());
        status = true;
    }
    return status;
}

/** @brief Creates text file with hexadecimal commands to configure chip
    @param filename file to create
    @return true if success
*/
bool LMS7002_MainControl::CreateConfigurationInstructions(const std::string filename)
{
    unsigned short addr = 0;
    unsigned short value = 0;
    char ctemp[80];
    unsigned int valueOut = 0;
    ofstream fout;
    fout.open(filename.c_str(), ios::out);

    map<unsigned short, unsigned short> regs;

    unsigned int finalAddr20val = 0xFFFF;
    sprintf(ctemp, "0X%08X", 0x8020FFFD); // swtich to A channel
    fout << ctemp << endl;

    regs = m_registersMap->GetRegistersValues(0);
    finalAddr20val = (0x8020 << 16) | regs[0x0020];
    std::map<unsigned short, unsigned short>::iterator iter;
    for (iter = regs.begin(); iter != regs.end(); ++iter)
    {
        addr = iter->first;
        if(addr == 0x0020)
            continue; //skip 0x0020 address to not change channel
        value = regs[addr];

        addr |= 0x8000; //set write bit
        valueOut = addr << 16;
        valueOut |= value;

        sprintf(ctemp, "0X%08X", valueOut);
        fout << ctemp << endl;
    }

    sprintf(ctemp, "0X%08X", 0x8020FFFE); // swtich to B channel
    fout << ctemp << endl;
    regs.clear();
    regs = m_registersMap->GetRegistersValues(1);

    for (iter = regs.begin(); iter != regs.end(); ++iter)
    {
        addr = iter->first;
        value = regs[addr];

        addr |= 0x8000; //set write bit
        valueOut = addr << 16;
        valueOut |= value;

        sprintf(ctemp, "0X%08X", valueOut);
        fout << ctemp << endl;
    }

    sprintf(ctemp, "0X%08X", finalAddr20val);
    fout << ctemp;

    fout.close();
    return true;
}

/** @brief Discovers all connected chips
*/
void LMS7002_MainControl::FindDevices()
{
    m_device->RefreshDeviceList();
}

/** @brief Sends reset signal to chip
*/
void LMS7002_MainControl::ResetChip()
{
    unsigned char outBuffer[1];
    outBuffer[0] = LMS_RST_PULSE;
    if( m_device->SendData(CMD_LMS7002_RST, outBuffer, 1) )
    {
        MessageLog::getInstance()->write("Chip Reset\n");
        SetParam(MIMO_SISO, 0); //enable B channel after reset
    }
    LMS_Message msg;
    msg.text = "CHIP RESET";
    Notify(msg);
}

/** @brief Resets all control settings and parameters
*/
void LMS7002_MainControl::ResetEverything()
{
    ResetChip();
    m_registersMap->SetDefaultValues();
    for(int i=0; i<8; ++i)
        ((unsigned short*)&mDC_REG)[i] = 0x7fff;
    m_firstConnect = true;
    gpioStates.resize(56, 0);
    memset(&gpioStates[0], 0, gpioStates.size());
    //default reference frequency
    m_referenceFreqNCO_Tx_MHz = 30.72;
    m_referenceFreqNCO_Rx_MHz = 30.72;
    m_RefFreqSXR_MHz = 30.72;
    m_RefFreqSXT_MHz = 30.72;
    m_RefFreqCGEN_MHz = 30.72;
    m_freqSXR_MHz=1950;
    m_freqSXT_MHz=2140;
    m_freqCGEN_MHz=61.44;
    memset(m_FCWfreq_MHz, 0, sizeof(double)*16*2*2);
    memset(m_PHO, 0, sizeof(int)*16*2*2);
    m_PLL_data.Reset();
    m_CGEN_data.Reset();

    UploadAll();
}

/** @brief Sends all configuration to the chip
    @return true if success
*/
bool LMS7002_MainControl::UploadAll()
{
    bool status = m_registersMap->UploadAll();
    //upload FCW and PHO
    int oldCh = getRegistersMap()->GetConfigChannel();
    bool configAll = getRegistersMap()->GetConfigAll();

    vector<double> vFCW;
    vector<int> vPHO;
    vFCW.resize(16, 0);
    vPHO.resize(16, 0);
    SelectConfigChannel(0, false);
    for(int i=0; i<16; ++i)
    {
        vFCW[i] = m_FCWfreq_MHz[i][0][0];
        vPHO[i] = m_PHO[i][0][0]; //Tx A
    }
    SetNCOconfiguration(vFCW, vPHO, false);
    for(int i=0; i<16; ++i)
    {
        vFCW[i] = m_FCWfreq_MHz[i][0][1];
        vPHO[i] = m_PHO[i][0][1]; //Rx A
    }
    SetNCOconfiguration(vFCW, vPHO, true);

    SelectConfigChannel(1, false);
    for(int i=0; i<16; ++i)
    {
        vFCW[i] = m_FCWfreq_MHz[i][1][0];
        vPHO[i] = m_PHO[i][1][0]; //Tx A
    }
    SetNCOconfiguration(vFCW, vPHO, false);
    for(int i=0; i<16; ++i)
    {
        vFCW[i] = m_FCWfreq_MHz[i][1][1];
        vPHO[i] = m_PHO[i][1][1]; //Tx A
    }
    SetNCOconfiguration(vFCW, vPHO, true);
    eLMS_DEV boardType = getSerPort()->GetConnectedDeviceType();
    if( boardType == LMS_DEV_SOCKETBOARD || boardType == LMS_DEV_EVB7V2 )
        UploadGPIOStates();
    //upload TSG DC_REG
    for(int i=0; i<2; ++i)
    {
        SelectConfigChannel(i, false);
        SetParam(DC_REG_TXTSP, mDC_REG[0][i][0]);
        SetParam(TSGDCLDI_TXTSP, 0);
        SetParam(TSGDCLDI_TXTSP, 1);
        SetParam(TSGDCLDI_TXTSP, 0);

        SetParam(DC_REG_TXTSP, mDC_REG[1][i][0]);
        SetParam(TSGDCLDQ_TXTSP, 0);
        SetParam(TSGDCLDQ_TXTSP, 1);
        SetParam(TSGDCLDQ_TXTSP, 0);

        SetParam(DC_REG_RXTSP, mDC_REG[0][i][1]);
        SetParam(TSGDCLDI_RXTSP, 0);
        SetParam(TSGDCLDI_RXTSP, 1);
        SetParam(TSGDCLDI_RXTSP, 0);

        SetParam(DC_REG_RXTSP, mDC_REG[1][i][1]);
        SetParam(TSGDCLDQ_RXTSP, 0);
        SetParam(TSGDCLDQ_RXTSP, 1);
        SetParam(TSGDCLDQ_RXTSP, 0);
    }
    SelectConfigChannel(oldCh, configAll);
    return status;
}

/** @brief Reads all configuration from the chip
    @return true if success
*/
bool LMS7002_MainControl::DownloadAll()
{
    bool status = m_registersMap->DownloadAll();

    //download FCW or PHO
    bool configAll = getRegistersMap()->GetConfigAll();
    int activeChannel = GetConfigChannel();
    vector<unsigned short> outBuffer;
    vector<int> fcwCodes;
    ConnectionManager *port = getSerPort();

    if(port->IsOpen())
    {
        for(int c=0; c<4; ++c) //channels and TxRx
        {
            outBuffer.clear();
            int channel = c%2;
            SelectConfigChannel(channel, false);
            unsigned short inBuffer[128];
            //Rx channel
            bool Rx = (c < 2);
            float refClk = Rx ? m_referenceFreqNCO_Rx_MHz : m_referenceFreqNCO_Tx_MHz;
            unsigned short addr = 0x0241;

            LMS7002_Parameter mode;
            if(Rx)
            {
                mode = MODE_RX;
                addr += 0x0200;
            }
            else
                mode = MODE_TX;

            stringstream ss;
            int mode_val = GetParam(mode);
            if( mode_val == 0) //read FCW
            {
                addr = 0x0242;
                if(Rx)
                    addr += 0x0200;
                for(unsigned int i=0; i<16; ++i)
                {
                    //read FCWi MSB
                    outBuffer.push_back(addr++);
                    //read FCWi LSB
                    outBuffer.push_back(addr++);
                }
            }
            else //read PHO
            {
                addr = 0x0244;
                if(Rx)
                    addr += 0x0200;
                for(int i=0; i<16; ++i) //read PHO
                {
                    outBuffer.push_back(addr++);
                }
            }
            unsigned long bToRead = (mode_val == 0) ? 128 : 64; //FCW 32 bit values, PHO 16 bit values
            if( port->SendReadData(CMD_LMS7002_RD, (const unsigned char*)&outBuffer[0], sizeof(unsigned short)*outBuffer.size(), (unsigned char*)inBuffer, bToRead) == STATUS_COMPLETED_CMD)
            {
                unsigned int value = 0;
                if(mode_val == 0) //update FCW
                {
                    unsigned index = 1;
                    for(int b=0; b<16 && index < 64; ++b)
                    {
                        value = 0;
                        value = inBuffer[index];
                        index += 2;
                        value = value << 16;
                        value |= inBuffer[index];
                        index += 2;
                        m_FCWfreq_MHz[b][channel][Rx] = (value ) * (refClk/pow(2.0, 32));
                    }
                }
                else //update PHO
                {
                    unsigned index = 1;
                    for(int b=0; b<16 && index < 32; ++b)
                    {
                        value = 0;
                        value = inBuffer[index];
                        index += 2;
                        m_PHO[b][channel][Rx] = value;
                    }
                }
            }
        }
        //read gpio states
        eLMS_DEV boardType = getSerPort()->GetConnectedDeviceType();
        if( boardType == LMS_DEV_SOCKETBOARD || boardType == LMS_DEV_EVB7V2 )
            DownloadGPIOStates();
    }
    SelectConfigChannel(activeChannel, configAll);
    return status;
}

/** @brief Set chosen parameter to given value
    @param param LMS7002 parameter
    @param value new parameter value
    @return true if success
*/
bool LMS7002_MainControl::SetParam(LMS7002_Parameter param, long value)
{
    return m_registersMap->SetParameterValue(param, value);
}

/** @brief Returns value of chosen parameter
    @param param LMS7002 parameter
    @return parameter value
*/
long LMS7002_MainControl::GetParam(LMS7002_Parameter param, bool fromChip, bool updateLocal) const
{
    return m_registersMap->GetParameterValue(param, fromChip, updateLocal);
}

ADF_module* LMS7002_MainControl::getADF() const
{
    return m_ADF;
}

Si5351C* LMS7002_MainControl::getSi5351() const
{
    return m_si5351c;
}

MCU_BD* LMS7002_MainControl::getMCU_BD() const
{
    return m_MCU_BD;
}

RegistersMap* LMS7002_MainControl::getRegistersMap() const
{
    return m_registersMap;
}

ConnectionManager* LMS7002_MainControl::getSerPort() const
{
    return m_device;
}

/** @brief Selects which chip channel to config.
    @param channel channel index starting from 0
    @param configAll send configuration to all channels
*/
void LMS7002_MainControl::SelectConfigChannel(int channel, bool configAll)
{
    m_registersMap->SelectConfigChannel(channel, configAll);
}

/** @brief Returns which channel is selected for configuration
    @return channel index
*/
int LMS7002_MainControl::GetConfigChannel() const
{
    return m_registersMap->GetConfigChannel();
}

/** @brief Enables or disables auto download mode
    @param enabled auto download enable
    When auto download is enabled each GetParam() call will read register value
    from chip, otherwise the returned value will be from local program memory
*/
void LMS7002_MainControl::SetAutoDownload(bool enabled)
{
    m_registersMap->SetAutoDownload(enabled);
}

/** @brief Returns auto download state
    @return auto download enabled
*/
bool LMS7002_MainControl::GetAutoDownload() const
{
    return m_registersMap->GetAutoDownload();
}

/** @brief Enables or disables auto uploading
    @param enabled auto upload enable
    When auto upload is enabled each SetParam call will write register value to
    the chip, otherwise value is written to local memory for later writing.
*/
void LMS7002_MainControl::SetAutoUpload(bool enabled)
{
    m_registersMap->SetAutoUpload(enabled);
}

/** @brief Returns auto upload state
    @return auto upload enabled
*/
bool LMS7002_MainControl::GetAutoUpload() const
{
    return m_registersMap->GetAutoUpload();
}

/** @brief Loads GFIR coefficients from file
    @param filename file to load
    @param id select GFIR, possible values 1,2,3
    @param Rx selects to write to receiver or transmitter
    @return true if success
*/
bool LMS7002_MainControl::LoadGFIRCoefficients(const string filename, int id, bool Rx)
{
    int cbuf[200];
    int iVal;

    iVal = Parser::getcoeffs((const char*)filename.c_str(), cbuf, 200);

    if(iVal == -2)
    {
        MessageLog::getInstance()->write("GFIR Coefficients parser: Syntax error within the file.\n");
        return false;
    }
    if(iVal == -4)
    {
        MessageLog::getInstance()->write("GFIR Coefficients parser: can not open the file.\n");
        return false;
    }

    vector<short> coefficients;
    for(int i=0; i<iVal; ++i)
        coefficients.push_back(cbuf[i]);
    return LoadGFIRCoefficients(&coefficients[0], coefficients.size(), id, Rx);
}

/** @brief Loads GFIR coefficients from array
    @param coefficients array containing coefficients
    @param coef_count number of given coefficients
    @param id select GFIR, possible values 1,2,3
    @param Rx selects to write to receiver or transmitter
    @return true if success
*/
bool LMS7002_MainControl::LoadGFIRCoefficients(short *coefficients, int coef_count, int id, bool Rx)
{
    unsigned short rx_addr_offset = 0x0200;
    int status = STATUS_UNDEFINED;
    unsigned short cbuf[200];
    memset(cbuf, 0, sizeof(unsigned short)*200);
    if(coef_count>200)
        coef_count = 200;
    memcpy(cbuf, coefficients, sizeof(short)*coef_count);
    int iVal;
    iVal = coef_count;

    if(iVal == -2)
    {
        MessageLog::getInstance()->write("GFIR Coefficients parser: Syntax error within the file.\n");
        return false;
    }
    if(iVal == -4)
    {
        MessageLog::getInstance()->write("GFIR Coefficients parser: can not open the file.\n");
        return false;
    }

    unsigned short addr = 0x0280;
    if(Rx == true)
        addr += rx_addr_offset;

    vector<unsigned short> outBuffer;

    if(id == 1)
    {
        if(Rx)
            m_GFIRcoefficients_RX[0].clear();
        else
            m_GFIRcoefficients_TX[0].clear();
        //GFIR1
        for(int k=0; k<5; ++k)
        {
            for(int i=0; i<8; ++i)
            {
                outBuffer.push_back(addr);
                outBuffer.push_back(cbuf[k*8+i]);
                if(Rx)
                    m_GFIRcoefficients_RX[0].push_back(cbuf[k*8+i]);
                else
                    m_GFIRcoefficients_TX[0].push_back(cbuf[k*8+i]);
                ++addr;
            }
        }
    }

    else if(id == 2)
    {
        if(Rx)
            m_GFIRcoefficients_RX[1].clear();
        else
            m_GFIRcoefficients_TX[1].clear();
        //GFIR2
        addr = 0x02C0;
        if(Rx == true)
            addr += rx_addr_offset;
        outBuffer.clear();
        for(int k=0; k<5; ++k)
        {
            for(int i=0; i<8; ++i)
            {
                outBuffer.push_back(addr);
                outBuffer.push_back(cbuf[k*8+i]);
                if(Rx)
                    m_GFIRcoefficients_RX[1].push_back(cbuf[k*8+i]);
                else
                    m_GFIRcoefficients_TX[1].push_back(cbuf[k*8+i]);
                ++addr;
            }
        }
    }
    else if(id == 3)
    {
        if(Rx)
            m_GFIRcoefficients_RX[2].clear();
        else
            m_GFIRcoefficients_TX[2].clear();
        //GFIR3
        addr = 0x0300;
        if(Rx == true)
            addr += rx_addr_offset;
        outBuffer.clear();

        int coefIndex = 0;
        unsigned short coefValue = 0;
        for(int n=0; n<3; ++n)
        {
            for(int k=0; k<5; ++k)
            {
                for(int i=0; i<8; ++i)
                {
                    coefValue = cbuf[coefIndex];
                    ++coefIndex;

                    outBuffer.push_back(addr);
                    outBuffer.push_back(coefValue);
                    if(Rx)
                        m_GFIRcoefficients_RX[2].push_back(coefValue);
                    else
                        m_GFIRcoefficients_TX[2].push_back(coefValue);
                    ++addr;
                }
            }
            addr += 24; //skip reserved
        }
    }
    else
    {
        MessageLog::getInstance()->write("GFIR id out of range, available ids: 1,2,3.\n", LOG_ERROR);
        return false;
    }

    bool uploadState = GetAutoUpload();
    SetAutoUpload(false);
    for(unsigned i=0; i<outBuffer.size(); i+=2)
    {
        m_registersMap->SetRegisterValue( outBuffer[i], outBuffer[i+1] );
    }
    SetAutoUpload(uploadState);

    if(!getSerPort()->IsOpen())
        return false;

    status = getSerPort()->SendData(CMD_LMS7002_WR, (const unsigned char*)&outBuffer[0], outBuffer.size()*sizeof(unsigned short));
    if(status != STATUS_COMPLETED_CMD)
    {
        MessageLog::getInstance()->write("Failed to upload GFIR3 coefficients.\n", LOG_ERROR);
        return false;
    }

    MessageLog::getInstance()->write("GFIR coefficients uploaded.\n", LOG_INFO);
    return true;
}

/** @brief Calculates dividers and Integer, Fractional parts for desired frequency
    @param desFreq_MHz desired frequency in MHz
    @param realFreq_MHz real frequency according to paramaters
    @param Nint integer section of division ratio
    @param NFrac fractional section of division ratio
    @param iVCO selected VCO index
    @param VCO_Freq_MHz real VCO frequency
    @param iDind Divider  (real divider is 2^(iDind+1), (DIV_LOCH)
    @param iEnDiv2 additional prescaler control (EN_DIV2_DIVPROG)
    @param EnDiv2mode 0-normal, 1-always on, 2-always off
    @return
    - -1 cannot deliver requested frequency
    - 0 success
    - 1 requested frequency out of range. Set to closest available frequency
*/
int LMS7002_MainControl::SetFrequency(const double desFreq_MHz, double &realFreq_MHz, unsigned &Nint, unsigned &NFrac, unsigned &iVCO, double &VCO_Freq_MHz, unsigned &iDind, unsigned &iEnDiv2, const int EnDiv2mode)
{
    double refClk_MHz;
    if(GetConfigChannel() == 0)
        refClk_MHz = m_RefFreqSXR_MHz;
    else
        refClk_MHz = m_RefFreqSXT_MHz;

    int status = m_PLL_data.FreqParams(refClk_MHz, desFreq_MHz, realFreq_MHz, Nint, NFrac, iVCO, VCO_Freq_MHz, iDind, iEnDiv2, EnDiv2mode);
    if( status < 0 )
    {
        //cannot deliver requested frequency
        stringstream ss;
        ss << "Cannot deliver requested frequency " << desFreq_MHz/1000.0 << " GHz. Frequency not changed." << endl;
        MessageLog::getInstance()->write(ss.str(), LOG_WARNING);
        return status;
    }
    SetParam(SEL_VCO, iVCO);
    SetParam(INT_SDM, Nint);
    SetParam(FRAC_SDM, NFrac);
    SetParam(DIV_LOCH, iDind);
    SetParam(EN_DIV2_DIVPROG, iEnDiv2);

    if(GetConfigChannel() == 0)
    {
        m_freqSXR_MHz = desFreq_MHz;
        Notify(LMS_Message(MSG_RX_FREQUENCY_CHANGED, "", (realFreq_MHz*1000)+0.5, 0));
    }
    else
    {
        m_freqSXT_MHz = desFreq_MHz;
        Notify(LMS_Message(MSG_TX_FREQUENCY_CHANGED, "", (realFreq_MHz+1000)+0.5, 0));
    }

    if(getRegistersMap()->GetConfigAll() == true)
    {
        m_freqSXR_MHz = desFreq_MHz;
        m_freqSXT_MHz = desFreq_MHz;
    }

    if(status == 1)
    {
        stringstream ss;
        ss << "Requested frequency out of available range. Configured to closest available frequency " << realFreq_MHz/1000.0 << " GHz" << endl;
        MessageLog::getInstance()->write(ss.str(), LOG_WARNING);
    }

    return status;
}

/** @brief Returns currently set SXT/SXR frequency in MHz
*/
double LMS7002_MainControl::GetFrequency()
{
    if(GetConfigChannel() == 0)
        return m_freqSXR_MHz;
    else
        return m_freqSXT_MHz;
}

/** @brief Calculates CGEN Integer, Fractional parts for desired frequency
    @param desFreq_MHz desired frequency in MHz
    @param realFreq_MHz real frequency according to parameters
    @param Nint integer section of division ratio
    @param NFrac fractional section of division ratio
    @param VCO_Freq_MHz real VCO frequency, MHz
    @param iHDiv Divider (real divider is 2^(DIV_OUTCH_CGEN+1)), (DIV_OUTCH_CGEN)
    @return true if success
*/
bool LMS7002_MainControl::SetFrequencyCGEN(const double desFreq_MHz, double &realFreq_MHz, unsigned &Nint, unsigned &NFrac, double &VCO_Freq_MHz, unsigned &iHDiv)
{
    int status = m_CGEN_data.FreqParams(m_RefFreqCGEN_MHz, desFreq_MHz, realFreq_MHz, Nint, NFrac, VCO_Freq_MHz, iHDiv);
    if( status >= 0)
    {
        m_freqCGEN_MHz = desFreq_MHz;
        SetParam(INT_SDM_CGEN, Nint);
        SetParam(FRAC_SDM_CGEN, NFrac);
        SetParam(DIV_OUTCH_CGEN, iHDiv);
        if(status == 1)
        {
            stringstream ss;
            ss << "Requested frequency out of available range. Configured to closest available frequency " << realFreq_MHz/1000.0 << " GHz" << endl;
            MessageLog::getInstance()->write(ss.str(), LOG_WARNING);
        }
		//Notify(LMS_Message(MSG_CGEN_FREQUENCY_CHANGED, "", realFreq_MHz * 1000000, 0));
        return true;
    }
    else
    {
        stringstream ss;
        ss << "Cannot deliver requested frequency " << desFreq_MHz/1000.0 << " GHz. Frequency not changed" << endl;
        MessageLog::getInstance()->write(ss.str(), LOG_WARNING);
    }
    return false;
}

/** @brief Returns CGEN frequency in MHz
*/
double LMS7002_MainControl::GetFrequencyCGEN()
{
    return m_freqCGEN_MHz;
}

/** @brief Sets reference frequency
    @param freq_MHz reference frequency in MHz
*/
bool LMS7002_MainControl::SetReferenceFrequencyNCO(const double freq_MHz, const bool Rx)
{
    if(Rx)
        m_referenceFreqNCO_Rx_MHz = freq_MHz;
    else
        m_referenceFreqNCO_Tx_MHz = freq_MHz;
    return true;
}

/** @brief Returns reference frequency
    @return reference frequency in MHz
*/
double LMS7002_MainControl::GetReferenceFrequencyNCO(const bool Rx) const
{
    if(Rx)
        return m_referenceFreqNCO_Rx_MHz;
    else
        return m_referenceFreqNCO_Tx_MHz;
}

/** @brief Sets reference frequency
    @param freq_MHz reference frequency in MHz
*/
bool LMS7002_MainControl::SetReferenceFrequencyPLL(const float freq_MHz, const bool Rx)
{
    if(Rx)
        //m_PLL_data.SetReferenceFrequency(freq_MHz);
        m_RefFreqSXR_MHz = freq_MHz;
    else
        //m_PLL_data.SetReferenceFrequency(freq_MHz);
        m_RefFreqSXT_MHz = freq_MHz;
    return true;
}

/** @brief Returns reference frequency
    @return reference frequency in MHz
*/
double LMS7002_MainControl::GetReferenceFrequencyPLL(const bool Rx) const
{
    if(Rx)
        //return m_PLL_data.GetReferenceFrequency();
        return m_RefFreqSXR_MHz;
    else
        //return m_PLL_data.GetReferenceFrequency();
        return m_RefFreqSXT_MHz;
}

bool LMS7002_MainControl::SetReferenceFrequencyCGEN(const float freq_MHz)
{
    m_RefFreqCGEN_MHz = freq_MHz;
    return true;
}
double LMS7002_MainControl::GetReferenceFrequencyCGEN() const
{
    return m_RefFreqCGEN_MHz;
}
/** @brief Recalculates last NCO parameters
*/
bool LMS7002_MainControl::ReconfigureNCO(int channel, bool Rx)
{
    int lastActiveChannel = GetConfigChannel();
    SelectConfigChannel(channel, false);
    vector<unsigned short> outBuffer;
    vector<int> fcwCodes;
    vector<int> PHO;
    ConnectionManager *port = getSerPort();
    float refClk = Rx ? m_referenceFreqNCO_Rx_MHz : m_referenceFreqNCO_Tx_MHz;
    for(unsigned int i=0; i<16; ++i) //create FCW codes from frequencies
        fcwCodes.push_back( CalculateNCO_FCW_Code(m_FCWfreq_MHz[i][channel][Rx], refClk) );
    for(unsigned int i=0; i<16; ++i) //create FCW codes from frequencies
        PHO.push_back( m_PHO[i][channel][Rx] );

    unsigned short addr = 0x0241;
    LMS7002_Parameter mode;
    if(Rx)
    {
        mode = MODE_RX;
        addr += 0x0200;
    }
    else
        mode = MODE_TX;

    stringstream ss;
    if( GetParam(mode) == 0) //Write FCW
    {
        if(fcwCodes.size() < 16)
        {
            ss << "Configuring NCO " << (Rx ? "Rx" : "Tx") << "ch. " << channel << " : FCW codes given " << fcwCodes.size() << ", needed 16." << endl;
            MessageLog::getInstance()->write(ss.str(), LOG_WARNING);
        }
        ss.str( string() );
        ss << "Configuring NCO " << (Rx ? "Rx" : "Tx") << "ch. " << channel << " : FCW codes" << endl;
        addr = 0x0242;
        if(Rx)
        {
            addr += 0x0200;
        }
        for(unsigned int i=0; i<16 && i<fcwCodes.size(); ++i)
        {
            //Write FCWi MSB
            outBuffer.push_back(addr++);
            outBuffer.push_back(fcwCodes[i] >> 16);
            //Write FCWi LSB
            outBuffer.push_back(addr++);
            outBuffer.push_back(fcwCodes[i] & 0xFFFF);
            ss << "FCW" << setw(2) << i << ": " << uint2hex(fcwCodes[i] >> 16, 4) << " " << uint2hex(fcwCodes[i] & 0xFFFF, 4) << endl;
        }
        MessageLog::getInstance()->write(ss.str(), LOG_DATA);
    }
    else //Write PHO
    {
        if(PHO.size() < 16)
        {
            ss << "Configuring NCO " << (Rx ? "Rx" : "Tx") << "ch. " << channel << ": PHO codes given " << PHO.size() << ", needed 16." << endl;
            MessageLog::getInstance()->write(ss.str(), LOG_WARNING);
        }
        ss.str( string() );
        ss << "Configuring NCO " << (Rx ? "Rx" : "Tx") << ": PHO codes" << endl;
        addr = 0x0244;
        if(Rx)
        {
            addr += 0x0200;
        }
        for(int i=0; i<16 && PHO.size(); ++i) //Write PHO
        {
            outBuffer.push_back(addr++);
            outBuffer.push_back(PHO[i]);
            ss << "PHO" << setw(2) << i << ": " << uint2hex(PHO[i], 4) << endl;
        }
        MessageLog::getInstance()->write(ss.str(), LOG_DATA);
    }
    int status = port->SendData(CMD_LMS7002_WR, (const unsigned char*)&outBuffer[0], sizeof(unsigned short)*outBuffer.size());
    SelectConfigChannel(lastActiveChannel, false);
    if( status == STATUS_COMPLETED_CMD)
    {
        char ctemp[512];
        sprintf(ctemp, "%s ch. %i NCO configured\n", Rx ? "Rx" : "Tx", channel);
        MessageLog::getInstance()->write(ctemp, LOG_INFO);
        return true;
    }
    else
    {
        MessageLog::getInstance()->write("NCO configuration failed\n", LOG_ERROR);
        return false;
    }
}

/** @brief Configures NCO FCW and PHO registers
    @param FCW frequencies in MHz
    @param PHO phase offset
    @param Rx Rx or Tx module
*/
bool LMS7002_MainControl::SetNCOconfiguration(const vector<double> &FCW, const vector<int> &PHO, const bool Rx)
{
    int activeChannel = GetConfigChannel();
    for(int i=0; i<16; ++i)
    {
        if(m_registersMap->GetConfigAll())
        {
            for(int c=0; c<2; ++c)
            {
                m_FCWfreq_MHz[i][c][Rx] = FCW[i];
                m_PHO[i][c][Rx] = PHO[i];
            }
        }
        else
        {
            m_FCWfreq_MHz[i][activeChannel][Rx] = FCW[i];
            m_PHO[i][activeChannel][Rx] = PHO[i];
        }
    }
    return ReconfigureNCO(activeChannel, Rx);
}

void LMS7002_MainControl::GetNCOconfiguration(vector<double> &FCW, vector<int> &PHO, const bool Rx)
{
    int activeChannel = GetConfigChannel();
    FCW.clear();
    PHO.clear();
    for(int i=0; i<16; ++i)
    {
        FCW.push_back( m_FCWfreq_MHz[i][activeChannel][Rx]);
        PHO.push_back( m_PHO[i][activeChannel][Rx]);
    }
}

/** @brief Calculates FCW code from given frequency.
    @param desiredFreq_MHz desired frequency in MHz.
    @param Fref_MHz reference frequency in MHz.
*/
unsigned int LMS7002_MainControl::CalculateNCO_FCW_Code(float desiredFreq_MHz, float Fref_MHz)
{
    float FCW_code = (desiredFreq_MHz * pow(2.0, 32) / Fref_MHz) + 0.5;
    return (unsigned int)FCW_code;
}

/** @brief Returns currently loaded GFIR coefficients
    @param gfirIndex which GFIR coefficients to return, possible ids 0,1,2
    @param Rx select receiver or transmitter coefficients
*/
vector<short> LMS7002_MainControl::GetGFIRcoefficients(int gfirIndex, bool Rx)
{
    if(gfirIndex >= 0 && gfirIndex < 3)
        if(Rx)
            return m_GFIRcoefficients_RX[gfirIndex];
        else
            return m_GFIRcoefficients_TX[gfirIndex];
    else
    {
        vector<short> emptyVector;
        return emptyVector;
    }
}

PLL_SX * LMS7002_MainControl::getPLL_SX()
{
    return &m_PLL_data;
}

PLL_CGEN *LMS7002_MainControl::getPLL_CGEN()
{
    return &m_CGEN_data;
}

/** @brief Send GPIO states to board
    @return true if success
*/
bool LMS7002_MainControl::UploadGPIOStates()
{
    unsigned char buffer[56];
    memset(buffer, 0, 56);
    unsigned char inBuffer[56];
    memcpy(buffer, &gpioStates[0], 56);
    unsigned long toRead = 2;
    if(getSerPort()->SendReadData(CMD_GPIO_WR, buffer, 2, inBuffer, toRead) == STATUS_COMPLETED_CMD)
        return true;
    else
        return false;
}

/** @brief Reads GPIO states from board
    @return true if success
*/
bool LMS7002_MainControl::DownloadGPIOStates()
{
    unsigned char buffer[2];
	memset(buffer, 0, 2);
    unsigned char inBuffer[56];
    memset(inBuffer, 0, 56);
    unsigned long toRead = 56;
    if(getSerPort()->SendReadData(CMD_GPIO_RD, buffer, 2, inBuffer, toRead) == STATUS_COMPLETED_CMD)
    {
        memcpy(&gpioStates[0], inBuffer, 56);
        return true;
    }
    else
        return false;
}

int LMS7002_MainControl::SetGPIOStates(const vector<unsigned char> &states)
{
    for(unsigned i=0; i<56 && i<states.size(); ++i)
        gpioStates[i] = states[i];
    return UploadGPIOStates();
}

void LMS7002_MainControl::GetGPIOStates(vector<unsigned char> &states)
{
    states.clear();
    states = gpioStates;
}
