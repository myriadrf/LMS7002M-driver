/**
@file	Algorithms.h
@author	Lime Microsystems
@brief	Header for Algorithms.cpp
*/

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

class ConnectionManager;
enum {MIMO_A, MIMO_B, MIMO_BOTH};

enum {//RBB Band_id
	RBB_1_4MHZ, RBB_3_0MHZ, RBB_5_0MHZ, RBB_10_0MHZ, RBB_15_0MHZ, RBB_20MHZ, //Low Band
	RBB_37_0MHZ, RBB_66_0MHZ, RBB_108_0MHZ, //High Band
	RBB_ALL
};

enum {//TBB Band_id
	TBB_11_0MHZ,//Low Band //not all
	TBB_18_5MHZ, TBB_38_0MHZ, TBB_54_0MHZ, //High Band
	TBB_ALL
};

class LMS7002_MainControl;

/**
    @class Algorithms
    @brief Class containing all calibration and tuning algorithms
*/
class Algorithms
{
public:
    Algorithms(LMS7002_MainControl *pControl);
    ~Algorithms();
    void Modify_SPI_Reg_bits (unsigned short SPI_reg_addr, unsigned char MSB_bit, unsigned char LSB_bit, unsigned short new_bits_data);
    unsigned short Get_SPI_Reg_bits (unsigned short SPI_reg_addr, unsigned char MSB_bit, unsigned char LSB_bit);

    void Modify_SPI_Reg_mask(const unsigned short addr[], const unsigned short masks[], const unsigned short value[], unsigned char start, unsigned char end);

    //Calibrated and corrected control values
    unsigned short RBB_CBANK[MIMO_BOTH][RBB_ALL];
    unsigned char RBB_RBANK[MIMO_BOTH], TBB_CBANK[MIMO_BOTH], TBB_RBANK[MIMO_BOTH][TBB_ALL];

    void MIMO_Ctrl (unsigned char ch);
    int VCO_CoarseTuning_SXT_SXR (float Fref_MHz, float Fvco_des_MHz, unsigned char ch);
    int VCO_Tuning_SXT_SXR (bool Rx);
    int VCO_CoarseTuning_CGEN (float Fref_MHz, float Fvco_des);
    int VCO_Tuning_CGEN ();
    float Resistor_calibration ();
    void Set_NCO_Freq (float Freq_MHz, float refClk_MHz, bool Rx);

    //RBB
    int Calibration_LowBand_RBB (unsigned char ch);
    int Calibration_HighBand_RBB (unsigned char ch);

    //TBB
    int Calibration_LowBand_TBB (unsigned char ch);
    int Calibration_HighBand_TBB (unsigned char ch);

    int DCCalibrationRX(char config, int *resultI = 0, int *resultQ = 0);
    int DCCalibrationRX_RSSI(char config);
    int DCCalibrationTX_PDET();
    int DCCalibrationTX_RFLOOP(char config);
    int DCCalibrationTX_RFLOOP_MCU(char config);
    int DCCalibrationTX_PDET_config();

    void LoadDCIQ(unsigned short I, unsigned short Q);

    int DetectRXSaturation();
    int FixRXSaturation();

    int VCO_Tuning(char module); // 0-cgen, 1-SXR, 2-SXT

    int TXIQCalibration_setup();
    int TXIQCalibration();

    int RXIQCalibration_setup();
    int RXIQCalibration();

    int DemoCalibration(int stage);
    void InitDemoStages();

    void ReadRSSIField(int minI, int maxI, int stepI, int minQ, int maxQ, int stepQ, int avgCnt);

    unsigned long FindMinRSSI2(unsigned short adr1, char msb1, char lsb1, unsigned short adr2, char msb2, char lsb2, int &result1, int &result2);
    unsigned long FindMinRSSI(unsigned short addr, char msb, char lsb, int startValue, int *result, const char staleLimit, char twoCompl, int stepMult = 1);

    int SetFrequency(char Rx, float refClk_MHz, float freq_MHz);
    int SetFrequencyCGEN(float refClk_MHz, float freq_MHz, unsigned long *Nint=0, unsigned long *Nfrac=0, char *iHdiv=0);
    float GetFrequencySX(bool Rx);
    float GetFrequencyCGEN();

    void CallMCU(int data);
    int WaitForMCU();
    void SetDefaults(unsigned short sAddr, unsigned short eAddr);

protected:

    void Set_DCOFF(char offsetI, char offsetQ);
    void BackupRegisters(const unsigned short *addrs, unsigned short *values, unsigned char start, unsigned char stop);
    void RestoreRegisters(const unsigned short *addrs, unsigned short *values, unsigned char start, unsigned char stop);
    void flipCapture();

    void Set_cal_path_RBB (unsigned char path_no);
    void Set_cal_path_TBB (unsigned char path_no);
    void Algorithm_A_RBB();
    unsigned short Algorithm_B_RBB();
    void Algorithm_F_RBB(unsigned char Band_id);

    void Algorithm_A_TBB();
    unsigned short Algorithm_B_TBB();
    void Algorithm_C_TBB(unsigned char Band_id);
    int Algorithm_D_TBB(unsigned char Band_id);
    void Algorithm_E_TBB(unsigned char Band_id);
    ConnectionManager *m_serPort; ///Connection manager which will be used for data writing and reading
    LMS7002_MainControl *lmsControl;
};

#endif // ALGORITHMS_h

