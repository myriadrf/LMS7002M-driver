///
/// \file LMS7002M/LMS7002M_sxx.h
///
/// LO tuning hooks for the LMS7002M C driver.
/// See SXR and SXT sections in the documentation.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#pragma once
#include <stdlib.h>
#include <LMS7002M/LMS7002M.h>

#ifdef __cplusplus
extern "C" {
#endif

LMS7002M_API void LMS7002M_sxx_enable(LMS7002M_t *self, const LMS7002M_dir_t direction, const bool enable)
{
    LMS7002M_set_mac_dir(self, direction);
    self->regs.reg_0x0124_en_dir_sxx = 1;
    LMS7002M_regs_spi_write(self, 0x0124);

    self->regs.reg_0x011c_en_g = enable?1:0;
    LMS7002M_regs_spi_write(self, 0x011c);
}

LMS7002M_API int LMS7002M_set_lo_freq(LMS7002M_t *self, const LMS7002M_dir_t direction, const double fref, const double fout, double *factual)
{
    LMS7002M_set_mac_dir(self, direction);

    //select VCO based on LO freq
    //boundaries for VCO selection determined by observing GUI
    int SEL_VCO = 0;
    double SXX_VCO_LO = 0;
    double SXX_VCO_HI = 0;
    if (fout < 1e9)
    {
        SEL_VCO = REG_0X0121_SEL_VCO_VCOH;
        SXX_VCO_LO = LMS7002M_SXX_VCOH_LO;
        SXX_VCO_HI = LMS7002M_SXX_VCOH_HI;
    }
    else if (fout < 2.4805e9)
    {
        SEL_VCO = REG_0X0121_SEL_VCO_VCOL;
        SXX_VCO_LO = LMS7002M_SXX_VCOL_LO;
        SXX_VCO_HI = LMS7002M_SXX_VCOL_HI;
    }
    else if (fout < 3.1530e9)
    {
        SEL_VCO = REG_0X0121_SEL_VCO_VCOM;
        SXX_VCO_LO = LMS7002M_SXX_VCOM_LO;
        SXX_VCO_HI = LMS7002M_SXX_VCOM_HI;
    }
    else
    {
        SEL_VCO = REG_0X0121_SEL_VCO_VCOH;
        SXX_VCO_LO = LMS7002M_SXX_VCOH_LO;
        SXX_VCO_HI = LMS7002M_SXX_VCOH_HI;
    }

    //The equations:
    // fref * N = fvco
    // fout = Fvco / divRatio_LOCH / 2
    int DIV_LOCH_SX = -1;
    int divRatio_LOCH = 0;
    double Ndiv = 0;
    double fvco = 0;
    int fdiv = 0;

    //calculation loop to find dividers that are possible
    while (true)
    {
        //try the next divider power
        DIV_LOCH_SX++;
        divRatio_LOCH = 1 << DIV_LOCH_SX;
        fdiv = divRatio_LOCH*2;

        Ndiv = fout*fdiv/fref;
        fvco = fout*fdiv;
        //printf("fdiv = %d, Ndiv = %f, fvco = %f MHz\n", fdiv, Ndiv, fvco/1e6);

        //check dividers and vco in range...
        if (fdiv > 128) return -1;
        if (Ndiv < 4) continue;
        if (Ndiv > 512) return -1;

        //check vco boundaries
        if (fvco < SXX_VCO_LO) continue;
        if (fvco > SXX_VCO_HI) continue;

        break; //its good
    }
    //printf("fdiv = %d, Ndiv = %f, fvco = %f MHz\n", fdiv, Ndiv, fvco/1e6);

    //deal with VCO divider
    const int EN_DIV2 = (fvco > 5.5e9)?1:0;

    //compensate for the lack of doubling when disabled
    if (EN_DIV2 == 0) Ndiv *= 2;

    //after a successful tune, stash the frequency
    if (direction == LMS_RX) self->sxr_freq = fout;
    if (direction == LMS_TX) self->sxt_freq = fout;
    if (direction == LMS_RX) self->sxr_fref = fref;
    if (direction == LMS_TX) self->sxt_fref = fref;

    //reset
    self->regs.reg_0x011c_reset_n = 0;
    LMS7002M_regs_spi_write(self, 0x011c);
    self->regs.reg_0x011c_reset_n = 1;
    LMS7002M_regs_spi_write(self, 0x011c);

    //configure and enable synthesizer
    self->regs.reg_0x011c_en_intonly_sdm = 0; //support frac-N
    self->regs.reg_0x011c_en_sdm_clk = 1; //enable
    self->regs.reg_0x011c_pd_cp = 0; //enable
    self->regs.reg_0x011c_pd_fbdiv = 0; //enable
    self->regs.reg_0x011c_pd_fdiv = 0; //enable
    self->regs.reg_0x011c_pd_sdm = 0; //enable
    self->regs.reg_0x011c_pd_vco = 0; //enable
    self->regs.reg_0x011c_pd_vco_comp = 0; //enable
    self->regs.reg_0x011c_en_g = 1;
    self->regs.reg_0x011c_en_coarsepll = 0;
    self->regs.reg_0x0121_coarse_start = 0;
    self->regs.reg_0x011c_en_div2_divprog = EN_DIV2;
    self->regs.reg_0x011c_spdup_vco = 1; //fast settling
    LMS7002M_regs_spi_write(self, 0x011c);

    //program the N divider
    const int Nint = (int)Ndiv - 4;
    const int Nfrac = (int)((Ndiv-int(Ndiv))*(1 << 20));
    self->regs.reg_0x011d_frac_sdm = (Nfrac) & 0xffff; //lower 16 bits
    self->regs.reg_0x011e_frac_sdm = (Nfrac) >> 16; //upper 4 bits
    self->regs.reg_0x011e_int_sdm = Nint;
    //printf("fdiv = %d, Ndiv = %f, Nint = %d, Nfrac = %d, DIV_LOCH_SX = %d, SEL_VCO = %d, fvco = %f MHz\n", fdiv, Ndiv, Nint, Nfrac, DIV_LOCH_SX, SEL_VCO, fvco/1e6);
    LMS7002M_regs_spi_write(self, 0x011d);
    LMS7002M_regs_spi_write(self, 0x011e);

    //program the feedback divider
    self->regs.reg_0x011f_sel_sdmclk = REG_0X011F_SEL_SDMCLK_CLK_DIV;
    self->regs.reg_0x011f_div_loch = DIV_LOCH_SX;
    LMS7002M_regs_spi_write(self, 0x011f);

    //select vco based on freq
    self->regs.reg_0x0121_sel_vco = SEL_VCO;
    LMS7002M_regs_spi_write(self, 0x0121);

    //select the correct CSW for this VCO frequency
    self->regs.reg_0x0121_csw_vco = 0;
    for (int i = 7; i >= 0; i--)
    {
        self->regs.reg_0x0121_csw_vco |= 1 << i;
        LMS7002M_regs_spi_write(self, 0x0121);
        LMS7002M_regs_spi_read(self, 0x0123);
        //printf("i=%d, hi=%d, lo=%d\n", i, self->regs.reg_0x0123_vco_cmpho, self->regs.reg_0x0123_vco_cmplo);
        if (self->regs.reg_0x0123_vco_cmpho != 0 || self->regs.reg_0x0123_vco_cmplo != 0)
        {
            self->regs.reg_0x0121_csw_vco &= ~(1 << i); //clear bit i
        }
        LMS7002M_regs_spi_write(self, 0x0121);
    }
    self->regs.reg_0x011c_spdup_vco = 0; //done with fast settling
    LMS7002M_regs_spi_write(self, 0x011c);

    //calculate the actual rate
    if (factual != NULL) *factual = ((1 << EN_DIV2)/2.0) * fref * ((Nint+4) + (Nfrac/double(1 << 20))) / fdiv;

    return 0; //OK
}

#ifdef __cplusplus
}
#endif
