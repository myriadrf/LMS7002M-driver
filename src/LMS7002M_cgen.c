///
/// \file LMS7002M_cgen.c
///
/// Clock generation for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2014-2016 Fairwaves, Inc.
/// Copyright (c) 2014-2016 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include <stdlib.h>
#include "LMS7002M_impl.h"
#include "LMS7002M_vco.h"
#include <LMS7002M/LMS7002M_logger.h>

int LMS7002M_set_data_clock(LMS7002M_t *self, const double fref, const double fout, double *factual)
{
    LMS7_logf(LMS7_INFO, "CGEN tune %f MHz (fref=%f MHz) begin", fout/1e6, fref/1e6);

    //always use the channel A shadow, CGEN is in global register space
    LMS7002M_set_mac_ch(self, LMS_CHA);

    //The equations:
    // fref * N = fvco
    // fvco / fdiv = fout
    // fref * N = fout * fdiv
    int fdiv = 512+2;
    double Ndiv = 0;
    double fvco = 0;

    //calculation loop to find dividers that are possible
    while (true)
    {
        //try the next even divider
        fdiv -= 2;

        Ndiv = fout*fdiv/fref;
        fvco = fout*fdiv;
        LMS7_logf(LMS7_TRACE, "Trying: fdiv = %d, Ndiv = %f, fvco = %f MHz", fdiv, Ndiv, fvco/1e6);

        //check dividers and vco in range...
        if (fdiv < 2) return -1;
        if (fdiv > 512) continue;
        if (Ndiv < 4) return -1;
        if (Ndiv > 512) continue;

        //check vco boundaries
        if (fvco < LMS7002M_CGEN_VCO_LO) continue;
        if (fvco > LMS7002M_CGEN_VCO_HI) continue;

        break; //its good
    }
    LMS7_logf(LMS7_DEBUG, "Using: fdiv = %d, Ndiv = %f, fvco = %f MHz", fdiv, Ndiv, fvco/1e6);

    //stash the freq now that we know the loop above passed
    self->cgen_freq = fout;
    self->cgen_fref = fref;

    //usually these references are all the same frequency
    //setting the clock is a good time to initialize them
    //if they are not otherwise initialized by tuning the LO
    if (self->sxt_fref == 0.0) self->sxt_fref = fref;
    if (self->sxr_fref == 0.0) self->sxr_fref = fref;

    //reset
    self->regs->reg_0x0086_reset_n_cgen = 0;
    LMS7002M_regs_spi_write(self, 0x0086);
    self->regs->reg_0x0086_reset_n_cgen = 1;
    LMS7002M_regs_spi_write(self, 0x0086);

    //configure and enable synthesizer
    self->regs->reg_0x0086_en_intonly_sdm_cgen = 0; //support frac-N
    self->regs->reg_0x0086_en_sdm_clk_cgen = 1; //enable
    self->regs->reg_0x0086_pd_cp_cgen = 0; //enable
    self->regs->reg_0x0086_pd_fdiv_fb_cgen = 0; //enable
    self->regs->reg_0x0086_pd_fdiv_o_cgen = 0; //enable
    self->regs->reg_0x0086_pd_sdm_cgen = 0; //enable
    self->regs->reg_0x0086_pd_vco_cgen = 0; //enable
    self->regs->reg_0x0086_pd_vco_comp_cgen = 0; //enable
    self->regs->reg_0x0086_en_g_cgen = 1;
    self->regs->reg_0x0086_en_coarse_cklgen = 0;
    self->regs->reg_0x008b_coarse_start_cgen = 0;
    self->regs->reg_0x0086_spdup_vco_cgen = 1; //fast settling
    LMS7002M_regs_spi_write(self, 0x0086);

    //program the N divider
    const int Nint = (int)Ndiv;
    const int Nfrac = (int)((Ndiv-Nint)*(1 << 20));
    self->regs->reg_0x0087_frac_sdm_cgen = (Nfrac) & 0xffff; //lower 16 bits
    self->regs->reg_0x0088_frac_sdm_cgen = (Nfrac) >> 16; //upper 4 bits
    self->regs->reg_0x0088_int_sdm_cgen = Nint-1;
    LMS7_logf(LMS7_DEBUG, "fdiv = %d, Ndiv = %f, Nint = %d, Nfrac = %d, fvco = %f MHz", fdiv, Ndiv, Nint, Nfrac, fvco/1e6);
    LMS7002M_regs_spi_write(self, 0x0087);
    LMS7002M_regs_spi_write(self, 0x0088);

    //program the feedback divider
    self->regs->reg_0x0089_sel_sdmclk_cgen = REG_0X0089_SEL_SDMCLK_CGEN_CLK_DIV;
    self->regs->reg_0x0089_div_outch_cgen = (fdiv/2)-1;
    LMS7002M_regs_spi_write(self, 0x0089);

    //select the correct CSW for this VCO frequency
    if (LMS7002M_tune_vco(self,
        &self->regs->reg_0x008b_csw_vco_cgen, 0x008B,
        &self->regs->reg_0x008c_vco_cmpho_cgen,
        &self->regs->reg_0x008c_vco_cmplo_cgen, 0x008C) != 0)
    {
        LMS7_log(LMS7_ERROR, "VCO select FAIL");
        return -3;
    }

    self->regs->reg_0x0086_spdup_vco_cgen = 0; //done with fast settling
    LMS7002M_regs_spi_write(self, 0x0086);

    //calculate the actual rate
    if (factual != NULL) *factual = fref * (Nint + (Nfrac/((double)(1 << 20)))) / fdiv;

    return 0; //OK
}
