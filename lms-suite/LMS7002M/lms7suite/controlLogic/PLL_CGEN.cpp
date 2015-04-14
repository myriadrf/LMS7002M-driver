/**
@file	PLL_CGEN.cpp
@author	Lime Microsystems
@brief	Parameter calculations for CLKGEN PLL
*/

#include "PLL_CGEN.h"
#include <math.h>
#include <fstream>
#include <string.h>
using namespace std;

/**
* Class constructor. Initialization of VCO frequencies, Min, Max
* PLL frequesncies is done there.
*/
PLL_CGEN::PLL_CGEN()
{
    m_pdVCO = NULL;
    Reset();
};

void PLL_CGEN::Reset()
{
    //VCO settings
    delete m_pdVCO;
    m_iVCOn = 2;
    m_pdVCO = new double[m_iVCOn];
    m_pdVCO[0] = 2000;
    m_pdVCO[1] = 2700;

    m_dMaxF = m_pdVCO[m_iVCOn-1]/2.0;  //Max frequency
    m_dMinF = m_pdVCO[0]/(2.0 * 256.0);
}

/**
* Class destructor.
*/
PLL_CGEN::~PLL_CGEN()
{
    delete [] m_pdVCO;
};

/**
* Calculates CGEN PLL parameters according to desired frequency.
* iHDiv is set to 1000 if it is not possible to deliver required frequency.
*
* @param[in] dDFH Desireg frequency, MHz
* @param[in] rdRF Real frequency according to parameters calculated, MHz
* @param[in] Nint Integer division ratio (INT_SDM)
* @param[in] Nfrac Fractional division ratio (FRAC_SDM)
* @param[in] Fvco VCO frequency, MHz
* @param[in] iHDiv Divider (real divider is 2^(DIV_OUTCH_CGEN+1)), (DIV_OUTCH_CGEN)
  @return
    - -1 cannot deliver requested frequency
    - 0 success
    - 1 requested frequency out of range, changed to closest available frequency
*/
int PLL_CGEN::FreqParams(double refClk_MHz, double dDFH, double &rdRF, unsigned &Nint, unsigned &Nfrac, double &Fvco, unsigned &iHDiv)
{
    double m_dRefF = refClk_MHz;    //Reference frequency
    double dMul = 1;
    double dFvco;
    double dFrac;
    double realDF;

    //Check if it is possible to generate desired frequency.
    //Set to limiting values if not.
    bool frequencyWithinRange = true;
    if (dDFH > m_dMaxF)
    {
        realDF = m_dMaxF;
        frequencyWithinRange = false;
    }
    else if (dDFH < m_dMinF)
    {
        realDF = m_dMinF;
        frequencyWithinRange = false;
    }
    else
        realDF = dDFH;
   
    //VCO frequency selection according to F_CLKH
    //Start from high dividers
    iHDiv = 1000;
    for(int i=255; i>=0; i--)
    {
        //Calculate VCO frequency according to the divider
        dMul = 2.0 * (double)(i+1);
        dFvco = dMul * realDF;
        if ( (dFvco >= m_pdVCO[0]) && (dFvco <= m_pdVCO[m_iVCOn-1]) )
        {
            iHDiv = i;
            break;
        }
    };

    //Check if it is possible to deliver required frequency
    if(iHDiv == 1000)
        return -1;

    //Return VCO frequency
    Fvco = dFvco;

    //Integer division
    Nint = unsigned(double(dFvco/m_dRefF)) - 1;

    //Fractional division
    dFrac = dFvco/m_dRefF - unsigned(dFvco/m_dRefF);
    Nfrac = dFrac * pow(2, 20);

    //Calculate real frequency according to the calculated parameters
    rdRF = m_dRefF * (1.0/dMul) * (((double)Nint + (double)Nfrac/(double)pow(2, 20)) + 1.0);
    if(frequencyWithinRange)
        return 0;
    else
        return 1;
};

vector<double> PLL_CGEN::GetVCOFrequencies() const
{
    vector<double> temp;
    for(unsigned i=0; i<m_iVCOn; ++i)
        temp.push_back(m_pdVCO[i]);
    return temp;
}

void PLL_CGEN::SetVCOFrequencies(double *frequencies, unsigned int f_count)
{
    if(m_pdVCO)
        delete []m_pdVCO;
    m_pdVCO = new double[f_count];
    m_iVCOn = f_count;
    for(unsigned i=0; i<f_count; ++i)
        m_pdVCO[i] = frequencies[i];
}

bool PLL_CGEN::SaveToFile(const char* filename)
{
    fstream fout;
    fout.open(filename, ios::out);
    if(!fout.good())
    {
        fout.close();
        return false;
    }

    vector<double> freqs;
    freqs.clear();
    freqs = GetVCOFrequencies();
    fout << "[VCO_CGEN] count: " << freqs.size() << "," << endl;
    for(unsigned i=0; i<freqs.size(); ++i)
        fout << freqs[i] << ' ' << "GHz," << endl;
    fout.close();
    return true;
}

/** @brief Loads VCO_CGEN values from file
    @param filename source file
    @return true on success
*/
bool PLL_CGEN::LoadFromFile(const char* filename)
{
    fstream fin;
    fin.open(filename, ios::in);
    if(!fin.good())
    {
        fin.close();
        return false;
    }

    char cline[128];
    int lineLen = 128;

    char vconame[80];
    char ctemp[80];
    double freq = 0;
    int freqCount = 0;

    vector<double> frequencies;

    while(!fin.eof())
    {
        freqCount = 0;
        fin.getline(cline, lineLen);
        //find name and frequency count
        sscanf(cline, "%s %s %i", vconame, ctemp, &freqCount);
        if(strcmp(vconame, "[VCO_CGEN]") == 0)
        {
            frequencies.clear();
            for(int i=0; i<freqCount; ++i)
            {
                fin.getline(cline, lineLen);
                sscanf(cline, "%lf %s", &freq, ctemp);
                frequencies.push_back(freq*1000);
            }
            SetVCOFrequencies(&frequencies[0], frequencies.size());
        }
        vconame[0] = 0;
    }
    fin.close();
    return true;
}
