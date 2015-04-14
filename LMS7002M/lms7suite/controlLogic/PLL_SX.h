/**
@file	PLL_SX.h
@brief	Header for PLL_SX.cpp
@author	Lime Microsystems
*/

#ifndef PLL_SX_H
#define PLL_SX_H

#include <vector>
using namespace std;

//---------------------------------------------------------------------------
class PLL_SX
{
private:
    double *m_pdVCOH; //High VCO frequencies, MHz
    unsigned m_iVCOHn;     //Length of m_pdVCOH
    double *m_pdVCOM; //Middle VCO frequencies, MHz
    unsigned m_iVCOMn;     //Length of m_pdVCOM
    double *m_pdVCOL; //Low VCO frequencies, MHz
    unsigned m_iVCOLn;     //Length of m_pdVCOL

    double m_dMaxF;   //Max frequency, MHz
    double m_dMinF;   //Min frequency, MHz
    double m_dThrF;   //Threshold frequency to switch additional divider, MHz

protected:

public:
    PLL_SX();
    ~PLL_SX();

    int FreqParams(double refClk_MHz, double dDF, double &rdRF, unsigned &Nint, unsigned &Nfrac, unsigned &iVCO, double &Fvco, unsigned &iDInd, unsigned &iEnDiv2, int EnDiv2mode = 0);
    double CalculateRealFrequency(double refClk_MHz, double dMul, int Nint, int Nfrac, int iEnDiv2);

    bool SaveToFile(const char* filename);
    bool LoadFromFile(const char* filename);

    vector<double> GetVCOHFrequencies() const;
    vector<double> GetVCOMFrequencies() const;
    vector<double> GetVCOLFrequencies() const;
    void SetVCOHFrequencies(double *frequencies, unsigned int f_count);
    void SetVCOMFrequencies(double *frequencies, unsigned int f_count);
    void SetVCOLFrequencies(double *frequencies, unsigned int f_count);

    void Reset();
};

#endif // PLL_SX_H
