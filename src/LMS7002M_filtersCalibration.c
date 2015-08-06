/*!
 * This is a C port of filter calibration implementations from the lms7api C++ project.
 */

#include "LMS7002M_lms7api.h"

#include <math.h> //pow

const float_type gLadder_lower_limit = 2;
const float_type gLadder_higher_limit = 16;
const float_type gRealpole_lower_limit = 0.8;
const float_type gRealpole_higher_limit = 3.2;
const float_type gHighband_lower_limit = 28;
const float_type  gHighband_higher_limit = 70;

const float_type gRxTIA_higher_limit = 60;
const float_type gRxTIA_lower_limit_g1 = 1.5;
const float_type gRxTIA_lower_limit_g23 = 0.5;
const float_type gRxLPF_low_lower_limit = 1;
const float_type gRxLPF_low_higher_limit = 20;
const float_type gRxLPF_high_lower_limit = 20;
const float_type gRxLPF_high_higher_limit = 70;

liblms7_status TuneTxFilterSetup(LMS7002M_t *self, TxFilter type, float_type cutoff_MHz)
{
    Modify_SPI_Reg_bits(self, LMS7param(EN_G_RFE), 0);
    Modify_SPI_Reg_bits(self, LMS7param(EN_G_TRF), 0);

    //RBB
    SetDefaults(self, RBB);
    Modify_SPI_Reg_bits(self, LMS7param(PD_LPFL_RBB), 1);
    Modify_SPI_Reg_bits(self, LMS7param(INPUT_CTL_PGA_RBB), 3);
    Modify_SPI_Reg_bits(self, LMS7param(ICT_PGA_OUT_RBB), 20);
    Modify_SPI_Reg_bits(self, LMS7param(ICT_PGA_IN_RBB), 20);
    Modify_SPI_Reg_bits(self, LMS7param(C_CTL_PGA_RBB), 3);

    //TBB
    SetDefaults(self, TBB);
    Modify_SPI_Reg_bits(self, LMS7param(CG_IAMP_TBB), 1);
    Modify_SPI_Reg_bits(self, LMS7param(ICT_IAMP_FRP_TBB), 1);
    Modify_SPI_Reg_bits(self, LMS7param(ICT_IAMP_GG_FRP_TBB), 6);

    //AFE
    uint8_t isel_dac_afe = (uint8_t)Get_SPI_Reg_bits_(self, 0x0082, 15, 13);
    SetDefaults(self, AFE);
    if (Get_SPI_Reg_bits(self, LMS7param(MAC)) == 2)
    {
        Modify_SPI_Reg_bits(self, LMS7param(PD_TX_AFE2), 0); //PD_RX_AFE2 0
        Modify_SPI_Reg_bits(self, LMS7param(PD_RX_AFE2), 0); //PD_RX_AFE2 0
    }
    Modify_SPI_Reg_bits_(self, 0x0082, 15, 13, isel_dac_afe);

    //BIAS
    uint8_t rpcalib_bias = (uint8_t)Get_SPI_Reg_bits(self, LMS7param(RP_CALIB_BIAS));
    SetDefaults(self, BIAS);
    Modify_SPI_Reg_bits(self, LMS7param(RP_CALIB_BIAS), rpcalib_bias);

    //XBUF
    Modify_SPI_Reg_bits(self, LMS7param(PD_XBUF_RX), 0);
    Modify_SPI_Reg_bits(self, LMS7param(PD_XBUF_TX), 0);
    Modify_SPI_Reg_bits(self, LMS7param(EN_G_XBUF), 1);

    //CGEN
    SetDefaults(self, CGEN);

    //txtsp
    SetDefaults(self, TxTSP);
    Modify_SPI_Reg_bits(self, LMS7param(TSGMODE_TXTSP), 1);
    Modify_SPI_Reg_bits(self, LMS7param(INSEL_TXTSP), 1);
    Modify_SPI_Reg_bits_(self, 0x0208, 6, 4, 7);
    LoadDC_REG_IQ(self, Tx, (int16_t)0x7FFF, (int16_t)0x8000);
    float_type txNCOfreq = 0.05;
    SetNCOFrequency(self, Tx, 0, txNCOfreq);

    //rxtsp
    SetDefaults(self, RxTSP);    
    SetNCOFrequency(self, Rx, 0, txNCOfreq - 1);

    Modify_SPI_Reg_bits(self, LMS7param(AGC_MODE_RXTSP), 1);
    Modify_SPI_Reg_bits_(self, 0x040C, 6, 3, 0x07);

    Modify_SPI_Reg_bits(self, LMS7param(AGC_AVG_RXTSP), 7);
    Modify_SPI_Reg_bits(self, LMS7param(CMIX_GAIN_RXTSP), 1);

    return LIBLMS7_SUCCESS;
}

liblms7_status TuneTxFilter(LMS7002M_t *self, TxFilter type, float_type cutoff_MHz)
{   
    liblms7_status status;
    float_type lowLimit = 0;
    float_type highLimit = 1000;
    uint32_t rssi = 0;
    int8_t dir;
    uint8_t ccal_lpflad_tbb;
    uint32_t rssi_value_100k;
    int16_t rcal;

    float_type ncoFreq = 0.05;
    float_type cgenFreq;
    uint8_t loopb_tbb;
    uint8_t cg_iamp_tbb = 1;
    uint8_t bypladder_tbb;
    uint8_t pd_lpfh_tbb;
    uint8_t pd_lpflad_tbb;
    uint8_t pd_lpfs5;
    uint8_t en_g_tbb = 1;
    uint8_t pd_iamp_tbb = 0;
    uint8_t tstin_tbb = 0;

    BackupAllRegisters(self);    
    //float_type userCLKGENfreq = GetFrequencyCGEN_MHz();

    status = TuneTxFilterSetup(self, type, cutoff_MHz);
    if (status != LIBLMS7_SUCCESS)
        goto TxFilterTuneEnd;    
    cgenFreq = cutoff_MHz * 20;
    if (cgenFreq < 60)
        cgenFreq = 60;
    if (cgenFreq > 640)
        cgenFreq = 640;
    if (type == TX_LADDER)
    {
        loopb_tbb = 2;
        bypladder_tbb = 0;
        pd_lpfh_tbb = 1;
        pd_lpflad_tbb = 0;
        pd_lpfs5 = 1;
        lowLimit = gLadder_lower_limit;
        highLimit = gLadder_higher_limit;
    }
    else if (type == TX_REALPOLE)
    {
        loopb_tbb = 3;
        bypladder_tbb = 1;
        pd_lpfh_tbb = 1;
        pd_lpflad_tbb = 1;
        pd_lpfs5 = 0;
        lowLimit = gRealpole_lower_limit;
        highLimit = gRealpole_higher_limit;
    }
    else if (type == TX_HIGHBAND)
    {
        loopb_tbb = 3;
        bypladder_tbb = 0;
        pd_lpfh_tbb = 0;
        pd_lpflad_tbb = 1;
        pd_lpfs5 = 1;
        lowLimit = gHighband_lower_limit;
        highLimit = gHighband_higher_limit;
    }
    if (cutoff_MHz == cgenFreq / 16)
        cgenFreq -= 10;

    if (cutoff_MHz < lowLimit || cutoff_MHz > highLimit)
    {
        status = LIBLMS7_FREQUENCY_OUT_OF_RANGE;
        goto TxFilterTuneEnd;
    }

    status = SetFrequencyCGEN(self, cgenFreq);
    if (status != LIBLMS7_SUCCESS)
        goto TxFilterTuneEnd;

    Modify_SPI_Reg_bits(self, LMS7param(LOOPB_TBB), loopb_tbb);
    Modify_SPI_Reg_bits(self, LMS7param(CG_IAMP_TBB), cg_iamp_tbb);
    Modify_SPI_Reg_bits(self, LMS7param(BYPLADDER_TBB), bypladder_tbb);
    Modify_SPI_Reg_bits(self, LMS7param(TSTIN_TBB), tstin_tbb);
    Modify_SPI_Reg_bits(self, LMS7param(PD_LPFH_TBB), pd_lpfh_tbb);
    Modify_SPI_Reg_bits(self, LMS7param(PD_LPFIAMP_TBB), pd_iamp_tbb);
    Modify_SPI_Reg_bits(self, LMS7param(PD_LPFLAD_TBB), pd_lpflad_tbb);
    Modify_SPI_Reg_bits(self, LMS7param(PD_LPFS5_TBB), pd_lpfs5);
    Modify_SPI_Reg_bits(self, LMS7param(EN_G_TBB), en_g_tbb);

    //B
    //LADDER coefficients
    float_type p1, p2, p3, p4, p5;
    switch (type)
    {
    case TX_LADDER:
        p1 = 1.29858903647958E-16;
        p2 = -0.000110746929967704;
        p3 = 0.00277593485991029;
        p4 = 21.0384293169607;
        p5 = -48.4092606238297;
        break;
    case TX_REALPOLE:
        p1 = 1.93821841029921E-15;
        p2 = -0.0429694461214244;
        p3 = 0.253501254059498;
        p4 = 88.9545445989649;
        p5 = -48.0847491316861;
        break;
    case TX_HIGHBAND:
        p1 = 1.10383E-06;
        p2 = -0.0002108;
        p3 = 0.019049487;
        p4 = 1.433174459;
        p5 = -47.69507793;
        break;
    }
    rcal = (int16_t)(pow(cutoff_MHz, 4)*p1 + pow(cutoff_MHz, 3)*p2 + pow(cutoff_MHz, 2)*p3 + cutoff_MHz * p4 + p5);
    if (rcal < 0)
        rcal = 0;
    if (rcal > 255)
        rcal = 255;

    if (type == TX_REALPOLE)
        Modify_SPI_Reg_bits(self, LMS7param(RCAL_LPFS5_TBB), rcal);
    else if (type == TX_LADDER)
        Modify_SPI_Reg_bits(self, LMS7param(RCAL_LPFLAD_TBB), rcal);
    else if (type == TX_HIGHBAND)
        Modify_SPI_Reg_bits(self, LMS7param(RCAL_LPFH_TBB), rcal);

    FilterTuning_AdjustGains(self);

    rssi_value_100k = GetRSSI(self)*0.707;

    SetNCOFrequency(self, Tx, 0, cutoff_MHz);
    SetNCOFrequency(self, Rx, 0, cutoff_MHz - 1);

    //SaveConfig("BeforeCsearch.ini");

    for (ccal_lpflad_tbb = 31; ccal_lpflad_tbb > 0; --ccal_lpflad_tbb)
    {
        Modify_SPI_Reg_bits(self, LMS7param(CCAL_LPFLAD_TBB), ccal_lpflad_tbb);
        rssi = GetRSSI(self);
        if (rssi > rssi_value_100k && ccal_lpflad_tbb == 31)
            break; //skip this search, continue to advanced search
        if (rssi > rssi_value_100k)
        {
            status = LIBLMS7_SUCCESS;
            goto TxFilterTuneEnd; //found correct value
        }
    }


    //advanced search for c and r values
    status = LIBLMS7_FAILURE;
    dir = ccal_lpflad_tbb == 31 ? -1 : 1;
    while (rcal > 0 && rcal < 255)
    {
        rcal += 5 * dir;
        if (rcal < 0 && rcal > 255)
            break;
        if (type == TX_REALPOLE)
            Modify_SPI_Reg_bits(self, LMS7param(RCAL_LPFS5_TBB), rcal);
        else if (type == TX_LADDER)
            Modify_SPI_Reg_bits(self, LMS7param(RCAL_LPFLAD_TBB), rcal);
        else if (type == TX_HIGHBAND)
            Modify_SPI_Reg_bits(self, LMS7param(RCAL_LPFH_TBB), rcal);
        SetNCOFrequency(self, Tx, 0, ncoFreq);
        SetNCOFrequency(self, Rx, 0, ncoFreq - 1);
        Modify_SPI_Reg_bits(self, LMS7param(CCAL_LPFLAD_TBB), 16);
        rssi_value_100k = GetRSSI(self);
        SetNCOFrequency(self, Tx, 0, cutoff_MHz);
        SetNCOFrequency(self, Rx, 0, cutoff_MHz - 1);
        for (ccal_lpflad_tbb = 31; ccal_lpflad_tbb > 0; --ccal_lpflad_tbb)
        {
            Modify_SPI_Reg_bits(self, LMS7param(CCAL_LPFLAD_TBB), ccal_lpflad_tbb);
            rssi = GetRSSI(self);
            if (rssi > rssi_value_100k*0.707 && ccal_lpflad_tbb == 31)
                break; //skip c search, need to change r value
            if (rssi > rssi_value_100k*0.707)
            {
                status = LIBLMS7_SUCCESS;
                goto TxFilterTuneEnd;
            }
        }
    }

    //end
TxFilterTuneEnd:
    RestoreAllRegisters(self);
    if (status != LIBLMS7_SUCCESS)
        return status;    
    Modify_SPI_Reg_bits(self, LMS7param(CCAL_LPFLAD_TBB), ccal_lpflad_tbb);
    Modify_SPI_Reg_bits(self, LMS7param(ICT_IAMP_FRP_TBB), 1);
    Modify_SPI_Reg_bits(self, LMS7param(ICT_IAMP_GG_FRP_TBB), 6);

    if (type == TX_REALPOLE)
        Modify_SPI_Reg_bits(self, LMS7param(RCAL_LPFS5_TBB), rcal);
    else if (type == TX_LADDER)
        Modify_SPI_Reg_bits(self, LMS7param(RCAL_LPFLAD_TBB), rcal);
    else if (type == TX_HIGHBAND)
        Modify_SPI_Reg_bits(self, LMS7param(RCAL_LPFH_TBB), rcal);
    return LIBLMS7_SUCCESS;
}

void FilterTuning_AdjustGains(LMS7002M_t *self)
{
    uint8_t cg_iamp_tbb;
    uint32_t rssi = 0;
    const uint32_t rssi_required = 0x8400;
    uint8_t g_pga_rbb = (uint8_t)Get_SPI_Reg_bits(self, LMS7param(G_PGA_RBB));

    while (g_pga_rbb < 31)
    {
        cg_iamp_tbb = 0;
        while (cg_iamp_tbb < 63 && rssi < rssi_required)
        {
            Modify_SPI_Reg_bits(self, LMS7param(CG_IAMP_TBB), cg_iamp_tbb);
            rssi = GetRSSI(self);
            if (rssi > rssi_required)
                return;
            ++cg_iamp_tbb;
        }
        g_pga_rbb += 6;
        if (g_pga_rbb > 31)
            g_pga_rbb = 31;
        Modify_SPI_Reg_bits(self, LMS7param(G_PGA_RBB), g_pga_rbb);
    }
}

liblms7_status TuneTxFilterLowBandChain(LMS7002M_t *self, float_type bandwidth, float_type realpole_MHz)
{
    uint32_t rssi;
    uint32_t rssi_value_10k;
    bool prevRSSIbigger;
    int16_t rcal;
    float_type p1,p2,p3,p4,p5;
    float_type ncoFreq = 0.05;
    float_type cgenFreq;
    BackupAllRegisters(self);

    liblms7_status status = TuneTxFilter(self, TX_LADDER, bandwidth);
    uint8_t ladder_c_value = (uint8_t)Get_SPI_Reg_bits(self, LMS7param(CCAL_LPFLAD_TBB));
    uint8_t ladder_r_value = (uint8_t)Get_SPI_Reg_bits(self, LMS7param(RCAL_LPFLAD_TBB));
    status = TuneTxFilterSetup(self, TX_LADDER, bandwidth);

    if (bandwidth < gLadder_lower_limit || bandwidth > gLadder_higher_limit)
        goto TxFilterLowBandChainEnd;

    //realpole calibration
    //float userCLKGENfreq = GetFrequencyCGEN();

    cgenFreq = realpole_MHz * 20;
    if (cgenFreq < 60)
        cgenFreq = 60;
    if (cgenFreq > 640)
        cgenFreq = 640;

    if (realpole_MHz < gRealpole_lower_limit || realpole_MHz > gRealpole_higher_limit)
    {
        status = LIBLMS7_FREQUENCY_OUT_OF_RANGE;
        goto TxFilterLowBandChainEnd;
    }

    status = SetFrequencyCGEN(self, cgenFreq);
    if (status != LIBLMS7_SUCCESS)
        goto TxFilterLowBandChainEnd;

    Modify_SPI_Reg_bits(self, LMS7param(LOOPB_TBB), 3);
    Modify_SPI_Reg_bits(self, LMS7param(CG_IAMP_TBB), 1);
    Modify_SPI_Reg_bits(self, LMS7param(BYPLADDER_TBB), 1);
    Modify_SPI_Reg_bits(self, LMS7param(TSTIN_TBB), 0);
    Modify_SPI_Reg_bits(self, LMS7param(PD_LPFH_TBB), 1);
    Modify_SPI_Reg_bits(self, LMS7param(PD_LPFIAMP_TBB), 0);
    Modify_SPI_Reg_bits(self, LMS7param(PD_LPFLAD_TBB), 1);
    Modify_SPI_Reg_bits(self, LMS7param(PD_LPFS5_TBB), 0);
    Modify_SPI_Reg_bits(self, LMS7param(EN_G_TBB), 1);

    //B
    p1 = 1.93821841029921E-15;
    p2 = -0.0429694461214244;
    p3 = 0.253501254059498;
    p4 = 88.9545445989649;
    p5 = -48.0847491316861;
    rcal = (int16_t)(pow(realpole_MHz, 4)*p1 + pow(realpole_MHz, 3)*p2 + pow(realpole_MHz, 2)*p3 + realpole_MHz * p4 + p5);
    if (rcal < 0)
        rcal = 0;
    if (rcal > 255)
        rcal = 255;
    Modify_SPI_Reg_bits(self, LMS7param(RCAL_LPFS5_TBB), rcal);

    FilterTuning_AdjustGains(self);

    rssi_value_10k = GetRSSI(self);
    SetNCOFrequency(self, Tx, 0, realpole_MHz);
    SetNCOFrequency(self, Rx, 0, realpole_MHz - 1);

    prevRSSIbigger = GetRSSI(self) > rssi_value_10k*0.707;
    status = LIBLMS7_FAILURE; //assuming r value is not found
    while (rcal >= 0 && rcal < 256)
    {
        Modify_SPI_Reg_bits(self, LMS7param(RCAL_LPFS5_TBB), rcal);
        SetNCOFrequency(self, Tx, 0, ncoFreq);
        SetNCOFrequency(self, Rx, 0, ncoFreq - 1);
        rssi_value_10k = GetRSSI(self)*0.707;

        SetNCOFrequency(self, Tx, 0, realpole_MHz);
        SetNCOFrequency(self, Rx, 0, realpole_MHz - 1);

        rssi = GetRSSI(self);
        if (rssi > rssi_value_10k)
            --rcal;
        else
        {
            if (prevRSSIbigger)
            {
                --rcal;
                status = LIBLMS7_SUCCESS;
                goto TxFilterLowBandChainEnd;
            }
            ++rcal;
        }
        prevRSSIbigger = rssi > rssi_value_10k;
    }

    //end
TxFilterLowBandChainEnd:
    RestoreAllRegisters(self);    
    if (status != LIBLMS7_SUCCESS)
        return status;

    Modify_SPI_Reg_bits(self, LMS7param(CCAL_LPFLAD_TBB), ladder_c_value);
    Modify_SPI_Reg_bits(self, LMS7param(RCAL_LPFLAD_TBB), ladder_r_value);
    Modify_SPI_Reg_bits(self, LMS7param(ICT_IAMP_FRP_TBB), 1);
    Modify_SPI_Reg_bits(self, LMS7param(ICT_IAMP_GG_FRP_TBB), 6);
    Modify_SPI_Reg_bits(self, LMS7param(RCAL_LPFS5_TBB), rcal);

    return LIBLMS7_SUCCESS;
}
