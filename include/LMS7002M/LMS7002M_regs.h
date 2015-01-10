
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

struct LMS7002M_regs_struct;
typedef struct LMS7002M_regs_struct LMS7002M_regs_t;

//! initialize a register structure with default values
static inline void LMS7002M_regs_init(LMS7002M_regs_t *regs);

//! set the fields from the value that belong to the register specified by addr
static inline void LMS7002M_regs_set(LMS7002M_regs_t *regs, const int addr, const int value);

//! get the value of the register specified by the fields at the given address
static inline int LMS7002M_regs_get(LMS7002M_regs_t *regs, const int addr);

//! enumerated values for some registers
#define REG_0X0021_SPIMODE_3WIRE 0
#define REG_0X0021_SPIMODE_4WIRE 1
#define REG_0X0023_LML_MODE1_TRXIQ 0
#define REG_0X0023_LML_MODE1_JESD207 1
#define REG_0X0023_LML_MODE2_TRXIQ 0
#define REG_0X0023_LML_MODE2_JESD207 1
#define REG_0X0023_LML_TXNRXIQ1_TXIQ 1
#define REG_0X0023_LML_TXNRXIQ1_RXIQ 0
#define REG_0X002A_RXRDCLK_MUX_MCLK1 0
#define REG_0X002A_RXRDCLK_MUX_FCLK2 3
#define REG_0X002A_RXRDCLK_MUX_FCLK1 2
#define REG_0X002A_RXRDCLK_MUX_MCLK2 1
#define REG_0X002A_RXWRCLK_MUX_RXTSPCLK_ 3
#define REG_0X002A_RXWRCLK_MUX_RXTSPCLK 2
#define REG_0X002A_RXWRCLK_MUX_FCLK1 0
#define REG_0X002A_RXWRCLK_MUX_FCLK2 1
#define REG_0X002A_RX_MUX_TXFIFO 1
#define REG_0X002A_RX_MUX_LFSR 2
#define REG_0X002A_RX_MUX_RXTSPCLK 0
#define REG_0X002A_RX_MUX_LFSR_ 3
#define REG_0X002A_TXRDCLK_MUX_TXTSPCLK_ 3
#define REG_0X002A_TXRDCLK_MUX_FCLK2 1
#define REG_0X002A_TXRDCLK_MUX_FCLK1 0
#define REG_0X002A_TXRDCLK_MUX_TXTSPCLK 2
#define REG_0X002A_TXWRCLK_MUX_RXTSPCLK_ 3
#define REG_0X002A_TXWRCLK_MUX_RXTSPCLK 2
#define REG_0X002A_TXWRCLK_MUX_FCLK1 0
#define REG_0X002A_TXWRCLK_MUX_FCLK2 1
#define REG_0X002A_TX_MUX_RXTSP_ 3
#define REG_0X002A_TX_MUX_PORT2 1
#define REG_0X002A_TX_MUX_RXTSP 2
#define REG_0X002A_TX_MUX_PORT1 0
#define REG_0X002B_MCLK1SRC_TXTSPCLKA_DIV 0
#define REG_0X002B_MCLK1SRC_RXTSPCLKA_DIV 1
#define REG_0X002B_MCLK1SRC_TXTSPCLKA 2
#define REG_0X002B_MCLK1SRC_RXTSPCLKA 3
#define REG_0X002B_MCLK2SRC_TXTSPCLKA_DIV 0
#define REG_0X002B_MCLK2SRC_RXTSPCLKA_DIV 1
#define REG_0X002B_MCLK2SRC_TXTSPCLKA 2
#define REG_0X002B_MCLK2SRC_RXTSPCLKA 3
#define REG_0X0089_SEL_SDMCLK_CGEN_CLK_DIV 0
#define REG_0X0089_SEL_SDMCLK_CGEN_CLK_REF 1
#define REG_0X0089_TST_CGEN_DISABLED 0
#define REG_0X0089_TST_CGEN_PFD_UP 5
#define REG_0X0089_TST_CGEN_VCO_TUNE 3
#define REG_0X0089_TST_CGEN_VCO_TUNE_50_KOHM 2
#define REG_0X0089_TST_CGEN_TSTDO 1

struct LMS7002M_regs_struct
{
    int reg_0x0020_lrst_rx_a;
    int reg_0x0020_lrst_rx_b;
    int reg_0x0020_lrst_tx_a;
    int reg_0x0020_lrst_tx_b;
    int reg_0x0020_mac;
    int reg_0x0020_mrst_rx_a;
    int reg_0x0020_mrst_rx_b;
    int reg_0x0020_mrst_tx_a;
    int reg_0x0020_mrst_tx_b;
    int reg_0x0020_rxen_a;
    int reg_0x0020_rxen_b;
    int reg_0x0020_srst_rxfifo;
    int reg_0x0020_srst_txfifo;
    int reg_0x0020_txen_a;
    int reg_0x0020_txen_b;
    int reg_0x0021_rx_clk_pe;
    int reg_0x0021_sclk_pe;
    int reg_0x0021_scl_ds;
    int reg_0x0021_scl_pe;
    int reg_0x0021_sda_ds;
    int reg_0x0021_sda_pe;
    int reg_0x0021_sdio_ds;
    int reg_0x0021_sdio_pe;
    int reg_0x0021_sdo_pe;
    int reg_0x0021_sen_pe;
    int reg_0x0021_spimode;
    int reg_0x0021_tx_clk_pe;
    int reg_0x0023_diqdir1;
    int reg_0x0023_diqdir2;
    int reg_0x0023_diqdirctr1;
    int reg_0x0023_diqdirctr2;
    int reg_0x0023_enabledir1;
    int reg_0x0023_enabledir2;
    int reg_0x0023_enabledirctr1;
    int reg_0x0023_enabledirctr2;
    int reg_0x0023_lml_fidm1;
    int reg_0x0023_lml_fidm2;
    int reg_0x0023_lml_mode1;
    int reg_0x0023_lml_mode2;
    int reg_0x0023_lml_txnrxiq1;
    int reg_0x0023_lml_txnrxiq2;
    int reg_0x0023_mod_en;
    int reg_0x002a_rxrdclk_mux;
    int reg_0x002a_rxwrclk_mux;
    int reg_0x002a_rx_mux;
    int reg_0x002a_txrdclk_mux;
    int reg_0x002a_txwrclk_mux;
    int reg_0x002a_tx_mux;
    int reg_0x002b_fclk1_inv;
    int reg_0x002b_fclk2_inv;
    int reg_0x002b_mclk1dly;
    int reg_0x002b_mclk1src;
    int reg_0x002b_mclk2dly;
    int reg_0x002b_mclk2src;
    int reg_0x002b_rxdiven;
    int reg_0x002b_txdiven;
    int reg_0x002f_mask;
    int reg_0x002f_rev;
    int reg_0x002f_ver;
    int reg_0x0085_byp_xbuf_rx;
    int reg_0x0085_byp_xbuf_tx;
    int reg_0x0085_en_g_xbuf;
    int reg_0x0085_en_out2_xbuf_tx;
    int reg_0x0085_en_tbufin_xbuf_rx;
    int reg_0x0085_pd_xbuf_rx;
    int reg_0x0085_pd_xbuf_tx;
    int reg_0x0085_slfb_xbuf_rx;
    int reg_0x0085_slfb_xbuf_tx;
    int reg_0x0086_en_adcclkh_clkgn;
    int reg_0x0086_en_coarse_cklgen;
    int reg_0x0086_en_g_cgen;
    int reg_0x0086_en_intonly_sdm_cgen;
    int reg_0x0086_en_sdm_clk_cgen;
    int reg_0x0086_pd_cp_cgen;
    int reg_0x0086_pd_fdiv_fb_cgen;
    int reg_0x0086_pd_fdiv_o_cgen;
    int reg_0x0086_pd_sdm_cgen;
    int reg_0x0086_pd_vco_cgen;
    int reg_0x0086_pd_vco_comp_cgen;
    int reg_0x0086_reset_n_cgen;
    int reg_0x0086_spdup_vco_cgen;
    int reg_0x0087_frac_sdm_cgen;
    int reg_0x0088_frac_sdm_cgen;
    int reg_0x0088_int_sdm_cgen;
    int reg_0x0089_clkh_ov_clkl_cgen;
    int reg_0x0089_div_outch_cgen;
    int reg_0x0089_rev_sdmclk_cgen;
    int reg_0x0089_sel_sdmclk_cgen;
    int reg_0x0089_sx_dither_en_cgen;
    int reg_0x0089_tst_cgen;
    int reg_0x008a_ioffset_cp_cgen;
    int reg_0x008a_ipulse_cp_cgen;
    int reg_0x008a_revph_pfd_cgen;
    int reg_0x008a_rev_clkadc_cgen;
    int reg_0x008a_rev_clkdac_cgen;
    int reg_0x008b_coarse_start_cgen;
    int reg_0x008b_csw_vco_cgen;
    int reg_0x008b_ict_vco_cgen;
    int reg_0x008c_coarsepll_compo_cgen;
    int reg_0x008c_coarse_stepdone_cgen;
    int reg_0x008c_cp2_cgen;
    int reg_0x008c_cp3_cgen;
    int reg_0x008c_cz_cgen;
    int reg_0x008c_vco_cmpho_cgen;
    int reg_0x008c_vco_cmplo_cgen;
    int reg_0x008d_resrv_cgn;
};

/***********************************************************************
 * Implementation details below
 **********************************************************************/

static inline void LMS7002M_regs_init(LMS7002M_regs_t *regs)
{
    LMS7002M_regs_set(regs, 0x0020, 0xffff);
    LMS7002M_regs_set(regs, 0x0021, 0xe9f);
    LMS7002M_regs_set(regs, 0x0023, 0x5559);
    LMS7002M_regs_set(regs, 0x002A, 0x86);
    LMS7002M_regs_set(regs, 0x002B, 0x10);
    LMS7002M_regs_set(regs, 0x002F, 0x3840);
    LMS7002M_regs_set(regs, 0x0085, 0x1);
    LMS7002M_regs_set(regs, 0x0086, 0x4905);
    LMS7002M_regs_set(regs, 0x0087, 0x400);
    LMS7002M_regs_set(regs, 0x0088, 0x780);
    LMS7002M_regs_set(regs, 0x0089, 0x20);
    LMS7002M_regs_set(regs, 0x008A, 0x514);
    LMS7002M_regs_set(regs, 0x008B, 0x1900);
    LMS7002M_regs_set(regs, 0x008C, 0x67b);
    LMS7002M_regs_set(regs, 0x008D, 0x0);
}

static inline void LMS7002M_regs_set(LMS7002M_regs_t *regs, const int addr, const int value)
{
    if (addr == 0x0020)
    {
        regs->reg_0x0020_lrst_rx_a = (value >> 9) & 0x1;
        regs->reg_0x0020_lrst_rx_b = (value >> 11) & 0x1;
        regs->reg_0x0020_lrst_tx_a = (value >> 13) & 0x1;
        regs->reg_0x0020_lrst_tx_b = (value >> 15) & 0x1;
        regs->reg_0x0020_mac = (value >> 0) & 0x3;
        regs->reg_0x0020_mrst_rx_a = (value >> 8) & 0x1;
        regs->reg_0x0020_mrst_rx_b = (value >> 10) & 0x1;
        regs->reg_0x0020_mrst_tx_a = (value >> 12) & 0x1;
        regs->reg_0x0020_mrst_tx_b = (value >> 14) & 0x1;
        regs->reg_0x0020_rxen_a = (value >> 4) & 0x1;
        regs->reg_0x0020_rxen_b = (value >> 5) & 0x1;
        regs->reg_0x0020_srst_rxfifo = (value >> 7) & 0x1;
        regs->reg_0x0020_srst_txfifo = (value >> 6) & 0x1;
        regs->reg_0x0020_txen_a = (value >> 2) & 0x1;
        regs->reg_0x0020_txen_b = (value >> 3) & 0x1;
        return;
    }
    if (addr == 0x0021)
    {
        regs->reg_0x0021_rx_clk_pe = (value >> 10) & 0x1;
        regs->reg_0x0021_sclk_pe = (value >> 2) & 0x1;
        regs->reg_0x0021_scl_ds = (value >> 6) & 0x1;
        regs->reg_0x0021_scl_pe = (value >> 7) & 0x1;
        regs->reg_0x0021_sda_ds = (value >> 8) & 0x1;
        regs->reg_0x0021_sda_pe = (value >> 9) & 0x1;
        regs->reg_0x0021_sdio_ds = (value >> 5) & 0x1;
        regs->reg_0x0021_sdio_pe = (value >> 4) & 0x1;
        regs->reg_0x0021_sdo_pe = (value >> 3) & 0x1;
        regs->reg_0x0021_sen_pe = (value >> 1) & 0x1;
        regs->reg_0x0021_spimode = (value >> 0) & 0x1;
        regs->reg_0x0021_tx_clk_pe = (value >> 11) & 0x1;
        return;
    }
    if (addr == 0x0023)
    {
        regs->reg_0x0023_diqdir1 = (value >> 12) & 0x1;
        regs->reg_0x0023_diqdir2 = (value >> 14) & 0x1;
        regs->reg_0x0023_diqdirctr1 = (value >> 13) & 0x1;
        regs->reg_0x0023_diqdirctr2 = (value >> 15) & 0x1;
        regs->reg_0x0023_enabledir1 = (value >> 8) & 0x1;
        regs->reg_0x0023_enabledir2 = (value >> 10) & 0x1;
        regs->reg_0x0023_enabledirctr1 = (value >> 9) & 0x1;
        regs->reg_0x0023_enabledirctr2 = (value >> 11) & 0x1;
        regs->reg_0x0023_lml_fidm1 = (value >> 2) & 0x1;
        regs->reg_0x0023_lml_fidm2 = (value >> 5) & 0x1;
        regs->reg_0x0023_lml_mode1 = (value >> 0) & 0x1;
        regs->reg_0x0023_lml_mode2 = (value >> 3) & 0x1;
        regs->reg_0x0023_lml_txnrxiq1 = (value >> 1) & 0x1;
        regs->reg_0x0023_lml_txnrxiq2 = (value >> 4) & 0x1;
        regs->reg_0x0023_mod_en = (value >> 6) & 0x1;
        return;
    }
    if (addr == 0x002A)
    {
        regs->reg_0x002a_rxrdclk_mux = (value >> 2) & 0x3;
        regs->reg_0x002a_rxwrclk_mux = (value >> 0) & 0x3;
        regs->reg_0x002a_rx_mux = (value >> 10) & 0x3;
        regs->reg_0x002a_txrdclk_mux = (value >> 6) & 0x3;
        regs->reg_0x002a_txwrclk_mux = (value >> 4) & 0x3;
        regs->reg_0x002a_tx_mux = (value >> 8) & 0x3;
        return;
    }
    if (addr == 0x002B)
    {
        regs->reg_0x002b_fclk1_inv = (value >> 14) & 0x1;
        regs->reg_0x002b_fclk2_inv = (value >> 15) & 0x1;
        regs->reg_0x002b_mclk1dly = (value >> 10) & 0x3;
        regs->reg_0x002b_mclk1src = (value >> 2) & 0x3;
        regs->reg_0x002b_mclk2dly = (value >> 12) & 0x3;
        regs->reg_0x002b_mclk2src = (value >> 4) & 0x3;
        regs->reg_0x002b_rxdiven = (value >> 0) & 0x1;
        regs->reg_0x002b_txdiven = (value >> 1) & 0x1;
        return;
    }
    if (addr == 0x002F)
    {
        regs->reg_0x002f_mask = (value >> 0) & 0x3f;
        regs->reg_0x002f_rev = (value >> 6) & 0x1f;
        regs->reg_0x002f_ver = (value >> 11) & 0x1f;
        return;
    }
    if (addr == 0x0085)
    {
        regs->reg_0x0085_byp_xbuf_rx = (value >> 6) & 0x1;
        regs->reg_0x0085_byp_xbuf_tx = (value >> 5) & 0x1;
        regs->reg_0x0085_en_g_xbuf = (value >> 0) & 0x1;
        regs->reg_0x0085_en_out2_xbuf_tx = (value >> 4) & 0x1;
        regs->reg_0x0085_en_tbufin_xbuf_rx = (value >> 3) & 0x1;
        regs->reg_0x0085_pd_xbuf_rx = (value >> 2) & 0x1;
        regs->reg_0x0085_pd_xbuf_tx = (value >> 1) & 0x1;
        regs->reg_0x0085_slfb_xbuf_rx = (value >> 8) & 0x1;
        regs->reg_0x0085_slfb_xbuf_tx = (value >> 7) & 0x1;
        return;
    }
    if (addr == 0x0086)
    {
        regs->reg_0x0086_en_adcclkh_clkgn = (value >> 11) & 0x1;
        regs->reg_0x0086_en_coarse_cklgen = (value >> 10) & 0x1;
        regs->reg_0x0086_en_g_cgen = (value >> 0) & 0x1;
        regs->reg_0x0086_en_intonly_sdm_cgen = (value >> 9) & 0x1;
        regs->reg_0x0086_en_sdm_clk_cgen = (value >> 8) & 0x1;
        regs->reg_0x0086_pd_cp_cgen = (value >> 6) & 0x1;
        regs->reg_0x0086_pd_fdiv_fb_cgen = (value >> 5) & 0x1;
        regs->reg_0x0086_pd_fdiv_o_cgen = (value >> 4) & 0x1;
        regs->reg_0x0086_pd_sdm_cgen = (value >> 3) & 0x1;
        regs->reg_0x0086_pd_vco_cgen = (value >> 2) & 0x1;
        regs->reg_0x0086_pd_vco_comp_cgen = (value >> 1) & 0x1;
        regs->reg_0x0086_reset_n_cgen = (value >> 14) & 0x1;
        regs->reg_0x0086_spdup_vco_cgen = (value >> 15) & 0x1;
        return;
    }
    if (addr == 0x0087)
    {
        regs->reg_0x0087_frac_sdm_cgen = (value >> 0) & 0xffff;
        return;
    }
    if (addr == 0x0088)
    {
        regs->reg_0x0088_frac_sdm_cgen = (value >> 0) & 0xf;
        regs->reg_0x0088_int_sdm_cgen = (value >> 4) & 0x3ff;
        return;
    }
    if (addr == 0x0089)
    {
        regs->reg_0x0089_clkh_ov_clkl_cgen = (value >> 11) & 0x3;
        regs->reg_0x0089_div_outch_cgen = (value >> 3) & 0xff;
        regs->reg_0x0089_rev_sdmclk_cgen = (value >> 15) & 0x1;
        regs->reg_0x0089_sel_sdmclk_cgen = (value >> 14) & 0x1;
        regs->reg_0x0089_sx_dither_en_cgen = (value >> 13) & 0x1;
        regs->reg_0x0089_tst_cgen = (value >> 0) & 0x7;
        return;
    }
    if (addr == 0x008A)
    {
        regs->reg_0x008a_ioffset_cp_cgen = (value >> 11) & 0x3f;
        regs->reg_0x008a_ipulse_cp_cgen = (value >> 0) & 0x3f;
        regs->reg_0x008a_revph_pfd_cgen = (value >> 12) & 0x1;
        regs->reg_0x008a_rev_clkadc_cgen = (value >> 13) & 0x1;
        regs->reg_0x008a_rev_clkdac_cgen = (value >> 14) & 0x1;
        return;
    }
    if (addr == 0x008B)
    {
        regs->reg_0x008b_coarse_start_cgen = (value >> 0) & 0x1;
        regs->reg_0x008b_csw_vco_cgen = (value >> 1) & 0xff;
        regs->reg_0x008b_ict_vco_cgen = (value >> 9) & 0x1f;
        return;
    }
    if (addr == 0x008C)
    {
        regs->reg_0x008c_coarsepll_compo_cgen = (value >> 14) & 0x1;
        regs->reg_0x008c_coarse_stepdone_cgen = (value >> 15) & 0x1;
        regs->reg_0x008c_cp2_cgen = (value >> 8) & 0xf;
        regs->reg_0x008c_cp3_cgen = (value >> 4) & 0xf;
        regs->reg_0x008c_cz_cgen = (value >> 0) & 0xf;
        regs->reg_0x008c_vco_cmpho_cgen = (value >> 13) & 0x1;
        regs->reg_0x008c_vco_cmplo_cgen = (value >> 12) & 0x1;
        return;
    }
    if (addr == 0x008D)
    {
        regs->reg_0x008d_resrv_cgn = (value >> 0) & 0x7;
        return;
    }
}

static inline int LMS7002M_regs_get(LMS7002M_regs_t *regs, const int addr)
{
    int value = 0;
    if (addr == 0x0020)
    {
        value |= (regs->reg_0x0020_lrst_rx_a & 0x1) << 9;
        value |= (regs->reg_0x0020_lrst_rx_b & 0x1) << 11;
        value |= (regs->reg_0x0020_lrst_tx_a & 0x1) << 13;
        value |= (regs->reg_0x0020_lrst_tx_b & 0x1) << 15;
        value |= (regs->reg_0x0020_mac & 0x3) << 0;
        value |= (regs->reg_0x0020_mrst_rx_a & 0x1) << 8;
        value |= (regs->reg_0x0020_mrst_rx_b & 0x1) << 10;
        value |= (regs->reg_0x0020_mrst_tx_a & 0x1) << 12;
        value |= (regs->reg_0x0020_mrst_tx_b & 0x1) << 14;
        value |= (regs->reg_0x0020_rxen_a & 0x1) << 4;
        value |= (regs->reg_0x0020_rxen_b & 0x1) << 5;
        value |= (regs->reg_0x0020_srst_rxfifo & 0x1) << 7;
        value |= (regs->reg_0x0020_srst_txfifo & 0x1) << 6;
        value |= (regs->reg_0x0020_txen_a & 0x1) << 2;
        value |= (regs->reg_0x0020_txen_b & 0x1) << 3;
    }
    if (addr == 0x0021)
    {
        value |= (regs->reg_0x0021_rx_clk_pe & 0x1) << 10;
        value |= (regs->reg_0x0021_sclk_pe & 0x1) << 2;
        value |= (regs->reg_0x0021_scl_ds & 0x1) << 6;
        value |= (regs->reg_0x0021_scl_pe & 0x1) << 7;
        value |= (regs->reg_0x0021_sda_ds & 0x1) << 8;
        value |= (regs->reg_0x0021_sda_pe & 0x1) << 9;
        value |= (regs->reg_0x0021_sdio_ds & 0x1) << 5;
        value |= (regs->reg_0x0021_sdio_pe & 0x1) << 4;
        value |= (regs->reg_0x0021_sdo_pe & 0x1) << 3;
        value |= (regs->reg_0x0021_sen_pe & 0x1) << 1;
        value |= (regs->reg_0x0021_spimode & 0x1) << 0;
        value |= (regs->reg_0x0021_tx_clk_pe & 0x1) << 11;
    }
    if (addr == 0x0023)
    {
        value |= (regs->reg_0x0023_diqdir1 & 0x1) << 12;
        value |= (regs->reg_0x0023_diqdir2 & 0x1) << 14;
        value |= (regs->reg_0x0023_diqdirctr1 & 0x1) << 13;
        value |= (regs->reg_0x0023_diqdirctr2 & 0x1) << 15;
        value |= (regs->reg_0x0023_enabledir1 & 0x1) << 8;
        value |= (regs->reg_0x0023_enabledir2 & 0x1) << 10;
        value |= (regs->reg_0x0023_enabledirctr1 & 0x1) << 9;
        value |= (regs->reg_0x0023_enabledirctr2 & 0x1) << 11;
        value |= (regs->reg_0x0023_lml_fidm1 & 0x1) << 2;
        value |= (regs->reg_0x0023_lml_fidm2 & 0x1) << 5;
        value |= (regs->reg_0x0023_lml_mode1 & 0x1) << 0;
        value |= (regs->reg_0x0023_lml_mode2 & 0x1) << 3;
        value |= (regs->reg_0x0023_lml_txnrxiq1 & 0x1) << 1;
        value |= (regs->reg_0x0023_lml_txnrxiq2 & 0x1) << 4;
        value |= (regs->reg_0x0023_mod_en & 0x1) << 6;
    }
    if (addr == 0x002A)
    {
        value |= (regs->reg_0x002a_rxrdclk_mux & 0x3) << 2;
        value |= (regs->reg_0x002a_rxwrclk_mux & 0x3) << 0;
        value |= (regs->reg_0x002a_rx_mux & 0x3) << 10;
        value |= (regs->reg_0x002a_txrdclk_mux & 0x3) << 6;
        value |= (regs->reg_0x002a_txwrclk_mux & 0x3) << 4;
        value |= (regs->reg_0x002a_tx_mux & 0x3) << 8;
    }
    if (addr == 0x002B)
    {
        value |= (regs->reg_0x002b_fclk1_inv & 0x1) << 14;
        value |= (regs->reg_0x002b_fclk2_inv & 0x1) << 15;
        value |= (regs->reg_0x002b_mclk1dly & 0x3) << 10;
        value |= (regs->reg_0x002b_mclk1src & 0x3) << 2;
        value |= (regs->reg_0x002b_mclk2dly & 0x3) << 12;
        value |= (regs->reg_0x002b_mclk2src & 0x3) << 4;
        value |= (regs->reg_0x002b_rxdiven & 0x1) << 0;
        value |= (regs->reg_0x002b_txdiven & 0x1) << 1;
    }
    if (addr == 0x002F)
    {
        value |= (regs->reg_0x002f_mask & 0x3f) << 0;
        value |= (regs->reg_0x002f_rev & 0x1f) << 6;
        value |= (regs->reg_0x002f_ver & 0x1f) << 11;
    }
    if (addr == 0x0085)
    {
        value |= (regs->reg_0x0085_byp_xbuf_rx & 0x1) << 6;
        value |= (regs->reg_0x0085_byp_xbuf_tx & 0x1) << 5;
        value |= (regs->reg_0x0085_en_g_xbuf & 0x1) << 0;
        value |= (regs->reg_0x0085_en_out2_xbuf_tx & 0x1) << 4;
        value |= (regs->reg_0x0085_en_tbufin_xbuf_rx & 0x1) << 3;
        value |= (regs->reg_0x0085_pd_xbuf_rx & 0x1) << 2;
        value |= (regs->reg_0x0085_pd_xbuf_tx & 0x1) << 1;
        value |= (regs->reg_0x0085_slfb_xbuf_rx & 0x1) << 8;
        value |= (regs->reg_0x0085_slfb_xbuf_tx & 0x1) << 7;
    }
    if (addr == 0x0086)
    {
        value |= (regs->reg_0x0086_en_adcclkh_clkgn & 0x1) << 11;
        value |= (regs->reg_0x0086_en_coarse_cklgen & 0x1) << 10;
        value |= (regs->reg_0x0086_en_g_cgen & 0x1) << 0;
        value |= (regs->reg_0x0086_en_intonly_sdm_cgen & 0x1) << 9;
        value |= (regs->reg_0x0086_en_sdm_clk_cgen & 0x1) << 8;
        value |= (regs->reg_0x0086_pd_cp_cgen & 0x1) << 6;
        value |= (regs->reg_0x0086_pd_fdiv_fb_cgen & 0x1) << 5;
        value |= (regs->reg_0x0086_pd_fdiv_o_cgen & 0x1) << 4;
        value |= (regs->reg_0x0086_pd_sdm_cgen & 0x1) << 3;
        value |= (regs->reg_0x0086_pd_vco_cgen & 0x1) << 2;
        value |= (regs->reg_0x0086_pd_vco_comp_cgen & 0x1) << 1;
        value |= (regs->reg_0x0086_reset_n_cgen & 0x1) << 14;
        value |= (regs->reg_0x0086_spdup_vco_cgen & 0x1) << 15;
    }
    if (addr == 0x0087)
    {
        value |= (regs->reg_0x0087_frac_sdm_cgen & 0xffff) << 0;
    }
    if (addr == 0x0088)
    {
        value |= (regs->reg_0x0088_frac_sdm_cgen & 0xf) << 0;
        value |= (regs->reg_0x0088_int_sdm_cgen & 0x3ff) << 4;
    }
    if (addr == 0x0089)
    {
        value |= (regs->reg_0x0089_clkh_ov_clkl_cgen & 0x3) << 11;
        value |= (regs->reg_0x0089_div_outch_cgen & 0xff) << 3;
        value |= (regs->reg_0x0089_rev_sdmclk_cgen & 0x1) << 15;
        value |= (regs->reg_0x0089_sel_sdmclk_cgen & 0x1) << 14;
        value |= (regs->reg_0x0089_sx_dither_en_cgen & 0x1) << 13;
        value |= (regs->reg_0x0089_tst_cgen & 0x7) << 0;
    }
    if (addr == 0x008A)
    {
        value |= (regs->reg_0x008a_ioffset_cp_cgen & 0x3f) << 11;
        value |= (regs->reg_0x008a_ipulse_cp_cgen & 0x3f) << 0;
        value |= (regs->reg_0x008a_revph_pfd_cgen & 0x1) << 12;
        value |= (regs->reg_0x008a_rev_clkadc_cgen & 0x1) << 13;
        value |= (regs->reg_0x008a_rev_clkdac_cgen & 0x1) << 14;
    }
    if (addr == 0x008B)
    {
        value |= (regs->reg_0x008b_coarse_start_cgen & 0x1) << 0;
        value |= (regs->reg_0x008b_csw_vco_cgen & 0xff) << 1;
        value |= (regs->reg_0x008b_ict_vco_cgen & 0x1f) << 9;
    }
    if (addr == 0x008C)
    {
        value |= (regs->reg_0x008c_coarsepll_compo_cgen & 0x1) << 14;
        value |= (regs->reg_0x008c_coarse_stepdone_cgen & 0x1) << 15;
        value |= (regs->reg_0x008c_cp2_cgen & 0xf) << 8;
        value |= (regs->reg_0x008c_cp3_cgen & 0xf) << 4;
        value |= (regs->reg_0x008c_cz_cgen & 0xf) << 0;
        value |= (regs->reg_0x008c_vco_cmpho_cgen & 0x1) << 13;
        value |= (regs->reg_0x008c_vco_cmplo_cgen & 0x1) << 12;
    }
    if (addr == 0x008D)
    {
        value |= (regs->reg_0x008d_resrv_cgn & 0x7) << 0;
    }
    return value;
}


