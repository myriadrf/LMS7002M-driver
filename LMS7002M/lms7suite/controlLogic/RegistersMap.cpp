/**
@file	RegistersMap.cpp
@author	Lime Microsystems
@brief 	Class for modifying LMS7002Mr2 registers
*/

#include "RegistersMap.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ConnectionManager.h"
#include "../CommonUtilities.h"
#include <string.h>
#include "MessageLog.h"
using namespace std;

unsigned short makeMask(int msb, int lsb)
{
    unsigned short mask;
    mask = ~(0xFFFF << (msb-lsb));
    mask = mask << lsb;
    return mask;
}

/** @brief Defines all parameter addresses, default values and positions inside registers
*/
void RegistersMap::InitializeControlParameters()
{
    //NCO
    m_parameters[SEL_TX].Set(0x0240, 0, 4, 1, true, "SEL_TX");
    m_parameters[MODE_TX].Set(0x0240, 0, 1, 0, true, "MODE_TX");
    m_parameters[DTHBIT_TX].Set(0x0240, 1, 4, 5, true, "DTHBIT_TX");

    m_parameters[SEL_RX].Set(0x0440, 0, 4, 1, true, "SEL_RX");
    m_parameters[MODE_RX].Set(0x0440, 0, 1, 0, true, "MODE_RX");
    m_parameters[DTHBIT_RX].Set(0x0440, 1, 4, 5, true, "DTHBIT_RX");

    //RFE
    m_parameters[PD_LNA_RFE].Set        (0x010c, 1, 1, 7, true, "PD_LNA_RFE");
    m_parameters[PD_RLOOPB_1_RFE].Set   (0x010c, 1, 1, 6, true, "PD_RLOOPB_1_RFE");
    m_parameters[PD_RLOOPB_2_RFE].Set   (0x010c, 1, 1, 5, true, "PD_RLOOPB_2_RFE");
    m_parameters[PD_MXLOBUF_RFE].Set    (0x010c, 1, 1, 4, true, "PD_MXLOBUF_RFE");
    m_parameters[PD_QGEN_RFE].Set       (0x010c, 1, 1, 3, true, "PD_QGEN_RFE");
    m_parameters[PD_RSSI_RFE].Set       (0x010c, 1, 1, 2, true, "PD_RSSI_RFE");
    m_parameters[PD_TIA_RFE].Set        (0x010c, 0, 1, 1, true, "PD_TIA_RFE");
    m_parameters[EN_G_RFE].Set          (0x010c, 1, 1, 0, true, "EN_G_RFE");
    m_parameters[SEL_PATH_RFE].Set      (0x010d, 1, 2, 7, true, "SEL_PATH_RFE");
    m_parameters[EN_DCOFF_RXFE_RFE].Set (0x010d, 0, 1, 6, true, "EN_DCOFF_RXFE");
    m_parameters[EN_INSHSW_LB1_RFE].Set (0x010d, 1, 1, 4, true, "EN_INSHSW_LB1_RFE");
    m_parameters[EN_INSHSW_LB2_RFE].Set (0x010d, 1, 1, 3, true, "EN_INSHSW_LB2_RFE");
    m_parameters[EN_INSHSW_L_RFE].Set   (0x010d, 1, 1, 2, true, "EN_INSHSW_L_RFE");
    m_parameters[EN_INSHSW_W_RFE].Set   (0x010d, 1, 1, 1, true, "EN_INSHSW_W_RFE");
    m_parameters[EN_NEXTRX_RFE].Set     (0x010d, 0, 1, 0, true, "EN_NEXTRX_RFE");
    m_parameters[DCOFFI_RFE].Set(0x010e, 64, 7, 7, true, "DCOFFI_RFE");
    m_parameters[DCOFFQ_RFE].Set(0x010e, 64, 7, 0, true, "DCOFFQ_RFE");
    m_parameters[ICT_LOOPB_RFE].Set     (0x010f, 12, 5, 10, true, "ICT_LOOPB_RFE");
    m_parameters[ICT_TIAMAIN_RFE].Set   (0x010f, 12, 5, 5, true, "ICT_TIAMAIN_RFE");
    m_parameters[ICT_TIAOUT_RFE].Set    (0x010f, 12, 5, 0, true, "ICT_TIAOUT_RFE");
    m_parameters[ICT_LNACMO_RFE].Set(0x0110, 2, 5, 10, true, "ICT_LNACMO_RFE");
    m_parameters[ICT_LNA_RFE].Set   (0x0110, 12, 5, 5, true, "ICT_LNA_RFE");
    m_parameters[ICT_LODC_RFE].Set  (0x0110, 20, 5, 0, true, "ICT_LODC_RFE");
    m_parameters[CAP_RXMXO_RFE].Set(0x0111, 4, 5, 5, true, "CAP_RXMXO_RFE");
    m_parameters[CGSIN_LNA_RFE].Set(0x0111, 3, 5, 0, true, "CGSIN_LNA_RFE");
    m_parameters[CCOMP_TIA_RFE].Set (0x0112, 12, 4, 12, true, "CCOMP_TIA_RFE");
    m_parameters[CFB_TIA_RFE].Set   (0x0112, 230, 12, 0, true, "CFB_TIA_RFE");
    m_parameters[G_LNA_RFE].Set     (0x0113, 15, 4, 6, true, "G_LNA_RFE");
    m_parameters[G_RXLOOPB_RFE].Set (0x0113, 0, 4, 2, true, "G_RXLOOPB_RFE");
    m_parameters[G_TIA_RFE].Set     (0x0113, 3, 2, 0, true, "G_TIA_RFE");
    m_parameters[RCOMP_TIA_RFE].Set (0x0114, 4, 4, 5, true, "RCOMP_TIA_RFE");
    m_parameters[RFB_TIA_RFE].Set   (0x0114, 13, 5, 0, true, "RFB_TIA_RFE");

    //RBB
    m_parameters[EN_LB_LPFH_RBB].Set(0x0115, 0, 1, 15, true, "EN_LB_LPFH_RBB");
    m_parameters[EN_LB_LPFL_RBB].Set(0x0115, 0, 1, 14, true, "EN_LB_LPFL_RBB");
    m_parameters[PD_LPFH_RBB].Set(0x0115, 1, 1, 3, true, "PD_LPFH_RBB");
    m_parameters[PD_LPFL_RBB].Set(0x0115, 0, 1, 2, true, "PD_LPFL_RBB");
    m_parameters[PD_PGA_RBB].Set(0x0115, 0, 1, 1, true, "PD_PGA_RBB");
    m_parameters[EN_G_RBB].Set(0x0115, 1, 1, 0, true, "EN_G_RBB");
    m_parameters[R_CTL_LPF_RBB].Set(0x0116, 16, 5, 11, true, "R_CTL_LPF_RBB");
    m_parameters[RCC_CTL_LPFH_RBB].Set(0x0116, 1, 3, 8, true, "RCC_CTL_LPFH_RBB");
    m_parameters[C_CTL_LPFH_RBB].Set(0x0116, 128, 8, 0, true, "C_CTL_LPFH_RBB");
    m_parameters[RCC_CTL_LPFL_RBB].Set(0x0117, 5, 3, 11, true, "RCC_CTL_LPFL_RBB");
    m_parameters[C_CTL_LPFL_RBB].Set(0x0117, 12, 11, 0, true, "C_CTL_LPFL_RBB");
    m_parameters[INPUT_CTL_PGA_RBB].Set(0x0118, 0, 3, 13, true, "INPUT_CTL_PGA_RBB");
    m_parameters[ICT_LPF_IN_RBB].Set(0x0118, 12, 5, 5, true, "ICT_LPF_IN_RBB");
    m_parameters[ICT_LPF_OUT_RBB].Set(0x0118, 12, 5, 0, true, "ICT_LPF_OUT_RBB");
    m_parameters[OSW_PGA_RBB].Set(0x0119, 0, 1, 15, true, "OSW_PGA_RBB");
    m_parameters[ICT_PGA_IN_RBB].Set(0x0119, 6, 5, 5, true, "ICT_PGA_IN_RBB");
    m_parameters[ICT_PGA_OUT_RBB].Set(0x0119, 6, 5, 10, true, "ICT_PGA_OUT_RBB");
    m_parameters[G_PGA_RBB].Set(0x0119, 11, 5, 0, true, "G_PGA_RBB");
    m_parameters[C_CTL_PGA_RBB].Set(0x011a, 2, 7, 0, true, "C_CTL_PGA_RBB");
    m_parameters[RCC_CTL_PGA_RBB].Set(0x011a, 23, 5, 9, true, "RCC_CTL_PGA_RBB");


    //TRF
    m_parameters[EN_AMPHF_PDET_TRF].Set(0x0100, 3, 2, 12, true, "EN_AMPHF_PDET_TRF");
    m_parameters[EN_G_TRF].Set(0x0100, 1, 1, 0, true, "EN_G_TRF");
    m_parameters[EN_LOOPB_TXPAD_TRF].Set(0x0101, 0, 1, 0, true, "EN_LOOPB_TXPAD");
    m_parameters[EN_LOWBWLOMX_TMX_TRF].Set(0x0100, 0, 1, 15, true, "EN_LOWBWLOMX_TMX_TRF");
    m_parameters[EN_NEXTTX_TRF].Set(0x0100, 0, 1, 14, true, "EN_NEXTTX_TRF");
    m_parameters[LOADR_PDET_TRF].Set(0x0100, 1, 2, 10, true, "LOADR_PDET_TRF");
    m_parameters[PD_PDET_TRF].Set(0x0100, 1, 1, 3, true, "PD_PDET_TRF");
    m_parameters[PD_TLOBUF_TRF].Set(0x0100, 0, 1, 2, true, "PD_TLOBUF_TRF");
    m_parameters[PD_TXPAD_TRF].Set(0x0100, 0, 1, 1, true, "PD_TXPAD_TRF");
    m_parameters[F_TXPAD_TRF].Set(0x0101, 3, 3, 13, true, "F_TXPAD_TRF");
    m_parameters[LOSS_LIN_TXPAD_TRF].Set(0x0101, 0, 5, 6, true, "LOSS_LIN_TXPADD_TRF");
    m_parameters[LOSS_MAIN_TXPAD_TRF].Set(0x0101, 0, 5, 1, true, "LOSS_MAIN_TXPAD_TRF");
    m_parameters[L_LOOPB_TXPAD_TRF].Set(0x0101, 3, 2, 11, true, "L_LOOPB_TXPAD_TRF");
    m_parameters[GCAS_GNDREF_TXPAD_TRF].Set(0x0102, 0, 1, 15, true, "GCAS_GNDREF_TXPAD_TRF");
    m_parameters[ICT_LIN_TXPAD_TRF].Set(0x0102, 12, 5, 10, true, "ICT_LIN_TXPAD_TRF");
    m_parameters[ICT_MAIN_TXPAD_TRF].Set(0x0102, 12, 5, 5, true, "ICT_MAIN_TXPAD_TRF");
    m_parameters[VGCAS_TXPAD_TRF].Set(0x0102, 0, 5, 0, true, "VGCAS_TXPAD_TRF");
    m_parameters[LOBIASN_TXM_TRF].Set(0x0103, 16, 5, 5, true, "LOBIASN_TXM_TRF");
    m_parameters[LOBIASP_TXX_TRF].Set(0x0103, 18, 5, 0, true, "LOBIASP_TXX_TRF");
    m_parameters[SEL_BAND1_TRF].Set(0x0103, 1, 1, 11, true, "SEL_BAND1_TRF");
    m_parameters[SEL_BAND2_TRF].Set(0x0103, 0, 1, 10, true, "SEL_BAND2_TRF");

    //TBB
    m_parameters[BYPLADDER_TBB].Set(0x010a, 0, 1, 13, true, "BYPLADDER_TBB");
    m_parameters[CCAL_LPFLAD_TBB].Set(0x010a, 16, 5, 8, true, "CCAL_LPFLAD_TBB");
    m_parameters[CG_IAMP_TBB].Set(0x0108, 37, 6, 10, true, "CG_IAMP_TBB");
    m_parameters[EN_G_TBB].Set(0x0105, 1, 1, 0, true, "EN_G_TBB");
    m_parameters[ICT_IAMP_FRP_TBB].Set(0x0108, 12, 5, 5, true, "ICT_IAMP_FRP_TBB");
    m_parameters[ICT_IAMP_GG_FRP_TBB].Set(0x0108, 12, 5, 0, true, "ICT_IAMP_GG_FRP_TBB");
    m_parameters[ICT_LPFH_F_TBB].Set(0x0107, 12, 5, 10, true, "ICT_LPFH_F_TBB");
    m_parameters[ICT_LPFLAD_F_TBB].Set(0x0107, 12, 5, 5, true, "ICT_LPFLAD_F_TBB");
    m_parameters[ICT_LPFLAD_PT_TBB].Set(0x0107, 12, 5, 0, true, "ICT_LPFLAD_PT_TBB");
    m_parameters[ICT_LPFS5_F_TBB].Set(0x0106, 12, 5, 10, true, "ICT_LPFS5_F_TBB");
    m_parameters[ICT_LPFS5_PT_TBB].Set(0x0106, 12, 5, 5, true, "ICT_LPFS5_PT_TBB");
    m_parameters[ICT_LPF_H_PT_TBB].Set(0x0106, 12, 5, 0, true, "ICT_LPF_H_PT_TBB");
    m_parameters[LOOPB_TBB].Set(0x0105, 0, 3, 12, true, "LOOPB_TBB");
    m_parameters[PD_LPFH_TBB].Set(0x0105, 0, 1, 4, true, "PD_LPFH_TBB");
    m_parameters[PD_LPFIAMP_TBB].Set(0x0105, 0, 1, 3, true, "PD_LPFIAMP_TBB");
    m_parameters[PD_LPFLAD_TBB].Set(0x0105, 1, 1, 2, true, "PD_LPFLAD_TBB");
    m_parameters[PD_LPFS5_TBB].Set(0x0105, 1, 1, 1, true, "PD_LPFS5_TBB");
    m_parameters[RCAL_LPFH_TBB].Set(0x0109, 97, 8, 8, true, "RCAL_LPFH_TBB");
    m_parameters[RCAL_LPFLAD_TBB].Set(0x0109, 193, 8, 0, true, "RCAL_LPFLAD_TBB");
    m_parameters[RCAL_LPFS5_TBB].Set(0x010a, 76, 8, 0, true, "RCAL_LPFS5_TBB");
    m_parameters[STATPULSE_TBB].Set(0x0105, 0, 1, 15, true, "STATPULSE_TBB");
    m_parameters[TSTIN_TBB].Set(0x010a, 0, 2, 14, true, "TSTIN_TBB");

    //AFE
    m_parameters[ISEL_DAC_AFE].Set          (0x0082, 4, 3, 13, false, "ISEL_DAC_AFE");
    m_parameters[MODE_INTERLEAVE_AFE].Set   (0x0082, 0, 1, 12, false, "MODE_INTERLEAVE_AFE");
    m_parameters[MUX_AFE_1].Set             (0x0082, 0, 2, 10, false, "MUX_AFE_1");
    m_parameters[MUX_AFE_2].Set             (0x0082, 0, 2, 8, false, "MUX_AFE_2");
    m_parameters[PD_AFE].Set                (0x0082, 0, 1, 5, false, "PD_AFE");
    m_parameters[PD_RX_AFE1].Set            (0x0082, 0, 1, 4, false, "PD_RX_AFE1");
    m_parameters[PD_RX_AFE2].Set            (0x0082, 1, 1, 3, false, "PD_RX_AFE2");
    m_parameters[PD_TX_AFE1].Set            (0x0082, 0, 1, 2, false, "PD_TX_AFE1");
    m_parameters[PD_TX_AFE2].Set            (0x0082, 1, 1, 1, false, "PD_TX_AFE2");
    m_parameters[EN_G_AFE].Set              (0x0082, 1, 1, 0, false, "EN_G_AFE");

    //BIAS
    m_parameters[MUX_BIAS_OUT].Set  (0x0084, 0, 2, 11, false, "MUX_BIAS_OUT");
    m_parameters[RP_CALIB_BIAS].Set (0x0084, 16, 5, 6, false, "RP_CALIB_BIAS");
    m_parameters[PD_FRP_BIAS].Set   (0x0084, 0, 1, 4, false, "PD_FRP_BIAS");
    m_parameters[PD_F_BIAS].Set     (0x0084, 0, 1, 3, false, "PD_F_BIAS");
    m_parameters[PD_PTRP_BIAS].Set  (0x0084, 0, 1, 2, false, "PD_PTRP_BIAS");
    m_parameters[PD_PT_BIAS].Set    (0x0084, 0, 1, 1, false, "PD_PT_BIAS");
    m_parameters[PD_BIAS_MASTER].Set(0x0084, 0, 1, 0, false, "PD_BIAS_MASTER");

    //XBUF
    m_parameters[BYP_XBUF_RX].Set(0x0085, 0, 1, 6, false, "BYP_XBUF_RX");
    m_parameters[BYP_XBUF_TX].Set(0x0085, 0, 1, 5, false, "BYP_XBUF_TX");
    m_parameters[EN_G_XBUF].Set(0x0085, 1, 1, 0, false, "EN_G_XBUF");
    m_parameters[EN_OUT2_XBUF_TX].Set(0x0085, 0, 1, 4, false, "EN_OUT2_XBUF_TX");
    m_parameters[EN_TBUFIN_XBUF_RX].Set(0x0085, 0, 1, 3, false, "EN_TBUFIN_XBUF_RX");
    m_parameters[PD_XBUF_RX].Set(0x0085, 0, 1, 2, false, "PD_XBUF_RX");
    m_parameters[PD_XBUF_TX].Set(0x0085, 0, 1, 1, false, "PD_XBUF_TX");
    m_parameters[SLFB_XBUF_RX].Set(0x0085, 0, 1, 8, false, "SLFB_XBUF_RX");
    m_parameters[SLFB_XBUF_TX].Set(0x0085, 0, 1, 7, false, "SLFB_XBUF_TX");

    //CLKGEN
    m_parameters[SPDUP_VCO_CGEN].Set    (0x0086, 0, 1, 15, false, "SPDUP_VCO_CGEN");
    m_parameters[RESET_N_CGEN].Set      (0x0086, 1, 1, 14, false, "RESET_N_CGEN");
    m_parameters[EN_ADCCLKH_CLKGN].Set  (0x0086, 1, 1, 11, false, "EN_ADCCLKH_CLKGN");
    m_parameters[EN_COARSE_CKLGEN].Set  (0x0086, 0, 1, 10, false, "EN_COARSE_CKLGEN");
    m_parameters[EN_INTONLY_SDM_CGEN].Set(0x0086, 0, 1, 9, false, "EN_INTONLY_SDM_CGEN");
    m_parameters[EN_SDM_CLK_CGEN].Set   (0x0086, 1, 1, 8, false, "EN_SDM_CLK_CGEN");
    m_parameters[EN_SDM_TSTO_CGEN].Set  (0x00A8, 0, 1, 4, false, "EN_SDM_TSTO_CGEN");
    m_parameters[PD_CP_CGEN].Set        (0x0086, 0, 1, 6, false, "PD_CP_CGEN");
    m_parameters[PD_FDIV_FB_CGEN].Set   (0x0086, 0, 1, 5, false, "PD_FDIV_FB_CGEN");
    m_parameters[PD_FDIV_O_CGEN].Set    (0x0086, 0, 1, 4, false, "PD_FDIV_O_CGEN");
    m_parameters[PD_SDM_CGEN].Set       (0x0086, 0, 1, 3, false, "PD_SDM_CGEN");
    m_parameters[PD_VCO_CGEN].Set       (0x0086, 1, 1, 2, false, "PD_VCO_CGEN");
    m_parameters[PD_VCO_COMP_CGEN].Set  (0x0086, 0, 1, 1, false, "PD_VCO_COMP_CGEN");
    m_parameters[EN_G_CGEN].Set         (0x0086, 1, 1, 0, false, "EN_G_CGEN");
    m_parameters[FRAC_SDM_CGEN].Set     (0x0087, 1024, 20, 0, false, "FRAC_SDM_CGEN");
    m_parameters[INT_SDM_CGEN].Set      (0x0088, 120, 10, 4, false, "INT_SDM_CGEN");
    m_parameters[COARSE_STEPDONE_CGEN].Set(0x008C, 0, 1, 15, false, "COARSE_STEPDONE_CGEN");
    m_parameters[COARSE_STEPDONE_CGEN].readonly = true;
    m_parameters[COARSEPLL_COMPO_CGEN].Set(0x008C, 0, 1, 14, false, "COARSEPLL_COMPO_CGEN");
    m_parameters[COARSEPLL_COMPO_CGEN].readonly = true;
    m_parameters[VCO_CMPHO_CGEN].Set(0x008C, 0, 1, 13, false, "VCO_CMPHO_CGEN");
    m_parameters[VCO_CMPHO_CGEN].readonly = true;
    m_parameters[VCO_CMPLO_CGEN].Set(0x008C, 0, 1, 12, false, "VCO_CMPLO_CGEN");
    m_parameters[VCO_CMPLO_CGEN].readonly = true;
    m_parameters[CLKH_OV_CLKL_CGEN].Set(0x0089, 0, 2, 11, false, "CLKH_OV_CLKL_CGEN");
    m_parameters[COARSE_START_CGEN].Set(0x008b, 0, 1, 0, false, "COARSE_START_CGEN");
    m_parameters[CP2_CGEN].Set(0x008c, 6, 4, 8, false, "CP2_CGEN");
    m_parameters[CP3_CGEN].Set(0x008c, 7, 4, 4, false, "CP3_CGEN");
    m_parameters[CSW_VCO_CGEN].Set(0x008b, 128, 8, 1, false, "CSW_VCO_CGEN");
    m_parameters[CZ_CGEN].Set(0x008c, 11, 4, 0, false, "CZ_CGEN");
    m_parameters[DIV_OUTCH_CGEN].Set(0x0089, 4, 8, 3, false, "DIV_OUTCH_CGEN");
    m_parameters[ICT_VCO_CGEN].Set(0x008b, 128, 5, 9, false, "ICT_VCO_CGEN");
    m_parameters[IOFFSET_CP_CGEN].Set(0x008a, 20, 6, 6, false, "IOFFSET_CP_CGEN");
    m_parameters[IPULSE_CP_CGEN].Set(0x008a, 20, 6, 0, false, "IPULSE_CP_CGEN");


    m_parameters[REVPH_PFD_CGEN].Set(0x008a, 0, 1, 12, false, "REVPH_PFD_CGEN");
    m_parameters[REV_CLKADC_CGEN].Set(0x008a, 0, 1, 13, false, "REV_CLKADC_CGEN");
    m_parameters[REV_CLKDAC_CGEN].Set(0x008a, 0, 1, 14, false, "REV_CLKDAC_CGEN");
    m_parameters[REV_SDMCLK_CGEN].Set(0x0089, 0, 1, 15, false, "REV_SDMCLK_CGEN");
    m_parameters[SEL_SDMCLK_CGEN].Set(0x0089, 0, 1, 14, false, "SEL_SDMCLK_CGEN");

    m_parameters[SX_DITHER_EN_CGEN].Set(0x0089, 0, 1, 13, false, "SX_DITHER_EN_CGEN");
    m_parameters[TST_CGEN].Set(0x0089, 0, 3, 0, false, "TST_CGEN");

    //SXT
    m_parameters[PD_FBDIV].Set(0x011c, 0, 1, 7, true, "PD_FBDIV");
    m_parameters[BYPLDO_VCO].Set(0x011c, 1, 1, 13, true, "BYPLDO_VCO");
    m_parameters[COARSEPLL_COMPO].Set(0x0123, 0, 1, 14, true, "COARSEPLL_COMPO");
    m_parameters[COARSEPLL_COMPO].readonly = true;
    m_parameters[COARSE_START].Set(0x0121, 0, 1, 0, false, "COARSE_START");
    m_parameters[COARSE_STEPDONE].Set(0x0123, 0, 1, 15, true, "COARSE_STEPDONE");
    m_parameters[COARSE_STEPDONE].readonly = true;
    m_parameters[CP2_PLL].Set(0x0123, 6, 4, 8, true, "CP2_PLL");
    m_parameters[CP3_PLL].Set(0x0123, 7, 4, 4, true, "CP3_PLL");
    m_parameters[CSW_VCO].Set(0x0121, 128, 8, 3, true, "CSW_VCO");
    m_parameters[CURLIM_VCO].Set(0x011c, 1, 1, 11, true, "CURLIM_VCO");
    m_parameters[CZ].Set(0x0123, 11, 4, 0, true, "CZ");
    m_parameters[DIV_LOCH].Set(0x011f, 1, 3, 6, true, "DIV_LOCH");
    m_parameters[EN_COARSEPLL].Set(0x011c, 0, 1, 12, true, "EN_COARSEPLL");
    m_parameters[EN_DIV2_DIVPROG].Set(0x011c, 1, 1, 10, true, "EN_DIV2_DIVPROG");
    m_parameters[EN_G].Set(0x011c, 1, 1, 0, true, "EN_G");
    m_parameters[EN_INTONLY_SDM].Set(0x011c, 0, 1, 9, true, "EN_INTONLY_SDM");
    m_parameters[EN_SDM_CLK].Set(0x011c, 1, 1, 8, true, "EN_SDM_CLK");
    m_parameters[EN_SDM_TSTO_SXR].Set(0x00A8, 0, 1, 5, false, "EN_SDM_TSTO_SXR");
    m_parameters[EN_SDM_TSTO_SXT].Set(0x00A8, 0, 1, 6, false, "EN_SDM_TSTO_SXT");
    m_parameters[FRAC_SDM].Set(0x011d, 1024, 20, 0, true, "FRAC_SDM");
    m_parameters[ICT_VCO].Set(0x0120, 128, 8, 0, true, "ICT_VCO");
    m_parameters[INT_SDM].Set(0x011e, 120, 10, 4, true, "INT_SDM");
    m_parameters[IOFFSET_CP].Set(0x0122, 20, 6, 6, true, "IOFFSET_CP");
    m_parameters[IPULSE_CP].Set(0x0122, 20, 6, 0, true, "IPULSE_CP");
    m_parameters[PD_CP].Set(0x011c, 0, 1, 5, true, "PD_CP");
    m_parameters[PD_FDIV].Set(0x011c, 0, 1, 4, true, "PD_FDIV");
    m_parameters[PD_LOCH_T2RBUF].Set(0x011c, 1, 1, 6, true, "PD_LOCH_T2RBUF");
    m_parameters[PD_SDM].Set(0x011c, 0, 1, 3, true, "PD_SDM");
    m_parameters[PD_VCO].Set(0x011c, 1, 1, 1, true, "PD_VCO");
    m_parameters[PD_VCO_COMP].Set(0x011c, 0, 1, 2, true, "PD_VCO_COMP");
    m_parameters[PW_DIV2_LOCH].Set(0x011f, 3, 3, 12, true, "PW_DIV2_LOCH");
    m_parameters[PW_DIV4_LOCH].Set(0x011f, 3, 3, 9, true, "PW_DIV4_LOCH");
    m_parameters[RESET_N].Set(0x011c, 1, 1, 15, true, "RESET_N");
    m_parameters[REVPH_PFD].Set(0x0122, 0, 1, 12, true, "REVPH_PFD");
    m_parameters[REV_SDMCLK].Set(0x011f, 0, 1, 0, true, "REV_SDMCLK");
    m_parameters[RSEL_LDO_VCO].Set(0x0121, 16, 5, 11, true, "RSEL_LDO_VCO");
    m_parameters[SEL_SDMCLK].Set(0x011f, 0, 1, 2, true, "SEL_SDMCLK");
    m_parameters[SEL_VCO].Set(0x0121, 2, 2, 1, true, "SEL_VCO");
    m_parameters[SPDUP_VCO].Set(0x011c, 0, 1, 14, true, "SPDUP_VCO");
    m_parameters[SX_DITHER_EN].Set(0x011f, 0, 1, 1, true, "SX_DITHER_EN");
    m_parameters[TST_SX].Set(0x011f, 0, 3, 3, true, "TST_SX");
    m_parameters[VDIV_VCO].Set(0x0120, 185, 8, 8, true, "VDIV_VCO");
    m_parameters[VCO_CMPHO].Set(0x0123, 0, 1, 13, true, "VCP_CMPHO");
    m_parameters[VCO_CMPHO].readonly = true;
    m_parameters[VCO_CMPLO].Set(0x0123, 0, 1, 12, true, "VCO_CMPLO");
    m_parameters[VCO_CMPLO].readonly = true;

    //LDO
    m_parameters[BYP_LDO_AFE].Set(0x0096, 0, 1, 15, false, "BYP_LDO_AFE");
    m_parameters[BYP_LDO_CPGN].Set(0x0096, 0, 1, 14, false, "BYP_LDO_CPGN");
    m_parameters[BYP_LDO_CPSXR].Set(0x0096, 0, 1, 13, false, "BYP_LDO_CPSXR");
    m_parameters[BYP_LDO_CPSXT].Set(0x0096, 0, 1, 12, false, "BYP_LDO_CPSXT");
    m_parameters[BYP_LDO_DIG].Set(0x0096, 0, 1, 11, false, "BYP_LDO_DIG");
    m_parameters[BYP_LDO_DIGGN].Set(0x0096, 0, 1, 10, false, "BYP_LDO_DIGGN");
    m_parameters[BYP_LDO_DIGIp1].Set(0x00a6, 0, 1, 7, false, "BYP_LDO_DIGIp1");
    m_parameters[BYP_LDO_DIGIp2].Set(0x00a6, 0, 1, 8, false, "BYP_LDO_DIGIp2");
    m_parameters[BYP_LDO_DIGSXR].Set(0x0096, 0, 1, 9, false, "BYP_LDO_DIGSXR");
    m_parameters[BYP_LDO_DIGSXT].Set(0x0096, 0, 1, 8, false, "BYP_LDO_DIGSXT");
    m_parameters[BYP_LDO_DIVGN].Set(0x0096, 0, 1, 7, false, "BYP_LDO_DIVGN");
    m_parameters[BYP_LDO_DIVSXR].Set(0x0096, 0, 1, 6, false, "BYP_LDO_DIVSXR");
    m_parameters[BYP_LDO_DIVSXT].Set(0x0096, 0, 1, 5, false, "BYP_LDO_DIVSXT");
    m_parameters[BYP_LDO_LNA12].Set(0x0096, 0, 1, 4, false, "BYP_LDO_LNA12");
    m_parameters[BYP_LDO_LNA14].Set(0x0096, 0, 1, 3, false, "BYP_LDO_LNA14");
    m_parameters[BYP_LDO_MXRFE].Set(0x0096, 0, 1, 2, false, "BYP_LDO_MXRFE");
    m_parameters[BYP_LDO_RBB].Set(0x0096, 0, 1, 1, false, "BYP_LDO_RBB");
    m_parameters[BYP_LDO_RXBUF].Set(0x0096, 0, 1, 0, false, "BYP_LDO_RXBUF");
    m_parameters[BYP_LDO_SPIBUF].Set(0x00a6, 0, 1, 9, false, "BYP_LDO_SPIBUF");
    m_parameters[BYP_LDO_TBB].Set(0x0095, 0, 1, 15, false, "BYP_LDO_TBB");
    m_parameters[BYP_LDO_TIA12].Set(0x0095, 0, 1, 14, false, "BYP_LDO_TIA12");
    m_parameters[BYP_LDO_TIA14].Set(0x0095, 0, 1, 13, false, "BYP_LDO_TIA14");
    m_parameters[BYP_LDO_TLOB].Set(0x0095, 0, 1, 12, false, "BYP_LDO_TLOB");
    m_parameters[BYP_LDO_TPAD].Set(0x0095, 0, 1, 11, false, "BYP_LDO_TPAD");
    m_parameters[BYP_LDO_TXBUF].Set(0x0095, 0, 1, 10, false, "BYP_LDO_TXBUF");
    m_parameters[BYP_LDO_VCOGN].Set(0x0095, 0, 1, 9, false, "BYP_LDO_VCOGN");
    m_parameters[BYP_LDO_VCOSXR].Set(0x0095, 0, 1, 8, false, "BYP_LDO_VCOSXR");
    m_parameters[BYP_LDO_VCOSXT].Set(0x0095, 0, 1, 7, false, "BYP_LDO_VCOSXT");
    m_parameters[EN_G_LDO].Set(0x0092, 1, 1, 0, false, "EN_G_LDO");
    m_parameters[EN_G_LDOP].Set(0x00a6, 1, 1, 0, false, "EN_G_LDOP");
    m_parameters[EN_LDO_AFE].Set(0x0093, 0, 1, 9, false, "EN_LDO_AFE");
    m_parameters[EN_LDO_CPGN].Set(0x0093, 0, 1, 8, false, "EN_LDO_CPGN");
    m_parameters[EN_LDO_CPSXR].Set(0x0093, 0, 1, 7, false, "EN_LDO_CPSXR");
    m_parameters[EN_LDO_CPSXT].Set(0x0093, 0, 1, 0, false, "EN_LDO_CPSXT");
    m_parameters[EN_LDO_DIG].Set(0x0092, 0, 1, 15, false, "EN_LDO_DIG");
    m_parameters[EN_LDO_DIGGN].Set(0x0092, 0, 1, 14, false, "EN_LDO_DIGGN");
    m_parameters[PD_LDO_DIGIp1].Set(0x00a6, 0, 1, 1, false, "PD_LDO_DIGIp1");
    m_parameters[PD_LDO_DIGIp2].Set(0x00a6, 0, 1, 2, false, "PD_LDO_DIGIp2");
    m_parameters[EN_LDO_DIGSXR].Set(0x0092, 0, 1, 13, false, "EN_LDO_DIGSXR");
    m_parameters[EN_LDO_DIGSXT].Set(0x0092, 0, 1, 12, false, "EN_LDO_DIGSXT");
    m_parameters[EN_LDO_DIVGN].Set(0x0092, 0, 1, 11, false, "EN_LDO_DIVGN");
    m_parameters[EN_LDO_DIVSXR].Set(0x0092, 0, 1, 10, false, "EN_LDO_DIVSXR");
    m_parameters[EN_LDO_DIVSXT].Set(0x0092, 0, 1, 9, false, "EN_LDO_DIVSXT");
    m_parameters[EN_LDO_LNA12].Set(0x0092, 0, 1, 8, false, "EN_LDO_LNA12");
    m_parameters[EN_LDO_LNA14].Set(0x0092, 0, 1, 7, false, "EN_LDO_LNA14");
    m_parameters[EN_LDO_MXRFE].Set(0x0092, 0, 1, 6, false, "EN_LDO_MXRFE");
    m_parameters[EN_LDO_RBB].Set(0x0092, 0, 1, 5, false, "EN_LDO_RBB");
    m_parameters[EN_LDO_RXBUF].Set(0x0092, 0, 1, 4, false, "EN_LDO_RXBUF");
    m_parameters[PD_LDO_SPIBUF].Set(0x00a6, 0, 1, 3, false, "PD_LDO_SPIBUF");
    m_parameters[EN_LDO_TBB].Set(0x0092, 0, 1, 3, false, "EN_LDO_TBB");
    m_parameters[EN_LDO_TIA12].Set(0x0092, 0, 1, 2, false, "EN_LDO_TIA12");
    m_parameters[EN_LDO_TIA14].Set(0x0092, 0, 1, 1, false, "EN_LDO_TIA14");
    m_parameters[EN_LDO_TLOB].Set(0x0093, 0, 1, 6, false, "EN_LDO_TLOB");
    m_parameters[EN_LDO_TPAD].Set(0x0093, 0, 1, 5, false, "EN_LDO_TPAD");
    m_parameters[EN_LDO_TXBUF].Set(0x0093, 0, 1, 4, false, "EN_LDO_TXBUF");
    m_parameters[EN_LDO_VCOGN].Set(0x0093, 0, 1, 3, false, "EN_LDO_VCOGN");
    m_parameters[EN_LDO_VCOSXR].Set(0x0093, 0, 1, 2, false, "EN_LDO_VCOSXR");
    m_parameters[EN_LDO_VCOSXT].Set(0x0093, 0, 1, 1, false, "EN_LDO_VCOSXT");
    m_parameters[EN_LOADIMP_LDO_AFE].Set(0x0095, 0, 1, 2, false, "EN_LOADIMP_LDO_AFE");
    m_parameters[EN_LOADIMP_LDO_CPGN].Set(0x0095, 0, 1, 1, false, "EN_LOADIMP_LDO_CPGN");
    m_parameters[EN_LOADIMP_LDO_CPSXR].Set(0x0095, 0, 1, 0, false, "EN_LOADIMP_LDO_CPSXR");
    m_parameters[EN_LOADIMP_LDO_CPSXT].Set(0x0094, 0, 1, 15, false, "EN_LOADIMP_LDO_CPSXT");
    m_parameters[EN_LOADIMP_LDO_DIG].Set(0x0094, 0, 1, 14, false, "EN_LOADIMP_LDO_DIG");
    m_parameters[EN_LOADIMP_LDO_DIGGN].Set(0x0094, 0, 1, 13, false, "EN_LOADIMP_LDO_DIGGN");
    m_parameters[EN_LOADIMP_LDO_DIGIp1].Set(0x00a6, 0, 1, 4, false, "EN_LOADIMP_LDO_DIGIp1");
    m_parameters[EN_LOADIMP_LDO_DIGIp2].Set(0x00a6, 0, 1, 5, false, "EN_LOADIMP_LDO_DIGIp2");
    m_parameters[EN_LOADIMP_LDO_DIGSXR].Set(0x0094, 0, 1, 12, false, "EN_LOADIMP_LDO_DIGSXR");
    m_parameters[EN_LOADIMP_LDO_DIGSXT].Set(0x0094, 0, 1, 11, false, "EN_LOADIMP_LDO_DIGSXT");
    m_parameters[EN_LOADIMP_LDO_DIVGN].Set(0x0094, 0, 1, 10, false, "EN_LOADIMP_LDO_DIVGN");
    m_parameters[EN_LOADIMP_LDO_DIVSXR].Set(0x0094, 0, 1, 9, false, "EN_LOADIMP_LDO_DIVSXR");
    m_parameters[EN_LOADIMP_LDO_DIVSXT].Set(0x0094, 0, 1, 8, false, "EN_LOADIMP_LDO_DIVSXT");
    m_parameters[EN_LOADIMP_LDO_LNA12].Set(0x0094, 0, 1, 7, false, "EN_LOADIMP_LDO_LNA12");
    m_parameters[EN_LOADIMP_LDO_LNA14].Set(0x0094, 0, 1, 6, false, "EN_LOADIMP_LDO_LNA14");
    m_parameters[EN_LOADIMP_LDO_MXRFE].Set(0x0094, 0, 1, 5, false, "EN_LOADIMP_LDO_MXRFE");
    m_parameters[EN_LOADIMP_LDO_RBB].Set(0x0094, 0, 1, 4, false, "EN_LOADIMP_LDO_RBB");
    m_parameters[EN_LOADIMP_LDO_RXBUF].Set(0x0094, 0, 1, 3, false, "EN_LOADIMP_LDO_RXBUF");
    m_parameters[EN_LOADIMP_LDO_SPIBUF].Set(0x00a6, 0, 1, 6, false, "EN_LOADIMP_LDO_SPIBUF");
    m_parameters[EN_LOADIMP_LDO_TBB].Set(0x0094, 0, 1, 2, false, "EN_LOADIMP_LDO_TBB");
    m_parameters[EN_LOADIMP_LDO_TIA12].Set(0x0094, 0, 1, 1, false, "EN_LOADIMP_LDO_TIA12");
    m_parameters[EN_LOADIMP_LDO_TIA14].Set(0x0094, 0, 1, 0, false, "EN_LOADIMP_LDO_TIA14");
    m_parameters[EN_LOADIMP_LDO_TLOB].Set(0x0093, 0, 1, 15, false, "EN_LOADIMP_LDO_TLOB");
    m_parameters[EN_LOADIMP_LDO_TPAD].Set(0x0093, 0, 1, 14, false, "EN_LOADIMP_LDO_TPAD");
    m_parameters[EN_LOADIMP_LDO_TXBUF].Set(0x0093, 0, 1, 13, false, "EN_LOADIMP_LDO_TXBUF");
    m_parameters[EN_LOADIMP_LDO_VCOGN].Set(0x0093, 0, 1, 12, false, "EN_LOADIMP_LDO_VCOGN");
    m_parameters[EN_LOADIMP_LDO_VCOSXR].Set(0x0093, 0, 1, 11, false, "EN_LOADIMP_LDO_VCOSXR");
    m_parameters[EN_LOADIMP_LDO_VCOSXT].Set(0x0093, 0, 1, 10, false, "EN_LOADIMP_LDO_VCOSXT");
    m_parameters[RDIV_AFE].Set(0x00a5, 101, 8, 0, false, "RDIV_AFE");
    m_parameters[RDIV_CPGN].Set(0x00a4, 101, 8, 8, false, "RDIV_CPGN");
    m_parameters[RDIV_CPSXR].Set(0x00a4, 101, 8, 0, false, "RDIV_CPSXR");
    m_parameters[RDIV_CPSXT].Set(0x00a3, 101, 8, 8, false, "RDIV_CPSXT");
    m_parameters[RDIV_DIG].Set(0x00a3, 101, 8, 0, false, "RDIV_DIG");
    m_parameters[RDIV_DIGGN].Set(0x00a2, 101, 8, 8, false, "RDIV_DIGGN");
    m_parameters[RDIV_DIGIp1].Set(0x00a7, 101, 8, 0, false, "RDIV_DIGIp1");
    m_parameters[RDIV_DIGIp2].Set(0x00a7, 101, 8, 8, false, "RDIV_DIGIp2");
    m_parameters[RDIV_DIGSXR].Set(0x00a2, 101, 8, 0, false, "RDIV_DIGSXR");
    m_parameters[RDIV_DIGSXT].Set(0x00a1, 101, 8, 8, false, "RDIV_DIGSXT");
    m_parameters[RDIV_DIVGN].Set(0x00a1, 101, 8, 0, false, "RDIV_DIVGN");
    m_parameters[RDIV_DIVSXR].Set(0x00a0, 101, 8, 8, false, "RDIV_DIVSXR");
    m_parameters[RDIV_DIVSXT].Set(0x00a0, 101, 8, 0, false, "RDIV_DIVSXT");
    m_parameters[RDIV_LNA12].Set(0x009f, 101, 8, 8, false, "RDIV_LNA12");
    m_parameters[RDIV_LNA14].Set(0x009f, 140, 8, 0, false, "RDIV_LNA14");
    m_parameters[RDIV_MXRFE].Set(0x009e, 101, 8, 8, false, "RDIV_MXRFE");
    m_parameters[RDIV_RBB].Set(0x009e, 140, 8, 0, false, "RDIV_RBB");
    m_parameters[RDIV_RXBUF].Set(0x009d, 101, 8, 8, false, "RDIV_RXBUF");
    m_parameters[RDIV_SPIBUF].Set(0x00a5, 101, 8, 8, false, "RDIV_SPIBUF");
    m_parameters[RDIV_TBB].Set(0x009d, 101, 8, 0, false, "RDIV_TBB");
    m_parameters[RDIV_TIA12].Set(0x009c, 101, 8, 8, false, "RDIV_TIA12");
    m_parameters[RDIV_TIA14].Set(0x009c, 140, 8, 0, false, "RDIV_TIA14");
    m_parameters[RDIV_TLOB].Set(0x009b, 101, 8, 8, false, "RDIV_TLOB");
    m_parameters[RDIV_TPAD].Set(0x009b, 101, 8, 0, false, "RDIV_TPAD");
    m_parameters[RDIV_TXBUF].Set(0x009a, 101, 8, 8, false, "RDIV_TXBUF");
    m_parameters[RDIV_VCOGN].Set(0x009a, 140, 8, 0, false, "RDIV_VCOGN");
    m_parameters[RDIV_VCOSXR].Set(0x0099, 101, 8, 8, false, "RDIV_VCOSXR");
    m_parameters[RDIV_VCOSXT].Set(0x0099, 101, 8, 0, false, "RDIV_VCOSXT");
    m_parameters[SPDUP_LDO_AFE].Set(0x0098, 0, 1, 8, false, "SPDUP_LDO_AFE");
    m_parameters[SPDUP_LDO_CPGN].Set(0x0098, 0, 1, 7, false, "SPDUP_LDO_CPGN");
    m_parameters[SPDUP_LDO_CPSXR].Set(0x0098, 0, 1, 6, false, "SPDUP_LDO_CPSXR");
    m_parameters[SPDUP_LDO_CPSXT].Set(0x0098, 0, 1, 5, false, "SPDUP_LDO_CPSXT");
    m_parameters[SPDUP_LDO_DIG].Set(0x0098, 0, 1, 4, false, "SPDUP_LDO_DIG");
    m_parameters[SPDUP_LDO_DIGGN].Set(0x0098, 0, 1, 3, false, "SPDUP_LDO_DIGGN");
    m_parameters[SPDUP_LDO_DIGIp1].Set(0x00a6, 0, 1, 10, false, "SPDUP_LDO_DIGIp1");
    m_parameters[SPDUP_LDO_DIGIp2].Set(0x00a6, 0, 1, 11, false, "SPDUP_LDO_DIGIp2");
    m_parameters[SPDUP_LDO_DIGSXR].Set(0x0098, 0, 1, 2, false, "SPDUP_LDO_DIGSXR");
    m_parameters[SPDUP_LDO_DIGSXT].Set(0x0098, 0, 1, 1, false, "SPDUP_LDO_DIGSXT");
    m_parameters[SPDUP_LDO_DIVGN].Set(0x0098, 0, 1, 0, false, "SPDUP_LDO_DIVGN");
    m_parameters[SPDUP_LDO_DIVSXR].Set(0x0097, 0, 1, 15, false, "SPDUP_LDO_DIVSXR");
    m_parameters[SPDUP_LDO_DIVSXT].Set(0x0097, 0, 1, 14, false, "SPDUP_LDO_DIVSXT");
    m_parameters[SPDUP_LDO_LNA12].Set(0x0097, 0, 1, 13, false, "SPDUP_LDO_LNA12");
    m_parameters[SPDUP_LDO_LNA14].Set(0x0097, 0, 1, 12, false, "SPDUP_LDO_LNA14");
    m_parameters[SPDUP_LDO_MXRFE].Set(0x0097, 0, 1, 11, false, "SPDUP_LDO_MXRFE");
    m_parameters[SPDUP_LDO_RBB].Set(0x0097, 0, 1, 10, false, "SPDUP_LDO_RBB");
    m_parameters[SPDUP_LDO_RXBUF].Set(0x0097, 0, 1, 9, false, "SPDUP_LDO_RXBUF");
    m_parameters[SPDUP_LDO_SPIBUF].Set(0x00a6, 0, 1, 12, false, "SPDUP_LDO_SPIBUF");
    m_parameters[SPDUP_LDO_TBB].Set(0x0097, 0, 1, 8, false, "SPDUP_LDO_TBB");
    m_parameters[SPDUP_LDO_TIA12].Set(0x0097, 0, 1, 7, false, "SPDUP_LDO_TIA12");
    m_parameters[SPDUP_LDO_TIA14].Set(0x0097, 0, 1, 6, false, "SPDUP_LDO_TIA14");
    m_parameters[SPDUP_LDO_TLOB].Set(0x0097, 0, 1, 5, false, "SPDUP_LDO_TLOB");
    m_parameters[SPDUP_LDO_TPAD].Set(0x0097, 0, 1, 4, false, "SPDUP_LDO_TPAD");
    m_parameters[SPDUP_LDO_TXBUF].Set(0x0097, 0, 1, 3, false, "SPDUP_LDO_TXBUF");
    m_parameters[SPDUP_LDO_VCOGN].Set(0x0097, 0, 1, 2, false, "SPDUP_LDO_VCOGN");
    m_parameters[SPDUP_LDO_VCOSXR].Set(0x0097, 0, 1, 1, false, "SPDUP_LDO_VCOSXR");
    m_parameters[SPDUP_LDO_VCOSXT].Set(0x0097, 0, 1, 0, false, "SPDUP_LDO_VCOSXT");


    //Lime Light and PAD configuration
    m_parameters[DIQ1_DS].Set(0x0022, 0, 1, 5, false, "DIQ1_DS");
    m_parameters[DIQ1_PE].Set(0x0022, 1, 1, 4, false, "DIQ1_PE");
    m_parameters[DIQ2_DS].Set(0x0022, 0, 1, 11, false, "DIQ2_DS");
    m_parameters[DIQ2_PE].Set(0x0022, 1, 1, 10, false, "DIQ2_PE");
    m_parameters[RX_MUX].Set(0x002a, 0, 2, 10, false, "RX_MUX");
    m_parameters[FCLK1_PE].Set(0x0022, 1, 1, 1, false, "FCLK1_PE");
    m_parameters[FCLK2_PE].Set(0x0022, 1, 1, 7, false, "FCLK2_PE");
    m_parameters[IQ_SEL_EN_1_PE].Set(0x0022, 1, 1, 3, false, "IQ_SEL_EN_1_PE");
    m_parameters[IQ_SEL_EN_2_PE].Set(0x0022, 1, 1, 9, false, "IQ_SEL_EN_2_PE");
    m_parameters[LML1_AIP].Set(0x0024, 0, 2, 0, false, "LML1_AIP");
    m_parameters[LML1_AQP].Set(0x0024, 1, 2, 2, false, "LML1_AQP");
    m_parameters[LML1_BIP].Set(0x0024, 2, 2, 4, false, "LML1_BIP");
    m_parameters[LML1_BQP].Set(0x0024, 3, 2, 6, false, "LML1_BQP");
    m_parameters[LML1_RF2BB_PRE].Set(0x0026, 1, 8, 0, false, "LML1_RF2BB_PRE");
    m_parameters[LML1_RF2BB_PST].Set(0x0026, 1, 8, 8, false, "LML1_RF2BB_PST");
    m_parameters[LML1_S0S].Set(0x0024, 0, 2, 8, false, "LML1_S0S");
    m_parameters[LML1_S1S].Set(0x0024, 1, 2, 10, false, "LML1_S1S");
    m_parameters[LML1_S2S].Set(0x0024, 2, 2, 12, false, "LML1_S2S");
    m_parameters[LML1_S3S].Set(0x0024, 3, 2, 14, false, "LML1_S3S");
    m_parameters[LML1_BB2RF_PRE].Set(0x0025, 1, 8, 0, false, "LML1_BB2RF_PRE");
    m_parameters[LML1_BB2RF_PST].Set(0x0025, 1, 8, 8, false, "LML1_BB2RF_PST");
    m_parameters[LML2_AIP].Set(0x0027, 0, 2, 0, false, "LML2_AIP");
    m_parameters[LML2_AQP].Set(0x0027, 1, 2, 2, false, "LML2_AQP");
    m_parameters[LML2_BIP].Set(0x0027, 2, 2, 4, false, "LML2_BIP");
    m_parameters[LML2_BQP].Set(0x0027, 3, 2, 6, false, "LML2_BQP");
    m_parameters[LML2_RF2BB_PRE].Set(0x0029, 1, 8, 0, false, "LML2_RF2BB_PRE");
    m_parameters[LML2_RF2BB_PST].Set(0x0029, 1, 8, 8, false, "LML2_RF2BB_PST");
    m_parameters[LML2_S0S].Set(0x0027, 0, 2, 8, false, "LML2_S0S");
    m_parameters[LML2_S1S].Set(0x0027, 1, 2, 10, false, "LML2_S1S");
    m_parameters[LML2_S2S].Set(0x0027, 2, 2, 12, false, "LML2_S2S");
    m_parameters[LML2_S3S].Set(0x0027, 3, 2, 14, false, "LML2_S3S");
    m_parameters[LML2_BB2RF_PRE].Set(0x0028, 1, 8, 0, false, "LML2_BB2RF_PRE");
    m_parameters[LML2_BB2RF_PST].Set(0x0028, 1, 8, 8, false, "LML2_BB2RF_PST");
    m_parameters[LML1_MODE].Set(0x0023, 1, 1, 0, false, "LML1_MODE");
    m_parameters[LML2_MODE].Set(0x0023, 1, 1, 3, false, "LML2_MODE");
    m_parameters[LML1_FIDM].Set(0x0023, 0, 1, 2, false, "LML1_FIDM");
    m_parameters[LML2_FIDM].Set(0x0023, 0, 1, 5, false, "LML2_FIDM");
    m_parameters[LML1_TXNRXIQ].Set(0x0023, 0, 1, 1, false, "LML1_TXNRXIQ");
    m_parameters[LML2_TXNRXIQ].Set(0x0023, 1, 1, 4, false, "LML2_TXNRXIQ");
    m_parameters[LRST_RX_A].Set(0x0020, 1, 1, 9, false, "LRST_RX_A");
    m_parameters[LRST_RX_B].Set(0x0020, 1, 1, 11, false, "LRST_RX_B");
    m_parameters[LRST_TX_A].Set(0x0020, 1, 1, 13, false, "LRST_TX_A");
    m_parameters[LRST_TX_B].Set(0x0020, 1, 1, 15, false, "LRST_TX_B");
    m_parameters[MAC].Set(0x0020, 3, 2, 0, false, "MAC");
    m_parameters[MCLK1SRC].Set(0x002b, 0, 2, 2, false, "MCLK1SRC");
    m_parameters[RXTSPCLKA_DIV].Set(0x002c, 255, 8, 0, false, "RXTSPCLKA_DIV");
    m_parameters[MCLK1_PE].Set(0x0022, 1, 1, 0, false, "MCLK1_PE");
    m_parameters[MCLK2SRC].Set(0x002b, 1, 2, 4, false, "MCLK2SRC");
    m_parameters[TXTSPCLKA_DIV].Set(0x002c, 255, 8, 8, false, "TXTSPCLKA_DIV");
    m_parameters[MCLK2_PE].Set(0x0022, 1, 1, 6, false, "MCLK2_PE");
    m_parameters[MIMO_SISO].Set(0x002e, 0, 1, 15, false, "MIMO_SISO");
    m_parameters[MOD_EN].Set(0x0023, 1, 1, 6, false, "MOD_EN");
    m_parameters[MRST_RX_A].Set(0x0020, 1, 1, 8, false, "MRST_RX_A");
    m_parameters[MRST_RX_B].Set(0x0020, 1, 1, 10, false, "MRST_RX_B");
    m_parameters[MRST_TX_A].Set(0x0020, 1, 1, 12, false, "MRST_TX_A");
    m_parameters[MRST_TX_B].Set(0x0020, 1, 1, 14, false, "MRST_TX_B");
    m_parameters[RXDIVEN].Set(0x002b, 0, 1, 0, false, "RXDIVEN");
    m_parameters[RXEN_A].Set(0x0020, 1, 1, 4, false, "RXEN_A");
    m_parameters[RXEN_B].Set(0x0020, 1, 1, 5, false, "RXEN_B");
    m_parameters[RXRDCLK_MUX].Set(0x002a, 1, 2, 2, false, "RXRDCLK_MUX");
    m_parameters[RXWRCLK_MUX].Set(0x002a, 2, 2, 0, false, "RXWRCLK_MUX");
    m_parameters[RX_CLK_PE].Set(0x0021, 1, 1, 10, false, "RX_CLK_PE");
    m_parameters[SCLK_PE].Set(0x0021, 1, 1, 2, false, "SCLK_PE");
    m_parameters[SCL_DS].Set(0x0021, 0, 1, 6, false, "SCL_DS");
    m_parameters[SCL_PE].Set(0x0021, 1, 1, 7, false, "SCL_PE");
    m_parameters[SDA_DS].Set(0x0021, 0, 1, 8, false, "SDA_DS");
    m_parameters[SDA_PE].Set(0x0021, 1, 1, 9, false, "SDA_PE");
    m_parameters[SDIO_DS].Set(0x0021, 0, 1, 5, false, "SDIO_DS");
    m_parameters[SDIO_PE].Set(0x0021, 1, 1, 4, false, "SDIO_PE");
    m_parameters[SDO_PE].Set(0x0021, 1, 1, 3, false, "SDO_PE");
    m_parameters[SEN_PE].Set(0x0021, 1, 1, 1, false, "SEN_PE");
    m_parameters[SPIMODE].Set(0x0021, 1, 1, 0, false, "SPIMODE");
    m_parameters[SRST_RXFIFO].Set(0x0020, 1, 1, 7, false, "SRST_RXFIFO");
    m_parameters[SRST_TXFIFO].Set(0x0020, 1, 1, 6, false, "SRST_TXFIFO");
    m_parameters[TXDIVEN].Set(0x002b, 0, 1, 1, false, "TXDIVEN");
    m_parameters[TXEN_A].Set(0x0020, 1, 1, 2, false, "TXEN_A");
    m_parameters[TXEN_B].Set(0x0020, 1, 1, 3, false, "TXEN_B");
    m_parameters[TX_MUX].Set(0x002a, 0, 2, 8, false, "TX_MUX");
    m_parameters[TXNRX1_PE].Set(0x0022, 1, 1, 2, false, "TXNRX1_PE");
    m_parameters[TXNRX2_PE].Set(0x0022, 1, 1, 8, false, "TXNRX2_PE");
    m_parameters[TXRDCLK_MUX].Set(0x002a, 2, 2, 6, false, "TXRDCLK_MUX");
    m_parameters[TXWRCLK_MUX].Set(0x002a, 0, 2, 4, false, "TXWRCLK_MUX");
    m_parameters[TX_CLK_PE].Set(0x0021, 1, 1, 11, false, "TX_CLK_PE");
    m_parameters[FCLK1_INV].Set(0x002B, 0, 1, 14, false, "FCLK1_INV");
    m_parameters[FCLK2_INV].Set(0x002B, 0, 1, 15, false, "FCLK2_INV");
    m_parameters[MCLK1DLY].Set(0x002B, 0, 2, 10, false, "MCLK1DLY");
    m_parameters[MCLK2DLY].Set(0x002B, 0, 2, 12, false, "MCLK2DLY");
    m_parameters[DIQDIRCTR2].Set(0x0023, 0, 1, 15, false, "DIQDIRCTR2");
    m_parameters[DIQDIR2].Set(0x0023, 1, 1, 14, false, "DIQDIR2");
    m_parameters[DIQDIRCTR1].Set(0x0023, 0, 1, 13, false, "DIQDIRCTR1");
    m_parameters[DIQDIR1].Set(0x0023, 1, 1, 12, false, "DIQDIR1");
    m_parameters[ENABLEDIRCTR2].Set(0x0023, 0, 1, 11, false, "ENABLEDIRCTR2");
    m_parameters[ENABLEDIR2].Set(0x0023, 1, 1, 10, false, "ENABLEDIR2");
    m_parameters[ENABLEDIRCTR1].Set(0x0023, 0, 1, 9, false, "ENABLEDIRCTR1");
    m_parameters[ENABLEDIR1].Set(0x0023, 1, 1, 8, false, "ENABLEDIR1");

    //Tx TSP
    m_parameters[TSGFC_TXTSP].Set      (0x0200, 0, 1, 9, true, "TSGFC_TXTSP");
    m_parameters[CMIX_SC_TXTSP].Set     (0x0208, 0, 1, 13, true, "CMIX_SC_TXTSP");
    m_parameters[BSTART_TXTSP].Set      (0x0200, 0, 1, 1, true, "BSTART_TXTSP");
    m_parameters[CMIX_BYP_TXTSP].Set    (0x0208, 0, 1, 8, true, "CMIX_BYP_TXTSP");
    m_parameters[CMIX_GAIN_TXTSP].Set   (0x0208, 0, 2, 14, true, "CMIX_GAIN_TXTSP");
    m_parameters[DCCORRI_TXTSP].Set     (0x0204, 0, 8, 8, true, "DCCORRI_TXTSP");
    m_parameters[DCCORRQ_TXTSP].Set     (0x0204, 0, 8, 0, true, "DCCORRQ_TXTSP");
    m_parameters[DC_BYP_TXTSP].Set      (0x0208, 0, 1, 3, true, "DC_BYP_TXTSP");
    m_parameters[EN_TXTSP].Set          (0x0200, 1, 1, 0, true, "EN_TXTSP");
    m_parameters[GCORRI_TXTSP].Set      (0x0202, 2047, 11, 0, true, "GCORRI_TXTSP");
    m_parameters[GCORRQ_TXTSP].Set      (0x0201, 2047, 11, 0, true, "GCORRQ_TXTSP");
    m_parameters[GC_BYP_TXTSP].Set      (0x0208, 0, 1, 1, true, "GC_BYP_TXTSP");
    m_parameters[GFIR1_BYP_TXTSP].Set   (0x0208, 0, 1, 4, true, "GFIR1_BYP_TXTSP");
    m_parameters[GFIR1_L_TXTSP].Set     (0x0205, 0, 3, 8, true, "GFIR1_L_TXTSP");
    m_parameters[GFIR1_N_TXTSP].Set     (0x0205, 0, 8, 0, true, "GFIR1_N_TXTSP");
    m_parameters[GFIR2_BYP_TXTSP].Set   (0x0208, 0, 1, 5, true, "GFIR2_BYP_TXTSP");
    m_parameters[GFIR2_L_TXTSP].Set     (0x0206, 0, 3, 8, true, "GFIR2_L_TXTSP");
    m_parameters[GFIR2_N_TXTSP].Set     (0x0206, 0, 8, 0, true, "GFIR2_N_TXTSP");
    m_parameters[GFIR3_BYP_TXTSP].Set   (0x0208, 0, 1, 6, true, "GFIR3_BYP_TXTSP");
    m_parameters[GFIR3_L_TXTSP].Set     (0x0207, 0, 3, 8, true, "GFIR3_L_TXTSP");
    m_parameters[GFIR3_N_TXTSP].Set     (0x0207, 0, 8, 0, true, "GFIR3_N_TXTSP");
    m_parameters[HBI_OVR_TXTSP].Set     (0x0203, 0, 3, 12, true, "HBI_OVR_TXTSP");
    m_parameters[IQCORR_TXTSP].Set      (0x0203, 0, 12, 0, true, "IQCORR_TXTSP");
    m_parameters[ISINC_BYP_TXTSP].Set   (0x0208, 0, 1, 7, true, "ISINC_BYP_TXTSP");
    m_parameters[PH_BYP_TXTSP].Set      (0x0208, 0, 1, 0, true, "PH_BYP_TXTSP");
    m_parameters[BSTATE_TXTSP].Set      (0x0209, 0, 1, 0, true, "BSTATE_TXTSP");
    m_parameters[BSTATE_TXTSP].readonly = true;
    m_parameters[BSIGI_TXTSP].Set       (0x0209, 0, 23, 1, true, "BSIGI_TXTSP");
    m_parameters[BSIGI_TXTSP].readonly = true;
    m_parameters[BSIGQ_TXTSP].Set       (0x020A, 0, 23, 8, true, "BSIGQ_TXTSP");
    m_parameters[BSIGQ_TXTSP].readonly = true;

    //RX TSP
    m_parameters[TSGFC_RXTSP].Set(0x0400, 0, 1, 9, true, "TSGFC_RXTSP");
    m_parameters[CMIX_SC_RXTSP].Set(0x040C, 0, 1, 13, true, "CMIX_SC_RXTSP");
    m_parameters[AGC_ADESIRED_RXTSP].Set(0x0409, 0, 12, 4, true, "AGC_ADESIRED_RXTSP");
    m_parameters[AGC_AVG_RXTSP].Set(0x040a, 0, 3, 0, true, "AGC_AVG_RXTSP");
    m_parameters[AGC_BYP_RXTSP].Set(0x040c, 0, 1, 6, true, "AGC_BYP_RXTSP");
    m_parameters[AGC_K_RXTSP].Set(0x0408, 0, 18, 0, true, "AGC_K_RXTSP");
    m_parameters[AGC_MODE_RXTSP].Set(0x040a, 0, 2, 12, true, "AGC_MODE_RXTSP");
    m_parameters[BSTART_RXTSP].Set(0x0400, 0, 1, 1, true, "BSTART_RXTSP");
    m_parameters[CMIX_BYP_RXTSP].Set(0x040c, 0, 1, 7, true, "CMIX_BYP_RXTSP");
    m_parameters[CMIX_GAIN_RXTSP].Set(0x040c, 0, 2, 14, true, "CMIX_GAIN_RXTSP");
    m_parameters[DCCORR_AVG_RXTSP].Set(0x0404, 0, 3, 0, true, "DCCORR_AVG_RXTSP");
    m_parameters[DC_BYP_RXTSP].Set(0x040c, 0, 1, 2, true, "DC_BYP_RXTSP");
    m_parameters[EN_RXTSP].Set(0x0400, 1, 1, 0, true, "EN_RXTSP");
    m_parameters[GCORRI_RXTSP].Set(0x0402, 2047, 11, 0, true, "GCORRI_RXTSP");
    m_parameters[GCORRQ_RXTSP].Set(0x0401, 2047, 11, 0, true, "GCORRQ_RXTSP");
    m_parameters[GC_BYP_RXTSP].Set(0x040c, 0, 1, 1, true, "GC_BYP_RXTSP");
    m_parameters[GFIR1_BYP_RXTSP].Set(0x040c, 0, 1, 3, true, "GFIR1_BYP_RXTSP");
    m_parameters[GFIR1_L_RXTSP].Set(0x0405, 0, 3, 8, true, "GFIR1_L_RXTSP");
    m_parameters[GFIR1_N_RXTSP].Set(0x0405, 0, 8, 0, true, "GFIR1_N_RXTSP");
    m_parameters[GFIR2_BYP_RXTSP].Set(0x040c, 0, 1, 4, true, "GFIR2_BYP_RXTSP");
    m_parameters[GFIR2_L_RXTSP].Set(0x0406, 0, 3, 8, true, "GFIR2_L_RXTSP");
    m_parameters[GFIR2_N_RXTSP].Set(0x0406, 0, 8, 0, true, "GFIR2_N_RXTSP");
    m_parameters[GFIR3_BYP_RXTSP].Set(0x040c, 0, 1, 5, true, "GFIR3_BYP_RXTSP");
    m_parameters[GFIR3_L_RXTSP].Set(0x0407, 0, 3, 8, true, "GFIR3_L_RXTSP");
    m_parameters[GFIR3_N_RXTSP].Set(0x0407, 0, 8, 0, true, "GFIR3_N_RXTSP");
    m_parameters[HBD_OVR_RXTSP].Set(0x0403, 0, 3, 12, true, "HBD_OVR_RXTSP");
    m_parameters[IQCORR_RXTSP].Set(0x0403, 0, 12, 0, true, "IQCORR_RXTSP");
    m_parameters[PH_BYP_RXTSP].Set(0x040c, 0, 1, 0, true, "PH_BYP_RXTSP");

    //BIST
    m_parameters[BENC].Set(0x00a8, 0, 1, 3, false, "BENC");
    m_parameters[BENR].Set(0x00a8, 0, 1, 2, false, "BENR");
    m_parameters[BENT].Set(0x00a8, 0, 1, 1, false, "BENT");
    m_parameters[BSTART].Set(0x00a8, 0, 1, 0, false, "BSTART");
    m_parameters[BSIGT].Set(0x00a8, 0, 23, 9, false, "BSIGT");
    m_parameters[BSIGT].readonly = true;
    m_parameters[BSIGR].Set(0x00aa, 0, 23, 0, false, "BSIGR");
    m_parameters[BSIGR].readonly = true;
    m_parameters[BSIGC].Set(0x00ab, 0, 23, 7, false, "BSIGC");
    m_parameters[BSIGC].readonly = true;
    m_parameters[BSTATE].Set(0x00a8, 0, 1, 8, false, "BSTATE");
    m_parameters[BSTATE].readonly = true;

    //CDS
    m_parameters[CDSN_MCLK1].Set(0x00ad, 1, 1, 0, false, "CDSN_MCLK1");
    m_parameters[CDSN_MCLK2].Set(0x00ad, 1, 1, 1, false, "CDSN_MCLK2");
    m_parameters[CDSN_RXALML ].Set(0x00ad, 1, 1, 2, false, "CDSN_RXALML");
    m_parameters[CDSN_RXATSP].Set(0x00ad, 1, 1, 6, false, "CDSN_RXATSP");
    m_parameters[CDSN_RXBLML].Set(0x00ad, 1, 1, 3, false, "CDSN_RXBLML");
    m_parameters[CDSN_RXBTSP].Set(0x00ad, 1, 1, 7, false, "CDSN_RXBTSP");
    m_parameters[CDSN_TXALML].Set(0x00ad, 1, 1, 4, false, "CDSN_TXALML");
    m_parameters[CDSN_TXATSP].Set(0x00ad, 1, 1, 8, false, "CDSN_TXATSP");
    m_parameters[CDSN_TXBLML].Set(0x00ad, 1, 1, 5, false, "CDSN_TXBLML");
    m_parameters[CDSN_TXBTSP].Set(0x00ad, 1, 1, 9, false, "CDSN_TXBTSP");
    m_parameters[CDS_MCLK1].Set(0x00ad, 0, 2, 12, false, "CDS_MCLK1");
    m_parameters[CDS_MCLK2].Set(0x00ad, 0, 2, 14, false, "CDS_MCLK2");
    m_parameters[CDS_RXALML].Set(0x00ae, 0, 2, 0, false, "CDS_RXALML");
    m_parameters[CDS_RXATSP].Set(0x00ae, 0, 2, 8, false, "CDS_RXATSP");
    m_parameters[CDS_RXBLML].Set(0x00ae, 0, 2, 2, false, "CDS_RXBLML");
    m_parameters[CDS_RXBTSP].Set(0x00ae, 0, 2, 10, false, "CDS_RXBTSP");
    m_parameters[CDS_TXALML].Set(0x00ae, 0, 2, 4, false, "CDS_TXALML");
    m_parameters[CDS_TXATSP].Set(0x00ae, 0, 2, 12, false, "CDS_TXATSP");
    m_parameters[CDS_TXBLML].Set(0x00ae, 0, 2, 6, false, "CDS_TXBLML");
    m_parameters[CDS_TXBTSP].Set(0x00ae, 0, 2, 14, false, "CDS_TXBTSP");


    //New controls (EN_DIR_) in 0x081 and 0x0124 registers
    m_parameters[EN_DIR_SXRSXT].Set(0x0124, 0, 1, 4, true, "EN_DIR_SXRSXT");
    m_parameters[EN_DIR_RBB].Set(0x0124, 0, 1, 3, true, "EN_DIR_RBB");
    m_parameters[EN_DIR_RFE].Set(0x0124, 0, 1, 2, true, "EN_DIR_RFE");
    m_parameters[EN_DIR_TBB].Set(0x0124, 0, 1, 1, true, "EN_DIR_TBB");
    m_parameters[EN_DIR_TRF].Set(0x0124, 0, 1, 0, true, "EN_DIR_TRF");

    m_parameters[EN_DIR_LDO].Set(0x0081, 0, 1, 3, false, "EN_DIR_LDO");
    m_parameters[EN_DIR_CGEN].Set(0x0081, 0, 1, 2, false, "EN_DIR_CGEN");
    m_parameters[EN_DIR_XBUF].Set(0x0081, 0, 1, 1, false, "EN_DIR_XBUF");
    m_parameters[EN_DIR_AFE].Set(0x0081, 0, 1, 0, false, "EN_DIR_AFE");


    //Added CDC_I_TRF_(1,2)[3:0] and CDC_Q_TRF_(1,2)[3:0] to address 0x0104.
    m_parameters[CDC_I_TRF].Set(0x0104, 8, 4, 4, true, "CDC_I_TRF");
    m_parameters[CDC_Q_TRF].Set(0x0104, 8, 4, 0, true, "CDC_Q_TRF");
    //Added CDC_I_RFE_(1,2)[3:0] and CDC_Q_RFE_(1,2)[3:0] to address 0x010C.
    m_parameters[CDC_I_RFE].Set(0x010C, 8, 4, 12, true, "CDC_I_RFE");
    m_parameters[CDC_Q_RFE].Set(0x010C, 8, 4, 8, true, "CDC_Q_RFE");

    //New registers VER[4:0], REV[4:0], MASK[5:0] added, address 0x002F.
    m_parameters[VER].Set(0x002F, 7, 5, 11, false, "VER");
    m_parameters[REV].Set(0x002F, 1, 5, 6, false, "REV");
    m_parameters[MASK].Set(0x002F, 0, 6, 0, false, "MASK");

//New registers added:
//DC_REG[15:0] (0x020C[15:0] / 0x040B);
    m_parameters[DC_REG_TXTSP].Set(0x020C, 0, 16, 0, true, "DC_REG_TXTSP");
    m_parameters[DC_REG_RXTSP].Set(0x040B, 0, 16, 0, true, "DC_REG_RXTSP");

//INSEL (0x0200[2] / 0x0400[2]);
    m_parameters[INSEL_TXTSP].Set(0x0200, 0, 1, 2, true, "INSEL_TXTSP");
    m_parameters[INSEL_RXTSP].Set(0x0400, 0, 1, 2, true, "INSEL_RXTSP");
//TSGMODE (0x0200[3] / 0x0400[3]);
    m_parameters[TSGMODE_TXTSP].Set(0x0200, 0, 1, 3, true, "TSGMODE_TXTSP");
    m_parameters[TSGMODE_RXTSP].Set(0x0400, 0, 1, 3, true, "TSGMODE_RXTSP");
//TSGSWAPIQ (0x0200[4] / 0x0400[4]);
    m_parameters[TSGSWAPIQ_TXTSP].Set(0x0200, 0, 1, 4, true, "TSGSWAPIQ_TXTSP");
    m_parameters[TSGSWAPIQ_RXTSP].Set(0x0400, 0, 1, 4, true, "TSGSWAPIQ_RXTSP");
//TSGDCLDI (0x0200[5] / 0x0400[5]);
    m_parameters[TSGDCLDI_TXTSP].Set(0x0200, 0, 1, 5, true, "TSGDCLDI_TXTSP");
    m_parameters[TSGDCLDI_RXTSP].Set(0x0400, 0, 1, 5, true, "TSGDCLDI_RXTSP");
//TSGDCLDQ (0x0200[6] / 0x0400[6]);
    m_parameters[TSGDCLDQ_TXTSP].Set(0x0200, 0, 1, 6, true, "TSGDCLDQ_TXTSP");
    m_parameters[TSGDCLDQ_RXTSP].Set(0x0400, 0, 1, 6, true, "TSGDCLDQ_RXTSP");
//TSGFCW (0x0200[8:7] / 0x0400[8:7]);
    m_parameters[TSGFCW_TXTSP].Set(0x0200, 1, 2, 7, true, "TSGFCW_TXTSP");
    m_parameters[TSGFCW_RXTSP].Set(0x0400, 1, 2, 7, true, "TSGFCW_RXTSP");
//CAPSEL[1:0] (0x0400[3:2]);
    m_parameters[CAPSEL].Set(0x0400, 0, 2, 13, true, "CAPSEL");
//CAPTURE (0x0400[4]);
    m_parameters[CAPTURE].Set(0x0400, 0, 1, 15, true, "CAPTURE");
//CAPD[31:0].
    m_parameters[CAPD].Set(0x040e, 0, 32, 0, true, "CAPD");

    //defaults changed
    m_parameters[ICT_TIAMAIN_RFE].defValue = 2;
    m_parameters[ICT_TIAOUT_RFE].defValue = 2;
    m_parameters[ICT_LPF_H_PT_TBB].defValue = 2;
    m_parameters[ICT_IAMP_FRP_TBB].defValue = 2;
    m_parameters[ICT_IAMP_GG_FRP_TBB].defValue = 2;
    m_parameters[ICT_VCO_CGEN].defValue = 16;
    m_parameters[PD_VCO_CGEN].defValue = 0;
    m_parameters[ICT_VCO].defValue = 255;
    m_parameters[IPULSE_CP].defValue = 63;
    m_parameters[IOFFSET_CP].defValue = 12;
    m_parameters[RSEL_LDO_VCO].defValue = 6;
    m_parameters[ICT_LNA_RFE].defValue = 31;

    //create register masks
    map<unsigned short, unsigned short> masks;
    map<unsigned short, MemoryRegister>::iterator iter;
    for(int i=0; i<LMS_PARAMETER_COUNT; i++)
        SetParameterValue((LMS7002_Parameter)i, m_parameters[i].readonly ? 0 : 0xFFFFFFFF);
    for(int i=0; i<m_channelCount; ++i)
        for (iter = m_registers[i].begin(); iter != m_registers[i].end(); ++iter)
            m_registers[i][iter->first].mask = m_registers[i][iter->first].value;

    //Set default parameter values to registers
    SelectConfigChannel(0, true); //switch to configure A and B channels
    for(int i=0; i<LMS_PARAMETER_COUNT; i++)
    {
        SetParameterValue((LMS7002_Parameter)i, m_parameters[i].defValue);
    }

    //Set current register values as their default values
    unsigned short addr;
    for(int i=0; i<m_channelCount; ++i)
    {
        for (iter = m_registers[i].begin(); iter != m_registers[i].end(); ++iter)
        {
            addr = iter->first;
            m_registers[i][addr].address = addr;
            m_registers[i][addr].defaultValue = m_registers[i][addr].value;
        }
    }
    MessageLog::getInstance()->write("Registers map control parameters initialized.\n", LOG_INFO);
    //CheckForOverlays();

}

/** @brief Creates and initializes registers map to default values
*/
RegistersMap::RegistersMap( ConnectionManager *pConMng) : m_activeChannel(0),
    m_lastActiveChannel(0), m_autoUpload(true), m_autoDownload(false), m_configAllChannels(false)
{
    //define module registers intervals for individual register testing
    m_modulesInfo[LIME_LIGHT] = RegTestPlan("LimeLight", 0x0020, 0x002E, true),
    m_modulesInfo[AFE] = RegTestPlan("AFE", 0x0082, 0x0082, true);
    m_modulesInfo[BIAS] = RegTestPlan("BIAS", 0x0083, 0x0084, true);
    m_modulesInfo[XBUF] = RegTestPlan("XBUF", 0x0085, 0x0085, true);
    m_modulesInfo[CGEN] = RegTestPlan("CGEN", 0x0086, 0x008D, true);
    m_modulesInfo[LDO] = RegTestPlan("LDO", 0x0092, 0x00A7, true);
    m_modulesInfo[BIST] = RegTestPlan("BIST", 0x00A8, 0x00AC, true);
    m_modulesInfo[CDS] = RegTestPlan("CDS", 0x00AD, 0x00AE, true);

    m_modulesInfo[TRF] = RegTestPlan("TRF", 0x0100, 0x0104, true),
    m_modulesInfo[TBB] = RegTestPlan("TBB", 0x0105, 0x010B, true),
    m_modulesInfo[RFE] = RegTestPlan("RFE", 0x010C, 0x0114, true),
    m_modulesInfo[RBB] = RegTestPlan("RBB", 0x0115, 0x011B, true),
    m_modulesInfo[SXRSXT] = RegTestPlan("SXR_SXT", 0x011C, 0x0124, true),
    m_modulesInfo[TxTSP] = RegTestPlan("TxTSP", 0x0200, 0x0240-1, true),
    m_modulesInfo[TxNCO] = RegTestPlan("TxNCO", 0x0240, 0x0261, false),
    m_modulesInfo[RxTSP] = RegTestPlan("RxTSP", 0x0400, 0x0440-1, true),
    m_modulesInfo[RxNCO] = RegTestPlan("RxNCO", 0x0440, 0x0461, false),

    m_cancelRegisterTest = false;
    if(pConMng == NULL)
        MessageLog::getInstance()->write("RegistersMap - connection manager not assigned\n", LOG_ERROR);
    m_serPort = pConMng;
    InitializeControlParameters();
    SetDefaultValues();
}

RegistersMap::~RegistersMap()
{
}

/** @brief Loads register values from binary file
    @param filename file to read
    @return true if success
*/
bool RegistersMap::LoadFromFile(const string filename)
{
    ifstream fin;
    fin.open(filename.c_str(), ios::in | ios::binary);
    bool status = LoadFromStream(fin);
    fin.close();
    stringstream ss;
    ss << "Configuration loaded from file " << filename << endl;
    MessageLog::getInstance()->write(ss.str());
    return status;
}

/** @brief Loads register values from binary stream
    @param fin stream to read
    @return true if success

    Data file consists of 16 bit values of addresses and values.

    Binary file description:
    14 bytes text header, 2 bytes number of channels

    channels description:
    14 bytes text header, 2 bytes number of address and data pairs,
    address(2 bytes), data(2 bytes)...
*/
bool RegistersMap::LoadFromStream(ifstream &fin)
{
    unsigned short addr;
    unsigned short value;
    std::map<unsigned short, MemoryRegister>::iterator iter;

    unsigned short channelsCount;
    unsigned short pairCount;
    char carr[16];
    //fin.open(filename.c_str(), ios::in | ios::binary);
    memset(carr,0, 16);
    fin.read(carr, 14); // Text header
    fin.read((char*)&channelsCount, 2); //number of channels
    for(int i=0; i<channelsCount && i<m_channelCount; ++i)
    {
        memset(carr,0, 16);
        fin.read(carr, 14); // channel text header
        fin.read((char*)&pairCount, 2); //number of address value pairs
        for(int j=0; j<pairCount; ++j)
        {
            fin.read((char*)&addr, 2); // register address
            fin.read((char*)&value, 2);// register value
            m_registers[i][addr].value = value;
        }
    }

    //fin.close();
    return true;
}

/** @brief Saves current register values to binary file
    @param filename file to save into
    @return true if success
    Saving format documented in SaveToStream method.
*/
bool RegistersMap::SaveToFile(const string filename)
{
    ofstream fout;
    fout.open(filename.c_str(), ios::out | ios::binary);
    bool status = SaveToStream(fout);
    fout.close();
    stringstream ss;
    ss << "Configuration saved to file " << filename << endl;
    MessageLog::getInstance()->write(ss.str());
    return status;
}

/** @brief Saves current register values to binary stream
    @param fout stream to write into
    @return true if success

    Binary file description:
    14 bytes text header, 2 bytes number of channels

    channels description:
    14 bytes text header, 2 bytes number of address and data pairs,
    address(2 bytes), data(2 bytes)...
*/
bool RegistersMap::SaveToStream(ofstream &fout)
{
    unsigned short addr;
    unsigned short value;
    std::map<unsigned short, MemoryRegister>::iterator iter;
    vector<unsigned short> data;

    char carr[16];
    memset(carr, 0, sizeof(carr));
    sprintf(carr, "%s" , "LMS7002 CONFIG");
    fout.write(carr, 14);
    unsigned short chCount = m_channelCount;
    fout.write((const char*)&chCount, 2);
    for(int i=0; i<m_channelCount; ++i)
    {
        unsigned short blockCount = 0;
        memset(carr, 0, sizeof(carr));
        sprintf(carr, "ch.%i Registers" , i);
        fout.write(carr, 14);
        for (iter = m_registers[i].begin(); iter != m_registers[i].end(); ++iter)
        {
            addr = iter->first;
            value = m_registers[i][addr].value;
            data.push_back(addr);
            data.push_back(value);
            ++blockCount;
        }
        fout.write((const char*)&blockCount, sizeof(blockCount));
        fout.write((const char*)&data[0], data.size()*sizeof(unsigned short));
        data.clear();
    }
    return true;
}

/** @brief Sets register value
    @param address register address
    @param value new value written to register
    @return true if operation succeeded
*/
bool RegistersMap::SetRegisterValue(unsigned short address, unsigned short value)
{
    bool status = false;
    int channelToWrite = m_activeChannel;
    if(m_serPort->IsOpen() && m_autoUpload)
    {
        unsigned short buf[2];
        buf[0] = address;
        unsigned short mask = GetRegisterMask(address);
//        if(mask != 0xFFFF)
//            printf("address 0x%04X  uses mask 0x%04X\n", address, mask);
        buf[1] = value & mask;
        if( m_serPort->SendData(CMD_LMS7002_WR, (const unsigned char*)buf, sizeof(buf)) == STATUS_COMPLETED_CMD )
        {
            stringstream ss;
//            ss << "Register " << int2hex(address, sizeof(address)) << " value " << int2hex(m_registers[channelToWrite][address].value, sizeof(value)) << " changed to " << int2hex(value, sizeof(value)) << endl;
//            MessageLog::getInstance()->write(ss.str(), LOG_DATA);
            m_registers[channelToWrite][address].value = value;
            status = true;
        }
        else
        {
            //stringstream ss;
            //ss << "Failed to change Register " << int2hex(address, sizeof(address)) << " value" << endl;
            //MessageLog::getInstance()->write(ss.str(), LOG_WARNING);
            m_registers[channelToWrite][address].value = value;
            status = false;
        }
    }
    else
        m_registers[channelToWrite][address].value = value;

    return status;
}

/** @brief Returns register value from given address
    @param address register address
    @return register value
*/
unsigned short RegistersMap::GetRegisterValue(unsigned short address, bool fromChip, bool updateLocal)
{
    if(m_serPort->IsOpen() && (m_autoDownload || fromChip))
    {
        long unsigned len = ConnectionManager::cMAX_CONTROL_PACKET_SIZE;
        unsigned short outbuf[1];
        outbuf[0] = address;
		unsigned short buf[ConnectionManager::cMAX_CONTROL_PACKET_SIZE];
        memset(buf, 0, len);
        unsigned long outlen = sizeof(outbuf);
        if( m_serPort->SendReadData(CMD_LMS7002_RD, (const unsigned char*)&outbuf, outlen, (unsigned char*)buf, len) == STATUS_COMPLETED_CMD)
        {
            if(updateLocal)
                m_registers[m_activeChannel][address].value = buf[1];
            else
                return buf[1];
        }
    }
    return m_registers[m_activeChannel][address].value;
}

/** @brief Sets selected parameter value in register
    @param param LMS7002 parameter enumerator
    @param value new value assigned to parameter
    @return true if operation succeeded

    Writing parameters that span more than one register, or need special treatment should be handled in switch cases.
    The default handling of multi address parameter is when current address bits are used, address is increased by 1, parameter LSB is at the lowest address
*/
bool RegistersMap::SetParameterValue(LMS7002_Parameter param, unsigned long value)
{
    ControlParameter cp = m_parameters[param];
	bool status = false;
	unsigned short regValue = 0;
	unsigned short newValue = 0;
	unsigned long mask = 0xFFFFFFFF;
	unsigned int channelToSet;
	mask = mask << cp.bitCount;
    mask = ~mask;

    switch(param)
    {
		default: //no special treatment is required, just write to register
			channelToSet = cp.multichannel ? m_activeChannel : 0;

			for(int d=0; d<(cp.bitCount+cp.LSBpos)/16 + ((cp.bitCount+cp.LSBpos)%16 > 0); ++d)
            {
                regValue = m_registers[channelToSet][cp.address+d].value; //read register value
                regValue &= ~((mask << cp.LSBpos) >> d*16); //clear paramter bits
                newValue = ((value & mask)<< cp.LSBpos) >> d*16; //form new value
                regValue |= newValue; //insert into register value
                if(m_configAllChannels && cp.multichannel)
                {
                    int prevChannel = m_activeChannel;
                    for(int i=0; i<m_channelCount; ++i)
                    {
                        SelectConfigChannel(i, m_configAllChannels);
                        //m_activeChannel = i;
                        status = SetRegisterValue(cp.address+d, regValue);
                    }
                    //m_activeChannel = prevChannel;
                    SelectConfigChannel(prevChannel, m_configAllChannels);
                }
                else if(m_activeChannel != channelToSet)
                {
                    int prevChannel = m_activeChannel;
                    SelectConfigChannel(channelToSet, m_configAllChannels);
                    status = SetRegisterValue(cp.address+d, regValue);
                    SelectConfigChannel(prevChannel, m_configAllChannels);
                }
                else
                    status = SetRegisterValue(cp.address+d, regValue);
            }
    }
	return status;
}

/** @brief Returns selected parameter value from register
    @param param LMS7002 parameter enumerator
    @return parameter value

    Reading parameters that span more than one register, or need special treatment should be handled in switch cases.
    The default handling of multi address parameter is when current address bits are used, address is increased by 1, parameter LSB is at the lowest address
*/
unsigned long RegistersMap::GetParameterValue(LMS7002_Parameter param, bool fromChip, bool updateLocal)
{
    ControlParameter cp = m_parameters[param];
	unsigned long retValue = 0;
    unsigned long regValue = 0;
    unsigned long mask = 0xFFFFFFFF;
    //mask = mask << cp.bitCount;
    for(int i=0; i<cp.bitCount; ++i)
        mask = mask << 1;
    mask = ~mask;

    switch(param)
    {
		default:
        for(int d=0; d<(cp.bitCount+cp.LSBpos)/16 + ((cp.bitCount+cp.LSBpos)%16 > 0); ++d)
        {
            if((m_autoDownload || fromChip) && m_serPort->IsOpen())
                regValue = m_serPort->mSPI_read(cp.address+d);
            else
                regValue = m_registers[cp.multichannel ? m_activeChannel : 0][cp.address+d].value;
            if(updateLocal)
                m_registers[cp.multichannel ? m_activeChannel : 0][cp.address+d].value = regValue;
            retValue |= regValue << d*16;
        }
        retValue = (retValue >> cp.LSBpos) & mask;
    }

    switch(param)
    {
    default:
        //do nothing
        break;
    }

	return retValue;
}

/** @brief Downloads all configuration from chip and writes it to file. Local register map is not updated
    @param filename file to create
    @return true if success
*/
bool RegistersMap::DownloadToHex(const string filename)
{
    if(!m_serPort->IsOpen())
    {
        MessageLog::getInstance()->write("Download to Hex file failed - control port not connected\n");
        return false;
    }
    std::map<unsigned short, MemoryRegister> tempMemory[m_channelCount];

    vector<unsigned short> addrToRead;
    std::map<unsigned short, MemoryRegister>::iterator iter;
    int success = 0;
    for(int i=0; i<m_channelCount; ++i)
    {
        SelectConfigChannel(i, false);
        for (iter = m_registers[i].begin(); iter != m_registers[i].end(); ++iter)
        {
            addrToRead.push_back(iter->first);
        }
        int bufSize = addrToRead.size()*sizeof(unsigned short);
        unsigned short *inbuf = new unsigned short[addrToRead.size()*2];
        memset(inbuf, 0, sizeof(unsigned short)*addrToRead.size()*2);
        unsigned long readLen = bufSize*2;
        success = m_serPort->SendReadData(CMD_LMS7002_RD, (const unsigned char*)&addrToRead[0], addrToRead.size()*sizeof(unsigned short), (unsigned char*)inbuf, readLen);
        if(success == STATUS_COMPLETED_CMD)
        {
            for(unsigned int j=0; j<readLen/4; ++j)
                tempMemory[i][addrToRead[j]].value = inbuf[1+j*2];
        }
        else
        {
            delete []inbuf;
            break;
        }
        addrToRead.clear();
        delete []inbuf;
        SelectConfigChannel(m_lastActiveChannel, false);
    }
    if(success == STATUS_COMPLETED_CMD)
        MessageLog::getInstance()->write("Downloaded all configuration to Hex\n");
    else
    {
        MessageLog::getInstance()->write("Failed to download all configuration to Hex\n", LOG_WARNING);
        return false;
    }

    fstream fout;
    unsigned short addr;
    unsigned short value;
    vector<unsigned short> data;

    fout.open(filename.c_str(), ios::out | ios::binary);
    char carr[16];
    memset(carr, 0, sizeof(carr));
    sprintf(carr, "%s" , "LMS7002 CONFIG");
    fout.write(carr, 14);
    unsigned short chCount = m_channelCount;
    fout.write((const char*)&chCount, 2);
    for(int i=0; i<m_channelCount; ++i)
    {
        unsigned short blockCount = 0;
        memset(carr, 0, sizeof(carr));
        sprintf(carr, "ch.%i Registers" , i);
        fout.write(carr, 14);
        for (iter = tempMemory[i].begin(); iter != tempMemory[i].end(); ++iter)
        {
            addr = iter->first;
            value = tempMemory[i][addr].value;
            data.push_back(addr);
            data.push_back(value);
            //fout << hex << addr << ' ' << value << endl;
            ++blockCount;
        }
        fout.write((const char*)&blockCount, sizeof(blockCount));
        fout.write((const char*)&data[0], data.size()*sizeof(unsigned short));
        data.clear();
    }

    fout.close();
    stringstream ss;
    ss << "Configuration saved to Hex file " << filename << endl;
    MessageLog::getInstance()->write(ss.str());
    return true;
}

/** @brief Reads all registers from the chip
    @return true if success
*/
bool RegistersMap::DownloadAll()
{
    if(!m_serPort->IsOpen())
    {
        MessageLog::getInstance()->write("Download all configuration failed - control port not connected\n");
        return false;
    }

    vector<unsigned short> addrToRead;
    std::map<unsigned short, MemoryRegister>::iterator iter;
    int success = 0;
    for(int i=0; i<m_channelCount; ++i)
    {
        SelectConfigChannel(i, false);
        for (iter = m_registers[i].begin(); iter != m_registers[i].end(); ++iter)
        {
            addrToRead.push_back(iter->first);
        }
        int bufSize = addrToRead.size()*sizeof(unsigned short);
        unsigned short *inbuf = new unsigned short[addrToRead.size()*2];
        memset(inbuf, 0, sizeof(unsigned short)*addrToRead.size()*2);
        unsigned long readLen = bufSize*2;
        success = m_serPort->SendReadData(CMD_LMS7002_RD, (const unsigned char*)&addrToRead[0], addrToRead.size()*sizeof(unsigned short), (unsigned char*)inbuf, readLen);
        if(success == STATUS_COMPLETED_CMD)
        {
            for(unsigned int j=0; j<readLen/4; ++j)
                m_registers[i][addrToRead[j]].value = inbuf[1+j*2];
        }
        else
        {
            delete []inbuf;
            break;
        }
        addrToRead.clear();
        delete []inbuf;
        SelectConfigChannel(m_lastActiveChannel, false);
    }
    if(success == STATUS_COMPLETED_CMD)
        MessageLog::getInstance()->write("Downloaded all configuration\n");
    else
        MessageLog::getInstance()->write("Failed to download all configuration\n", LOG_WARNING);
    return success;
}

/** @brief Writes all registers to the chip
    @return true if success
*/
bool RegistersMap::UploadAll()
{
    if(!m_serPort->IsOpen())
    {
        MessageLog::getInstance()->write("Upload all configuration failed - control port not connected\n");
        return false;
    }

    vector<unsigned short> addrToWrite;
    std::map<unsigned short, MemoryRegister>::iterator iter;
    int success = 0;
    int prevUsedChannel = m_activeChannel;
    for(int i=0; i<m_channelCount; ++i)
    {
        SelectConfigChannel(i, false);
        for (iter = m_registers[i].begin(); iter != m_registers[i].end(); ++iter)
        {
            addrToWrite.push_back(iter->first); //address
            addrToWrite.push_back(iter->second.value); //value
        }
        success = m_serPort->SendData(CMD_LMS7002_WR, (const unsigned char*)&addrToWrite[0], addrToWrite.size()*sizeof(unsigned short));
        if(success != STATUS_COMPLETED_CMD)
        {
            break;
        }
        addrToWrite.clear();
    }
    SelectConfigChannel(prevUsedChannel, m_configAllChannels);
    if(success == STATUS_COMPLETED_CMD)
    {
        MessageLog::getInstance()->write("Uploaded all configuration\n");
        return true;
    }
    else
        MessageLog::getInstance()->write("Failed to upload all configuration\n", LOG_WARNING);
    return false;
}

/** @brief Sets default register values
*/
void RegistersMap::SetDefaultValues()
{
    unsigned short addr;
    std::map<unsigned short, MemoryRegister>::iterator iter;
    for(int i=0; i<m_channelCount; ++i)
        for (iter = m_registers[i].begin(); iter != m_registers[i].end(); ++iter)
        {
            addr = iter->first;
            m_registers[i][addr].value = m_registers[i][addr].defaultValue;
        }
    MessageLog::getInstance()->write("Registers set to default values\n");
    if(m_serPort->IsOpen())
        UploadAll();
}

/** @brief Selects which chip channel to configure.
    @param channel channel index starting from 0
    @param configAll send configuration to all channels
*/
void RegistersMap::SelectConfigChannel(int channel, bool configAll)
{
    m_lastActiveChannel = m_activeChannel;
    m_lastConfigAll = m_configAllChannels;
    m_configAllChannels = configAll;
    if(configAll)
    {
        m_activeChannel = 0; //channel selecting always in 0
        SetParameterValue(MAC, 3);
        m_activeChannel = channel;
    }
    else
        switch(channel)
        {
        case 0:
            m_activeChannel = 0; //channel selecting always in 0
            SetParameterValue(MAC, 1);
            m_activeChannel = channel;
            break;
        case 1:
            m_activeChannel = 0; //channel selecting always in 0
            SetParameterValue(MAC, 2);
            m_activeChannel = channel;
            break;
        }
}

/** @brief Switch back to last used channel config
*/
void RegistersMap::RestoreLastSelectedChannel()
{
    SelectConfigChannel(m_lastActiveChannel, m_lastConfigAll);
}

/** @brief Returns currently selected channel for configuration
    @return channel index
*/
int RegistersMap::GetConfigChannel() const
{
    return m_activeChannel;
}

/** @brief Sets whether parameter changes should be written to chip immediately
    @param enabled automatic writing enabled
*/
void RegistersMap::SetAutoUpload(bool enabled)
{
    m_autoUpload = enabled;
}

/** @brief Returns automatic uploading state
    @return true if auto upload enabled
*/
bool RegistersMap::GetAutoUpload() const
{
    return m_autoUpload;
}

/** @brief Sets whether register values should be read back from chip for making new values.
    @param enabled parameter values read-back enabled
*/
void RegistersMap::SetAutoDownload(bool enabled)
{
    m_autoDownload = enabled;
}

/** @brief Returns automatic downloading state
    @return true if auto download enabled
*/
bool RegistersMap::GetAutoDownload() const
{
    return m_autoDownload;
}

/** @brief Checks if there are no parameters with overlapping bits
*/
bool RegistersMap::CheckForOverlays()
{
    cout << "Checking for overlapping bits" << endl;
    bool status = false;
    SetAutoUpload(false); //write and read locally from memory
    SetAutoDownload(false);
    //set all memory to zeros
    for(int i=0; i<LMS_PARAMETER_COUNT; i++)
        SetParameterValue((LMS7002_Parameter)i, 0);
    //read parameter and check if all bits are zeros, then fill with ones
    unsigned long value = 0;
    for(int i=0; i<LMS_PARAMETER_COUNT; i++)
    {
        value = 0;
        value = GetParameterValue((LMS7002_Parameter)i);
        if(value != 0)
        {
            cout << m_parameters[i].m_name << " Register bits overlapping at address " << int2hex(m_parameters[i].address, 2) << endl;
            status = true;
        }

        unsigned long mask = 0xffffffff;
        mask = mask << m_parameters[i].bitCount;
        mask = ~mask;
        SetParameterValue((LMS7002_Parameter)i, mask);

        //readback to ensure correct writing
        value = 0;
        value = GetParameterValue((LMS7002_Parameter)i);
        if(value != mask)
            cout << m_parameters[i].m_name << " writing failed at address " << int2hex(m_parameters[i].address, 2) << "   set value " << mask << "  read value " << value << endl;
    }
//    SetAutoUpload(true);
//    SetAutoDownload(true);
    cout << "Overlay checking finished" << endl;
    return status;
}

/** @brief Performs register testing
    @return true if registers work correctly
*/
bool RegistersMap::RegisterTest()
{
    m_cancelRegisterTest = false;
    const int testsCommonCount = 8;
    RegTestPlan testsCommon[testsCommonCount] =
    {
        RegTestPlan("LimeLight", 0x0020, 0x002E, true),
        RegTestPlan("AFE", 0x0082, 0x0082, true),
        RegTestPlan("BIAS", 0x0083, 0x0084, true),
        RegTestPlan("XBUF", 0x0085, 0x0085, true),
        RegTestPlan("CGEN", 0x0086, 0x008D, true),
        RegTestPlan("LDO", 0x0092, 0x00A7, true),
        RegTestPlan("BIST", 0x00A8, 0x00AC, true),
        RegTestPlan("CDS", 0x00AD, 0x00AE, true)
    };

    const int testsChannelsCount = 19;
    RegTestPlan testsChannels[testsChannelsCount] =
    {
        RegTestPlan("TRF ", 0x0100, 0x0104, true),
        RegTestPlan("TBB ", 0x0105, 0x010B, true),
        RegTestPlan("RFE ", 0x010C, 0x0114, true),
        RegTestPlan("RBB ", 0x0115, 0x011B, true),
        RegTestPlan("SXR_SXT ", 0x011C, 0x0124, true),
        RegTestPlan("TxTSP", 0x0200, 0x0240-1, true),
        RegTestPlan("TxNCO", 0x0240, 0x0261, false),
        RegTestPlan("TxGFIR1", 0x0280, 0x02A8-1, false),
        RegTestPlan("TxGFIR2", 0x02C0, 0x02E8-1, false),
        RegTestPlan("TxGFIR3a", 0x0300, 0x0328-1, false),
        RegTestPlan("TxGFIR3b", 0x0340, 0x0368-1, false),
        RegTestPlan("TxGFIR3c", 0x0380, 0x03A8-1, false),

        RegTestPlan("RxTSP", 0x0400, 0x0440-1, true),
        RegTestPlan("RxNCO", 0x0440, 0x0461, false),
        RegTestPlan("RxGFIR1", 0x0480, 0x04A8-1, false),
        RegTestPlan("RxGFIR2", 0x04C0, 0x04E8-1, false),
        RegTestPlan("RxGFIR3a", 0x0500, 0x0528-1, false),
        RegTestPlan("RxGFIR3b", 0x0540, 0x0568-1, false),
        RegTestPlan("RxGFIR3c", 0x0580, 0x05A8-1, false),
    };

    if(!m_serPort->IsOpen())
    {
        MessageLog::getInstance()->write("Registers test canceled: control port not connected.\n", LOG_WARNING);
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Registers test canceled: control port not connected.\n", 0, 0));
        return false;
    }

    bool status = true;
    int retVal = 0;
    MessageLog::getInstance()->write("Registers test started.\n", LOG_INFO);
    m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Register test started\n", 0, 0));

    for(int i=0; i<testsCommonCount && !m_cancelRegisterTest ; ++i)
    {
        string name = testsCommon[i].name;
        unsigned short sadr = testsCommon[i].startAddr;
        unsigned short eadr = testsCommon[i].endAddr;
        char ctemp[40];
        sprintf(ctemp, " [0x%04X : 0x%04X]", sadr, eadr);
        name.append(ctemp);
        bool bused = testsCommon[i].onlyUsedAddresses;
        retVal = TestRegistersWithinRange( name, sadr, eadr, bused);
        if( retVal >= 0)
            status &= retVal;
        else
            return false;
    }

    if(m_cancelRegisterTest)
    {
        MessageLog::getInstance()->write("Registers test canceled.\n", LOG_INFO);
        return false;
    }
    char testName[128];
    //test channel A
    m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "\nTesting Channel A\n", 0, 0));
    SetParameterValue(MAC, 1);

    for(int i=0; i<testsChannelsCount && !m_cancelRegisterTest; ++i)
    {
        sprintf(testName, "%s [0x%04X : 0x%04X] channel A", testsChannels[i].name.c_str(), testsChannels[i].startAddr, testsChannels[i].endAddr);
        retVal = TestRegistersWithinRange( testName, testsChannels[i].startAddr, testsChannels[i].endAddr, testsChannels[i].onlyUsedAddresses);
        if( retVal >= 0)
            status &= retVal;
        else
            return false;
    }

    if(m_cancelRegisterTest)
    {
        MessageLog::getInstance()->write("Registers test canceled.\n", LOG_INFO);
        return false;
    }

    m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "\nTesting Channel B\n", 0, 0));
    SetParameterValue(MAC, 2);
    SetParameterValue(MIMO_SISO, 0);

    for(int i=0; i<testsChannelsCount && !m_cancelRegisterTest; ++i)
    {
        sprintf(testName, "%s channel B", testsChannels[i].name.c_str());
        retVal = TestRegistersWithinRange( testName, testsChannels[i].startAddr, testsChannels[i].endAddr, testsChannels[i].onlyUsedAddresses);
        if( retVal >= 0)
            status &= retVal;
        else
            return false;
    }

    if(m_cancelRegisterTest)
    {
        MessageLog::getInstance()->write("Registers test canceled.\n", LOG_INFO);
        return false;
    }

    if(status == true)
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Registers test PASSED", 0, 0));
    else
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Registers test FAILED", 0, 0));
    return status;
}

/** @brief Stops registers test if it is running
*/
void RegistersMap::CancelRegisterTest()
{
    m_cancelRegisterTest = true;
}

/** @brief Tests used registers within given address range
    @param name test name
    @param addr1 starting address
    @param addr2 end address
    @param onlyUsed whether test only used registers or all available registers
    @return -1 timeout, 0 failed, 1 passed
*/
int RegistersMap::TestRegistersWithinRange(const string name, unsigned short addr1, unsigned short addr2, bool onlyUsed)
{
    string title = "\n";
    title.append(name);
    title.append("\n");
    m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, title, 0, 0));
    bool testResult = true;
    int status;
    int patternCount = 2;
    unsigned short testPatterns[2] = {0xFFFF, 0xAAAA};
    //find registers within range
    vector<MemoryRegister> usedRegs;
    if(onlyUsed)
    {
        std::map<unsigned short, MemoryRegister>::iterator iter;
        for (iter = m_registers[0].begin(); iter != m_registers[0].end(); ++iter)
        {
            if(iter->first > addr2)
                break;

            if(iter->first >= addr1)
                usedRegs.push_back(m_registers[0][iter->first]);
        }
    }
    else
    {
        for(int i=0; i<=addr2-addr1; ++i)
        {
            usedRegs.push_back( MemoryRegister() );
            usedRegs[i].address = addr1+i;
        }
    }
    //write data
    vector<unsigned short> writtenBuffer;
    unsigned short *inBuffer = new unsigned short[usedRegs.size()*2];
    memset(inBuffer, 0, usedRegs.size()*2*sizeof(unsigned short));
    for(int p=0; p<patternCount; ++p)
    {
        testResult = true;
        writtenBuffer.clear();
        unsigned short writeValue = 0;
        for(unsigned i=0; i<usedRegs.size(); ++i)
        {
            writtenBuffer.push_back(usedRegs[i].address);
//#warning this condition is needed not to change SPI mode, or latter tests will fail
            writeValue = testPatterns[p] & GetRegisterMask(usedRegs[i].address);
            if(usedRegs[i].address == 0x0021)
            {
                writtenBuffer.push_back(writeValue | 0x0001);
            }
            else
                writtenBuffer.push_back(writeValue);
        }
        unsigned long bytesToSend, bytesToRead;
        bytesToSend = writtenBuffer.size()*sizeof(unsigned short);
        bytesToRead = bytesToSend*2;

        status = m_serPort->SendData(CMD_LMS7002_WR, (unsigned char*)&writtenBuffer[0], bytesToSend);
        if(status != STATUS_COMPLETED_CMD)
        {
            m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Register Test FAILED: error writing data.\n", 0, 0));
            return -1;
        }

        vector<unsigned short> outBuffer;
        for(unsigned i=0; i<usedRegs.size(); ++i)
            outBuffer.push_back(usedRegs[i].address);
        bytesToSend = outBuffer.size()*sizeof(unsigned short);
        bytesToRead = 2*bytesToSend;

        status = m_serPort->SendReadData(CMD_LMS7002_RD, (unsigned char*)&outBuffer[0], bytesToSend, (unsigned char*)inBuffer, bytesToRead);
        if(status != STATUS_COMPLETED_CMD)
        {
            m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Register Test FAILED: error reading data.", 0, 0));
            delete inBuffer;
            inBuffer = NULL;
            return -1;
        }
        //compare results
        stringstream ssr;
        ssr.clear();
        ssr.str( string() );
        unsigned short readValue = 0;
        for(unsigned int i=0; i<outBuffer.size(); ++i)
        {
            readValue = inBuffer[1+i*2] & GetRegisterMask(inBuffer[i*2]);
            if( readValue != writtenBuffer[1+i*2])
            {
                ssr << "address " << int2hex(outBuffer[i],2) << " (write/read) : " << int2hex(writtenBuffer[1+i*2], 2) << "/" << int2hex(inBuffer[1+i*2], 2) << endl;
                testResult = 0;
            }
        }

        if(testResult == 1)
        {
            ssr.clear();
            ssr.str( string() );
            ssr << "Registers OK : (write/read) : " << int2hex(testPatterns[p], 2) << "/" << int2hex(testPatterns[p], 2) << endl;
            m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, ssr.str(), 0, 0));
        }
        else
        {
            m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, ssr.str(), 0, 0));
        }
    }
    delete inBuffer;
    inBuffer = NULL;
    return testResult;
}

/** @brief Tests used registers within given address range
    @param name test name
    @param addr1 starting address
    @param addr2 end address
    @param pattern data pattern to write for testing
    @param onlyUsed whether test only used registers or all available registers
    @return -1 timeout, 0 failed, 1 passed
*/
int RegistersMap::RegisterTestBatch(const string name, const unsigned short addr1, const unsigned short addr2, const unsigned short pattern, const bool onlyUsed)
{
    string title = "";
    title.append(name);
    char ctemp[80];
    sprintf(ctemp, "  interval [%#.4x : %#.4x]", addr1, addr2);
    title.append(ctemp);
    title.append("\n");
    m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, title, 0, 0));
    bool testResult = true;
    int status;
    //find registers within range
    vector<MemoryRegister> usedRegs;
    if(onlyUsed)
    {
        std::map<unsigned short, MemoryRegister>::iterator iter;
        for (iter = m_registers[0].begin(); iter != m_registers[0].end(); ++iter)
        {
            if(iter->first > addr2)
                break;

            if(iter->first >= addr1)
                usedRegs.push_back(m_registers[0][iter->first]);
        }
    }
    else
    {
        for(int i=0; i<=addr2-addr1; ++i)
        {
            usedRegs.push_back( MemoryRegister() );
            usedRegs[i].address = addr1+i;
        }
    }
    //write data
    vector<unsigned short> writtenBuffer;
    unsigned short *inBuffer = new unsigned short[usedRegs.size()*2];
    memset(inBuffer, 0, usedRegs.size()*2*sizeof(unsigned short));

    testResult = true;
    writtenBuffer.clear();
    unsigned short writeValue = 0;
    for(unsigned i=0; i<usedRegs.size(); ++i)
    {
        writtenBuffer.push_back(usedRegs[i].address);
//#warning this condition is needed not to change SPI mode, or latter tests will fail
        writeValue = pattern & GetRegisterMask(usedRegs[i].address);
        if(usedRegs[i].address == 0x0021)
        {
            writtenBuffer.push_back(writeValue | 0x0001);
        }
        else
            writtenBuffer.push_back(writeValue);
    }
    unsigned long bytesToSend, bytesToRead;
    bytesToSend = writtenBuffer.size()*sizeof(unsigned short);
    bytesToRead = bytesToSend*2;

    status = m_serPort->SendData(CMD_LMS7002_WR, (unsigned char*)&writtenBuffer[0], bytesToSend);
    if(status != STATUS_COMPLETED_CMD)
    {
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Register Test FAILED: error writing data.", 0, 0));
        return -1;
    }

    vector<unsigned short> outBuffer;
    for(unsigned i=0; i<usedRegs.size(); ++i)
        outBuffer.push_back(usedRegs[i].address);
    bytesToSend = outBuffer.size()*sizeof(unsigned short);
    bytesToRead = 2*bytesToSend;

    status = m_serPort->SendReadData(CMD_LMS7002_RD, (unsigned char*)&outBuffer[0], bytesToSend, (unsigned char*)inBuffer, bytesToRead);
    if(status != STATUS_COMPLETED_CMD)
    {
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Register Test FAILED: error reading data.", 0, 0));
        return -1;
    }
    //compare results
    stringstream ssr;
    ssr.clear();
    ssr.str( string() );
    unsigned short readValue = 0;
    for(unsigned int i=0; i<outBuffer.size(); ++i)
    {
        readValue = inBuffer[1+i*2] & GetRegisterMask(inBuffer[i*2]);
        if( readValue != writtenBuffer[1+i*2])
        {
            ssr << "address " << int2hex(outBuffer[i],2) << " (write/read) : " << int2hex(writtenBuffer[1+i*2], 2) << "/" << int2hex(inBuffer[1+i*2], 2) << endl;
            testResult = 0;
        }
    }

    if(testResult == 1)
    {
        ssr.clear();
        ssr.str( string() );
        ssr << "Registers OK : (write/read) : " << int2hex(pattern, 2) << "/" << int2hex(pattern, 2) << endl;
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, ssr.str(), 0, 0));
    }
    else
    {
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, ssr.str(), 0, 0));
    }

    delete inBuffer;
    inBuffer = NULL;
    return testResult;
}

/** @brief Tests used registers within given address range
    @param name test name
    @param addr1 starting address
    @param addr2 end address
    @param pattern data pattern to write for testing
    @param onlyUsed whether test only used registers or all available registers
    @return -1 timeout, 0 failed, 1 passed
*/
int RegistersMap::RegisterTestSimple(const string name, const unsigned short addr1, const unsigned short addr2, const unsigned short pattern, const bool onlyUsed)
{
    string title = "";
    title.append(name);
    char ctemp[80];
    sprintf(ctemp, "  interval [%#.4x : %#.4x]", addr1, addr2);
    title.append(ctemp);
    title.append("\n");
    m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, title, 0, 0));
    bool testResult = true;

    //find registers within range
    vector<MemoryRegister> usedRegs;
    if(onlyUsed)
    {
        std::map<unsigned short, MemoryRegister>::iterator iter;
        for (iter = m_registers[0].begin(); iter != m_registers[0].end(); ++iter)
        {
            if(iter->first > addr2)
                break;

            if(iter->first >= addr1)
                usedRegs.push_back(m_registers[0][iter->first]);
        }
    }
    else
    {
        for(int i=0; i<=addr2-addr1; ++i)
        {
            usedRegs.push_back( MemoryRegister() );
            usedRegs[i].address = addr1+i;
        }
    }
    //prepare data for writing
    vector<unsigned short> writtenBuffer;
    unsigned short *inBuffer = new unsigned short[usedRegs.size()*2];
    memset(inBuffer, 0, usedRegs.size()*2*sizeof(unsigned short));
    testResult = true;
    unsigned short writeValue = 0;
    for(unsigned i=0; i<usedRegs.size(); ++i)
    {
        writtenBuffer.push_back(usedRegs[i].address);
//#warning this condition is needed not to change SPI mode, or latter tests will fail
        writeValue = pattern & GetRegisterMask(usedRegs[i].address);
        if(usedRegs[i].address == 0x0021)
        {
            writtenBuffer.push_back(writeValue | 0x0001);
        }
        else
            writtenBuffer.push_back(writeValue);
    }

    for(unsigned i=0; i<writtenBuffer.size(); i+=2)
    {
        if( m_serPort->mSPI_write(writtenBuffer[i], writtenBuffer[i+1]) != STATUS_COMPLETED_CMD)
        {
            m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, "Register Test FAILED: error writing data.", 0, 0));
            return -1;
        }
        inBuffer[i] = writtenBuffer[i];
        inBuffer[i+1] = m_serPort->mSPI_read(writtenBuffer[i]);
    }


    //compare results
    stringstream ssr;
    ssr.clear();
    ssr.str( string() );
    unsigned short readValue = 0;
    for(unsigned int i=0; i<writtenBuffer.size()/2; ++i)
    {
        readValue = inBuffer[1+i*2] & GetRegisterMask(inBuffer[i*2]);
        if( readValue != writtenBuffer[1+i*2])
        {
            ssr << "address " << int2hex(writtenBuffer[i*2],2) << " (write/read) : " << int2hex(writtenBuffer[1+i*2], 2) << "/" << int2hex(inBuffer[1+i*2], 2) << endl;
            testResult = 0;
        }
    }

    if(testResult == 1)
    {
        ssr.clear();
        ssr.str( string() );
        ssr << "Registers OK : (write/read) : " << int2hex(pattern, 2) << "/" << int2hex(pattern, 2) << endl;
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, ssr.str(), 0, 0));
    }
    else
    {
        m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, ssr.str(), 0, 0));
    }

    delete inBuffer;
    inBuffer = NULL;
    return testResult;
}

/** @brief returns copy of all register values
    @param channel channel index, starting from 0
    @return map of register addresses and values
*/
map<unsigned short, unsigned short> RegistersMap::GetRegistersValues(int channel)
{
    map<unsigned short, unsigned short> regValues;

    std::map<unsigned short, MemoryRegister>::iterator iter;
    for (iter = m_registers[channel].begin(); iter != m_registers[channel].end(); ++iter)
    {
        regValues.insert( pair<unsigned short, unsigned short>(iter->first, iter->second.value));
    }
    return regValues;
}

/** @brief Returns parameter description
*/
const ControlParameter RegistersMap::getParameterInfo(const LMS7002_Parameter param )
{
    return m_parameters[param];
}

/** @brief Returns true if currently configuring both channels
*/
bool RegistersMap::GetConfigAll() const
{
    return m_configAllChannels;
}

unsigned short RegistersMap::GetRegisterMask(unsigned short addr) const
{
    map<unsigned short, MemoryRegister>::const_iterator iter;
    iter = m_registers[0].find(addr);
    if(iter != m_registers[0].end())
        return iter->second.mask;
    else
        return 0xFFFF;
}

MemoryRegister RegistersMap::getRegisterInfo(const unsigned channel, const unsigned short address) const
{
    if(channel < 2)
    {
        map<unsigned short, MemoryRegister>::const_iterator iter;
        iter = m_registers[channel].find(address);
        if(iter != m_registers[channel].end())
            return iter->second;
    }
    MemoryRegister reg;
    return reg;
}
