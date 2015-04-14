/**
@file	PLL_CGEN.h
@author	Lime Microsystems
@brief 	Header for PLL_CGEN.cpp
*/

#ifndef PLL_CGEN_H_INCLUDED
#define PLL_CGEN_H_INCLUDED

#include <vector>
using namespace std;

//---------------------------------------------------------------------------
class PLL_CGEN
{
private:
    double *m_pdVCO; //High VCO frequencies, MHz
    unsigned m_iVCOn;     //Length of m_pdVCOH

    double m_dRefF;   //Reference frequency, MHz
    double m_dMaxF;   //Max frequency, MHz
    double m_dMinF;   //Min frequency, MHz

protected:

public:
    PLL_CGEN();
    ~PLL_CGEN();

    int FreqParams(double refClk_MHz, double dDFH, double &rdRF, unsigned &Nint, unsigned &Nfrac, double &Fvco, unsigned &iHDiv);

    vector<double> GetVCOFrequencies() const;
    void SetVCOFrequencies(double *frequencies, unsigned int f_count);
    bool SaveToFile(const char* filename);
    bool LoadFromFile(const char* filename);
    void Reset();
};

#endif // PLL_CGEN_H_INCLUDED
