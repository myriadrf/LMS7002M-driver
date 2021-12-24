
///
/// \file LMS7002M/LMS7002M_regs.h
///
/// Register address and field shift constants for LMS7002M.
///
/// \copyright
/// Copyright (c) 2014-2015 Fairwaves, Inc.
/// Copyright (c) 2014-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

//------ this is a generated file, do not edit --------//

#pragma once
#include <stdio.h>

struct LMS7002M_regs_struct;
typedef struct LMS7002M_regs_struct LMS7002M_regs_t;

//! initialize a register structure with default values
static inline void LMS7002M_regs_init(LMS7002M_regs_t *regs);

//! set the fields from the value that belong to the register specified by addr
static inline void LMS7002M_regs_set(LMS7002M_regs_t *regs, const int addr, const int value);

//! get the reset or default value of register specified by its address
static inline int LMS7002M_regs_default(const int addr);

//! get the value of the register specified by the fields at the given address
static inline int LMS7002M_regs_get(LMS7002M_regs_t *regs, const int addr);

//! enumerated values for some registers
#define REG_0X0020_MAC_NONE 0
#define REG_0X0020_MAC_CHA 1
#define REG_0X0020_MAC_CHB 2
#define REG_0X0020_MAC_CHAB 3
#define REG_0X0021_SPIMODE_3WIRE 0
#define REG_0X0021_SPIMODE_4WIRE 1
#define REG_0X0022_DIQ2_DS_4MA 0
#define REG_0X0022_DIQ2_DS_8MA 1
#define REG_0X0022_DIQ1_DS_4MA 0
#define REG_0X0022_DIQ1_DS_8MA 1
#define REG_0X0023_DIQDIR2_OUTPUT 0
#define REG_0X0023_DIQDIR2_INPUT 1
#define REG_0X0023_DIQDIR1_OUTPUT 0
#define REG_0X0023_DIQDIR1_INPUT 1
#define REG_0X0023_ENABLEDIR2_OUTPUT 0
#define REG_0X0023_ENABLEDIR2_INPUT 1
#define REG_0X0023_ENABLEDIR1_OUTPUT 0
#define REG_0X0023_ENABLEDIR1_INPUT 1
#define REG_0X0023_LML2_RXNTXIQ_RXIQ 0
#define REG_0X0023_LML2_RXNTXIQ_TXIQ 1
#define REG_0X0023_LML2_MODE_TRXIQ 0
#define REG_0X0023_LML2_MODE_JESD207 1
#define REG_0X0023_LML1_RXNTXIQ_RXIQ 0
#define REG_0X0023_LML1_RXNTXIQ_TXIQ 1
#define REG_0X0023_LML1_MODE_TRXIQ 0
#define REG_0X0023_LML1_MODE_JESD207 1
#define REG_0X0024_LML1_S3S_AI 0
#define REG_0X0024_LML1_S3S_AQ 1
#define REG_0X0024_LML1_S3S_BI 2
#define REG_0X0024_LML1_S3S_BQ 3
#define REG_0X0024_LML1_S2S_AI 0
#define REG_0X0024_LML1_S2S_AQ 1
#define REG_0X0024_LML1_S2S_BI 2
#define REG_0X0024_LML1_S2S_BQ 3
#define REG_0X0024_LML1_S1S_AI 0
#define REG_0X0024_LML1_S1S_AQ 1
#define REG_0X0024_LML1_S1S_BI 2
#define REG_0X0024_LML1_S1S_BQ 3
#define REG_0X0024_LML1_S0S_AI 0
#define REG_0X0024_LML1_S0S_AQ 1
#define REG_0X0024_LML1_S0S_BI 2
#define REG_0X0024_LML1_S0S_BQ 3
#define REG_0X0027_LML2_S3S_AI 0
#define REG_0X0027_LML2_S3S_AQ 1
#define REG_0X0027_LML2_S3S_BI 2
#define REG_0X0027_LML2_S3S_BQ 3
#define REG_0X0027_LML2_S2S_AI 0
#define REG_0X0027_LML2_S2S_AQ 1
#define REG_0X0027_LML2_S2S_BI 2
#define REG_0X0027_LML2_S2S_BQ 3
#define REG_0X0027_LML2_S1S_AI 0
#define REG_0X0027_LML2_S1S_AQ 1
#define REG_0X0027_LML2_S1S_BI 2
#define REG_0X0027_LML2_S1S_BQ 3
#define REG_0X0027_LML2_S0S_AI 0
#define REG_0X0027_LML2_S0S_AQ 1
#define REG_0X0027_LML2_S0S_BI 2
#define REG_0X0027_LML2_S0S_BQ 3
#define REG_0X002A_RX_MUX_RXTSP 0
#define REG_0X002A_RX_MUX_TXFIFO 1
#define REG_0X002A_RX_MUX_LFSR 2
#define REG_0X002A_RX_MUX_LFSR_ 3
#define REG_0X002A_TX_MUX_PORT1 0
#define REG_0X002A_TX_MUX_PORT2 1
#define REG_0X002A_TX_MUX_RXTSP 2
#define REG_0X002A_TX_MUX_RXTSP_ 3
#define REG_0X002A_TXRDCLK_MUX_FCLK1 0
#define REG_0X002A_TXRDCLK_MUX_FCLK2 1
#define REG_0X002A_TXRDCLK_MUX_TXTSPCLK 2
#define REG_0X002A_TXRDCLK_MUX_TXTSPCLK_ 3
#define REG_0X002A_TXWRCLK_MUX_FCLK1 0
#define REG_0X002A_TXWRCLK_MUX_FCLK2 1
#define REG_0X002A_TXWRCLK_MUX_RXTSPCLK 2
#define REG_0X002A_TXWRCLK_MUX_RXTSPCLK_ 3
#define REG_0X002A_RXRDCLK_MUX_MCLK1 0
#define REG_0X002A_RXRDCLK_MUX_MCLK2 1
#define REG_0X002A_RXRDCLK_MUX_FCLK1 2
#define REG_0X002A_RXRDCLK_MUX_FCLK2 3
#define REG_0X002A_RXWRCLK_MUX_FCLK1 0
#define REG_0X002A_RXWRCLK_MUX_FCLK2 1
#define REG_0X002A_RXWRCLK_MUX_RXTSPCLK 2
#define REG_0X002A_RXWRCLK_MUX_RXTSPCLK_ 3
#define REG_0X002B_MCLK2SRC_TXTSPCLKA_DIV 0
#define REG_0X002B_MCLK2SRC_RXTSPCLKA_DIV 1
#define REG_0X002B_MCLK2SRC_TXTSPCLKA 2
#define REG_0X002B_MCLK2SRC_RXTSPCLKA 3
#define REG_0X002B_MCLK1SRC_TXTSPCLKA_DIV 0
#define REG_0X002B_MCLK1SRC_RXTSPCLKA_DIV 1
#define REG_0X002B_MCLK1SRC_TXTSPCLKA 2
#define REG_0X002B_MCLK1SRC_RXTSPCLKA 3
#define REG_0X0082_MODE_INTERLEAVE_AFE_2ADCS 0
#define REG_0X0082_MODE_INTERLEAVE_AFE_INTERLEAVED 1
#define REG_0X0082_MUX_AFE_1_MUXOFF 0
#define REG_0X0082_MUX_AFE_1_PDET_1 1
#define REG_0X0082_MUX_AFE_1_BIAS_TOP 2
#define REG_0X0082_MUX_AFE_1_RSSI1 3
#define REG_0X0082_MUX_AFE_2_MUXOFF 0
#define REG_0X0082_MUX_AFE_2_PDET_2 1
#define REG_0X0082_MUX_AFE_2_RSSI1 2
#define REG_0X0082_MUX_AFE_2_RSSI2 3
#define REG_0X0089_SEL_SDMCLK_CGEN_CLK_DIV 0
#define REG_0X0089_SEL_SDMCLK_CGEN_CLK_REF 1
#define REG_0X0089_TST_CGEN_DISABLED 0
#define REG_0X0089_TST_CGEN_TSTDO 1
#define REG_0X0089_TST_CGEN_VCO_TUNE_50_KOHM 2
#define REG_0X0089_TST_CGEN_VCO_TUNE 3
#define REG_0X0089_TST_CGEN_PFD_UP 5
#define REG_0X0100_EN_NEXTTX_TRF_SISO 0
#define REG_0X0100_EN_NEXTTX_TRF_MIMO 1
#define REG_0X010D_SEL_PATH_RFE_NONE 0
#define REG_0X010D_SEL_PATH_RFE_LNAH 1
#define REG_0X010D_SEL_PATH_RFE_LNAL 2
#define REG_0X010D_SEL_PATH_RFE_LNAW 3
#define REG_0X010D_EN_NEXTRX_RFE_SISO 0
#define REG_0X010D_EN_NEXTRX_RFE_MIMO 1
#define REG_0X0118_INPUT_CTL_PGA_RBB_LPFL 0
#define REG_0X0118_INPUT_CTL_PGA_RBB_LPFH 1
#define REG_0X0118_INPUT_CTL_PGA_RBB_BYPASS 2
#define REG_0X0118_INPUT_CTL_PGA_RBB_TBB 3
#define REG_0X0118_INPUT_CTL_PGA_RBB_PDET 4
#define REG_0X011F_SEL_SDMCLK_CLK_DIV 0
#define REG_0X011F_SEL_SDMCLK_CLK_REF 1
#define REG_0X0121_SEL_VCO_VCOL 0
#define REG_0X0121_SEL_VCO_VCOM 1
#define REG_0X0121_SEL_VCO_VCOH 2
#define REG_0X0200_TSGFC_NEG6DB 0
#define REG_0X0200_TSGFC_FS 1
#define REG_0X0200_TSGFCW_DIV8 1
#define REG_0X0200_TSGFCW_DIV4 2
#define REG_0X0200_TSGMODE_NCO 0
#define REG_0X0200_TSGMODE_DC 1
#define REG_0X0200_INSEL_LML 0
#define REG_0X0200_INSEL_TEST 1
#define REG_0X0203_HBI_OVR_BYPASS 7
#define REG_0X0208_CMIX_GAIN_0DB 0
#define REG_0X0208_CMIX_GAIN_POS6DB 1
#define REG_0X0208_CMIX_GAIN_NEG6DB 2
#define REG_0X0208_CMIX_SC_UPCONVERT 0
#define REG_0X0208_CMIX_SC_DOWNCONVERT 1
#define REG_0X0240_MODE_FCW 0
#define REG_0X0240_MODE_PHO 1
#define REG_0X0400_CAPSEL_RSSI 0
#define REG_0X0400_CAPSEL_ADCI_ADCQ 1
#define REG_0X0400_CAPSEL_BSIGI_BSTATE 2
#define REG_0X0400_CAPSEL_BSIGQ_BSTATE 3
#define REG_0X0400_TSGFC_NEG6DB 0
#define REG_0X0400_TSGFC_FS 1
#define REG_0X0400_TSGFCW_DIV8 1
#define REG_0X0400_TSGFCW_DIV4 2
#define REG_0X0400_TSGMODE_NCO 0
#define REG_0X0400_TSGMODE_DC 1
#define REG_0X0400_INSEL_LML 0
#define REG_0X0400_INSEL_TEST 1
#define REG_0X0403_HBD_OVR_BYPASS 7
#define REG_0X040A_AGC_MODE_AGC 0
#define REG_0X040A_AGC_MODE_RSSI 1
#define REG_0X040A_AGC_MODE_BYPASS 2
#define REG_0X040C_CMIX_GAIN_0DB 0
#define REG_0X040C_CMIX_GAIN_POS6DB 1
#define REG_0X040C_CMIX_GAIN_NEG6DB 2
#define REG_0X040C_CMIX_SC_UPCONVERT 0
#define REG_0X040C_CMIX_SC_DOWNCONVERT 1
#define REG_0X0440_MODE_FCW 0
#define REG_0X0440_MODE_PHO 1

struct LMS7002M_regs_struct
{
    int reg_0x0020_lrst_tx_b;
    int reg_0x0020_mrst_tx_b;
    int reg_0x0020_lrst_tx_a;
    int reg_0x0020_mrst_tx_a;
    int reg_0x0020_lrst_rx_b;
    int reg_0x0020_mrst_rx_b;
    int reg_0x0020_lrst_rx_a;
    int reg_0x0020_mrst_rx_a;
    int reg_0x0020_srst_rxfifo;
    int reg_0x0020_srst_txfifo;
    int reg_0x0020_rxen_b;
    int reg_0x0020_rxen_a;
    int reg_0x0020_txen_b;
    int reg_0x0020_txen_a;
    int reg_0x0020_mac;
    int reg_0x0021_tx_clk_pe;
    int reg_0x0021_rx_clk_pe;
    int reg_0x0021_sda_pe;
    int reg_0x0021_sda_ds;
    int reg_0x0021_scl_pe;
    int reg_0x0021_scl_ds;
    int reg_0x0021_sdio_ds;
    int reg_0x0021_sdio_pe;
    int reg_0x0021_sdo_pe;
    int reg_0x0021_sclk_pe;
    int reg_0x0021_sen_pe;
    int reg_0x0021_spimode;
    int reg_0x0022_diq2_ds;
    int reg_0x0022_diq2_pe;
    int reg_0x0022_iq_sel_en_2_pe;
    int reg_0x0022_txnrx2_pe;
    int reg_0x0022_fclk2_pe;
    int reg_0x0022_mclk2_pe;
    int reg_0x0022_diq1_ds;
    int reg_0x0022_diq1_pe;
    int reg_0x0022_iq_sel_en_1_pe;
    int reg_0x0022_txnrx1_pe;
    int reg_0x0022_fclk1_pe;
    int reg_0x0022_mclk1_pe;
    int reg_0x0023_diqdirctr2;
    int reg_0x0023_diqdir2;
    int reg_0x0023_diqdirctr1;
    int reg_0x0023_diqdir1;
    int reg_0x0023_enabledirctr2;
    int reg_0x0023_enabledir2;
    int reg_0x0023_enabledirctr1;
    int reg_0x0023_enabledir1;
    int reg_0x0023_mod_en;
    int reg_0x0023_lml2_fidm;
    int reg_0x0023_lml2_rxntxiq;
    int reg_0x0023_lml2_mode;
    int reg_0x0023_lml1_fidm;
    int reg_0x0023_lml1_rxntxiq;
    int reg_0x0023_lml1_mode;
    int reg_0x0024_lml1_s3s;
    int reg_0x0024_lml1_s2s;
    int reg_0x0024_lml1_s1s;
    int reg_0x0024_lml1_s0s;
    int reg_0x0024_lml1_bqp;
    int reg_0x0024_lml1_bip;
    int reg_0x0024_lml1_aqp;
    int reg_0x0024_lml1_aip;
    int reg_0x0025_value;
    int reg_0x0026_value;
    int reg_0x0027_lml2_s3s;
    int reg_0x0027_lml2_s2s;
    int reg_0x0027_lml2_s1s;
    int reg_0x0027_lml2_s0s;
    int reg_0x0027_lml2_bqp;
    int reg_0x0027_lml2_bip;
    int reg_0x0027_lml2_aqp;
    int reg_0x0027_lml2_aip;
    int reg_0x0028_value;
    int reg_0x0029_value;
    int reg_0x002a_fclk2_dly;
    int reg_0x002a_fclk1_dly;
    int reg_0x002a_rx_mux;
    int reg_0x002a_tx_mux;
    int reg_0x002a_txrdclk_mux;
    int reg_0x002a_txwrclk_mux;
    int reg_0x002a_rxrdclk_mux;
    int reg_0x002a_rxwrclk_mux;
    int reg_0x002b_fclk2_inv;
    int reg_0x002b_fclk1_inv;
    int reg_0x002b_mclk2src;
    int reg_0x002b_mclk1src;
    int reg_0x002b_txdiven;
    int reg_0x002b_rxdiven;
    int reg_0x002c_txtspclk_div;
    int reg_0x002c_rxtspclk_div;
    int reg_0x002e_mimo_siso;
    int reg_0x002f_ver;
    int reg_0x002f_rev;
    int reg_0x002f_mask;
    int reg_0x0081_en_dir_ldo;
    int reg_0x0081_en_dir_cgen;
    int reg_0x0081_en_dir_xbuf;
    int reg_0x0081_en_dir_afe;
    int reg_0x0082_isel_dac_afe;
    int reg_0x0082_mode_interleave_afe;
    int reg_0x0082_mux_afe_1;
    int reg_0x0082_mux_afe_2;
    int reg_0x0082_pd_afe;
    int reg_0x0082_pd_rx_afe1;
    int reg_0x0082_pd_rx_afe2;
    int reg_0x0082_pd_tx_afe1;
    int reg_0x0082_pd_tx_afe2;
    int reg_0x0082_en_g_afe;
    int reg_0x0084_mux_bias_out;
    int reg_0x0084_rp_calib_bias;
    int reg_0x0084_pd_frp_bias;
    int reg_0x0084_pd_f_bias;
    int reg_0x0084_pd_ptrp_bias;
    int reg_0x0084_pd_pt_bias;
    int reg_0x0084_pd_bias_master;
    int reg_0x0085_slfb_xbuf_rx;
    int reg_0x0085_slfb_xbuf_tx;
    int reg_0x0085_byp_xbuf_rx;
    int reg_0x0085_byp_xbuf_tx;
    int reg_0x0085_en_out2_xbuf_tx;
    int reg_0x0085_en_tbufin_xbuf_rx;
    int reg_0x0085_pd_xbuf_rx;
    int reg_0x0085_pd_xbuf_tx;
    int reg_0x0085_en_g_xbuf;
    int reg_0x0086_spdup_vco_cgen;
    int reg_0x0086_reset_n_cgen;
    int reg_0x0086_en_adcclkh_clkgn;
    int reg_0x0086_en_coarse_cklgen;
    int reg_0x0086_en_intonly_sdm_cgen;
    int reg_0x0086_en_sdm_clk_cgen;
    int reg_0x0086_pd_cp_cgen;
    int reg_0x0086_pd_fdiv_fb_cgen;
    int reg_0x0086_pd_fdiv_o_cgen;
    int reg_0x0086_pd_sdm_cgen;
    int reg_0x0086_pd_vco_cgen;
    int reg_0x0086_pd_vco_comp_cgen;
    int reg_0x0086_en_g_cgen;
    int reg_0x0087_frac_sdm_cgen;
    int reg_0x0088_int_sdm_cgen;
    int reg_0x0088_frac_sdm_cgen;
    int reg_0x0089_rev_sdmclk_cgen;
    int reg_0x0089_sel_sdmclk_cgen;
    int reg_0x0089_sx_dither_en_cgen;
    int reg_0x0089_clkh_ov_clkl_cgen;
    int reg_0x0089_div_outch_cgen;
    int reg_0x0089_tst_cgen;
    int reg_0x008a_rev_clkdac_cgen;
    int reg_0x008a_rev_clkadc_cgen;
    int reg_0x008a_revph_pfd_cgen;
    int reg_0x008a_ioffset_cp_cgen;
    int reg_0x008a_ipulse_cp_cgen;
    int reg_0x008b_ict_vco_cgen;
    int reg_0x008b_csw_vco_cgen;
    int reg_0x008b_coarse_start_cgen;
    int reg_0x008c_coarse_stepdone_cgen;
    int reg_0x008c_coarsepll_compo_cgen;
    int reg_0x008c_vco_cmpho_cgen;
    int reg_0x008c_vco_cmplo_cgen;
    int reg_0x008c_cp2_cgen;
    int reg_0x008c_cp3_cgen;
    int reg_0x008c_cz_cgen;
    int reg_0x008d_resrv_cgn;
    int reg_0x0092_en_ldo_dig;
    int reg_0x0092_en_ldo_diggn;
    int reg_0x0092_en_ldo_digsxr;
    int reg_0x0092_en_ldo_digsxt;
    int reg_0x0092_en_ldo_divgn;
    int reg_0x0092_en_ldo_divsxr;
    int reg_0x0092_en_ldo_divsxt;
    int reg_0x0092_en_ldo_lna12;
    int reg_0x0092_en_ldo_lna14;
    int reg_0x0092_en_ldo_mxrfe;
    int reg_0x0092_en_ldo_rbb;
    int reg_0x0092_en_ldo_rxbuf;
    int reg_0x0092_en_ldo_tbb;
    int reg_0x0092_en_ldo_tia12;
    int reg_0x0092_en_ldo_tia14;
    int reg_0x0092_en_g_ldo;
    int reg_0x0093_en_loadimp_ldo_tlob;
    int reg_0x0093_en_loadimp_ldo_tpad;
    int reg_0x0093_en_loadimp_ldo_txbuf;
    int reg_0x0093_en_loadimp_ldo_vcogn;
    int reg_0x0093_en_loadimp_ldo_vcosxr;
    int reg_0x0093_en_loadimp_ldo_vcosxt;
    int reg_0x0093_en_ldo_afe;
    int reg_0x0093_en_ldo_cpgn;
    int reg_0x0093_en_ldo_cpsxr;
    int reg_0x0093_en_ldo_tlob;
    int reg_0x0093_en_ldo_tpad;
    int reg_0x0093_en_ldo_txbuf;
    int reg_0x0093_en_ldo_vcogn;
    int reg_0x0093_en_ldo_vcosxr;
    int reg_0x0093_en_ldo_vcosxt;
    int reg_0x0093_en_ldo_cpsxt;
    int reg_0x0094_en_loadimp_ldo_cpsxt;
    int reg_0x0094_en_loadimp_ldo_dig;
    int reg_0x0094_en_loadimp_ldo_diggn;
    int reg_0x0094_en_loadimp_ldo_digsxr;
    int reg_0x0094_en_loadimp_ldo_digsxt;
    int reg_0x0094_en_loadimp_ldo_divgn;
    int reg_0x0094_en_loadimp_ldo_divsxr;
    int reg_0x0094_en_loadimp_ldo_divsxt;
    int reg_0x0094_en_loadimp_ldo_lna12;
    int reg_0x0094_en_loadimp_ldo_lna14;
    int reg_0x0094_en_loadimp_ldo_mxrfe;
    int reg_0x0094_en_loadimp_ldo_rbb;
    int reg_0x0094_en_loadimp_ldo_rxbuf;
    int reg_0x0094_en_loadimp_ldo_tbb;
    int reg_0x0094_en_loadimp_ldo_tia12;
    int reg_0x0094_en_loadimp_ldo_tia14;
    int reg_0x0095_byp_ldo_tbb;
    int reg_0x0095_byp_ldo_tia12;
    int reg_0x0095_byp_ldo_tia14;
    int reg_0x0095_byp_ldo_tlob;
    int reg_0x0095_byp_ldo_tpad;
    int reg_0x0095_byp_ldo_txbuf;
    int reg_0x0095_byp_ldo_vcogn;
    int reg_0x0095_byp_ldo_vcosxr;
    int reg_0x0095_byp_ldo_vcosxt;
    int reg_0x0095_en_loadimp_ldo_afe;
    int reg_0x0095_en_loadimp_ldo_cpgn;
    int reg_0x0095_en_loadimp_ldo_cpsxr;
    int reg_0x0096_byp_ldo_afe;
    int reg_0x0096_byp_ldo_cpgn;
    int reg_0x0096_byp_ldo_cpsxr;
    int reg_0x0096_byp_ldo_cpsxt;
    int reg_0x0096_byp_ldo_dig;
    int reg_0x0096_byp_ldo_diggn;
    int reg_0x0096_byp_ldo_digsxr;
    int reg_0x0096_byp_ldo_digsxt;
    int reg_0x0096_byp_ldo_divgn;
    int reg_0x0096_byp_ldo_divsxr;
    int reg_0x0096_byp_ldo_divsxt;
    int reg_0x0096_byp_ldo_lna12;
    int reg_0x0096_byp_ldo_lna14;
    int reg_0x0096_byp_ldo_mxrfe;
    int reg_0x0096_byp_ldo_rbb;
    int reg_0x0096_byp_ldo_rxbuf;
    int reg_0x0097_spdup_ldo_divsxr;
    int reg_0x0097_spdup_ldo_divsxt;
    int reg_0x0097_spdup_ldo_lna12;
    int reg_0x0097_spdup_ldo_lna14;
    int reg_0x0097_spdup_ldo_mxrfe;
    int reg_0x0097_spdup_ldo_rbb;
    int reg_0x0097_spdup_ldo_rxbuf;
    int reg_0x0097_spdup_ldo_tbb;
    int reg_0x0097_spdup_ldo_tia12;
    int reg_0x0097_spdup_ldo_tia14;
    int reg_0x0097_spdup_ldo_tlob;
    int reg_0x0097_spdup_ldo_tpad;
    int reg_0x0097_spdup_ldo_txbuf;
    int reg_0x0097_spdup_ldo_vcogn;
    int reg_0x0097_spdup_ldo_vcosxr;
    int reg_0x0097_spdup_ldo_vcosxt;
    int reg_0x0098_spdup_ldo_afe;
    int reg_0x0098_spdup_ldo_cpgn;
    int reg_0x0098_spdup_ldo_cpsxr;
    int reg_0x0098_spdup_ldo_cpsxt;
    int reg_0x0098_spdup_ldo_dig;
    int reg_0x0098_spdup_ldo_diggn;
    int reg_0x0098_spdup_ldo_digsxr;
    int reg_0x0098_spdup_ldo_digsxt;
    int reg_0x0098_spdup_ldo_divgn;
    int reg_0x0099_rdiv_vcosxr;
    int reg_0x0099_rdiv_vcosxt;
    int reg_0x009a_rdiv_txbuf;
    int reg_0x009a_rdiv_vcogn;
    int reg_0x009b_rdiv_tlob;
    int reg_0x009b_rdiv_tpad;
    int reg_0x009c_rdiv_tia12;
    int reg_0x009c_rdiv_tia14;
    int reg_0x009d_rdiv_rxbuf;
    int reg_0x009d_rdiv_tbb;
    int reg_0x009e_rdiv_mxrfe;
    int reg_0x009e_rdiv_rbb;
    int reg_0x009f_rdiv_lna12;
    int reg_0x009f_rdiv_lna14;
    int reg_0x00a0_rdiv_divsxr;
    int reg_0x00a0_rdiv_divsxt;
    int reg_0x00a1_rdiv_digsxt;
    int reg_0x00a1_rdiv_divgn;
    int reg_0x00a2_rdiv_diggn;
    int reg_0x00a2_rdiv_digsxr;
    int reg_0x00a3_rdiv_cpsxt;
    int reg_0x00a3_rdiv_dig;
    int reg_0x00a4_rdiv_cpgn;
    int reg_0x00a4_rdiv_cpsxr;
    int reg_0x00a5_rdiv_spibuf;
    int reg_0x00a5_rdiv_afe;
    int reg_0x00a6_spdup_ldo_spibuf;
    int reg_0x00a6_spdup_ldo_digip2;
    int reg_0x00a6_spdup_ldo_digip1;
    int reg_0x00a6_byp_ldo_spibuf;
    int reg_0x00a6_byp_ldo_digip2;
    int reg_0x00a6_byp_ldo_digip1;
    int reg_0x00a6_en_loadimp_ldo_spibuf;
    int reg_0x00a6_en_loadimp_ldo_digip2;
    int reg_0x00a6_en_loadimp_ldo_digip1;
    int reg_0x00a6_pd_ldo_spibuf;
    int reg_0x00a6_pd_ldo_digip2;
    int reg_0x00a6_pd_ldo_digip1;
    int reg_0x00a6_en_g_ldop;
    int reg_0x00a7_rdiv_digip2;
    int reg_0x00a7_rdiv_digip1;
    int reg_0x00a8_value;
    int reg_0x00aa_value;
    int reg_0x00ab_value;
    int reg_0x00ad_value;
    int reg_0x00ae_value;
    int reg_0x0100_en_lowbwlomx_tmx_trf;
    int reg_0x0100_en_nexttx_trf;
    int reg_0x0100_en_amphf_pdet_trf;
    int reg_0x0100_loadr_pdet_trf;
    int reg_0x0100_pd_pdet_trf;
    int reg_0x0100_pd_tlobuf_trf;
    int reg_0x0100_pd_txpad_trf;
    int reg_0x0100_en_g_trf;
    int reg_0x0101_f_txpad_trf;
    int reg_0x0101_l_loopb_txpad_trf;
    int reg_0x0101_loss_lin_txpad_trf;
    int reg_0x0101_loss_main_txpad_trf;
    int reg_0x0101_en_loopb_txpad_trf;
    int reg_0x0102_gcas_gndref_txpad_trf;
    int reg_0x0102_ict_lin_txpad_trf;
    int reg_0x0102_ict_main_txpad_trf;
    int reg_0x0102_vgcas_txpad_trf;
    int reg_0x0103_sel_band1_trf;
    int reg_0x0103_sel_band2_trf;
    int reg_0x0103_lobiasn_txm_trf;
    int reg_0x0103_lobiasp_txx_trf;
    int reg_0x0104_cdc_i_trf;
    int reg_0x0104_cdc_q_trf;
    int reg_0x0105_statpulse_tbb;
    int reg_0x0105_loopb_tbb;
    int reg_0x0105_pd_lpfh_tbb;
    int reg_0x0105_pd_lpfiamp_tbb;
    int reg_0x0105_pd_lpflad_tbb;
    int reg_0x0105_pd_lpfs5_tbb;
    int reg_0x0105_en_g_tbb;
    int reg_0x0106_ict_lpfs5_f_tbb;
    int reg_0x0106_ict_lpfs5_pt_tbb;
    int reg_0x0106_ict_lpf_h_pt_tbb;
    int reg_0x0107_ict_lpfh_f_tbb;
    int reg_0x0107_ict_lpflad_f_tbb;
    int reg_0x0107_ict_lpflad_pt_tbb;
    int reg_0x0108_cg_iamp_tbb;
    int reg_0x0108_ict_iamp_frp_tbb;
    int reg_0x0108_ict_iamp_gg_frp_tbb;
    int reg_0x0109_rcal_lpfh_tbb;
    int reg_0x0109_rcal_lpflad_tbb;
    int reg_0x010a_tstin_tbb;
    int reg_0x010a_bypladder_tbb;
    int reg_0x010a_ccal_lpflad_tbb;
    int reg_0x010a_rcal_lpfs5_tbb;
    int reg_0x010b_value;
    int reg_0x010c_cdc_i_rfe;
    int reg_0x010c_cdc_q_rfe;
    int reg_0x010c_pd_lna_rfe;
    int reg_0x010c_pd_rloopb_1_rfe;
    int reg_0x010c_pd_rloopb_2_rfe;
    int reg_0x010c_pd_mxlobuf_rfe;
    int reg_0x010c_pd_qgen_rfe;
    int reg_0x010c_pd_rssi_rfe;
    int reg_0x010c_pd_tia_rfe;
    int reg_0x010c_en_g_rfe;
    int reg_0x010d_sel_path_rfe;
    int reg_0x010d_en_dcoff_rxfe_rfe;
    int reg_0x010d_en_inshsw_lb1_rfe;
    int reg_0x010d_en_inshsw_lb2_rfe;
    int reg_0x010d_en_inshsw_l_rfe;
    int reg_0x010d_en_inshsw_w_rfe;
    int reg_0x010d_en_nextrx_rfe;
    int reg_0x010e_dcoffi_rfe;
    int reg_0x010e_dcoffq_rfe;
    int reg_0x010f_ict_loopb_rfe;
    int reg_0x010f_ict_tiamain_rfe;
    int reg_0x010f_ict_tiaout_rfe;
    int reg_0x0110_ict_lnacmo_rfe;
    int reg_0x0110_ict_lna_rfe;
    int reg_0x0110_ict_lodc_rfe;
    int reg_0x0111_cap_rxmxo_rfe;
    int reg_0x0111_cgsin_lna_rfe;
    int reg_0x0112_ccomp_tia_rfe;
    int reg_0x0112_cfb_tia_rfe;
    int reg_0x0113_g_lna_rfe;
    int reg_0x0113_g_rxloopb_rfe;
    int reg_0x0113_g_tia_rfe;
    int reg_0x0114_rcomp_tia_rfe;
    int reg_0x0114_rfb_tia_rfe;
    int reg_0x0115_en_lb_lpfh_rbb;
    int reg_0x0115_en_lb_lpfl_rbb;
    int reg_0x0115_pd_lpfh_rbb;
    int reg_0x0115_pd_lpfl_rbb;
    int reg_0x0115_pd_pga_rbb;
    int reg_0x0115_en_g_rbb;
    int reg_0x0116_r_ctl_lpf_rbb;
    int reg_0x0116_rcc_ctl_lpfh_rbb;
    int reg_0x0116_c_ctl_lpfh_rbb;
    int reg_0x0117_rcc_ctl_lpfl_rbb;
    int reg_0x0117_c_ctl_lpfl_rbb;
    int reg_0x0118_input_ctl_pga_rbb;
    int reg_0x0118_ict_lpf_in_rbb;
    int reg_0x0118_ict_lpf_out_rbb;
    int reg_0x0119_osw_pga_rbb;
    int reg_0x0119_ict_pga_out_rbb;
    int reg_0x0119_ict_pga_in_rbb;
    int reg_0x0119_g_pga_rbb;
    int reg_0x011a_rcc_ctl_pga_rbb;
    int reg_0x011a_c_ctl_pga_rbb;
    int reg_0x011b_resrv_rbb;
    int reg_0x011c_reset_n;
    int reg_0x011c_spdup_vco;
    int reg_0x011c_bypldo_vco;
    int reg_0x011c_en_coarsepll;
    int reg_0x011c_curlim_vco;
    int reg_0x011c_en_div2_divprog;
    int reg_0x011c_en_intonly_sdm;
    int reg_0x011c_en_sdm_clk;
    int reg_0x011c_pd_fbdiv;
    int reg_0x011c_pd_loch_t2rbuf;
    int reg_0x011c_pd_cp;
    int reg_0x011c_pd_fdiv;
    int reg_0x011c_pd_sdm;
    int reg_0x011c_pd_vco_comp;
    int reg_0x011c_pd_vco;
    int reg_0x011c_en_g;
    int reg_0x011d_frac_sdm;
    int reg_0x011e_int_sdm;
    int reg_0x011e_frac_sdm;
    int reg_0x011f_pw_div2_loch;
    int reg_0x011f_pw_div4_loch;
    int reg_0x011f_div_loch;
    int reg_0x011f_tst_sx;
    int reg_0x011f_sel_sdmclk;
    int reg_0x011f_sx_dither_en;
    int reg_0x011f_rev_sdmclk;
    int reg_0x0120_vdiv_vco;
    int reg_0x0120_ict_vco;
    int reg_0x0121_rsel_ldo_vco;
    int reg_0x0121_csw_vco;
    int reg_0x0121_sel_vco;
    int reg_0x0121_coarse_start;
    int reg_0x0122_revph_pfd;
    int reg_0x0122_ioffset_cp;
    int reg_0x0122_ipulse_cp;
    int reg_0x0123_coarse_stepdone;
    int reg_0x0123_coarsepll_compo;
    int reg_0x0123_vco_cmpho;
    int reg_0x0123_vco_cmplo;
    int reg_0x0123_cp2_pll;
    int reg_0x0123_cp3_pll;
    int reg_0x0123_cz;
    int reg_0x0124_en_dir_sxx;
    int reg_0x0124_en_dir_rbb;
    int reg_0x0124_en_dir_rfe;
    int reg_0x0124_en_dir_tbb;
    int reg_0x0124_en_dir_trf;
    int reg_0x0125_value;
    int reg_0x0126_value;
    int reg_0x0200_tsgfc;
    int reg_0x0200_tsgfcw;
    int reg_0x0200_tsgdcldq;
    int reg_0x0200_tsgdcldi;
    int reg_0x0200_tsgswapiq;
    int reg_0x0200_tsgmode;
    int reg_0x0200_insel;
    int reg_0x0200_bstart;
    int reg_0x0200_en;
    int reg_0x0201_gcorrq;
    int reg_0x0202_gcorri;
    int reg_0x0203_hbi_ovr;
    int reg_0x0203_iqcorr;
    int reg_0x0204_dccorri;
    int reg_0x0204_dccorrq;
    int reg_0x0205_gfir1_l;
    int reg_0x0205_gfir1_n;
    int reg_0x0206_gfir2_l;
    int reg_0x0206_gfir2_n;
    int reg_0x0207_gfir3_l;
    int reg_0x0207_gfir3_n;
    int reg_0x0208_cmix_gain;
    int reg_0x0208_cmix_sc;
    int reg_0x0208_cmix_byp;
    int reg_0x0208_isinc_byp;
    int reg_0x0208_gfir3_byp;
    int reg_0x0208_gfir2_byp;
    int reg_0x0208_gfir1_byp;
    int reg_0x0208_dc_byp;
    int reg_0x0208_gc_byp;
    int reg_0x0208_ph_byp;
    int reg_0x0209_value;
    int reg_0x020a_value;
    int reg_0x020c_dc_reg;
    int reg_0x0240_dthbit;
    int reg_0x0240_sel;
    int reg_0x0240_mode;
    int reg_0x0241_pho;
    int reg_0x0242_fcw0_hi;
    int reg_0x0243_fcw0_lo;
    int reg_0x0400_capture;
    int reg_0x0400_capsel;
    int reg_0x0400_tsgfc;
    int reg_0x0400_tsgfcw;
    int reg_0x0400_tsgdcldq;
    int reg_0x0400_tsgdcldi;
    int reg_0x0400_tsgswapiq;
    int reg_0x0400_tsgmode;
    int reg_0x0400_insel;
    int reg_0x0400_bstart;
    int reg_0x0400_en;
    int reg_0x0401_gcorrq;
    int reg_0x0402_gcorri;
    int reg_0x0403_hbd_ovr;
    int reg_0x0403_iqcorr;
    int reg_0x0404_dccorr_avg;
    int reg_0x0405_gfir1_l;
    int reg_0x0405_gfir1_n;
    int reg_0x0406_gfir2_l;
    int reg_0x0406_gfir2_n;
    int reg_0x0407_gfir3_l;
    int reg_0x0407_gfir3_n;
    int reg_0x0408_agc_k_lsb;
    int reg_0x0409_agc_adesired;
    int reg_0x0409_agc_k_msb;
    int reg_0x040a_agc_mode;
    int reg_0x040a_agc_avg;
    int reg_0x040b_dc_reg;
    int reg_0x040c_cmix_gain;
    int reg_0x040c_cmix_sc;
    int reg_0x040c_cmix_byp;
    int reg_0x040c_agc_byp;
    int reg_0x040c_gfir3_byp;
    int reg_0x040c_gfir2_byp;
    int reg_0x040c_gfir1_byp;
    int reg_0x040c_dc_byp;
    int reg_0x040c_gc_byp;
    int reg_0x040c_ph_byp;
    int reg_0x040e_value;
    int reg_0x0440_dthbit;
    int reg_0x0440_sel;
    int reg_0x0440_mode;
    int reg_0x0441_pho;
    int reg_0x0442_fcw0_hi;
    int reg_0x0443_fcw0_lo;
    int reg_0x05c0_value;
    int reg_0x05c1_value;
    int reg_0x05c2_value;
    int reg_0x05c3_value;
    int reg_0x05c4_value;
    int reg_0x05c5_value;
    int reg_0x05c6_value;
    int reg_0x05c7_value;
    int reg_0x05c8_value;
    int reg_0x05c9_value;
    int reg_0x05ca_value;
    int reg_0x05cb_value;
    int reg_0x05cc_value;
    int reg_0x0600_value;
    int reg_0x0601_value;
    int reg_0x0602_value;
    int reg_0x0603_value;
    int reg_0x0604_value;
    int reg_0x0605_value;
    int reg_0x0606_value;
    int reg_0x0640_value;
    int reg_0x0641_value;
};

/***********************************************************************
 * Implementation details below
 **********************************************************************/

static inline void LMS7002M_regs_init(LMS7002M_regs_t *regs)
{
    LMS7002M_regs_set(regs, 0x0020, 0xffff);
    LMS7002M_regs_set(regs, 0x0021, 0xe9f);
    LMS7002M_regs_set(regs, 0x0022, 0x7df);
    LMS7002M_regs_set(regs, 0x0023, 0x5559);
    LMS7002M_regs_set(regs, 0x0024, 0xe4e4);
    LMS7002M_regs_set(regs, 0x0025, 0x101);
    LMS7002M_regs_set(regs, 0x0026, 0x101);
    LMS7002M_regs_set(regs, 0x0027, 0xe4e4);
    LMS7002M_regs_set(regs, 0x0028, 0x101);
    LMS7002M_regs_set(regs, 0x0029, 0x101);
    LMS7002M_regs_set(regs, 0x002A, 0x86);
    LMS7002M_regs_set(regs, 0x002B, 0x10);
    LMS7002M_regs_set(regs, 0x002C, 0xffff);
    LMS7002M_regs_set(regs, 0x002E, 0x0);
    LMS7002M_regs_set(regs, 0x002F, 0x3840);
    LMS7002M_regs_set(regs, 0x0081, 0x0);
    LMS7002M_regs_set(regs, 0x0082, 0x800b);
    LMS7002M_regs_set(regs, 0x0084, 0x400);
    LMS7002M_regs_set(regs, 0x0085, 0x1);
    LMS7002M_regs_set(regs, 0x0086, 0x4901);
    LMS7002M_regs_set(regs, 0x0087, 0x400);
    LMS7002M_regs_set(regs, 0x0088, 0x780);
    LMS7002M_regs_set(regs, 0x0089, 0x20);
    LMS7002M_regs_set(regs, 0x008A, 0x514);
    LMS7002M_regs_set(regs, 0x008B, 0x2100);
    LMS7002M_regs_set(regs, 0x008C, 0x67b);
    LMS7002M_regs_set(regs, 0x008D, 0x0);
    LMS7002M_regs_set(regs, 0x0092, 0x1);
    LMS7002M_regs_set(regs, 0x0093, 0x0);
    LMS7002M_regs_set(regs, 0x0094, 0x0);
    LMS7002M_regs_set(regs, 0x0095, 0x0);
    LMS7002M_regs_set(regs, 0x0096, 0x0);
    LMS7002M_regs_set(regs, 0x0097, 0x0);
    LMS7002M_regs_set(regs, 0x0098, 0x0);
    LMS7002M_regs_set(regs, 0x0099, 0x6565);
    LMS7002M_regs_set(regs, 0x009A, 0x658c);
    LMS7002M_regs_set(regs, 0x009B, 0x6565);
    LMS7002M_regs_set(regs, 0x009C, 0x658c);
    LMS7002M_regs_set(regs, 0x009D, 0x6565);
    LMS7002M_regs_set(regs, 0x009E, 0x658c);
    LMS7002M_regs_set(regs, 0x009F, 0x658c);
    LMS7002M_regs_set(regs, 0x00A0, 0x6565);
    LMS7002M_regs_set(regs, 0x00A1, 0x6565);
    LMS7002M_regs_set(regs, 0x00A2, 0x6565);
    LMS7002M_regs_set(regs, 0x00A3, 0x6565);
    LMS7002M_regs_set(regs, 0x00A4, 0x6565);
    LMS7002M_regs_set(regs, 0x00A5, 0x6565);
    LMS7002M_regs_set(regs, 0x00A6, 0xf);
    LMS7002M_regs_set(regs, 0x00A7, 0x6565);
    LMS7002M_regs_set(regs, 0x00a8, 0x0);
    LMS7002M_regs_set(regs, 0x00aa, 0x0);
    LMS7002M_regs_set(regs, 0x00ab, 0x0);
    LMS7002M_regs_set(regs, 0x00ad, 0x3ff);
    LMS7002M_regs_set(regs, 0x00ae, 0xf000);
    LMS7002M_regs_set(regs, 0x0100, 0x3409);
    LMS7002M_regs_set(regs, 0x0101, 0x7800);
    LMS7002M_regs_set(regs, 0x0102, 0x3180);
    LMS7002M_regs_set(regs, 0x0103, 0xa12);
    LMS7002M_regs_set(regs, 0x0104, 0x88);
    LMS7002M_regs_set(regs, 0x0105, 0x7);
    LMS7002M_regs_set(regs, 0x0106, 0x318c);
    LMS7002M_regs_set(regs, 0x0107, 0x318c);
    LMS7002M_regs_set(regs, 0x0108, 0x9426);
    LMS7002M_regs_set(regs, 0x0109, 0x61c1);
    LMS7002M_regs_set(regs, 0x010A, 0x104c);
    LMS7002M_regs_set(regs, 0x010b, 0x0);
    LMS7002M_regs_set(regs, 0x010C, 0x88fd);
    LMS7002M_regs_set(regs, 0x010D, 0x9e);
    LMS7002M_regs_set(regs, 0x010E, 0x2040);
    LMS7002M_regs_set(regs, 0x010F, 0x3042);
    LMS7002M_regs_set(regs, 0x0110, 0xbf4);
    LMS7002M_regs_set(regs, 0x0111, 0x83);
    LMS7002M_regs_set(regs, 0x0112, 0xc0e6);
    LMS7002M_regs_set(regs, 0x0113, 0x3c3);
    LMS7002M_regs_set(regs, 0x0114, 0x8d);
    LMS7002M_regs_set(regs, 0x0115, 0x9);
    LMS7002M_regs_set(regs, 0x0116, 0x8180);
    LMS7002M_regs_set(regs, 0x0117, 0x280c);
    LMS7002M_regs_set(regs, 0x0118, 0x18c);
    LMS7002M_regs_set(regs, 0x0119, 0x18cb);
    LMS7002M_regs_set(regs, 0x011A, 0x2e02);
    LMS7002M_regs_set(regs, 0x011B, 0x0);
    LMS7002M_regs_set(regs, 0x011C, 0xad43);
    LMS7002M_regs_set(regs, 0x011D, 0x400);
    LMS7002M_regs_set(regs, 0x011E, 0x780);
    LMS7002M_regs_set(regs, 0x011F, 0x3640);
    LMS7002M_regs_set(regs, 0x0120, 0xb9ff);
    LMS7002M_regs_set(regs, 0x0121, 0x3404);
    LMS7002M_regs_set(regs, 0x0122, 0x33f);
    LMS7002M_regs_set(regs, 0x0123, 0x67b);
    LMS7002M_regs_set(regs, 0x0124, 0x0);
    LMS7002M_regs_set(regs, 0x0125, 0x9400);
    LMS7002M_regs_set(regs, 0x0126, 0x12ff);
    LMS7002M_regs_set(regs, 0x0200, 0x81);
    LMS7002M_regs_set(regs, 0x0201, 0x7ff);
    LMS7002M_regs_set(regs, 0x0202, 0x7ff);
    LMS7002M_regs_set(regs, 0x0203, 0x0);
    LMS7002M_regs_set(regs, 0x0204, 0x0);
    LMS7002M_regs_set(regs, 0x0205, 0x0);
    LMS7002M_regs_set(regs, 0x0206, 0x0);
    LMS7002M_regs_set(regs, 0x0207, 0x0);
    LMS7002M_regs_set(regs, 0x0208, 0x0);
    LMS7002M_regs_set(regs, 0x0209, 0x0);
    LMS7002M_regs_set(regs, 0x020a, 0x0);
    LMS7002M_regs_set(regs, 0x020C, 0x0);
    LMS7002M_regs_set(regs, 0x0240, 0x20);
    LMS7002M_regs_set(regs, 0x0241, 0x0);
    LMS7002M_regs_set(regs, 0x0242, 0x0);
    LMS7002M_regs_set(regs, 0x0243, 0x0);
    LMS7002M_regs_set(regs, 0x0400, 0x81);
    LMS7002M_regs_set(regs, 0x0401, 0x7ff);
    LMS7002M_regs_set(regs, 0x0402, 0x7ff);
    LMS7002M_regs_set(regs, 0x0403, 0x0);
    LMS7002M_regs_set(regs, 0x0404, 0x0);
    LMS7002M_regs_set(regs, 0x0405, 0x0);
    LMS7002M_regs_set(regs, 0x0406, 0x0);
    LMS7002M_regs_set(regs, 0x0407, 0x0);
    LMS7002M_regs_set(regs, 0x0408, 0x0);
    LMS7002M_regs_set(regs, 0x0409, 0x0);
    LMS7002M_regs_set(regs, 0x040A, 0x0);
    LMS7002M_regs_set(regs, 0x040B, 0x0);
    LMS7002M_regs_set(regs, 0x040C, 0x0);
    LMS7002M_regs_set(regs, 0x040e, 0x0);
    LMS7002M_regs_set(regs, 0x0440, 0x20);
    LMS7002M_regs_set(regs, 0x0441, 0x0);
    LMS7002M_regs_set(regs, 0x0442, 0x0);
    LMS7002M_regs_set(regs, 0x0443, 0x0);
    LMS7002M_regs_set(regs, 0x05c0, 0x0);
    LMS7002M_regs_set(regs, 0x05c1, 0x0);
    LMS7002M_regs_set(regs, 0x05c2, 0x0);
    LMS7002M_regs_set(regs, 0x05c3, 0x0);
    LMS7002M_regs_set(regs, 0x05c4, 0x0);
    LMS7002M_regs_set(regs, 0x05c5, 0x0);
    LMS7002M_regs_set(regs, 0x05c6, 0x0);
    LMS7002M_regs_set(regs, 0x05c7, 0x0);
    LMS7002M_regs_set(regs, 0x05c8, 0x0);
    LMS7002M_regs_set(regs, 0x05c9, 0x0);
    LMS7002M_regs_set(regs, 0x05ca, 0x0);
    LMS7002M_regs_set(regs, 0x05cb, 0x0);
    LMS7002M_regs_set(regs, 0x05cc, 0x0);
    LMS7002M_regs_set(regs, 0x0600, 0xf00);
    LMS7002M_regs_set(regs, 0x0601, 0x0);
    LMS7002M_regs_set(regs, 0x0602, 0x2000);
    LMS7002M_regs_set(regs, 0x0603, 0x0);
    LMS7002M_regs_set(regs, 0x0604, 0x0);
    LMS7002M_regs_set(regs, 0x0605, 0x0);
    LMS7002M_regs_set(regs, 0x0606, 0x0);
    LMS7002M_regs_set(regs, 0x0640, 0xa0);
    LMS7002M_regs_set(regs, 0x0641, 0x1020);
}

static inline int LMS7002M_regs_default(const int addr)
{
    if (addr == 0x0020) return 0xffff;
    if (addr == 0x0021) return 0xe9f;
    if (addr == 0x0022) return 0x7df;
    if (addr == 0x0023) return 0x5559;
    if (addr == 0x0024) return 0xe4e4;
    if (addr == 0x0025) return 0x101;
    if (addr == 0x0026) return 0x101;
    if (addr == 0x0027) return 0xe4e4;
    if (addr == 0x0028) return 0x101;
    if (addr == 0x0029) return 0x101;
    if (addr == 0x002A) return 0x86;
    if (addr == 0x002B) return 0x10;
    if (addr == 0x002C) return 0xffff;
    if (addr == 0x002E) return 0x0;
    if (addr == 0x002F) return 0x3840;
    if (addr == 0x0081) return 0x0;
    if (addr == 0x0082) return 0x800b;
    if (addr == 0x0084) return 0x400;
    if (addr == 0x0085) return 0x1;
    if (addr == 0x0086) return 0x4901;
    if (addr == 0x0087) return 0x400;
    if (addr == 0x0088) return 0x780;
    if (addr == 0x0089) return 0x20;
    if (addr == 0x008A) return 0x514;
    if (addr == 0x008B) return 0x2100;
    if (addr == 0x008C) return 0x67b;
    if (addr == 0x008D) return 0x0;
    if (addr == 0x0092) return 0x1;
    if (addr == 0x0093) return 0x0;
    if (addr == 0x0094) return 0x0;
    if (addr == 0x0095) return 0x0;
    if (addr == 0x0096) return 0x0;
    if (addr == 0x0097) return 0x0;
    if (addr == 0x0098) return 0x0;
    if (addr == 0x0099) return 0x6565;
    if (addr == 0x009A) return 0x658c;
    if (addr == 0x009B) return 0x6565;
    if (addr == 0x009C) return 0x658c;
    if (addr == 0x009D) return 0x6565;
    if (addr == 0x009E) return 0x658c;
    if (addr == 0x009F) return 0x658c;
    if (addr == 0x00A0) return 0x6565;
    if (addr == 0x00A1) return 0x6565;
    if (addr == 0x00A2) return 0x6565;
    if (addr == 0x00A3) return 0x6565;
    if (addr == 0x00A4) return 0x6565;
    if (addr == 0x00A5) return 0x6565;
    if (addr == 0x00A6) return 0xf;
    if (addr == 0x00A7) return 0x6565;
    if (addr == 0x00a8) return 0x0;
    if (addr == 0x00aa) return 0x0;
    if (addr == 0x00ab) return 0x0;
    if (addr == 0x00ad) return 0x3ff;
    if (addr == 0x00ae) return 0xf000;
    if (addr == 0x0100) return 0x3409;
    if (addr == 0x0101) return 0x7800;
    if (addr == 0x0102) return 0x3180;
    if (addr == 0x0103) return 0xa12;
    if (addr == 0x0104) return 0x88;
    if (addr == 0x0105) return 0x7;
    if (addr == 0x0106) return 0x318c;
    if (addr == 0x0107) return 0x318c;
    if (addr == 0x0108) return 0x9426;
    if (addr == 0x0109) return 0x61c1;
    if (addr == 0x010A) return 0x104c;
    if (addr == 0x010b) return 0x0;
    if (addr == 0x010C) return 0x88fd;
    if (addr == 0x010D) return 0x9e;
    if (addr == 0x010E) return 0x2040;
    if (addr == 0x010F) return 0x3042;
    if (addr == 0x0110) return 0xbf4;
    if (addr == 0x0111) return 0x83;
    if (addr == 0x0112) return 0xc0e6;
    if (addr == 0x0113) return 0x3c3;
    if (addr == 0x0114) return 0x8d;
    if (addr == 0x0115) return 0x9;
    if (addr == 0x0116) return 0x8180;
    if (addr == 0x0117) return 0x280c;
    if (addr == 0x0118) return 0x18c;
    if (addr == 0x0119) return 0x18cb;
    if (addr == 0x011A) return 0x2e02;
    if (addr == 0x011B) return 0x0;
    if (addr == 0x011C) return 0xad43;
    if (addr == 0x011D) return 0x400;
    if (addr == 0x011E) return 0x780;
    if (addr == 0x011F) return 0x3640;
    if (addr == 0x0120) return 0xb9ff;
    if (addr == 0x0121) return 0x3404;
    if (addr == 0x0122) return 0x33f;
    if (addr == 0x0123) return 0x67b;
    if (addr == 0x0124) return 0x0;
    if (addr == 0x0125) return 0x9400;
    if (addr == 0x0126) return 0x12ff;
    if (addr == 0x0200) return 0x81;
    if (addr == 0x0201) return 0x7ff;
    if (addr == 0x0202) return 0x7ff;
    if (addr == 0x0203) return 0x0;
    if (addr == 0x0204) return 0x0;
    if (addr == 0x0205) return 0x0;
    if (addr == 0x0206) return 0x0;
    if (addr == 0x0207) return 0x0;
    if (addr == 0x0208) return 0x0;
    if (addr == 0x0209) return 0x0;
    if (addr == 0x020a) return 0x0;
    if (addr == 0x020C) return 0x0;
    if (addr == 0x0240) return 0x20;
    if (addr == 0x0241) return 0x0;
    if (addr == 0x0242) return 0x0;
    if (addr == 0x0243) return 0x0;
    if (addr == 0x0400) return 0x81;
    if (addr == 0x0401) return 0x7ff;
    if (addr == 0x0402) return 0x7ff;
    if (addr == 0x0403) return 0x0;
    if (addr == 0x0404) return 0x0;
    if (addr == 0x0405) return 0x0;
    if (addr == 0x0406) return 0x0;
    if (addr == 0x0407) return 0x0;
    if (addr == 0x0408) return 0x0;
    if (addr == 0x0409) return 0x0;
    if (addr == 0x040A) return 0x0;
    if (addr == 0x040B) return 0x0;
    if (addr == 0x040C) return 0x0;
    if (addr == 0x040e) return 0x0;
    if (addr == 0x0440) return 0x20;
    if (addr == 0x0441) return 0x0;
    if (addr == 0x0442) return 0x0;
    if (addr == 0x0443) return 0x0;
    if (addr == 0x05c0) return 0x0;
    if (addr == 0x05c1) return 0x0;
    if (addr == 0x05c2) return 0x0;
    if (addr == 0x05c3) return 0x0;
    if (addr == 0x05c4) return 0x0;
    if (addr == 0x05c5) return 0x0;
    if (addr == 0x05c6) return 0x0;
    if (addr == 0x05c7) return 0x0;
    if (addr == 0x05c8) return 0x0;
    if (addr == 0x05c9) return 0x0;
    if (addr == 0x05ca) return 0x0;
    if (addr == 0x05cb) return 0x0;
    if (addr == 0x05cc) return 0x0;
    if (addr == 0x0600) return 0xf00;
    if (addr == 0x0601) return 0x0;
    if (addr == 0x0602) return 0x2000;
    if (addr == 0x0603) return 0x0;
    if (addr == 0x0604) return 0x0;
    if (addr == 0x0605) return 0x0;
    if (addr == 0x0606) return 0x0;
    if (addr == 0x0640) return 0xa0;
    if (addr == 0x0641) return 0x1020;
    return -1;
}

static inline void LMS7002M_regs_set(LMS7002M_regs_t *regs, const int addr, const int value)
{
    if (addr == 0x0020)
    {
        regs->reg_0x0020_lrst_tx_b = (value >> 15) & 0x1;
        regs->reg_0x0020_mrst_tx_b = (value >> 14) & 0x1;
        regs->reg_0x0020_lrst_tx_a = (value >> 13) & 0x1;
        regs->reg_0x0020_mrst_tx_a = (value >> 12) & 0x1;
        regs->reg_0x0020_lrst_rx_b = (value >> 11) & 0x1;
        regs->reg_0x0020_mrst_rx_b = (value >> 10) & 0x1;
        regs->reg_0x0020_lrst_rx_a = (value >> 9) & 0x1;
        regs->reg_0x0020_mrst_rx_a = (value >> 8) & 0x1;
        regs->reg_0x0020_srst_rxfifo = (value >> 7) & 0x1;
        regs->reg_0x0020_srst_txfifo = (value >> 6) & 0x1;
        regs->reg_0x0020_rxen_b = (value >> 5) & 0x1;
        regs->reg_0x0020_rxen_a = (value >> 4) & 0x1;
        regs->reg_0x0020_txen_b = (value >> 3) & 0x1;
        regs->reg_0x0020_txen_a = (value >> 2) & 0x1;
        regs->reg_0x0020_mac = (value >> 0) & 0x3;
        return;
    }
    if (addr == 0x0021)
    {
        regs->reg_0x0021_tx_clk_pe = (value >> 11) & 0x1;
        regs->reg_0x0021_rx_clk_pe = (value >> 10) & 0x1;
        regs->reg_0x0021_sda_pe = (value >> 9) & 0x1;
        regs->reg_0x0021_sda_ds = (value >> 8) & 0x1;
        regs->reg_0x0021_scl_pe = (value >> 7) & 0x1;
        regs->reg_0x0021_scl_ds = (value >> 6) & 0x1;
        regs->reg_0x0021_sdio_ds = (value >> 5) & 0x1;
        regs->reg_0x0021_sdio_pe = (value >> 4) & 0x1;
        regs->reg_0x0021_sdo_pe = (value >> 3) & 0x1;
        regs->reg_0x0021_sclk_pe = (value >> 2) & 0x1;
        regs->reg_0x0021_sen_pe = (value >> 1) & 0x1;
        regs->reg_0x0021_spimode = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0022)
    {
        regs->reg_0x0022_diq2_ds = (value >> 11) & 0x1;
        regs->reg_0x0022_diq2_pe = (value >> 10) & 0x1;
        regs->reg_0x0022_iq_sel_en_2_pe = (value >> 9) & 0x1;
        regs->reg_0x0022_txnrx2_pe = (value >> 8) & 0x1;
        regs->reg_0x0022_fclk2_pe = (value >> 7) & 0x1;
        regs->reg_0x0022_mclk2_pe = (value >> 6) & 0x1;
        regs->reg_0x0022_diq1_ds = (value >> 5) & 0x1;
        regs->reg_0x0022_diq1_pe = (value >> 4) & 0x1;
        regs->reg_0x0022_iq_sel_en_1_pe = (value >> 3) & 0x1;
        regs->reg_0x0022_txnrx1_pe = (value >> 2) & 0x1;
        regs->reg_0x0022_fclk1_pe = (value >> 1) & 0x1;
        regs->reg_0x0022_mclk1_pe = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0023)
    {
        regs->reg_0x0023_diqdirctr2 = (value >> 15) & 0x1;
        regs->reg_0x0023_diqdir2 = (value >> 14) & 0x1;
        regs->reg_0x0023_diqdirctr1 = (value >> 13) & 0x1;
        regs->reg_0x0023_diqdir1 = (value >> 12) & 0x1;
        regs->reg_0x0023_enabledirctr2 = (value >> 11) & 0x1;
        regs->reg_0x0023_enabledir2 = (value >> 10) & 0x1;
        regs->reg_0x0023_enabledirctr1 = (value >> 9) & 0x1;
        regs->reg_0x0023_enabledir1 = (value >> 8) & 0x1;
        regs->reg_0x0023_mod_en = (value >> 6) & 0x1;
        regs->reg_0x0023_lml2_fidm = (value >> 5) & 0x1;
        regs->reg_0x0023_lml2_rxntxiq = (value >> 4) & 0x1;
        regs->reg_0x0023_lml2_mode = (value >> 3) & 0x1;
        regs->reg_0x0023_lml1_fidm = (value >> 2) & 0x1;
        regs->reg_0x0023_lml1_rxntxiq = (value >> 1) & 0x1;
        regs->reg_0x0023_lml1_mode = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0024)
    {
        regs->reg_0x0024_lml1_s3s = (value >> 14) & 0x3;
        regs->reg_0x0024_lml1_s2s = (value >> 12) & 0x3;
        regs->reg_0x0024_lml1_s1s = (value >> 10) & 0x3;
        regs->reg_0x0024_lml1_s0s = (value >> 8) & 0x3;
        regs->reg_0x0024_lml1_bqp = (value >> 6) & 0x3;
        regs->reg_0x0024_lml1_bip = (value >> 4) & 0x3;
        regs->reg_0x0024_lml1_aqp = (value >> 2) & 0x3;
        regs->reg_0x0024_lml1_aip = (value >> 0) & 0x3;
        return;
    }
    if (addr == 0x0025)
    {
        regs->reg_0x0025_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0026)
    {
        regs->reg_0x0026_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0027)
    {
        regs->reg_0x0027_lml2_s3s = (value >> 14) & 0x3;
        regs->reg_0x0027_lml2_s2s = (value >> 12) & 0x3;
        regs->reg_0x0027_lml2_s1s = (value >> 10) & 0x3;
        regs->reg_0x0027_lml2_s0s = (value >> 8) & 0x3;
        regs->reg_0x0027_lml2_bqp = (value >> 6) & 0x3;
        regs->reg_0x0027_lml2_bip = (value >> 4) & 0x3;
        regs->reg_0x0027_lml2_aqp = (value >> 2) & 0x3;
        regs->reg_0x0027_lml2_aip = (value >> 0) & 0x3;
        return;
    }
    if (addr == 0x0028)
    {
        regs->reg_0x0028_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0029)
    {
        regs->reg_0x0029_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x002A)
    {
        regs->reg_0x002a_fclk2_dly = (value >> 14) & 0x3;
        regs->reg_0x002a_fclk1_dly = (value >> 12) & 0x3;
        regs->reg_0x002a_rx_mux = (value >> 10) & 0x3;
        regs->reg_0x002a_tx_mux = (value >> 8) & 0x3;
        regs->reg_0x002a_txrdclk_mux = (value >> 6) & 0x3;
        regs->reg_0x002a_txwrclk_mux = (value >> 4) & 0x3;
        regs->reg_0x002a_rxrdclk_mux = (value >> 2) & 0x3;
        regs->reg_0x002a_rxwrclk_mux = (value >> 0) & 0x3;
        return;
    }
    if (addr == 0x002B)
    {
        regs->reg_0x002b_fclk2_inv = (value >> 15) & 0x1;
        regs->reg_0x002b_fclk1_inv = (value >> 14) & 0x1;
        regs->reg_0x002b_mclk2src = (value >> 4) & 0x3;
        regs->reg_0x002b_mclk1src = (value >> 2) & 0x3;
        regs->reg_0x002b_txdiven = (value >> 1) & 0x1;
        regs->reg_0x002b_rxdiven = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x002C)
    {
        regs->reg_0x002c_txtspclk_div = (value >> 8) & 0xff;
        regs->reg_0x002c_rxtspclk_div = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x002E)
    {
        regs->reg_0x002e_mimo_siso = (value >> 15) & 0x1;
        return;
    }
    if (addr == 0x002F)
    {
        regs->reg_0x002f_ver = (value >> 11) & 0x1f;
        regs->reg_0x002f_rev = (value >> 6) & 0x1f;
        regs->reg_0x002f_mask = (value >> 0) & 0x3f;
        return;
    }
    if (addr == 0x0081)
    {
        regs->reg_0x0081_en_dir_ldo = (value >> 3) & 0x1;
        regs->reg_0x0081_en_dir_cgen = (value >> 2) & 0x1;
        regs->reg_0x0081_en_dir_xbuf = (value >> 1) & 0x1;
        regs->reg_0x0081_en_dir_afe = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0082)
    {
        regs->reg_0x0082_isel_dac_afe = (value >> 13) & 0x7;
        regs->reg_0x0082_mode_interleave_afe = (value >> 12) & 0x1;
        regs->reg_0x0082_mux_afe_1 = (value >> 10) & 0x3;
        regs->reg_0x0082_mux_afe_2 = (value >> 8) & 0x3;
        regs->reg_0x0082_pd_afe = (value >> 5) & 0x1;
        regs->reg_0x0082_pd_rx_afe1 = (value >> 4) & 0x1;
        regs->reg_0x0082_pd_rx_afe2 = (value >> 3) & 0x1;
        regs->reg_0x0082_pd_tx_afe1 = (value >> 2) & 0x1;
        regs->reg_0x0082_pd_tx_afe2 = (value >> 1) & 0x1;
        regs->reg_0x0082_en_g_afe = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0084)
    {
        regs->reg_0x0084_mux_bias_out = (value >> 11) & 0x3;
        regs->reg_0x0084_rp_calib_bias = (value >> 6) & 0x1f;
        regs->reg_0x0084_pd_frp_bias = (value >> 4) & 0x1;
        regs->reg_0x0084_pd_f_bias = (value >> 3) & 0x1;
        regs->reg_0x0084_pd_ptrp_bias = (value >> 2) & 0x1;
        regs->reg_0x0084_pd_pt_bias = (value >> 1) & 0x1;
        regs->reg_0x0084_pd_bias_master = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0085)
    {
        regs->reg_0x0085_slfb_xbuf_rx = (value >> 8) & 0x1;
        regs->reg_0x0085_slfb_xbuf_tx = (value >> 7) & 0x1;
        regs->reg_0x0085_byp_xbuf_rx = (value >> 6) & 0x1;
        regs->reg_0x0085_byp_xbuf_tx = (value >> 5) & 0x1;
        regs->reg_0x0085_en_out2_xbuf_tx = (value >> 4) & 0x1;
        regs->reg_0x0085_en_tbufin_xbuf_rx = (value >> 3) & 0x1;
        regs->reg_0x0085_pd_xbuf_rx = (value >> 2) & 0x1;
        regs->reg_0x0085_pd_xbuf_tx = (value >> 1) & 0x1;
        regs->reg_0x0085_en_g_xbuf = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0086)
    {
        regs->reg_0x0086_spdup_vco_cgen = (value >> 15) & 0x1;
        regs->reg_0x0086_reset_n_cgen = (value >> 14) & 0x1;
        regs->reg_0x0086_en_adcclkh_clkgn = (value >> 11) & 0x1;
        regs->reg_0x0086_en_coarse_cklgen = (value >> 10) & 0x1;
        regs->reg_0x0086_en_intonly_sdm_cgen = (value >> 9) & 0x1;
        regs->reg_0x0086_en_sdm_clk_cgen = (value >> 8) & 0x1;
        regs->reg_0x0086_pd_cp_cgen = (value >> 6) & 0x1;
        regs->reg_0x0086_pd_fdiv_fb_cgen = (value >> 5) & 0x1;
        regs->reg_0x0086_pd_fdiv_o_cgen = (value >> 4) & 0x1;
        regs->reg_0x0086_pd_sdm_cgen = (value >> 3) & 0x1;
        regs->reg_0x0086_pd_vco_cgen = (value >> 2) & 0x1;
        regs->reg_0x0086_pd_vco_comp_cgen = (value >> 1) & 0x1;
        regs->reg_0x0086_en_g_cgen = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0087)
    {
        regs->reg_0x0087_frac_sdm_cgen = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0088)
    {
        regs->reg_0x0088_int_sdm_cgen = (value >> 4) & 0x3ff;
        regs->reg_0x0088_frac_sdm_cgen = (value >> 0) & 0xf;
        return;
    }
    if (addr == 0x0089)
    {
        regs->reg_0x0089_rev_sdmclk_cgen = (value >> 15) & 0x1;
        regs->reg_0x0089_sel_sdmclk_cgen = (value >> 14) & 0x1;
        regs->reg_0x0089_sx_dither_en_cgen = (value >> 13) & 0x1;
        regs->reg_0x0089_clkh_ov_clkl_cgen = (value >> 11) & 0x3;
        regs->reg_0x0089_div_outch_cgen = (value >> 3) & 0xff;
        regs->reg_0x0089_tst_cgen = (value >> 0) & 0x7;
        return;
    }
    if (addr == 0x008A)
    {
        regs->reg_0x008a_rev_clkdac_cgen = (value >> 14) & 0x1;
        regs->reg_0x008a_rev_clkadc_cgen = (value >> 13) & 0x1;
        regs->reg_0x008a_revph_pfd_cgen = (value >> 12) & 0x1;
        regs->reg_0x008a_ioffset_cp_cgen = (value >> 6) & 0x3f;
        regs->reg_0x008a_ipulse_cp_cgen = (value >> 0) & 0x3f;
        return;
    }
    if (addr == 0x008B)
    {
        regs->reg_0x008b_ict_vco_cgen = (value >> 9) & 0x1f;
        regs->reg_0x008b_csw_vco_cgen = (value >> 1) & 0xff;
        regs->reg_0x008b_coarse_start_cgen = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x008C)
    {
        regs->reg_0x008c_coarse_stepdone_cgen = (value >> 15) & 0x1;
        regs->reg_0x008c_coarsepll_compo_cgen = (value >> 14) & 0x1;
        regs->reg_0x008c_vco_cmpho_cgen = (value >> 13) & 0x1;
        regs->reg_0x008c_vco_cmplo_cgen = (value >> 12) & 0x1;
        regs->reg_0x008c_cp2_cgen = (value >> 8) & 0xf;
        regs->reg_0x008c_cp3_cgen = (value >> 4) & 0xf;
        regs->reg_0x008c_cz_cgen = (value >> 0) & 0xf;
        return;
    }
    if (addr == 0x008D)
    {
        regs->reg_0x008d_resrv_cgn = (value >> 0) & 0x7;
        return;
    }
    if (addr == 0x0092)
    {
        regs->reg_0x0092_en_ldo_dig = (value >> 15) & 0x1;
        regs->reg_0x0092_en_ldo_diggn = (value >> 14) & 0x1;
        regs->reg_0x0092_en_ldo_digsxr = (value >> 13) & 0x1;
        regs->reg_0x0092_en_ldo_digsxt = (value >> 12) & 0x1;
        regs->reg_0x0092_en_ldo_divgn = (value >> 11) & 0x1;
        regs->reg_0x0092_en_ldo_divsxr = (value >> 10) & 0x1;
        regs->reg_0x0092_en_ldo_divsxt = (value >> 9) & 0x1;
        regs->reg_0x0092_en_ldo_lna12 = (value >> 8) & 0x1;
        regs->reg_0x0092_en_ldo_lna14 = (value >> 7) & 0x1;
        regs->reg_0x0092_en_ldo_mxrfe = (value >> 6) & 0x1;
        regs->reg_0x0092_en_ldo_rbb = (value >> 5) & 0x1;
        regs->reg_0x0092_en_ldo_rxbuf = (value >> 4) & 0x1;
        regs->reg_0x0092_en_ldo_tbb = (value >> 3) & 0x1;
        regs->reg_0x0092_en_ldo_tia12 = (value >> 2) & 0x1;
        regs->reg_0x0092_en_ldo_tia14 = (value >> 1) & 0x1;
        regs->reg_0x0092_en_g_ldo = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0093)
    {
        regs->reg_0x0093_en_loadimp_ldo_tlob = (value >> 15) & 0x1;
        regs->reg_0x0093_en_loadimp_ldo_tpad = (value >> 14) & 0x1;
        regs->reg_0x0093_en_loadimp_ldo_txbuf = (value >> 13) & 0x1;
        regs->reg_0x0093_en_loadimp_ldo_vcogn = (value >> 12) & 0x1;
        regs->reg_0x0093_en_loadimp_ldo_vcosxr = (value >> 11) & 0x1;
        regs->reg_0x0093_en_loadimp_ldo_vcosxt = (value >> 10) & 0x1;
        regs->reg_0x0093_en_ldo_afe = (value >> 9) & 0x1;
        regs->reg_0x0093_en_ldo_cpgn = (value >> 8) & 0x1;
        regs->reg_0x0093_en_ldo_cpsxr = (value >> 7) & 0x1;
        regs->reg_0x0093_en_ldo_tlob = (value >> 6) & 0x1;
        regs->reg_0x0093_en_ldo_tpad = (value >> 5) & 0x1;
        regs->reg_0x0093_en_ldo_txbuf = (value >> 4) & 0x1;
        regs->reg_0x0093_en_ldo_vcogn = (value >> 3) & 0x1;
        regs->reg_0x0093_en_ldo_vcosxr = (value >> 2) & 0x1;
        regs->reg_0x0093_en_ldo_vcosxt = (value >> 1) & 0x1;
        regs->reg_0x0093_en_ldo_cpsxt = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0094)
    {
        regs->reg_0x0094_en_loadimp_ldo_cpsxt = (value >> 15) & 0x1;
        regs->reg_0x0094_en_loadimp_ldo_dig = (value >> 14) & 0x1;
        regs->reg_0x0094_en_loadimp_ldo_diggn = (value >> 13) & 0x1;
        regs->reg_0x0094_en_loadimp_ldo_digsxr = (value >> 12) & 0x1;
        regs->reg_0x0094_en_loadimp_ldo_digsxt = (value >> 11) & 0x1;
        regs->reg_0x0094_en_loadimp_ldo_divgn = (value >> 10) & 0x1;
        regs->reg_0x0094_en_loadimp_ldo_divsxr = (value >> 9) & 0x1;
        regs->reg_0x0094_en_loadimp_ldo_divsxt = (value >> 8) & 0x1;
        regs->reg_0x0094_en_loadimp_ldo_lna12 = (value >> 7) & 0x1;
        regs->reg_0x0094_en_loadimp_ldo_lna14 = (value >> 6) & 0x1;
        regs->reg_0x0094_en_loadimp_ldo_mxrfe = (value >> 5) & 0x1;
        regs->reg_0x0094_en_loadimp_ldo_rbb = (value >> 4) & 0x1;
        regs->reg_0x0094_en_loadimp_ldo_rxbuf = (value >> 3) & 0x1;
        regs->reg_0x0094_en_loadimp_ldo_tbb = (value >> 2) & 0x1;
        regs->reg_0x0094_en_loadimp_ldo_tia12 = (value >> 1) & 0x1;
        regs->reg_0x0094_en_loadimp_ldo_tia14 = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0095)
    {
        regs->reg_0x0095_byp_ldo_tbb = (value >> 15) & 0x1;
        regs->reg_0x0095_byp_ldo_tia12 = (value >> 14) & 0x1;
        regs->reg_0x0095_byp_ldo_tia14 = (value >> 13) & 0x1;
        regs->reg_0x0095_byp_ldo_tlob = (value >> 12) & 0x1;
        regs->reg_0x0095_byp_ldo_tpad = (value >> 11) & 0x1;
        regs->reg_0x0095_byp_ldo_txbuf = (value >> 10) & 0x1;
        regs->reg_0x0095_byp_ldo_vcogn = (value >> 9) & 0x1;
        regs->reg_0x0095_byp_ldo_vcosxr = (value >> 8) & 0x1;
        regs->reg_0x0095_byp_ldo_vcosxt = (value >> 7) & 0x1;
        regs->reg_0x0095_en_loadimp_ldo_afe = (value >> 2) & 0x1;
        regs->reg_0x0095_en_loadimp_ldo_cpgn = (value >> 1) & 0x1;
        regs->reg_0x0095_en_loadimp_ldo_cpsxr = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0096)
    {
        regs->reg_0x0096_byp_ldo_afe = (value >> 15) & 0x1;
        regs->reg_0x0096_byp_ldo_cpgn = (value >> 14) & 0x1;
        regs->reg_0x0096_byp_ldo_cpsxr = (value >> 13) & 0x1;
        regs->reg_0x0096_byp_ldo_cpsxt = (value >> 12) & 0x1;
        regs->reg_0x0096_byp_ldo_dig = (value >> 11) & 0x1;
        regs->reg_0x0096_byp_ldo_diggn = (value >> 10) & 0x1;
        regs->reg_0x0096_byp_ldo_digsxr = (value >> 9) & 0x1;
        regs->reg_0x0096_byp_ldo_digsxt = (value >> 8) & 0x1;
        regs->reg_0x0096_byp_ldo_divgn = (value >> 7) & 0x1;
        regs->reg_0x0096_byp_ldo_divsxr = (value >> 6) & 0x1;
        regs->reg_0x0096_byp_ldo_divsxt = (value >> 5) & 0x1;
        regs->reg_0x0096_byp_ldo_lna12 = (value >> 4) & 0x1;
        regs->reg_0x0096_byp_ldo_lna14 = (value >> 3) & 0x1;
        regs->reg_0x0096_byp_ldo_mxrfe = (value >> 2) & 0x1;
        regs->reg_0x0096_byp_ldo_rbb = (value >> 1) & 0x1;
        regs->reg_0x0096_byp_ldo_rxbuf = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0097)
    {
        regs->reg_0x0097_spdup_ldo_divsxr = (value >> 15) & 0x1;
        regs->reg_0x0097_spdup_ldo_divsxt = (value >> 14) & 0x1;
        regs->reg_0x0097_spdup_ldo_lna12 = (value >> 13) & 0x1;
        regs->reg_0x0097_spdup_ldo_lna14 = (value >> 12) & 0x1;
        regs->reg_0x0097_spdup_ldo_mxrfe = (value >> 11) & 0x1;
        regs->reg_0x0097_spdup_ldo_rbb = (value >> 10) & 0x1;
        regs->reg_0x0097_spdup_ldo_rxbuf = (value >> 9) & 0x1;
        regs->reg_0x0097_spdup_ldo_tbb = (value >> 8) & 0x1;
        regs->reg_0x0097_spdup_ldo_tia12 = (value >> 7) & 0x1;
        regs->reg_0x0097_spdup_ldo_tia14 = (value >> 6) & 0x1;
        regs->reg_0x0097_spdup_ldo_tlob = (value >> 5) & 0x1;
        regs->reg_0x0097_spdup_ldo_tpad = (value >> 4) & 0x1;
        regs->reg_0x0097_spdup_ldo_txbuf = (value >> 3) & 0x1;
        regs->reg_0x0097_spdup_ldo_vcogn = (value >> 2) & 0x1;
        regs->reg_0x0097_spdup_ldo_vcosxr = (value >> 1) & 0x1;
        regs->reg_0x0097_spdup_ldo_vcosxt = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0098)
    {
        regs->reg_0x0098_spdup_ldo_afe = (value >> 8) & 0x1;
        regs->reg_0x0098_spdup_ldo_cpgn = (value >> 7) & 0x1;
        regs->reg_0x0098_spdup_ldo_cpsxr = (value >> 6) & 0x1;
        regs->reg_0x0098_spdup_ldo_cpsxt = (value >> 5) & 0x1;
        regs->reg_0x0098_spdup_ldo_dig = (value >> 4) & 0x1;
        regs->reg_0x0098_spdup_ldo_diggn = (value >> 3) & 0x1;
        regs->reg_0x0098_spdup_ldo_digsxr = (value >> 2) & 0x1;
        regs->reg_0x0098_spdup_ldo_digsxt = (value >> 1) & 0x1;
        regs->reg_0x0098_spdup_ldo_divgn = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0099)
    {
        regs->reg_0x0099_rdiv_vcosxr = (value >> 8) & 0xff;
        regs->reg_0x0099_rdiv_vcosxt = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x009A)
    {
        regs->reg_0x009a_rdiv_txbuf = (value >> 8) & 0xff;
        regs->reg_0x009a_rdiv_vcogn = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x009B)
    {
        regs->reg_0x009b_rdiv_tlob = (value >> 8) & 0xff;
        regs->reg_0x009b_rdiv_tpad = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x009C)
    {
        regs->reg_0x009c_rdiv_tia12 = (value >> 8) & 0xff;
        regs->reg_0x009c_rdiv_tia14 = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x009D)
    {
        regs->reg_0x009d_rdiv_rxbuf = (value >> 8) & 0xff;
        regs->reg_0x009d_rdiv_tbb = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x009E)
    {
        regs->reg_0x009e_rdiv_mxrfe = (value >> 8) & 0xff;
        regs->reg_0x009e_rdiv_rbb = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x009F)
    {
        regs->reg_0x009f_rdiv_lna12 = (value >> 8) & 0xff;
        regs->reg_0x009f_rdiv_lna14 = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x00A0)
    {
        regs->reg_0x00a0_rdiv_divsxr = (value >> 8) & 0xff;
        regs->reg_0x00a0_rdiv_divsxt = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x00A1)
    {
        regs->reg_0x00a1_rdiv_digsxt = (value >> 8) & 0xff;
        regs->reg_0x00a1_rdiv_divgn = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x00A2)
    {
        regs->reg_0x00a2_rdiv_diggn = (value >> 8) & 0xff;
        regs->reg_0x00a2_rdiv_digsxr = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x00A3)
    {
        regs->reg_0x00a3_rdiv_cpsxt = (value >> 8) & 0xff;
        regs->reg_0x00a3_rdiv_dig = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x00A4)
    {
        regs->reg_0x00a4_rdiv_cpgn = (value >> 8) & 0xff;
        regs->reg_0x00a4_rdiv_cpsxr = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x00A5)
    {
        regs->reg_0x00a5_rdiv_spibuf = (value >> 8) & 0xff;
        regs->reg_0x00a5_rdiv_afe = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x00A6)
    {
        regs->reg_0x00a6_spdup_ldo_spibuf = (value >> 12) & 0x1;
        regs->reg_0x00a6_spdup_ldo_digip2 = (value >> 11) & 0x1;
        regs->reg_0x00a6_spdup_ldo_digip1 = (value >> 10) & 0x1;
        regs->reg_0x00a6_byp_ldo_spibuf = (value >> 9) & 0x1;
        regs->reg_0x00a6_byp_ldo_digip2 = (value >> 8) & 0x1;
        regs->reg_0x00a6_byp_ldo_digip1 = (value >> 7) & 0x1;
        regs->reg_0x00a6_en_loadimp_ldo_spibuf = (value >> 6) & 0x1;
        regs->reg_0x00a6_en_loadimp_ldo_digip2 = (value >> 5) & 0x1;
        regs->reg_0x00a6_en_loadimp_ldo_digip1 = (value >> 4) & 0x1;
        regs->reg_0x00a6_pd_ldo_spibuf = (value >> 3) & 0x1;
        regs->reg_0x00a6_pd_ldo_digip2 = (value >> 2) & 0x1;
        regs->reg_0x00a6_pd_ldo_digip1 = (value >> 1) & 0x1;
        regs->reg_0x00a6_en_g_ldop = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x00A7)
    {
        regs->reg_0x00a7_rdiv_digip2 = (value >> 8) & 0xff;
        regs->reg_0x00a7_rdiv_digip1 = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x00a8)
    {
        regs->reg_0x00a8_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x00aa)
    {
        regs->reg_0x00aa_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x00ab)
    {
        regs->reg_0x00ab_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x00ad)
    {
        regs->reg_0x00ad_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x00ae)
    {
        regs->reg_0x00ae_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0100)
    {
        regs->reg_0x0100_en_lowbwlomx_tmx_trf = (value >> 15) & 0x1;
        regs->reg_0x0100_en_nexttx_trf = (value >> 14) & 0x1;
        regs->reg_0x0100_en_amphf_pdet_trf = (value >> 12) & 0x3;
        regs->reg_0x0100_loadr_pdet_trf = (value >> 10) & 0x3;
        regs->reg_0x0100_pd_pdet_trf = (value >> 3) & 0x1;
        regs->reg_0x0100_pd_tlobuf_trf = (value >> 2) & 0x1;
        regs->reg_0x0100_pd_txpad_trf = (value >> 1) & 0x1;
        regs->reg_0x0100_en_g_trf = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0101)
    {
        regs->reg_0x0101_f_txpad_trf = (value >> 13) & 0x7;
        regs->reg_0x0101_l_loopb_txpad_trf = (value >> 11) & 0x3;
        regs->reg_0x0101_loss_lin_txpad_trf = (value >> 6) & 0x1f;
        regs->reg_0x0101_loss_main_txpad_trf = (value >> 1) & 0x1f;
        regs->reg_0x0101_en_loopb_txpad_trf = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0102)
    {
        regs->reg_0x0102_gcas_gndref_txpad_trf = (value >> 15) & 0x1;
        regs->reg_0x0102_ict_lin_txpad_trf = (value >> 10) & 0x1f;
        regs->reg_0x0102_ict_main_txpad_trf = (value >> 5) & 0x1f;
        regs->reg_0x0102_vgcas_txpad_trf = (value >> 0) & 0x1f;
        return;
    }
    if (addr == 0x0103)
    {
        regs->reg_0x0103_sel_band1_trf = (value >> 11) & 0x1;
        regs->reg_0x0103_sel_band2_trf = (value >> 10) & 0x1;
        regs->reg_0x0103_lobiasn_txm_trf = (value >> 5) & 0x1f;
        regs->reg_0x0103_lobiasp_txx_trf = (value >> 0) & 0x1f;
        return;
    }
    if (addr == 0x0104)
    {
        regs->reg_0x0104_cdc_i_trf = (value >> 4) & 0xf;
        regs->reg_0x0104_cdc_q_trf = (value >> 0) & 0xf;
        return;
    }
    if (addr == 0x0105)
    {
        regs->reg_0x0105_statpulse_tbb = (value >> 15) & 0x1;
        regs->reg_0x0105_loopb_tbb = (value >> 12) & 0x7;
        regs->reg_0x0105_pd_lpfh_tbb = (value >> 4) & 0x1;
        regs->reg_0x0105_pd_lpfiamp_tbb = (value >> 3) & 0x1;
        regs->reg_0x0105_pd_lpflad_tbb = (value >> 2) & 0x1;
        regs->reg_0x0105_pd_lpfs5_tbb = (value >> 1) & 0x1;
        regs->reg_0x0105_en_g_tbb = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0106)
    {
        regs->reg_0x0106_ict_lpfs5_f_tbb = (value >> 10) & 0x1f;
        regs->reg_0x0106_ict_lpfs5_pt_tbb = (value >> 5) & 0x1f;
        regs->reg_0x0106_ict_lpf_h_pt_tbb = (value >> 0) & 0x1f;
        return;
    }
    if (addr == 0x0107)
    {
        regs->reg_0x0107_ict_lpfh_f_tbb = (value >> 10) & 0x1f;
        regs->reg_0x0107_ict_lpflad_f_tbb = (value >> 5) & 0x1f;
        regs->reg_0x0107_ict_lpflad_pt_tbb = (value >> 0) & 0x1f;
        return;
    }
    if (addr == 0x0108)
    {
        regs->reg_0x0108_cg_iamp_tbb = (value >> 10) & 0x3f;
        regs->reg_0x0108_ict_iamp_frp_tbb = (value >> 5) & 0x1f;
        regs->reg_0x0108_ict_iamp_gg_frp_tbb = (value >> 0) & 0x1f;
        return;
    }
    if (addr == 0x0109)
    {
        regs->reg_0x0109_rcal_lpfh_tbb = (value >> 8) & 0xff;
        regs->reg_0x0109_rcal_lpflad_tbb = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x010A)
    {
        regs->reg_0x010a_tstin_tbb = (value >> 14) & 0x3;
        regs->reg_0x010a_bypladder_tbb = (value >> 13) & 0x1;
        regs->reg_0x010a_ccal_lpflad_tbb = (value >> 8) & 0x1f;
        regs->reg_0x010a_rcal_lpfs5_tbb = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x010b)
    {
        regs->reg_0x010b_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x010C)
    {
        regs->reg_0x010c_cdc_i_rfe = (value >> 12) & 0xf;
        regs->reg_0x010c_cdc_q_rfe = (value >> 8) & 0xf;
        regs->reg_0x010c_pd_lna_rfe = (value >> 7) & 0x1;
        regs->reg_0x010c_pd_rloopb_1_rfe = (value >> 6) & 0x1;
        regs->reg_0x010c_pd_rloopb_2_rfe = (value >> 5) & 0x1;
        regs->reg_0x010c_pd_mxlobuf_rfe = (value >> 4) & 0x1;
        regs->reg_0x010c_pd_qgen_rfe = (value >> 3) & 0x1;
        regs->reg_0x010c_pd_rssi_rfe = (value >> 2) & 0x1;
        regs->reg_0x010c_pd_tia_rfe = (value >> 1) & 0x1;
        regs->reg_0x010c_en_g_rfe = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x010D)
    {
        regs->reg_0x010d_sel_path_rfe = (value >> 7) & 0x3;
        regs->reg_0x010d_en_dcoff_rxfe_rfe = (value >> 6) & 0x1;
        regs->reg_0x010d_en_inshsw_lb1_rfe = (value >> 4) & 0x1;
        regs->reg_0x010d_en_inshsw_lb2_rfe = (value >> 3) & 0x1;
        regs->reg_0x010d_en_inshsw_l_rfe = (value >> 2) & 0x1;
        regs->reg_0x010d_en_inshsw_w_rfe = (value >> 1) & 0x1;
        regs->reg_0x010d_en_nextrx_rfe = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x010E)
    {
        regs->reg_0x010e_dcoffi_rfe = (value >> 7) & 0x7f;
        regs->reg_0x010e_dcoffq_rfe = (value >> 0) & 0x7f;
        return;
    }
    if (addr == 0x010F)
    {
        regs->reg_0x010f_ict_loopb_rfe = (value >> 10) & 0x1f;
        regs->reg_0x010f_ict_tiamain_rfe = (value >> 5) & 0x1f;
        regs->reg_0x010f_ict_tiaout_rfe = (value >> 0) & 0x1f;
        return;
    }
    if (addr == 0x0110)
    {
        regs->reg_0x0110_ict_lnacmo_rfe = (value >> 10) & 0x1f;
        regs->reg_0x0110_ict_lna_rfe = (value >> 5) & 0x1f;
        regs->reg_0x0110_ict_lodc_rfe = (value >> 0) & 0x1f;
        return;
    }
    if (addr == 0x0111)
    {
        regs->reg_0x0111_cap_rxmxo_rfe = (value >> 5) & 0x1f;
        regs->reg_0x0111_cgsin_lna_rfe = (value >> 0) & 0x1f;
        return;
    }
    if (addr == 0x0112)
    {
        regs->reg_0x0112_ccomp_tia_rfe = (value >> 12) & 0xf;
        regs->reg_0x0112_cfb_tia_rfe = (value >> 0) & 0xfff;
        return;
    }
    if (addr == 0x0113)
    {
        regs->reg_0x0113_g_lna_rfe = (value >> 6) & 0xf;
        regs->reg_0x0113_g_rxloopb_rfe = (value >> 2) & 0xf;
        regs->reg_0x0113_g_tia_rfe = (value >> 0) & 0x3;
        return;
    }
    if (addr == 0x0114)
    {
        regs->reg_0x0114_rcomp_tia_rfe = (value >> 5) & 0xf;
        regs->reg_0x0114_rfb_tia_rfe = (value >> 0) & 0x1f;
        return;
    }
    if (addr == 0x0115)
    {
        regs->reg_0x0115_en_lb_lpfh_rbb = (value >> 15) & 0x1;
        regs->reg_0x0115_en_lb_lpfl_rbb = (value >> 14) & 0x1;
        regs->reg_0x0115_pd_lpfh_rbb = (value >> 3) & 0x1;
        regs->reg_0x0115_pd_lpfl_rbb = (value >> 2) & 0x1;
        regs->reg_0x0115_pd_pga_rbb = (value >> 1) & 0x1;
        regs->reg_0x0115_en_g_rbb = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0116)
    {
        regs->reg_0x0116_r_ctl_lpf_rbb = (value >> 11) & 0x1f;
        regs->reg_0x0116_rcc_ctl_lpfh_rbb = (value >> 8) & 0x7;
        regs->reg_0x0116_c_ctl_lpfh_rbb = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x0117)
    {
        regs->reg_0x0117_rcc_ctl_lpfl_rbb = (value >> 11) & 0x7;
        regs->reg_0x0117_c_ctl_lpfl_rbb = (value >> 0) & 0x7ff;
        return;
    }
    if (addr == 0x0118)
    {
        regs->reg_0x0118_input_ctl_pga_rbb = (value >> 13) & 0x7;
        regs->reg_0x0118_ict_lpf_in_rbb = (value >> 5) & 0x1f;
        regs->reg_0x0118_ict_lpf_out_rbb = (value >> 0) & 0x1f;
        return;
    }
    if (addr == 0x0119)
    {
        regs->reg_0x0119_osw_pga_rbb = (value >> 15) & 0x1;
        regs->reg_0x0119_ict_pga_out_rbb = (value >> 10) & 0x1f;
        regs->reg_0x0119_ict_pga_in_rbb = (value >> 5) & 0x1f;
        regs->reg_0x0119_g_pga_rbb = (value >> 0) & 0x1f;
        return;
    }
    if (addr == 0x011A)
    {
        regs->reg_0x011a_rcc_ctl_pga_rbb = (value >> 9) & 0x1f;
        regs->reg_0x011a_c_ctl_pga_rbb = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x011B)
    {
        regs->reg_0x011b_resrv_rbb = (value >> 0) & 0x7f;
        return;
    }
    if (addr == 0x011C)
    {
        regs->reg_0x011c_reset_n = (value >> 15) & 0x1;
        regs->reg_0x011c_spdup_vco = (value >> 14) & 0x1;
        regs->reg_0x011c_bypldo_vco = (value >> 13) & 0x1;
        regs->reg_0x011c_en_coarsepll = (value >> 12) & 0x1;
        regs->reg_0x011c_curlim_vco = (value >> 11) & 0x1;
        regs->reg_0x011c_en_div2_divprog = (value >> 10) & 0x1;
        regs->reg_0x011c_en_intonly_sdm = (value >> 9) & 0x1;
        regs->reg_0x011c_en_sdm_clk = (value >> 8) & 0x1;
        regs->reg_0x011c_pd_fbdiv = (value >> 7) & 0x1;
        regs->reg_0x011c_pd_loch_t2rbuf = (value >> 6) & 0x1;
        regs->reg_0x011c_pd_cp = (value >> 5) & 0x1;
        regs->reg_0x011c_pd_fdiv = (value >> 4) & 0x1;
        regs->reg_0x011c_pd_sdm = (value >> 3) & 0x1;
        regs->reg_0x011c_pd_vco_comp = (value >> 2) & 0x1;
        regs->reg_0x011c_pd_vco = (value >> 1) & 0x1;
        regs->reg_0x011c_en_g = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x011D)
    {
        regs->reg_0x011d_frac_sdm = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x011E)
    {
        regs->reg_0x011e_int_sdm = (value >> 4) & 0x3ff;
        regs->reg_0x011e_frac_sdm = (value >> 0) & 0xf;
        return;
    }
    if (addr == 0x011F)
    {
        regs->reg_0x011f_pw_div2_loch = (value >> 12) & 0x7;
        regs->reg_0x011f_pw_div4_loch = (value >> 9) & 0x7;
        regs->reg_0x011f_div_loch = (value >> 6) & 0x7;
        regs->reg_0x011f_tst_sx = (value >> 3) & 0x7;
        regs->reg_0x011f_sel_sdmclk = (value >> 2) & 0x1;
        regs->reg_0x011f_sx_dither_en = (value >> 1) & 0x1;
        regs->reg_0x011f_rev_sdmclk = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0120)
    {
        regs->reg_0x0120_vdiv_vco = (value >> 8) & 0xff;
        regs->reg_0x0120_ict_vco = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x0121)
    {
        regs->reg_0x0121_rsel_ldo_vco = (value >> 11) & 0x1f;
        regs->reg_0x0121_csw_vco = (value >> 3) & 0xff;
        regs->reg_0x0121_sel_vco = (value >> 1) & 0x3;
        regs->reg_0x0121_coarse_start = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0122)
    {
        regs->reg_0x0122_revph_pfd = (value >> 12) & 0x1;
        regs->reg_0x0122_ioffset_cp = (value >> 6) & 0x3f;
        regs->reg_0x0122_ipulse_cp = (value >> 0) & 0x3f;
        return;
    }
    if (addr == 0x0123)
    {
        regs->reg_0x0123_coarse_stepdone = (value >> 15) & 0x1;
        regs->reg_0x0123_coarsepll_compo = (value >> 14) & 0x1;
        regs->reg_0x0123_vco_cmpho = (value >> 13) & 0x1;
        regs->reg_0x0123_vco_cmplo = (value >> 12) & 0x1;
        regs->reg_0x0123_cp2_pll = (value >> 8) & 0xf;
        regs->reg_0x0123_cp3_pll = (value >> 4) & 0xf;
        regs->reg_0x0123_cz = (value >> 0) & 0xf;
        return;
    }
    if (addr == 0x0124)
    {
        regs->reg_0x0124_en_dir_sxx = (value >> 4) & 0x1;
        regs->reg_0x0124_en_dir_rbb = (value >> 3) & 0x1;
        regs->reg_0x0124_en_dir_rfe = (value >> 2) & 0x1;
        regs->reg_0x0124_en_dir_tbb = (value >> 1) & 0x1;
        regs->reg_0x0124_en_dir_trf = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0125)
    {
        regs->reg_0x0125_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0126)
    {
        regs->reg_0x0126_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0200)
    {
        regs->reg_0x0200_tsgfc = (value >> 9) & 0x1;
        regs->reg_0x0200_tsgfcw = (value >> 7) & 0x3;
        regs->reg_0x0200_tsgdcldq = (value >> 6) & 0x1;
        regs->reg_0x0200_tsgdcldi = (value >> 5) & 0x1;
        regs->reg_0x0200_tsgswapiq = (value >> 4) & 0x1;
        regs->reg_0x0200_tsgmode = (value >> 3) & 0x1;
        regs->reg_0x0200_insel = (value >> 2) & 0x1;
        regs->reg_0x0200_bstart = (value >> 1) & 0x1;
        regs->reg_0x0200_en = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0201)
    {
        regs->reg_0x0201_gcorrq = (value >> 0) & 0x7ff;
        return;
    }
    if (addr == 0x0202)
    {
        regs->reg_0x0202_gcorri = (value >> 0) & 0x7ff;
        return;
    }
    if (addr == 0x0203)
    {
        regs->reg_0x0203_hbi_ovr = (value >> 12) & 0x7;
        regs->reg_0x0203_iqcorr = (value >> 0) & 0xfff;
        return;
    }
    if (addr == 0x0204)
    {
        regs->reg_0x0204_dccorri = (value >> 8) & 0xff;
        regs->reg_0x0204_dccorrq = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x0205)
    {
        regs->reg_0x0205_gfir1_l = (value >> 8) & 0x7;
        regs->reg_0x0205_gfir1_n = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x0206)
    {
        regs->reg_0x0206_gfir2_l = (value >> 8) & 0x7;
        regs->reg_0x0206_gfir2_n = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x0207)
    {
        regs->reg_0x0207_gfir3_l = (value >> 8) & 0x7;
        regs->reg_0x0207_gfir3_n = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x0208)
    {
        regs->reg_0x0208_cmix_gain = (value >> 14) & 0x3;
        regs->reg_0x0208_cmix_sc = (value >> 13) & 0x1;
        regs->reg_0x0208_cmix_byp = (value >> 8) & 0x1;
        regs->reg_0x0208_isinc_byp = (value >> 7) & 0x1;
        regs->reg_0x0208_gfir3_byp = (value >> 6) & 0x1;
        regs->reg_0x0208_gfir2_byp = (value >> 5) & 0x1;
        regs->reg_0x0208_gfir1_byp = (value >> 4) & 0x1;
        regs->reg_0x0208_dc_byp = (value >> 3) & 0x1;
        regs->reg_0x0208_gc_byp = (value >> 1) & 0x1;
        regs->reg_0x0208_ph_byp = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0209)
    {
        regs->reg_0x0209_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x020a)
    {
        regs->reg_0x020a_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x020C)
    {
        regs->reg_0x020c_dc_reg = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0240)
    {
        regs->reg_0x0240_dthbit = (value >> 5) & 0xf;
        regs->reg_0x0240_sel = (value >> 1) & 0xf;
        regs->reg_0x0240_mode = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0241)
    {
        regs->reg_0x0241_pho = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0242)
    {
        regs->reg_0x0242_fcw0_hi = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0243)
    {
        regs->reg_0x0243_fcw0_lo = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0400)
    {
        regs->reg_0x0400_capture = (value >> 15) & 0x1;
        regs->reg_0x0400_capsel = (value >> 13) & 0x3;
        regs->reg_0x0400_tsgfc = (value >> 9) & 0x1;
        regs->reg_0x0400_tsgfcw = (value >> 7) & 0x3;
        regs->reg_0x0400_tsgdcldq = (value >> 6) & 0x1;
        regs->reg_0x0400_tsgdcldi = (value >> 5) & 0x1;
        regs->reg_0x0400_tsgswapiq = (value >> 4) & 0x1;
        regs->reg_0x0400_tsgmode = (value >> 3) & 0x1;
        regs->reg_0x0400_insel = (value >> 2) & 0x1;
        regs->reg_0x0400_bstart = (value >> 1) & 0x1;
        regs->reg_0x0400_en = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0401)
    {
        regs->reg_0x0401_gcorrq = (value >> 0) & 0x7ff;
        return;
    }
    if (addr == 0x0402)
    {
        regs->reg_0x0402_gcorri = (value >> 0) & 0x7ff;
        return;
    }
    if (addr == 0x0403)
    {
        regs->reg_0x0403_hbd_ovr = (value >> 12) & 0x7;
        regs->reg_0x0403_iqcorr = (value >> 0) & 0xfff;
        return;
    }
    if (addr == 0x0404)
    {
        regs->reg_0x0404_dccorr_avg = (value >> 0) & 0x7;
        return;
    }
    if (addr == 0x0405)
    {
        regs->reg_0x0405_gfir1_l = (value >> 8) & 0x7;
        regs->reg_0x0405_gfir1_n = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x0406)
    {
        regs->reg_0x0406_gfir2_l = (value >> 8) & 0x7;
        regs->reg_0x0406_gfir2_n = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x0407)
    {
        regs->reg_0x0407_gfir3_l = (value >> 8) & 0x7;
        regs->reg_0x0407_gfir3_n = (value >> 0) & 0xff;
        return;
    }
    if (addr == 0x0408)
    {
        regs->reg_0x0408_agc_k_lsb = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0409)
    {
        regs->reg_0x0409_agc_adesired = (value >> 4) & 0xfff;
        regs->reg_0x0409_agc_k_msb = (value >> 0) & 0x3;
        return;
    }
    if (addr == 0x040A)
    {
        regs->reg_0x040a_agc_mode = (value >> 12) & 0x3;
        regs->reg_0x040a_agc_avg = (value >> 0) & 0x7;
        return;
    }
    if (addr == 0x040B)
    {
        regs->reg_0x040b_dc_reg = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x040C)
    {
        regs->reg_0x040c_cmix_gain = (value >> 14) & 0x3;
        regs->reg_0x040c_cmix_sc = (value >> 13) & 0x1;
        regs->reg_0x040c_cmix_byp = (value >> 7) & 0x1;
        regs->reg_0x040c_agc_byp = (value >> 6) & 0x1;
        regs->reg_0x040c_gfir3_byp = (value >> 5) & 0x1;
        regs->reg_0x040c_gfir2_byp = (value >> 4) & 0x1;
        regs->reg_0x040c_gfir1_byp = (value >> 3) & 0x1;
        regs->reg_0x040c_dc_byp = (value >> 2) & 0x1;
        regs->reg_0x040c_gc_byp = (value >> 1) & 0x1;
        regs->reg_0x040c_ph_byp = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x040e)
    {
        regs->reg_0x040e_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0440)
    {
        regs->reg_0x0440_dthbit = (value >> 5) & 0xf;
        regs->reg_0x0440_sel = (value >> 1) & 0xf;
        regs->reg_0x0440_mode = (value >> 0) & 0x1;
        return;
    }
    if (addr == 0x0441)
    {
        regs->reg_0x0441_pho = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0442)
    {
        regs->reg_0x0442_fcw0_hi = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0443)
    {
        regs->reg_0x0443_fcw0_lo = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x05c0)
    {
        regs->reg_0x05c0_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x05c1)
    {
        regs->reg_0x05c1_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x05c2)
    {
        regs->reg_0x05c2_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x05c3)
    {
        regs->reg_0x05c3_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x05c4)
    {
        regs->reg_0x05c4_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x05c5)
    {
        regs->reg_0x05c5_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x05c6)
    {
        regs->reg_0x05c6_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x05c7)
    {
        regs->reg_0x05c7_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x05c8)
    {
        regs->reg_0x05c8_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x05c9)
    {
        regs->reg_0x05c9_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x05ca)
    {
        regs->reg_0x05ca_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x05cb)
    {
        regs->reg_0x05cb_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x05cc)
    {
        regs->reg_0x05cc_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0600)
    {
        regs->reg_0x0600_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0601)
    {
        regs->reg_0x0601_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0602)
    {
        regs->reg_0x0602_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0603)
    {
        regs->reg_0x0603_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0604)
    {
        regs->reg_0x0604_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0605)
    {
        regs->reg_0x0605_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0606)
    {
        regs->reg_0x0606_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0640)
    {
        regs->reg_0x0640_value = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0641)
    {
        regs->reg_0x0641_value = (value >> 0) & 0xffff;
        return;
    }
}

static inline int LMS7002M_regs_get(LMS7002M_regs_t *regs, const int addr)
{
    int value = 0;
    if (addr == 0x0020)
    {
        value |= (regs->reg_0x0020_lrst_tx_b & 0x1) << 15;
        value |= (regs->reg_0x0020_mrst_tx_b & 0x1) << 14;
        value |= (regs->reg_0x0020_lrst_tx_a & 0x1) << 13;
        value |= (regs->reg_0x0020_mrst_tx_a & 0x1) << 12;
        value |= (regs->reg_0x0020_lrst_rx_b & 0x1) << 11;
        value |= (regs->reg_0x0020_mrst_rx_b & 0x1) << 10;
        value |= (regs->reg_0x0020_lrst_rx_a & 0x1) << 9;
        value |= (regs->reg_0x0020_mrst_rx_a & 0x1) << 8;
        value |= (regs->reg_0x0020_srst_rxfifo & 0x1) << 7;
        value |= (regs->reg_0x0020_srst_txfifo & 0x1) << 6;
        value |= (regs->reg_0x0020_rxen_b & 0x1) << 5;
        value |= (regs->reg_0x0020_rxen_a & 0x1) << 4;
        value |= (regs->reg_0x0020_txen_b & 0x1) << 3;
        value |= (regs->reg_0x0020_txen_a & 0x1) << 2;
        value |= (regs->reg_0x0020_mac & 0x3) << 0;
    }
    if (addr == 0x0021)
    {
        value |= (regs->reg_0x0021_tx_clk_pe & 0x1) << 11;
        value |= (regs->reg_0x0021_rx_clk_pe & 0x1) << 10;
        value |= (regs->reg_0x0021_sda_pe & 0x1) << 9;
        value |= (regs->reg_0x0021_sda_ds & 0x1) << 8;
        value |= (regs->reg_0x0021_scl_pe & 0x1) << 7;
        value |= (regs->reg_0x0021_scl_ds & 0x1) << 6;
        value |= (regs->reg_0x0021_sdio_ds & 0x1) << 5;
        value |= (regs->reg_0x0021_sdio_pe & 0x1) << 4;
        value |= (regs->reg_0x0021_sdo_pe & 0x1) << 3;
        value |= (regs->reg_0x0021_sclk_pe & 0x1) << 2;
        value |= (regs->reg_0x0021_sen_pe & 0x1) << 1;
        value |= (regs->reg_0x0021_spimode & 0x1) << 0;
    }
    if (addr == 0x0022)
    {
        value |= (regs->reg_0x0022_diq2_ds & 0x1) << 11;
        value |= (regs->reg_0x0022_diq2_pe & 0x1) << 10;
        value |= (regs->reg_0x0022_iq_sel_en_2_pe & 0x1) << 9;
        value |= (regs->reg_0x0022_txnrx2_pe & 0x1) << 8;
        value |= (regs->reg_0x0022_fclk2_pe & 0x1) << 7;
        value |= (regs->reg_0x0022_mclk2_pe & 0x1) << 6;
        value |= (regs->reg_0x0022_diq1_ds & 0x1) << 5;
        value |= (regs->reg_0x0022_diq1_pe & 0x1) << 4;
        value |= (regs->reg_0x0022_iq_sel_en_1_pe & 0x1) << 3;
        value |= (regs->reg_0x0022_txnrx1_pe & 0x1) << 2;
        value |= (regs->reg_0x0022_fclk1_pe & 0x1) << 1;
        value |= (regs->reg_0x0022_mclk1_pe & 0x1) << 0;
    }
    if (addr == 0x0023)
    {
        value |= (regs->reg_0x0023_diqdirctr2 & 0x1) << 15;
        value |= (regs->reg_0x0023_diqdir2 & 0x1) << 14;
        value |= (regs->reg_0x0023_diqdirctr1 & 0x1) << 13;
        value |= (regs->reg_0x0023_diqdir1 & 0x1) << 12;
        value |= (regs->reg_0x0023_enabledirctr2 & 0x1) << 11;
        value |= (regs->reg_0x0023_enabledir2 & 0x1) << 10;
        value |= (regs->reg_0x0023_enabledirctr1 & 0x1) << 9;
        value |= (regs->reg_0x0023_enabledir1 & 0x1) << 8;
        value |= (regs->reg_0x0023_mod_en & 0x1) << 6;
        value |= (regs->reg_0x0023_lml2_fidm & 0x1) << 5;
        value |= (regs->reg_0x0023_lml2_rxntxiq & 0x1) << 4;
        value |= (regs->reg_0x0023_lml2_mode & 0x1) << 3;
        value |= (regs->reg_0x0023_lml1_fidm & 0x1) << 2;
        value |= (regs->reg_0x0023_lml1_rxntxiq & 0x1) << 1;
        value |= (regs->reg_0x0023_lml1_mode & 0x1) << 0;
    }
    if (addr == 0x0024)
    {
        value |= (regs->reg_0x0024_lml1_s3s & 0x3) << 14;
        value |= (regs->reg_0x0024_lml1_s2s & 0x3) << 12;
        value |= (regs->reg_0x0024_lml1_s1s & 0x3) << 10;
        value |= (regs->reg_0x0024_lml1_s0s & 0x3) << 8;
        value |= (regs->reg_0x0024_lml1_bqp & 0x3) << 6;
        value |= (regs->reg_0x0024_lml1_bip & 0x3) << 4;
        value |= (regs->reg_0x0024_lml1_aqp & 0x3) << 2;
        value |= (regs->reg_0x0024_lml1_aip & 0x3) << 0;
    }
    if (addr == 0x0025)
    {
        value |= (regs->reg_0x0025_value & 0xffff) << 0;
    }
    if (addr == 0x0026)
    {
        value |= (regs->reg_0x0026_value & 0xffff) << 0;
    }
    if (addr == 0x0027)
    {
        value |= (regs->reg_0x0027_lml2_s3s & 0x3) << 14;
        value |= (regs->reg_0x0027_lml2_s2s & 0x3) << 12;
        value |= (regs->reg_0x0027_lml2_s1s & 0x3) << 10;
        value |= (regs->reg_0x0027_lml2_s0s & 0x3) << 8;
        value |= (regs->reg_0x0027_lml2_bqp & 0x3) << 6;
        value |= (regs->reg_0x0027_lml2_bip & 0x3) << 4;
        value |= (regs->reg_0x0027_lml2_aqp & 0x3) << 2;
        value |= (regs->reg_0x0027_lml2_aip & 0x3) << 0;
    }
    if (addr == 0x0028)
    {
        value |= (regs->reg_0x0028_value & 0xffff) << 0;
    }
    if (addr == 0x0029)
    {
        value |= (regs->reg_0x0029_value & 0xffff) << 0;
    }
    if (addr == 0x002A)
    {
        value |= (regs->reg_0x002a_fclk2_dly & 0x3) << 14;
        value |= (regs->reg_0x002a_fclk1_dly & 0x3) << 12;
        value |= (regs->reg_0x002a_rx_mux & 0x3) << 10;
        value |= (regs->reg_0x002a_tx_mux & 0x3) << 8;
        value |= (regs->reg_0x002a_txrdclk_mux & 0x3) << 6;
        value |= (regs->reg_0x002a_txwrclk_mux & 0x3) << 4;
        value |= (regs->reg_0x002a_rxrdclk_mux & 0x3) << 2;
        value |= (regs->reg_0x002a_rxwrclk_mux & 0x3) << 0;
    }
    if (addr == 0x002B)
    {
        value |= (regs->reg_0x002b_fclk2_inv & 0x1) << 15;
        value |= (regs->reg_0x002b_fclk1_inv & 0x1) << 14;
        value |= (regs->reg_0x002b_mclk2src & 0x3) << 4;
        value |= (regs->reg_0x002b_mclk1src & 0x3) << 2;
        value |= (regs->reg_0x002b_txdiven & 0x1) << 1;
        value |= (regs->reg_0x002b_rxdiven & 0x1) << 0;
    }
    if (addr == 0x002C)
    {
        value |= (regs->reg_0x002c_txtspclk_div & 0xff) << 8;
        value |= (regs->reg_0x002c_rxtspclk_div & 0xff) << 0;
    }
    if (addr == 0x002E)
    {
        value |= (regs->reg_0x002e_mimo_siso & 0x1) << 15;
    }
    if (addr == 0x002F)
    {
        value |= (regs->reg_0x002f_ver & 0x1f) << 11;
        value |= (regs->reg_0x002f_rev & 0x1f) << 6;
        value |= (regs->reg_0x002f_mask & 0x3f) << 0;
    }
    if (addr == 0x0081)
    {
        value |= (regs->reg_0x0081_en_dir_ldo & 0x1) << 3;
        value |= (regs->reg_0x0081_en_dir_cgen & 0x1) << 2;
        value |= (regs->reg_0x0081_en_dir_xbuf & 0x1) << 1;
        value |= (regs->reg_0x0081_en_dir_afe & 0x1) << 0;
    }
    if (addr == 0x0082)
    {
        value |= (regs->reg_0x0082_isel_dac_afe & 0x7) << 13;
        value |= (regs->reg_0x0082_mode_interleave_afe & 0x1) << 12;
        value |= (regs->reg_0x0082_mux_afe_1 & 0x3) << 10;
        value |= (regs->reg_0x0082_mux_afe_2 & 0x3) << 8;
        value |= (regs->reg_0x0082_pd_afe & 0x1) << 5;
        value |= (regs->reg_0x0082_pd_rx_afe1 & 0x1) << 4;
        value |= (regs->reg_0x0082_pd_rx_afe2 & 0x1) << 3;
        value |= (regs->reg_0x0082_pd_tx_afe1 & 0x1) << 2;
        value |= (regs->reg_0x0082_pd_tx_afe2 & 0x1) << 1;
        value |= (regs->reg_0x0082_en_g_afe & 0x1) << 0;
    }
    if (addr == 0x0084)
    {
        value |= (regs->reg_0x0084_mux_bias_out & 0x3) << 11;
        value |= (regs->reg_0x0084_rp_calib_bias & 0x1f) << 6;
        value |= (regs->reg_0x0084_pd_frp_bias & 0x1) << 4;
        value |= (regs->reg_0x0084_pd_f_bias & 0x1) << 3;
        value |= (regs->reg_0x0084_pd_ptrp_bias & 0x1) << 2;
        value |= (regs->reg_0x0084_pd_pt_bias & 0x1) << 1;
        value |= (regs->reg_0x0084_pd_bias_master & 0x1) << 0;
    }
    if (addr == 0x0085)
    {
        value |= (regs->reg_0x0085_slfb_xbuf_rx & 0x1) << 8;
        value |= (regs->reg_0x0085_slfb_xbuf_tx & 0x1) << 7;
        value |= (regs->reg_0x0085_byp_xbuf_rx & 0x1) << 6;
        value |= (regs->reg_0x0085_byp_xbuf_tx & 0x1) << 5;
        value |= (regs->reg_0x0085_en_out2_xbuf_tx & 0x1) << 4;
        value |= (regs->reg_0x0085_en_tbufin_xbuf_rx & 0x1) << 3;
        value |= (regs->reg_0x0085_pd_xbuf_rx & 0x1) << 2;
        value |= (regs->reg_0x0085_pd_xbuf_tx & 0x1) << 1;
        value |= (regs->reg_0x0085_en_g_xbuf & 0x1) << 0;
    }
    if (addr == 0x0086)
    {
        value |= (regs->reg_0x0086_spdup_vco_cgen & 0x1) << 15;
        value |= (regs->reg_0x0086_reset_n_cgen & 0x1) << 14;
        value |= (regs->reg_0x0086_en_adcclkh_clkgn & 0x1) << 11;
        value |= (regs->reg_0x0086_en_coarse_cklgen & 0x1) << 10;
        value |= (regs->reg_0x0086_en_intonly_sdm_cgen & 0x1) << 9;
        value |= (regs->reg_0x0086_en_sdm_clk_cgen & 0x1) << 8;
        value |= (regs->reg_0x0086_pd_cp_cgen & 0x1) << 6;
        value |= (regs->reg_0x0086_pd_fdiv_fb_cgen & 0x1) << 5;
        value |= (regs->reg_0x0086_pd_fdiv_o_cgen & 0x1) << 4;
        value |= (regs->reg_0x0086_pd_sdm_cgen & 0x1) << 3;
        value |= (regs->reg_0x0086_pd_vco_cgen & 0x1) << 2;
        value |= (regs->reg_0x0086_pd_vco_comp_cgen & 0x1) << 1;
        value |= (regs->reg_0x0086_en_g_cgen & 0x1) << 0;
    }
    if (addr == 0x0087)
    {
        value |= (regs->reg_0x0087_frac_sdm_cgen & 0xffff) << 0;
    }
    if (addr == 0x0088)
    {
        value |= (regs->reg_0x0088_int_sdm_cgen & 0x3ff) << 4;
        value |= (regs->reg_0x0088_frac_sdm_cgen & 0xf) << 0;
    }
    if (addr == 0x0089)
    {
        value |= (regs->reg_0x0089_rev_sdmclk_cgen & 0x1) << 15;
        value |= (regs->reg_0x0089_sel_sdmclk_cgen & 0x1) << 14;
        value |= (regs->reg_0x0089_sx_dither_en_cgen & 0x1) << 13;
        value |= (regs->reg_0x0089_clkh_ov_clkl_cgen & 0x3) << 11;
        value |= (regs->reg_0x0089_div_outch_cgen & 0xff) << 3;
        value |= (regs->reg_0x0089_tst_cgen & 0x7) << 0;
    }
    if (addr == 0x008A)
    {
        value |= (regs->reg_0x008a_rev_clkdac_cgen & 0x1) << 14;
        value |= (regs->reg_0x008a_rev_clkadc_cgen & 0x1) << 13;
        value |= (regs->reg_0x008a_revph_pfd_cgen & 0x1) << 12;
        value |= (regs->reg_0x008a_ioffset_cp_cgen & 0x3f) << 6;
        value |= (regs->reg_0x008a_ipulse_cp_cgen & 0x3f) << 0;
    }
    if (addr == 0x008B)
    {
        value |= (regs->reg_0x008b_ict_vco_cgen & 0x1f) << 9;
        value |= (regs->reg_0x008b_csw_vco_cgen & 0xff) << 1;
        value |= (regs->reg_0x008b_coarse_start_cgen & 0x1) << 0;
    }
    if (addr == 0x008C)
    {
        value |= (regs->reg_0x008c_coarse_stepdone_cgen & 0x1) << 15;
        value |= (regs->reg_0x008c_coarsepll_compo_cgen & 0x1) << 14;
        value |= (regs->reg_0x008c_vco_cmpho_cgen & 0x1) << 13;
        value |= (regs->reg_0x008c_vco_cmplo_cgen & 0x1) << 12;
        value |= (regs->reg_0x008c_cp2_cgen & 0xf) << 8;
        value |= (regs->reg_0x008c_cp3_cgen & 0xf) << 4;
        value |= (regs->reg_0x008c_cz_cgen & 0xf) << 0;
    }
    if (addr == 0x008D)
    {
        value |= (regs->reg_0x008d_resrv_cgn & 0x7) << 0;
    }
    if (addr == 0x0092)
    {
        value |= (regs->reg_0x0092_en_ldo_dig & 0x1) << 15;
        value |= (regs->reg_0x0092_en_ldo_diggn & 0x1) << 14;
        value |= (regs->reg_0x0092_en_ldo_digsxr & 0x1) << 13;
        value |= (regs->reg_0x0092_en_ldo_digsxt & 0x1) << 12;
        value |= (regs->reg_0x0092_en_ldo_divgn & 0x1) << 11;
        value |= (regs->reg_0x0092_en_ldo_divsxr & 0x1) << 10;
        value |= (regs->reg_0x0092_en_ldo_divsxt & 0x1) << 9;
        value |= (regs->reg_0x0092_en_ldo_lna12 & 0x1) << 8;
        value |= (regs->reg_0x0092_en_ldo_lna14 & 0x1) << 7;
        value |= (regs->reg_0x0092_en_ldo_mxrfe & 0x1) << 6;
        value |= (regs->reg_0x0092_en_ldo_rbb & 0x1) << 5;
        value |= (regs->reg_0x0092_en_ldo_rxbuf & 0x1) << 4;
        value |= (regs->reg_0x0092_en_ldo_tbb & 0x1) << 3;
        value |= (regs->reg_0x0092_en_ldo_tia12 & 0x1) << 2;
        value |= (regs->reg_0x0092_en_ldo_tia14 & 0x1) << 1;
        value |= (regs->reg_0x0092_en_g_ldo & 0x1) << 0;
    }
    if (addr == 0x0093)
    {
        value |= (regs->reg_0x0093_en_loadimp_ldo_tlob & 0x1) << 15;
        value |= (regs->reg_0x0093_en_loadimp_ldo_tpad & 0x1) << 14;
        value |= (regs->reg_0x0093_en_loadimp_ldo_txbuf & 0x1) << 13;
        value |= (regs->reg_0x0093_en_loadimp_ldo_vcogn & 0x1) << 12;
        value |= (regs->reg_0x0093_en_loadimp_ldo_vcosxr & 0x1) << 11;
        value |= (regs->reg_0x0093_en_loadimp_ldo_vcosxt & 0x1) << 10;
        value |= (regs->reg_0x0093_en_ldo_afe & 0x1) << 9;
        value |= (regs->reg_0x0093_en_ldo_cpgn & 0x1) << 8;
        value |= (regs->reg_0x0093_en_ldo_cpsxr & 0x1) << 7;
        value |= (regs->reg_0x0093_en_ldo_tlob & 0x1) << 6;
        value |= (regs->reg_0x0093_en_ldo_tpad & 0x1) << 5;
        value |= (regs->reg_0x0093_en_ldo_txbuf & 0x1) << 4;
        value |= (regs->reg_0x0093_en_ldo_vcogn & 0x1) << 3;
        value |= (regs->reg_0x0093_en_ldo_vcosxr & 0x1) << 2;
        value |= (regs->reg_0x0093_en_ldo_vcosxt & 0x1) << 1;
        value |= (regs->reg_0x0093_en_ldo_cpsxt & 0x1) << 0;
    }
    if (addr == 0x0094)
    {
        value |= (regs->reg_0x0094_en_loadimp_ldo_cpsxt & 0x1) << 15;
        value |= (regs->reg_0x0094_en_loadimp_ldo_dig & 0x1) << 14;
        value |= (regs->reg_0x0094_en_loadimp_ldo_diggn & 0x1) << 13;
        value |= (regs->reg_0x0094_en_loadimp_ldo_digsxr & 0x1) << 12;
        value |= (regs->reg_0x0094_en_loadimp_ldo_digsxt & 0x1) << 11;
        value |= (regs->reg_0x0094_en_loadimp_ldo_divgn & 0x1) << 10;
        value |= (regs->reg_0x0094_en_loadimp_ldo_divsxr & 0x1) << 9;
        value |= (regs->reg_0x0094_en_loadimp_ldo_divsxt & 0x1) << 8;
        value |= (regs->reg_0x0094_en_loadimp_ldo_lna12 & 0x1) << 7;
        value |= (regs->reg_0x0094_en_loadimp_ldo_lna14 & 0x1) << 6;
        value |= (regs->reg_0x0094_en_loadimp_ldo_mxrfe & 0x1) << 5;
        value |= (regs->reg_0x0094_en_loadimp_ldo_rbb & 0x1) << 4;
        value |= (regs->reg_0x0094_en_loadimp_ldo_rxbuf & 0x1) << 3;
        value |= (regs->reg_0x0094_en_loadimp_ldo_tbb & 0x1) << 2;
        value |= (regs->reg_0x0094_en_loadimp_ldo_tia12 & 0x1) << 1;
        value |= (regs->reg_0x0094_en_loadimp_ldo_tia14 & 0x1) << 0;
    }
    if (addr == 0x0095)
    {
        value |= (regs->reg_0x0095_byp_ldo_tbb & 0x1) << 15;
        value |= (regs->reg_0x0095_byp_ldo_tia12 & 0x1) << 14;
        value |= (regs->reg_0x0095_byp_ldo_tia14 & 0x1) << 13;
        value |= (regs->reg_0x0095_byp_ldo_tlob & 0x1) << 12;
        value |= (regs->reg_0x0095_byp_ldo_tpad & 0x1) << 11;
        value |= (regs->reg_0x0095_byp_ldo_txbuf & 0x1) << 10;
        value |= (regs->reg_0x0095_byp_ldo_vcogn & 0x1) << 9;
        value |= (regs->reg_0x0095_byp_ldo_vcosxr & 0x1) << 8;
        value |= (regs->reg_0x0095_byp_ldo_vcosxt & 0x1) << 7;
        value |= (regs->reg_0x0095_en_loadimp_ldo_afe & 0x1) << 2;
        value |= (regs->reg_0x0095_en_loadimp_ldo_cpgn & 0x1) << 1;
        value |= (regs->reg_0x0095_en_loadimp_ldo_cpsxr & 0x1) << 0;
    }
    if (addr == 0x0096)
    {
        value |= (regs->reg_0x0096_byp_ldo_afe & 0x1) << 15;
        value |= (regs->reg_0x0096_byp_ldo_cpgn & 0x1) << 14;
        value |= (regs->reg_0x0096_byp_ldo_cpsxr & 0x1) << 13;
        value |= (regs->reg_0x0096_byp_ldo_cpsxt & 0x1) << 12;
        value |= (regs->reg_0x0096_byp_ldo_dig & 0x1) << 11;
        value |= (regs->reg_0x0096_byp_ldo_diggn & 0x1) << 10;
        value |= (regs->reg_0x0096_byp_ldo_digsxr & 0x1) << 9;
        value |= (regs->reg_0x0096_byp_ldo_digsxt & 0x1) << 8;
        value |= (regs->reg_0x0096_byp_ldo_divgn & 0x1) << 7;
        value |= (regs->reg_0x0096_byp_ldo_divsxr & 0x1) << 6;
        value |= (regs->reg_0x0096_byp_ldo_divsxt & 0x1) << 5;
        value |= (regs->reg_0x0096_byp_ldo_lna12 & 0x1) << 4;
        value |= (regs->reg_0x0096_byp_ldo_lna14 & 0x1) << 3;
        value |= (regs->reg_0x0096_byp_ldo_mxrfe & 0x1) << 2;
        value |= (regs->reg_0x0096_byp_ldo_rbb & 0x1) << 1;
        value |= (regs->reg_0x0096_byp_ldo_rxbuf & 0x1) << 0;
    }
    if (addr == 0x0097)
    {
        value |= (regs->reg_0x0097_spdup_ldo_divsxr & 0x1) << 15;
        value |= (regs->reg_0x0097_spdup_ldo_divsxt & 0x1) << 14;
        value |= (regs->reg_0x0097_spdup_ldo_lna12 & 0x1) << 13;
        value |= (regs->reg_0x0097_spdup_ldo_lna14 & 0x1) << 12;
        value |= (regs->reg_0x0097_spdup_ldo_mxrfe & 0x1) << 11;
        value |= (regs->reg_0x0097_spdup_ldo_rbb & 0x1) << 10;
        value |= (regs->reg_0x0097_spdup_ldo_rxbuf & 0x1) << 9;
        value |= (regs->reg_0x0097_spdup_ldo_tbb & 0x1) << 8;
        value |= (regs->reg_0x0097_spdup_ldo_tia12 & 0x1) << 7;
        value |= (regs->reg_0x0097_spdup_ldo_tia14 & 0x1) << 6;
        value |= (regs->reg_0x0097_spdup_ldo_tlob & 0x1) << 5;
        value |= (regs->reg_0x0097_spdup_ldo_tpad & 0x1) << 4;
        value |= (regs->reg_0x0097_spdup_ldo_txbuf & 0x1) << 3;
        value |= (regs->reg_0x0097_spdup_ldo_vcogn & 0x1) << 2;
        value |= (regs->reg_0x0097_spdup_ldo_vcosxr & 0x1) << 1;
        value |= (regs->reg_0x0097_spdup_ldo_vcosxt & 0x1) << 0;
    }
    if (addr == 0x0098)
    {
        value |= (regs->reg_0x0098_spdup_ldo_afe & 0x1) << 8;
        value |= (regs->reg_0x0098_spdup_ldo_cpgn & 0x1) << 7;
        value |= (regs->reg_0x0098_spdup_ldo_cpsxr & 0x1) << 6;
        value |= (regs->reg_0x0098_spdup_ldo_cpsxt & 0x1) << 5;
        value |= (regs->reg_0x0098_spdup_ldo_dig & 0x1) << 4;
        value |= (regs->reg_0x0098_spdup_ldo_diggn & 0x1) << 3;
        value |= (regs->reg_0x0098_spdup_ldo_digsxr & 0x1) << 2;
        value |= (regs->reg_0x0098_spdup_ldo_digsxt & 0x1) << 1;
        value |= (regs->reg_0x0098_spdup_ldo_divgn & 0x1) << 0;
    }
    if (addr == 0x0099)
    {
        value |= (regs->reg_0x0099_rdiv_vcosxr & 0xff) << 8;
        value |= (regs->reg_0x0099_rdiv_vcosxt & 0xff) << 0;
    }
    if (addr == 0x009A)
    {
        value |= (regs->reg_0x009a_rdiv_txbuf & 0xff) << 8;
        value |= (regs->reg_0x009a_rdiv_vcogn & 0xff) << 0;
    }
    if (addr == 0x009B)
    {
        value |= (regs->reg_0x009b_rdiv_tlob & 0xff) << 8;
        value |= (regs->reg_0x009b_rdiv_tpad & 0xff) << 0;
    }
    if (addr == 0x009C)
    {
        value |= (regs->reg_0x009c_rdiv_tia12 & 0xff) << 8;
        value |= (regs->reg_0x009c_rdiv_tia14 & 0xff) << 0;
    }
    if (addr == 0x009D)
    {
        value |= (regs->reg_0x009d_rdiv_rxbuf & 0xff) << 8;
        value |= (regs->reg_0x009d_rdiv_tbb & 0xff) << 0;
    }
    if (addr == 0x009E)
    {
        value |= (regs->reg_0x009e_rdiv_mxrfe & 0xff) << 8;
        value |= (regs->reg_0x009e_rdiv_rbb & 0xff) << 0;
    }
    if (addr == 0x009F)
    {
        value |= (regs->reg_0x009f_rdiv_lna12 & 0xff) << 8;
        value |= (regs->reg_0x009f_rdiv_lna14 & 0xff) << 0;
    }
    if (addr == 0x00A0)
    {
        value |= (regs->reg_0x00a0_rdiv_divsxr & 0xff) << 8;
        value |= (regs->reg_0x00a0_rdiv_divsxt & 0xff) << 0;
    }
    if (addr == 0x00A1)
    {
        value |= (regs->reg_0x00a1_rdiv_digsxt & 0xff) << 8;
        value |= (regs->reg_0x00a1_rdiv_divgn & 0xff) << 0;
    }
    if (addr == 0x00A2)
    {
        value |= (regs->reg_0x00a2_rdiv_diggn & 0xff) << 8;
        value |= (regs->reg_0x00a2_rdiv_digsxr & 0xff) << 0;
    }
    if (addr == 0x00A3)
    {
        value |= (regs->reg_0x00a3_rdiv_cpsxt & 0xff) << 8;
        value |= (regs->reg_0x00a3_rdiv_dig & 0xff) << 0;
    }
    if (addr == 0x00A4)
    {
        value |= (regs->reg_0x00a4_rdiv_cpgn & 0xff) << 8;
        value |= (regs->reg_0x00a4_rdiv_cpsxr & 0xff) << 0;
    }
    if (addr == 0x00A5)
    {
        value |= (regs->reg_0x00a5_rdiv_spibuf & 0xff) << 8;
        value |= (regs->reg_0x00a5_rdiv_afe & 0xff) << 0;
    }
    if (addr == 0x00A6)
    {
        value |= (regs->reg_0x00a6_spdup_ldo_spibuf & 0x1) << 12;
        value |= (regs->reg_0x00a6_spdup_ldo_digip2 & 0x1) << 11;
        value |= (regs->reg_0x00a6_spdup_ldo_digip1 & 0x1) << 10;
        value |= (regs->reg_0x00a6_byp_ldo_spibuf & 0x1) << 9;
        value |= (regs->reg_0x00a6_byp_ldo_digip2 & 0x1) << 8;
        value |= (regs->reg_0x00a6_byp_ldo_digip1 & 0x1) << 7;
        value |= (regs->reg_0x00a6_en_loadimp_ldo_spibuf & 0x1) << 6;
        value |= (regs->reg_0x00a6_en_loadimp_ldo_digip2 & 0x1) << 5;
        value |= (regs->reg_0x00a6_en_loadimp_ldo_digip1 & 0x1) << 4;
        value |= (regs->reg_0x00a6_pd_ldo_spibuf & 0x1) << 3;
        value |= (regs->reg_0x00a6_pd_ldo_digip2 & 0x1) << 2;
        value |= (regs->reg_0x00a6_pd_ldo_digip1 & 0x1) << 1;
        value |= (regs->reg_0x00a6_en_g_ldop & 0x1) << 0;
    }
    if (addr == 0x00A7)
    {
        value |= (regs->reg_0x00a7_rdiv_digip2 & 0xff) << 8;
        value |= (regs->reg_0x00a7_rdiv_digip1 & 0xff) << 0;
    }
    if (addr == 0x00a8)
    {
        value |= (regs->reg_0x00a8_value & 0xffff) << 0;
    }
    if (addr == 0x00aa)
    {
        value |= (regs->reg_0x00aa_value & 0xffff) << 0;
    }
    if (addr == 0x00ab)
    {
        value |= (regs->reg_0x00ab_value & 0xffff) << 0;
    }
    if (addr == 0x00ad)
    {
        value |= (regs->reg_0x00ad_value & 0xffff) << 0;
    }
    if (addr == 0x00ae)
    {
        value |= (regs->reg_0x00ae_value & 0xffff) << 0;
    }
    if (addr == 0x0100)
    {
        value |= (regs->reg_0x0100_en_lowbwlomx_tmx_trf & 0x1) << 15;
        value |= (regs->reg_0x0100_en_nexttx_trf & 0x1) << 14;
        value |= (regs->reg_0x0100_en_amphf_pdet_trf & 0x3) << 12;
        value |= (regs->reg_0x0100_loadr_pdet_trf & 0x3) << 10;
        value |= (regs->reg_0x0100_pd_pdet_trf & 0x1) << 3;
        value |= (regs->reg_0x0100_pd_tlobuf_trf & 0x1) << 2;
        value |= (regs->reg_0x0100_pd_txpad_trf & 0x1) << 1;
        value |= (regs->reg_0x0100_en_g_trf & 0x1) << 0;
    }
    if (addr == 0x0101)
    {
        value |= (regs->reg_0x0101_f_txpad_trf & 0x7) << 13;
        value |= (regs->reg_0x0101_l_loopb_txpad_trf & 0x3) << 11;
        value |= (regs->reg_0x0101_loss_lin_txpad_trf & 0x1f) << 6;
        value |= (regs->reg_0x0101_loss_main_txpad_trf & 0x1f) << 1;
        value |= (regs->reg_0x0101_en_loopb_txpad_trf & 0x1) << 0;
    }
    if (addr == 0x0102)
    {
        value |= (regs->reg_0x0102_gcas_gndref_txpad_trf & 0x1) << 15;
        value |= (regs->reg_0x0102_ict_lin_txpad_trf & 0x1f) << 10;
        value |= (regs->reg_0x0102_ict_main_txpad_trf & 0x1f) << 5;
        value |= (regs->reg_0x0102_vgcas_txpad_trf & 0x1f) << 0;
    }
    if (addr == 0x0103)
    {
        value |= (regs->reg_0x0103_sel_band1_trf & 0x1) << 11;
        value |= (regs->reg_0x0103_sel_band2_trf & 0x1) << 10;
        value |= (regs->reg_0x0103_lobiasn_txm_trf & 0x1f) << 5;
        value |= (regs->reg_0x0103_lobiasp_txx_trf & 0x1f) << 0;
    }
    if (addr == 0x0104)
    {
        value |= (regs->reg_0x0104_cdc_i_trf & 0xf) << 4;
        value |= (regs->reg_0x0104_cdc_q_trf & 0xf) << 0;
    }
    if (addr == 0x0105)
    {
        value |= (regs->reg_0x0105_statpulse_tbb & 0x1) << 15;
        value |= (regs->reg_0x0105_loopb_tbb & 0x7) << 12;
        value |= (regs->reg_0x0105_pd_lpfh_tbb & 0x1) << 4;
        value |= (regs->reg_0x0105_pd_lpfiamp_tbb & 0x1) << 3;
        value |= (regs->reg_0x0105_pd_lpflad_tbb & 0x1) << 2;
        value |= (regs->reg_0x0105_pd_lpfs5_tbb & 0x1) << 1;
        value |= (regs->reg_0x0105_en_g_tbb & 0x1) << 0;
    }
    if (addr == 0x0106)
    {
        value |= (regs->reg_0x0106_ict_lpfs5_f_tbb & 0x1f) << 10;
        value |= (regs->reg_0x0106_ict_lpfs5_pt_tbb & 0x1f) << 5;
        value |= (regs->reg_0x0106_ict_lpf_h_pt_tbb & 0x1f) << 0;
    }
    if (addr == 0x0107)
    {
        value |= (regs->reg_0x0107_ict_lpfh_f_tbb & 0x1f) << 10;
        value |= (regs->reg_0x0107_ict_lpflad_f_tbb & 0x1f) << 5;
        value |= (regs->reg_0x0107_ict_lpflad_pt_tbb & 0x1f) << 0;
    }
    if (addr == 0x0108)
    {
        value |= (regs->reg_0x0108_cg_iamp_tbb & 0x3f) << 10;
        value |= (regs->reg_0x0108_ict_iamp_frp_tbb & 0x1f) << 5;
        value |= (regs->reg_0x0108_ict_iamp_gg_frp_tbb & 0x1f) << 0;
    }
    if (addr == 0x0109)
    {
        value |= (regs->reg_0x0109_rcal_lpfh_tbb & 0xff) << 8;
        value |= (regs->reg_0x0109_rcal_lpflad_tbb & 0xff) << 0;
    }
    if (addr == 0x010A)
    {
        value |= (regs->reg_0x010a_tstin_tbb & 0x3) << 14;
        value |= (regs->reg_0x010a_bypladder_tbb & 0x1) << 13;
        value |= (regs->reg_0x010a_ccal_lpflad_tbb & 0x1f) << 8;
        value |= (regs->reg_0x010a_rcal_lpfs5_tbb & 0xff) << 0;
    }
    if (addr == 0x010b)
    {
        value |= (regs->reg_0x010b_value & 0xffff) << 0;
    }
    if (addr == 0x010C)
    {
        value |= (regs->reg_0x010c_cdc_i_rfe & 0xf) << 12;
        value |= (regs->reg_0x010c_cdc_q_rfe & 0xf) << 8;
        value |= (regs->reg_0x010c_pd_lna_rfe & 0x1) << 7;
        value |= (regs->reg_0x010c_pd_rloopb_1_rfe & 0x1) << 6;
        value |= (regs->reg_0x010c_pd_rloopb_2_rfe & 0x1) << 5;
        value |= (regs->reg_0x010c_pd_mxlobuf_rfe & 0x1) << 4;
        value |= (regs->reg_0x010c_pd_qgen_rfe & 0x1) << 3;
        value |= (regs->reg_0x010c_pd_rssi_rfe & 0x1) << 2;
        value |= (regs->reg_0x010c_pd_tia_rfe & 0x1) << 1;
        value |= (regs->reg_0x010c_en_g_rfe & 0x1) << 0;
    }
    if (addr == 0x010D)
    {
        value |= (regs->reg_0x010d_sel_path_rfe & 0x3) << 7;
        value |= (regs->reg_0x010d_en_dcoff_rxfe_rfe & 0x1) << 6;
        value |= (regs->reg_0x010d_en_inshsw_lb1_rfe & 0x1) << 4;
        value |= (regs->reg_0x010d_en_inshsw_lb2_rfe & 0x1) << 3;
        value |= (regs->reg_0x010d_en_inshsw_l_rfe & 0x1) << 2;
        value |= (regs->reg_0x010d_en_inshsw_w_rfe & 0x1) << 1;
        value |= (regs->reg_0x010d_en_nextrx_rfe & 0x1) << 0;
    }
    if (addr == 0x010E)
    {
        value |= (regs->reg_0x010e_dcoffi_rfe & 0x7f) << 7;
        value |= (regs->reg_0x010e_dcoffq_rfe & 0x7f) << 0;
    }
    if (addr == 0x010F)
    {
        value |= (regs->reg_0x010f_ict_loopb_rfe & 0x1f) << 10;
        value |= (regs->reg_0x010f_ict_tiamain_rfe & 0x1f) << 5;
        value |= (regs->reg_0x010f_ict_tiaout_rfe & 0x1f) << 0;
    }
    if (addr == 0x0110)
    {
        value |= (regs->reg_0x0110_ict_lnacmo_rfe & 0x1f) << 10;
        value |= (regs->reg_0x0110_ict_lna_rfe & 0x1f) << 5;
        value |= (regs->reg_0x0110_ict_lodc_rfe & 0x1f) << 0;
    }
    if (addr == 0x0111)
    {
        value |= (regs->reg_0x0111_cap_rxmxo_rfe & 0x1f) << 5;
        value |= (regs->reg_0x0111_cgsin_lna_rfe & 0x1f) << 0;
    }
    if (addr == 0x0112)
    {
        value |= (regs->reg_0x0112_ccomp_tia_rfe & 0xf) << 12;
        value |= (regs->reg_0x0112_cfb_tia_rfe & 0xfff) << 0;
    }
    if (addr == 0x0113)
    {
        value |= (regs->reg_0x0113_g_lna_rfe & 0xf) << 6;
        value |= (regs->reg_0x0113_g_rxloopb_rfe & 0xf) << 2;
        value |= (regs->reg_0x0113_g_tia_rfe & 0x3) << 0;
    }
    if (addr == 0x0114)
    {
        value |= (regs->reg_0x0114_rcomp_tia_rfe & 0xf) << 5;
        value |= (regs->reg_0x0114_rfb_tia_rfe & 0x1f) << 0;
    }
    if (addr == 0x0115)
    {
        value |= (regs->reg_0x0115_en_lb_lpfh_rbb & 0x1) << 15;
        value |= (regs->reg_0x0115_en_lb_lpfl_rbb & 0x1) << 14;
        value |= (regs->reg_0x0115_pd_lpfh_rbb & 0x1) << 3;
        value |= (regs->reg_0x0115_pd_lpfl_rbb & 0x1) << 2;
        value |= (regs->reg_0x0115_pd_pga_rbb & 0x1) << 1;
        value |= (regs->reg_0x0115_en_g_rbb & 0x1) << 0;
    }
    if (addr == 0x0116)
    {
        value |= (regs->reg_0x0116_r_ctl_lpf_rbb & 0x1f) << 11;
        value |= (regs->reg_0x0116_rcc_ctl_lpfh_rbb & 0x7) << 8;
        value |= (regs->reg_0x0116_c_ctl_lpfh_rbb & 0xff) << 0;
    }
    if (addr == 0x0117)
    {
        value |= (regs->reg_0x0117_rcc_ctl_lpfl_rbb & 0x7) << 11;
        value |= (regs->reg_0x0117_c_ctl_lpfl_rbb & 0x7ff) << 0;
    }
    if (addr == 0x0118)
    {
        value |= (regs->reg_0x0118_input_ctl_pga_rbb & 0x7) << 13;
        value |= (regs->reg_0x0118_ict_lpf_in_rbb & 0x1f) << 5;
        value |= (regs->reg_0x0118_ict_lpf_out_rbb & 0x1f) << 0;
    }
    if (addr == 0x0119)
    {
        value |= (regs->reg_0x0119_osw_pga_rbb & 0x1) << 15;
        value |= (regs->reg_0x0119_ict_pga_out_rbb & 0x1f) << 10;
        value |= (regs->reg_0x0119_ict_pga_in_rbb & 0x1f) << 5;
        value |= (regs->reg_0x0119_g_pga_rbb & 0x1f) << 0;
    }
    if (addr == 0x011A)
    {
        value |= (regs->reg_0x011a_rcc_ctl_pga_rbb & 0x1f) << 9;
        value |= (regs->reg_0x011a_c_ctl_pga_rbb & 0xff) << 0;
    }
    if (addr == 0x011B)
    {
        value |= (regs->reg_0x011b_resrv_rbb & 0x7f) << 0;
    }
    if (addr == 0x011C)
    {
        value |= (regs->reg_0x011c_reset_n & 0x1) << 15;
        value |= (regs->reg_0x011c_spdup_vco & 0x1) << 14;
        value |= (regs->reg_0x011c_bypldo_vco & 0x1) << 13;
        value |= (regs->reg_0x011c_en_coarsepll & 0x1) << 12;
        value |= (regs->reg_0x011c_curlim_vco & 0x1) << 11;
        value |= (regs->reg_0x011c_en_div2_divprog & 0x1) << 10;
        value |= (regs->reg_0x011c_en_intonly_sdm & 0x1) << 9;
        value |= (regs->reg_0x011c_en_sdm_clk & 0x1) << 8;
        value |= (regs->reg_0x011c_pd_fbdiv & 0x1) << 7;
        value |= (regs->reg_0x011c_pd_loch_t2rbuf & 0x1) << 6;
        value |= (regs->reg_0x011c_pd_cp & 0x1) << 5;
        value |= (regs->reg_0x011c_pd_fdiv & 0x1) << 4;
        value |= (regs->reg_0x011c_pd_sdm & 0x1) << 3;
        value |= (regs->reg_0x011c_pd_vco_comp & 0x1) << 2;
        value |= (regs->reg_0x011c_pd_vco & 0x1) << 1;
        value |= (regs->reg_0x011c_en_g & 0x1) << 0;
    }
    if (addr == 0x011D)
    {
        value |= (regs->reg_0x011d_frac_sdm & 0xffff) << 0;
    }
    if (addr == 0x011E)
    {
        value |= (regs->reg_0x011e_int_sdm & 0x3ff) << 4;
        value |= (regs->reg_0x011e_frac_sdm & 0xf) << 0;
    }
    if (addr == 0x011F)
    {
        value |= (regs->reg_0x011f_pw_div2_loch & 0x7) << 12;
        value |= (regs->reg_0x011f_pw_div4_loch & 0x7) << 9;
        value |= (regs->reg_0x011f_div_loch & 0x7) << 6;
        value |= (regs->reg_0x011f_tst_sx & 0x7) << 3;
        value |= (regs->reg_0x011f_sel_sdmclk & 0x1) << 2;
        value |= (regs->reg_0x011f_sx_dither_en & 0x1) << 1;
        value |= (regs->reg_0x011f_rev_sdmclk & 0x1) << 0;
    }
    if (addr == 0x0120)
    {
        value |= (regs->reg_0x0120_vdiv_vco & 0xff) << 8;
        value |= (regs->reg_0x0120_ict_vco & 0xff) << 0;
    }
    if (addr == 0x0121)
    {
        value |= (regs->reg_0x0121_rsel_ldo_vco & 0x1f) << 11;
        value |= (regs->reg_0x0121_csw_vco & 0xff) << 3;
        value |= (regs->reg_0x0121_sel_vco & 0x3) << 1;
        value |= (regs->reg_0x0121_coarse_start & 0x1) << 0;
    }
    if (addr == 0x0122)
    {
        value |= (regs->reg_0x0122_revph_pfd & 0x1) << 12;
        value |= (regs->reg_0x0122_ioffset_cp & 0x3f) << 6;
        value |= (regs->reg_0x0122_ipulse_cp & 0x3f) << 0;
    }
    if (addr == 0x0123)
    {
        value |= (regs->reg_0x0123_coarse_stepdone & 0x1) << 15;
        value |= (regs->reg_0x0123_coarsepll_compo & 0x1) << 14;
        value |= (regs->reg_0x0123_vco_cmpho & 0x1) << 13;
        value |= (regs->reg_0x0123_vco_cmplo & 0x1) << 12;
        value |= (regs->reg_0x0123_cp2_pll & 0xf) << 8;
        value |= (regs->reg_0x0123_cp3_pll & 0xf) << 4;
        value |= (regs->reg_0x0123_cz & 0xf) << 0;
    }
    if (addr == 0x0124)
    {
        value |= (regs->reg_0x0124_en_dir_sxx & 0x1) << 4;
        value |= (regs->reg_0x0124_en_dir_rbb & 0x1) << 3;
        value |= (regs->reg_0x0124_en_dir_rfe & 0x1) << 2;
        value |= (regs->reg_0x0124_en_dir_tbb & 0x1) << 1;
        value |= (regs->reg_0x0124_en_dir_trf & 0x1) << 0;
    }
    if (addr == 0x0125)
    {
        value |= (regs->reg_0x0125_value & 0xffff) << 0;
    }
    if (addr == 0x0126)
    {
        value |= (regs->reg_0x0126_value & 0xffff) << 0;
    }
    if (addr == 0x0200)
    {
        value |= (regs->reg_0x0200_tsgfc & 0x1) << 9;
        value |= (regs->reg_0x0200_tsgfcw & 0x3) << 7;
        value |= (regs->reg_0x0200_tsgdcldq & 0x1) << 6;
        value |= (regs->reg_0x0200_tsgdcldi & 0x1) << 5;
        value |= (regs->reg_0x0200_tsgswapiq & 0x1) << 4;
        value |= (regs->reg_0x0200_tsgmode & 0x1) << 3;
        value |= (regs->reg_0x0200_insel & 0x1) << 2;
        value |= (regs->reg_0x0200_bstart & 0x1) << 1;
        value |= (regs->reg_0x0200_en & 0x1) << 0;
    }
    if (addr == 0x0201)
    {
        value |= (regs->reg_0x0201_gcorrq & 0x7ff) << 0;
    }
    if (addr == 0x0202)
    {
        value |= (regs->reg_0x0202_gcorri & 0x7ff) << 0;
    }
    if (addr == 0x0203)
    {
        value |= (regs->reg_0x0203_hbi_ovr & 0x7) << 12;
        value |= (regs->reg_0x0203_iqcorr & 0xfff) << 0;
    }
    if (addr == 0x0204)
    {
        value |= (regs->reg_0x0204_dccorri & 0xff) << 8;
        value |= (regs->reg_0x0204_dccorrq & 0xff) << 0;
    }
    if (addr == 0x0205)
    {
        value |= (regs->reg_0x0205_gfir1_l & 0x7) << 8;
        value |= (regs->reg_0x0205_gfir1_n & 0xff) << 0;
    }
    if (addr == 0x0206)
    {
        value |= (regs->reg_0x0206_gfir2_l & 0x7) << 8;
        value |= (regs->reg_0x0206_gfir2_n & 0xff) << 0;
    }
    if (addr == 0x0207)
    {
        value |= (regs->reg_0x0207_gfir3_l & 0x7) << 8;
        value |= (regs->reg_0x0207_gfir3_n & 0xff) << 0;
    }
    if (addr == 0x0208)
    {
        value |= (regs->reg_0x0208_cmix_gain & 0x3) << 14;
        value |= (regs->reg_0x0208_cmix_sc & 0x1) << 13;
        value |= (regs->reg_0x0208_cmix_byp & 0x1) << 8;
        value |= (regs->reg_0x0208_isinc_byp & 0x1) << 7;
        value |= (regs->reg_0x0208_gfir3_byp & 0x1) << 6;
        value |= (regs->reg_0x0208_gfir2_byp & 0x1) << 5;
        value |= (regs->reg_0x0208_gfir1_byp & 0x1) << 4;
        value |= (regs->reg_0x0208_dc_byp & 0x1) << 3;
        value |= (regs->reg_0x0208_gc_byp & 0x1) << 1;
        value |= (regs->reg_0x0208_ph_byp & 0x1) << 0;
    }
    if (addr == 0x0209)
    {
        value |= (regs->reg_0x0209_value & 0xffff) << 0;
    }
    if (addr == 0x020a)
    {
        value |= (regs->reg_0x020a_value & 0xffff) << 0;
    }
    if (addr == 0x020C)
    {
        value |= (regs->reg_0x020c_dc_reg & 0xffff) << 0;
    }
    if (addr == 0x0240)
    {
        value |= (regs->reg_0x0240_dthbit & 0xf) << 5;
        value |= (regs->reg_0x0240_sel & 0xf) << 1;
        value |= (regs->reg_0x0240_mode & 0x1) << 0;
    }
    if (addr == 0x0241)
    {
        value |= (regs->reg_0x0241_pho & 0xffff) << 0;
    }
    if (addr == 0x0242)
    {
        value |= (regs->reg_0x0242_fcw0_hi & 0xffff) << 0;
    }
    if (addr == 0x0243)
    {
        value |= (regs->reg_0x0243_fcw0_lo & 0xffff) << 0;
    }
    if (addr == 0x0400)
    {
        value |= (regs->reg_0x0400_capture & 0x1) << 15;
        value |= (regs->reg_0x0400_capsel & 0x3) << 13;
        value |= (regs->reg_0x0400_tsgfc & 0x1) << 9;
        value |= (regs->reg_0x0400_tsgfcw & 0x3) << 7;
        value |= (regs->reg_0x0400_tsgdcldq & 0x1) << 6;
        value |= (regs->reg_0x0400_tsgdcldi & 0x1) << 5;
        value |= (regs->reg_0x0400_tsgswapiq & 0x1) << 4;
        value |= (regs->reg_0x0400_tsgmode & 0x1) << 3;
        value |= (regs->reg_0x0400_insel & 0x1) << 2;
        value |= (regs->reg_0x0400_bstart & 0x1) << 1;
        value |= (regs->reg_0x0400_en & 0x1) << 0;
    }
    if (addr == 0x0401)
    {
        value |= (regs->reg_0x0401_gcorrq & 0x7ff) << 0;
    }
    if (addr == 0x0402)
    {
        value |= (regs->reg_0x0402_gcorri & 0x7ff) << 0;
    }
    if (addr == 0x0403)
    {
        value |= (regs->reg_0x0403_hbd_ovr & 0x7) << 12;
        value |= (regs->reg_0x0403_iqcorr & 0xfff) << 0;
    }
    if (addr == 0x0404)
    {
        value |= (regs->reg_0x0404_dccorr_avg & 0x7) << 0;
    }
    if (addr == 0x0405)
    {
        value |= (regs->reg_0x0405_gfir1_l & 0x7) << 8;
        value |= (regs->reg_0x0405_gfir1_n & 0xff) << 0;
    }
    if (addr == 0x0406)
    {
        value |= (regs->reg_0x0406_gfir2_l & 0x7) << 8;
        value |= (regs->reg_0x0406_gfir2_n & 0xff) << 0;
    }
    if (addr == 0x0407)
    {
        value |= (regs->reg_0x0407_gfir3_l & 0x7) << 8;
        value |= (regs->reg_0x0407_gfir3_n & 0xff) << 0;
    }
    if (addr == 0x0408)
    {
        value |= (regs->reg_0x0408_agc_k_lsb & 0xffff) << 0;
    }
    if (addr == 0x0409)
    {
        value |= (regs->reg_0x0409_agc_adesired & 0xfff) << 4;
        value |= (regs->reg_0x0409_agc_k_msb & 0x3) << 0;
    }
    if (addr == 0x040A)
    {
        value |= (regs->reg_0x040a_agc_mode & 0x3) << 12;
        value |= (regs->reg_0x040a_agc_avg & 0x7) << 0;
    }
    if (addr == 0x040B)
    {
        value |= (regs->reg_0x040b_dc_reg & 0xffff) << 0;
    }
    if (addr == 0x040C)
    {
        value |= (regs->reg_0x040c_cmix_gain & 0x3) << 14;
        value |= (regs->reg_0x040c_cmix_sc & 0x1) << 13;
        value |= (regs->reg_0x040c_cmix_byp & 0x1) << 7;
        value |= (regs->reg_0x040c_agc_byp & 0x1) << 6;
        value |= (regs->reg_0x040c_gfir3_byp & 0x1) << 5;
        value |= (regs->reg_0x040c_gfir2_byp & 0x1) << 4;
        value |= (regs->reg_0x040c_gfir1_byp & 0x1) << 3;
        value |= (regs->reg_0x040c_dc_byp & 0x1) << 2;
        value |= (regs->reg_0x040c_gc_byp & 0x1) << 1;
        value |= (regs->reg_0x040c_ph_byp & 0x1) << 0;
    }
    if (addr == 0x040e)
    {
        value |= (regs->reg_0x040e_value & 0xffff) << 0;
    }
    if (addr == 0x0440)
    {
        value |= (regs->reg_0x0440_dthbit & 0xf) << 5;
        value |= (regs->reg_0x0440_sel & 0xf) << 1;
        value |= (regs->reg_0x0440_mode & 0x1) << 0;
    }
    if (addr == 0x0441)
    {
        value |= (regs->reg_0x0441_pho & 0xffff) << 0;
    }
    if (addr == 0x0442)
    {
        value |= (regs->reg_0x0442_fcw0_hi & 0xffff) << 0;
    }
    if (addr == 0x0443)
    {
        value |= (regs->reg_0x0443_fcw0_lo & 0xffff) << 0;
    }
    if (addr == 0x05c0)
    {
        value |= (regs->reg_0x05c0_value & 0xffff) << 0;
    }
    if (addr == 0x05c1)
    {
        value |= (regs->reg_0x05c1_value & 0xffff) << 0;
    }
    if (addr == 0x05c2)
    {
        value |= (regs->reg_0x05c2_value & 0xffff) << 0;
    }
    if (addr == 0x05c3)
    {
        value |= (regs->reg_0x05c3_value & 0xffff) << 0;
    }
    if (addr == 0x05c4)
    {
        value |= (regs->reg_0x05c4_value & 0xffff) << 0;
    }
    if (addr == 0x05c5)
    {
        value |= (regs->reg_0x05c5_value & 0xffff) << 0;
    }
    if (addr == 0x05c6)
    {
        value |= (regs->reg_0x05c6_value & 0xffff) << 0;
    }
    if (addr == 0x05c7)
    {
        value |= (regs->reg_0x05c7_value & 0xffff) << 0;
    }
    if (addr == 0x05c8)
    {
        value |= (regs->reg_0x05c8_value & 0xffff) << 0;
    }
    if (addr == 0x05c9)
    {
        value |= (regs->reg_0x05c9_value & 0xffff) << 0;
    }
    if (addr == 0x05ca)
    {
        value |= (regs->reg_0x05ca_value & 0xffff) << 0;
    }
    if (addr == 0x05cb)
    {
        value |= (regs->reg_0x05cb_value & 0xffff) << 0;
    }
    if (addr == 0x05cc)
    {
        value |= (regs->reg_0x05cc_value & 0xffff) << 0;
    }
    if (addr == 0x0600)
    {
        value |= (regs->reg_0x0600_value & 0xffff) << 0;
    }
    if (addr == 0x0601)
    {
        value |= (regs->reg_0x0601_value & 0xffff) << 0;
    }
    if (addr == 0x0602)
    {
        value |= (regs->reg_0x0602_value & 0xffff) << 0;
    }
    if (addr == 0x0603)
    {
        value |= (regs->reg_0x0603_value & 0xffff) << 0;
    }
    if (addr == 0x0604)
    {
        value |= (regs->reg_0x0604_value & 0xffff) << 0;
    }
    if (addr == 0x0605)
    {
        value |= (regs->reg_0x0605_value & 0xffff) << 0;
    }
    if (addr == 0x0606)
    {
        value |= (regs->reg_0x0606_value & 0xffff) << 0;
    }
    if (addr == 0x0640)
    {
        value |= (regs->reg_0x0640_value & 0xffff) << 0;
    }
    if (addr == 0x0641)
    {
        value |= (regs->reg_0x0641_value & 0xffff) << 0;
    }
    return value;
}

static inline const int *LMS7002M_regs_addrs(void)
{
    static const int addrs[] = {
    0x0020,
    0x0021,
    0x0022,
    0x0023,
    0x0024,
    0x0025,
    0x0026,
    0x0027,
    0x0028,
    0x0029,
    0x002A,
    0x002B,
    0x002C,
    0x002E,
    0x002F,
    0x0081,
    0x0082,
    0x0084,
    0x0085,
    0x0086,
    0x0087,
    0x0088,
    0x0089,
    0x008A,
    0x008B,
    0x008C,
    0x008D,
    0x0092,
    0x0093,
    0x0094,
    0x0095,
    0x0096,
    0x0097,
    0x0098,
    0x0099,
    0x009A,
    0x009B,
    0x009C,
    0x009D,
    0x009E,
    0x009F,
    0x00A0,
    0x00A1,
    0x00A2,
    0x00A3,
    0x00A4,
    0x00A5,
    0x00A6,
    0x00A7,
    0x00a8,
    0x00aa,
    0x00ab,
    0x00ad,
    0x00ae,
    0x0100,
    0x0101,
    0x0102,
    0x0103,
    0x0104,
    0x0105,
    0x0106,
    0x0107,
    0x0108,
    0x0109,
    0x010A,
    0x010b,
    0x010C,
    0x010D,
    0x010E,
    0x010F,
    0x0110,
    0x0111,
    0x0112,
    0x0113,
    0x0114,
    0x0115,
    0x0116,
    0x0117,
    0x0118,
    0x0119,
    0x011A,
    0x011B,
    0x011C,
    0x011D,
    0x011E,
    0x011F,
    0x0120,
    0x0121,
    0x0122,
    0x0123,
    0x0124,
    0x0125,
    0x0126,
    0x0200,
    0x0201,
    0x0202,
    0x0203,
    0x0204,
    0x0205,
    0x0206,
    0x0207,
    0x0208,
    0x0209,
    0x020a,
    0x020C,
    0x0240,
    0x0241,
    0x0242,
    0x0243,
    0x0400,
    0x0401,
    0x0402,
    0x0403,
    0x0404,
    0x0405,
    0x0406,
    0x0407,
    0x0408,
    0x0409,
    0x040A,
    0x040B,
    0x040C,
    0x040e,
    0x0440,
    0x0441,
    0x0442,
    0x0443,
    0x05c0,
    0x05c1,
    0x05c2,
    0x05c3,
    0x05c4,
    0x05c5,
    0x05c6,
    0x05c7,
    0x05c8,
    0x05c9,
    0x05ca,
    0x05cb,
    0x05cc,
    0x0600,
    0x0601,
    0x0602,
    0x0603,
    0x0604,
    0x0605,
    0x0606,
    0x0640,
    0x0641,
    0x0000 //end
    };
    return addrs;
}


