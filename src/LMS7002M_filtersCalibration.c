/*!
 * This is a C port of filter calibration implementations from the lms7api C++ project.
 */

#include "LMS7002M_lms7api.h"

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
