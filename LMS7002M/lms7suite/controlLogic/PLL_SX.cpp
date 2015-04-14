/**
@file	PLL_SX.cpp
@author	Lime Microsystems
@brief	Parameter calculations for CLKGEN PLL
*/

#include "PLL_SX.h"
#include <math.h>
#include <fstream>
#include <string.h>

/** @brief Class constructor.
    Initialization of VCO frequencies, Min, Max
    PLL frequencies, threshold frequency is done there.
*/
PLL_SX::PLL_SX()
{
    m_pdVCOL = NULL;
    m_pdVCOM = NULL;
    m_pdVCOH = NULL;
    Reset();
};

void PLL_SX::Reset()
{
    //Low VCO settings
    delete m_pdVCOL;
    m_iVCOLn = 2;
    m_pdVCOL = new double[m_iVCOLn];
    m_pdVCOL[0] = 3800.000;
    m_pdVCOL[1] = 5222.000;

    //Middle VCO settings
    delete m_pdVCOM;
    m_iVCOMn = 2;
    m_pdVCOM = new double[m_iVCOMn];
    m_pdVCOM[0] = 4961.000;
    m_pdVCOM[1] = 6754;

    //High VCO settings
    delete m_pdVCOH;
    m_iVCOHn = 2;
    m_pdVCOH = new double[m_iVCOHn];
    m_pdVCOH[0] = 6306.000;
    m_pdVCOH[1] = 7714.000;

    //m_dRefF = 30.720;    //Reference frequency MHz
    m_dMaxF = m_pdVCOH[m_iVCOHn-1]/2.0;  //Max frequency MHz
    m_dMinF = m_pdVCOL[0]/128.0;
    m_dThrF = 5500.000;//Threshold frequency to switch additional divider
}

/** @brief Class destructor.
*/
PLL_SX::~PLL_SX()
{
  delete [] m_pdVCOH;
  delete [] m_pdVCOM;
  delete [] m_pdVCOL;
};

/**
* Find the greatest common divisor of 2 numbers
* See http://en.wikipedia.org/wiki/Greatest_common_divisor
* @param refClk_MHz reference clock, MHz
* @param dDF Desireg frequency, MHz
* @param rdRF Real frequency according to parameters calculated, MHz
* @param Nint Integer division ratio (INT_SDM)
* @param Nfrac Fractional division ratio (FRAC_SDM)
* @param iVCO VCO index (SEL_VCO)
* @param Fvco VCO frequency, MHz
* @param iDInd Divider (real divider is 2^(iDInd+1)), (DIV_LOCH)
* @param iEnDiv2 Additional prescaler control (EN_DIV2_DIVPROG)
* @param EnDiv2mode 0-normal, 1-always on, 2-always off
  @return
    - -1 cannot deliver requested frequency
    - 0 success
    - 1 requested frequency out of range. Set to closest available frequency
*/
int PLL_SX::FreqParams(double refClk_MHz, double dDF, double &rdRF, unsigned &Nint, unsigned &Nfrac, unsigned &iVCO, double &Fvco, unsigned &iDInd, unsigned &iEnDiv2, int EnDiv2mode)
{
    double m_dRefF = refClk_MHz;
    bool canDeliverFrequency = false;
    bool frequencyWithinRange = true;
    iDInd = 0;
    double dMul = 1;
    double dFvco;
    double dFrac;
    double realDF;

    //Check if it is possible to generate desired frequency.
    //Set to limiting values if not.
    if (dDF > m_dMaxF)
    {
       realDF = m_dMaxF;
       frequencyWithinRange = false;
    }
    else if (dDF < m_dMinF)
    {
      realDF = m_dMinF;
      frequencyWithinRange = false;
    }
    else
        realDF = dDF;

    //VCO selection
    //High VCO
    if     ((realDF >= (m_pdVCOH[0]/128.0)) && (realDF <=  (m_pdVCOH[m_iVCOHn-1]/128.0))) { dMul = (double) 128.0; iDInd = 6; iVCO = 2; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOH[0]/64.0))  && (realDF <=  (m_pdVCOH[m_iVCOHn-1]/64.0)))  { dMul = (double) 64.0;  iDInd = 5; iVCO = 2; canDeliverFrequency = true; }
    else if((realDF >= (m_pdVCOH[0]/32.0))  && (realDF <=  (m_pdVCOH[m_iVCOHn-1]/32.0)))  { dMul = (double) 32.0;  iDInd = 4; iVCO = 2; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOH[0]/16.0))  && (realDF <=  (m_pdVCOH[m_iVCOHn-1]/16.0)))  { dMul = (double) 16.0;  iDInd = 3; iVCO = 2; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOH[0]/8.0))   && (realDF <=  (m_pdVCOH[m_iVCOHn-1]/8.0)))   { dMul = (double) 8.0 ;  iDInd = 2; iVCO = 2; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOH[0]/4.0))   && (realDF <=  (m_pdVCOH[m_iVCOHn-1]/4.0)))   { dMul = (double) 4.0 ;  iDInd = 1; iVCO = 2; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOH[0]/2.0))   && (realDF <=  (m_pdVCOH[m_iVCOHn-1]/2.0)))   { dMul = (double) 2.0 ;  iDInd = 0; iVCO = 2; canDeliverFrequency = true;}

    //Middle VCO
    else if((realDF >= (m_pdVCOM[0]/128.0)) && (realDF <=  (m_pdVCOM[m_iVCOMn-1]/128.0))) { dMul = (double) 128.0; iDInd = 6; iVCO = 1; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOM[0]/64.0))  && (realDF <=  (m_pdVCOM[m_iVCOMn-1]/64.0)))  { dMul = (double) 64.0;  iDInd = 5; iVCO = 1; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOM[0]/32.0))  && (realDF <=  (m_pdVCOM[m_iVCOMn-1]/32.0)))  { dMul = (double) 32.0;  iDInd = 4; iVCO = 1; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOM[0]/16.0))  && (realDF <=  (m_pdVCOM[m_iVCOMn-1]/16.0)))  { dMul = (double) 16.0;  iDInd = 3; iVCO = 1; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOM[0]/8.0))   && (realDF <=  (m_pdVCOM[m_iVCOMn-1]/8.0)))   { dMul = (double) 8.0 ;  iDInd = 2; iVCO = 1; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOM[0]/4.0))   && (realDF <=  (m_pdVCOM[m_iVCOMn-1]/4.0)))   { dMul = (double) 4.0 ;  iDInd = 1; iVCO = 1; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOM[0]/2.0))   && (realDF <=  (m_pdVCOM[m_iVCOMn-1]/2.0)))   { dMul = (double) 2.0 ;  iDInd = 0; iVCO = 1; canDeliverFrequency = true;}

    //Low VCO
    else if((realDF >= (m_pdVCOL[0]/128.0)) && (realDF <=  (m_pdVCOL[m_iVCOLn-1]/128.0))) { dMul = (double) 128.0; iDInd = 6; iVCO = 0; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOL[0]/64.0))  && (realDF <=  (m_pdVCOL[m_iVCOLn-1]/64.0)))  { dMul = (double) 64.0;  iDInd = 5; iVCO = 0; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOL[0]/32.0))  && (realDF <=  (m_pdVCOL[m_iVCOLn-1]/32.0)))  { dMul = (double) 32.0;  iDInd = 4; iVCO = 0; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOL[0]/16.0))  && (realDF <=  (m_pdVCOL[m_iVCOLn-1]/16.0)))  { dMul = (double) 16.0;  iDInd = 3; iVCO = 0; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOL[0]/8.0))   && (realDF <=  (m_pdVCOL[m_iVCOLn-1]/8.0)))   { dMul = (double) 8.0 ;  iDInd = 2; iVCO = 0; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOL[0]/4.0))   && (realDF <=  (m_pdVCOL[m_iVCOLn-1]/4.0)))   { dMul = (double) 4.0 ;  iDInd = 1; iVCO = 0; canDeliverFrequency = true;}
    else if((realDF >= (m_pdVCOL[0]/2.0))   && (realDF <=  (m_pdVCOL[m_iVCOLn-1]/2.0)))   { dMul = (double) 2.0 ;  iDInd = 0; iVCO = 0; canDeliverFrequency = true;}

    if(!canDeliverFrequency)
    {
        rdRF = 0;
        return -1;
    }

    //Calculate VCO frequency
    dFvco = dMul * realDF;
    //Fvco = (unsigned)dFvco;
    Fvco = dFvco;

    //Additional presaler control
    if( (dFvco > m_dThrF))
        iEnDiv2 = 1;
    else
        iEnDiv2 = 0;

    // forces change EnDiv2, for testing purposes
    if(EnDiv2mode == 1) //always on
        iEnDiv2 = 1;
    else if(EnDiv2mode == 2) // always off
        iEnDiv2 = 0;

    //Integer division
    Nint = unsigned(double(dFvco/(m_dRefF * pow(2.0, iEnDiv2)))) - 4;

    //Fractional division
//    dFrac = dFvco/m_dRefF - unsigned(dFvco/m_dRefF);
//    Nfrac = dFrac * pow(2, 20);
//    Nfrac = Nfrac >> iEnDiv2;

    dFrac = dFvco/(m_dRefF * pow(2.0, iEnDiv2)) - unsigned(dFvco/(m_dRefF * pow(2.0, iEnDiv2)));
    Nfrac = dFrac * pow(2, 20);
    //Nfrac = Nfrac >> iEnDiv2;


    //Calculate real frequency according to the calculated parameters
    rdRF = m_dRefF * (1.0/dMul) * (((double)Nint + (double)Nfrac/(double)pow(2, 20)) + 4.0) * (double)pow(2, iEnDiv2);
    if(frequencyWithinRange)
        return 0;
    else
        return 1;
};

/** @brief Returns real frequency in MHz according to given parameters
*/
double PLL_SX::CalculateRealFrequency(double refClk_MHz, double dMul, int Nint, int Nfrac, int iEnDiv2)
{
    double rdRF = refClk_MHz * (1.0/dMul) * (((double)Nint + (double)Nfrac/(double)pow(2, 20)) + 4.0) * (double)pow(2, iEnDiv2);
    return rdRF;
}

vector<double> PLL_SX::GetVCOHFrequencies() const
{
    vector<double> temp;
    for(unsigned i=0; i<m_iVCOHn; ++i)
        temp.push_back(m_pdVCOH[i]);
    return temp;
}

vector<double> PLL_SX::GetVCOMFrequencies() const
{
    vector<double> temp;
    for(unsigned i=0; i<m_iVCOMn; ++i)
        temp.push_back(m_pdVCOM[i]);
    return temp;
}

vector<double> PLL_SX::GetVCOLFrequencies() const
{
    vector<double> temp;
    for(unsigned i=0; i<m_iVCOLn; ++i)
        temp.push_back(m_pdVCOL[i]);
    return temp;
}

void PLL_SX::SetVCOHFrequencies(double *frequencies, unsigned int f_count)
{
    if(m_pdVCOH)
        delete []m_pdVCOH;
    m_pdVCOH = new double[f_count];
    m_iVCOHn = f_count;
    for(unsigned i=0; i<f_count; ++i)
        m_pdVCOH[i] = frequencies[i];

    if(m_iVCOHn > 0)
        m_dMaxF = m_pdVCOH[m_iVCOHn-1]/2.0;  //Max frequency MHz
}

void PLL_SX::SetVCOMFrequencies(double *frequencies, unsigned int f_count)
{
    if(m_pdVCOM)
        delete []m_pdVCOM;
    m_pdVCOM = new double[f_count];
    m_iVCOMn = f_count;
    for(unsigned i=0; i<f_count; ++i)
        m_pdVCOM[i] = frequencies[i];
}

void PLL_SX::SetVCOLFrequencies(double *frequencies, unsigned int f_count)
{
    if(m_pdVCOL)
        delete []m_pdVCOL;
    m_pdVCOL = new double[f_count];
    m_iVCOLn = f_count;
    for(unsigned i=0; i<f_count; ++i)
        m_pdVCOL[i] = frequencies[i];

    if(m_iVCOLn > 0)
        m_dMinF = m_pdVCOL[0]/128.0;
}

bool PLL_SX::SaveToFile(const char* filename)
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
    freqs = GetVCOHFrequencies();
    fout << "[VCOH] count: " << freqs.size() << "," << endl;
    for(unsigned i=0; i<freqs.size(); ++i)
        fout << freqs[i] << ' ' << "GHz," << endl;

    freqs.clear();
    freqs = GetVCOMFrequencies();
    fout << "[VCOM] count: " << freqs.size() << ","  << endl;
    for(unsigned i=0; i<freqs.size(); ++i)
        fout << freqs[i] << ' ' << "GHz," << endl;

    freqs.clear();
    freqs = GetVCOLFrequencies();
    fout << "[VCOL] count: " << freqs.size() << ","  << endl;
    for(unsigned i=0; i<freqs.size(); ++i)
        fout << freqs[i] << ' ' << "GHz," << endl;

    fout.close();
    return true;
}

/** @brief Loads VCOH VCOM VCOL values from file
    @param filename source file
    @return true on success
*/
bool PLL_SX::LoadFromFile(const char* filename)
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
        if(strcmp(vconame, "[VCOH]") == 0)
        {
            frequencies.clear();
            for(int i=0; i<freqCount; ++i)
            {
                fin.getline(cline, lineLen);
                sscanf(cline, "%lf %s", &freq, ctemp);
                frequencies.push_back(freq*1000); //GHz in file, MHz in variables
            }
            SetVCOHFrequencies(&frequencies[0], frequencies.size());
        }
        if(strcmp(vconame, "[VCOM]") == 0)
        {
            frequencies.clear();
            for(int i=0; i<freqCount; ++i)
            {
                fin.getline(cline, lineLen);
                sscanf(cline, "%lf %s", &freq, ctemp);
                frequencies.push_back(freq*1000);
            }
            SetVCOMFrequencies(&frequencies[0], frequencies.size());
        }
        if(strcmp(vconame, "[VCOL]") == 0)
        {
            frequencies.clear();
            for(int i=0; i<freqCount; ++i)
            {
                fin.getline(cline, lineLen);
                sscanf(cline, "%lf %s", &freq, ctemp);
                frequencies.push_back(freq*1000);
            }
            SetVCOLFrequencies(&frequencies[0], frequencies.size());
        }
        vconame[0] = 0;
    }
    fin.close();
    return true;
}
