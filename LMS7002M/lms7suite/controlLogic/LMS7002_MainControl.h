/**
@file	LMS7002_MainControl.h
@author	Lime Microsystems
@brief	Header for LMS7002_MainControl.h
*/

#ifndef LMS7002_MAIN_CONTROL_H
#define LMS7002_MAIN_CONTROL_H

#include <string>
#include <vector>
using namespace std;
#include "ControlParameters.h"
#include "PLL_SX.h"
#include "PLL_CGEN.h"
#include "Algorithms.h"
#include "SignalHandler.h"

class ConnectionManager;
class RegistersMap;
class Si5356A_module;
class Si5351C;
class ADF_module;
class MCU_BD;

/** @class LMS7002_MainControl
    @brief Main class for controlling LMS7002 chip
*/

class LMS7002_MainControl : public SignalHandler
{
    public:
        LMS7002_MainControl();
        ~LMS7002_MainControl();

        void HandleMessage(const LMS_Message &msg);

        bool CreateConfigurationInstructions(const std::string filename);

        bool LoadFromFile(const std::string filename);
        bool SaveToFile(const std::string filename, bool binary);

        bool LoadGFIRCoefficients(const std::string filename, int id, bool Rx);
        bool LoadGFIRCoefficients(short *coefficients, int coef_count, int id, bool Rx);

        void FindDevices();
        void ResetChip();
        void ResetEverything();

        bool UploadAll();
        bool DownloadAll();

        void SelectConfigChannel(int channel, bool configAll);
        int GetConfigChannel() const;

        bool SetParam(LMS7002_Parameter param, long value);
        long GetParam(LMS7002_Parameter param, bool fromChip = false, bool updateLocal = true) const;

        bool SetNCOconfiguration(const vector<double> &FCW, const vector<int> &PHO, const bool Rx);
        void GetNCOconfiguration(vector<double> &FCW, vector<int> &PHO, const bool Rx);
        bool ReconfigureNCO(int channel, bool Rx);

        bool SetReferenceFrequencyNCO(const double freq_MHz, const bool Rx);
        double GetReferenceFrequencyNCO(const bool Rx) const;

        bool SetReferenceFrequencyPLL(const float freq_MHz, const bool Rx);
        double GetReferenceFrequencyPLL(const bool Rx) const;

        bool SetReferenceFrequencyCGEN(const float freq_MHz);
        double GetReferenceFrequencyCGEN() const;

        int SetFrequency(const double desFreq_MHz, double &realFreq_MHz, unsigned &Nint, unsigned &Nfrac, unsigned &iVCO, double &Fvco, unsigned &iDind, unsigned &iEnDiv2, const int EnDiv2mode=0);
        double GetFrequency();

        bool SetFrequencyCGEN(const double desFreq_MHz, double &realFreq_MHz, unsigned &Nint, unsigned &Nfrac, double &Fvco, unsigned &iHDiv);
        double GetFrequencyCGEN();

        void SetAutoDownload(bool enabled);
        bool GetAutoDownload() const;
        void SetAutoUpload(bool enabled);
        bool GetAutoUpload() const;

        vector<short> GetGFIRcoefficients(int gfirIndex, bool Rx);

        ADF_module *getADF() const;
        Si5351C *getSi5351() const;
        MCU_BD *getMCU_BD() const;
        RegistersMap *getRegistersMap() const;
        ConnectionManager *getSerPort() const;
        Algorithms *algorithms;

        PLL_SX *getPLL_SX();
        PLL_CGEN *getPLL_CGEN();

        int SetGPIOStates(const vector<unsigned char> &states);
        void GetGPIOStates(vector<unsigned char> &states);
        bool UploadGPIOStates();
        bool DownloadGPIOStates();

        unsigned short mDC_REG[2][2][2]; //IQ/channel/TxRx
    protected:
        bool m_firstConnect;
        vector<short> m_GFIRcoefficients_TX[3];
        vector<short> m_GFIRcoefficients_RX[3];

        void Initialize();
        unsigned int CalculateNCO_FCW_Code(float desiredFreq_MHz, float Fref_MHz);

        ConnectionManager *m_device;
        RegistersMap *m_registersMap;
        Si5351C *m_si5351c;
        ADF_module *m_ADF;
        MCU_BD *m_MCU_BD;

        PLL_SX m_PLL_data;
        PLL_CGEN m_CGEN_data;

        double m_freqCGEN_MHz;

        double m_freqSXR_MHz;
        double m_freqSXT_MHz;

        double m_referenceFreqNCO_Tx_MHz;
        double m_referenceFreqNCO_Rx_MHz;

        double m_RefFreqSXR_MHz;
        double m_RefFreqSXT_MHz;
        double m_RefFreqCGEN_MHz;

        double m_FCWfreq_MHz[16][2][2]; // FCW index/channel/TxRx
        int m_PHO[16][2][2]; // PHO index/channel/TxRx

        vector<unsigned char> gpioStates;

    private:

};


#endif // LMS7002_MAIN_CONTROL_H

