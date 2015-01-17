///
/// \file LMS7002M/LMS7002M_cgen.h
///
/// Clock generation for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2014-2015 Fairwaves, Inc.
/// Copyright (c) 2014-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <LMS7002M/LMS7002M.h>

#ifdef __cplusplus
extern "C" {
#endif

LMS7002M_API int LMS7002M_set_data_clock(LMS7002M_t *self, const double fref, const double fout)
{
    //The equations:
    // fref * N = fvco
    // fvco / fdiv = fout
    // fref * N = fout * fdiv
    int fdiv = 0;
    double Ndiv = 0;
    double fvco = 0;

    //calculation loop to find dividers that are possible
    while (true)
    {
        //try the next even divider
        fdiv += 2;

        Ndiv = fout*fdiv/fref;
        fvco = fout*fdiv;
        //printf("fdiv = %d, fvco = %f MHz\n", fdiv, fvco/1e6);

        //check dividers and vco in range...
        if (fdiv > 512) return -1;
        if (Ndiv < 4) continue;
        if (Ndiv > 512) return -1;
        //these boundaries observed from the EVB7 GUI
        if (fvco < 2.6e9) continue;
        if (fvco > 2.7e9) continue;

        break; //its good
    }

    //configure and enable synthesizer
    self->regs.reg_0x0086_en_intonly_sdm_cgen = 0; //support frac-N
    self->regs.reg_0x0086_en_sdm_clk_cgen = 1; //enable
    self->regs.reg_0x0086_pd_cp_cgen = 0; //enable
    self->regs.reg_0x0086_pd_fdiv_fb_cgen = 0; //enable
    self->regs.reg_0x0086_pd_fdiv_o_cgen = 0; //enable
    self->regs.reg_0x0086_pd_sdm_cgen = 0; //enable
    self->regs.reg_0x0086_pd_vco_cgen = 0; //enable
    self->regs.reg_0x0086_pd_vco_comp_cgen = 0; //enable

    //coarse tuning algorithm
    self->regs.reg_0x0086_en_coarse_cklgen = 1;
    self->regs.reg_0x008b_coarse_start_cgen = 0;
    self->regs.reg_0x0086_en_intonly_sdm_cgen = 1;
    self->regs.reg_0x0086_spdup_vco_cgen = 1;
    self->regs.reg_0x008b_csw_vco_cgen = 0; //clear all 8 bits
    self->regs.reg_0x0087_frac_sdm_cgen = 0;
    self->regs.reg_0x0088_frac_sdm_cgen = 0;
    int Nround = (int)(4*fvco/fref+0.5); //Nround=round(4*Fvco_des/Fref)
    self->regs.reg_0x0088_int_sdm_cgen = Nround-4;
    LMS7002M_regs_spi_write(self, 0x0086);
    LMS7002M_regs_spi_write(self, 0x0087);
    LMS7002M_regs_spi_write(self, 0x0088);
    LMS7002M_regs_spi_write(self, 0x0089);
    LMS7002M_regs_spi_write(self, 0x008B);

    //loop through all 8 bits
    for (int i = 7; i >= 0; i--)
    {
        self->regs.reg_0x008b_csw_vco_cgen |= (1 << i); //set bit i
        self->regs.reg_0x008b_coarse_start_cgen = 1;
        LMS7002M_regs_spi_write(self, 0x008B);

        //finte loop to wait for stepdone
        for (size_t to = 0; to < 100; to++)
        {
            LMS7002M_regs_spi_read(self, 0x008C);
            if (self->regs.reg_0x008c_coarse_stepdone_cgen == 1) break;
        }

        //timeout failure
        if (self->regs.reg_0x008c_coarse_stepdone_cgen != 1) return -2;

        //react to result
        if (self->regs.reg_0x008c_coarsepll_compo_cgen == 1)
        {
            self->regs.reg_0x008b_csw_vco_cgen &= ~(1 << i); //clear bit i
        }
        self->regs.reg_0x008b_coarse_start_cgen = 0;
        LMS7002M_regs_spi_write(self, 0x008B);
    }

    //cleanup coarse tuning configuration
    self->regs.reg_0x0086_en_coarse_cklgen = 0;
    self->regs.reg_0x0086_en_intonly_sdm_cgen = 0;
    self->regs.reg_0x0086_spdup_vco_cgen = 0;
    self->regs.reg_0x0086_en_intonly_sdm_cgen = 0; //support frac-N
    LMS7002M_regs_spi_write(self, 0x0086);

    //program the N divider
    const int Nint = (int)Ndiv;
    const int Nfrac = (int)((Ndiv-Nint)*(1 << 20));
    self->regs.reg_0x0087_frac_sdm_cgen = (Nfrac-1) & 0xffff; //lower 16 bits
    self->regs.reg_0x0088_frac_sdm_cgen = (Nfrac-1) >> 16; //upper 4 bits
    self->regs.reg_0x0088_int_sdm_cgen = Nint-1;
    //printf("fdiv = %d, Ndiv = %f, Nint = %d, Nfrac = %d, fvco = %f MHz\n", fdiv, Ndiv, Nint, Nfrac, fvco/1e6);
    LMS7002M_regs_spi_write(self, 0x0087);
    LMS7002M_regs_spi_write(self, 0x0088);

    //program the feedback divider
    self->regs.reg_0x0089_sel_sdmclk_cgen = REG_0X0089_SEL_SDMCLK_CGEN_CLK_DIV;
    self->regs.reg_0x0089_div_outch_cgen = (fdiv/2)-1;
    LMS7002M_regs_spi_write(self, 0x0089);

    return 0; //OK
}

#ifdef __cplusplus
}
#endif
