///
/// \file LMS7002M/LMS7002M_rbb.h
///
/// RX baseband controls for the LMS7002M C driver.
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
#include <math.h> //pow

#ifdef __cplusplus
extern "C" {
#endif

LMS7002M_API void LMS7002M_rbb_select_input(LMS7002M_t *self, const LMS7002M_chan_t channel, const int path)
{
    LMS7002M_set_mac_ch(self, channel);

    self->regs.reg_0x0115_en_g_rbb = 1; //individual controls
    self->regs.reg_0x0115_pd_lpfh_rbb = 1;
    self->regs.reg_0x0115_pd_lpfl_rbb = 1;
    self->regs.reg_0x0115_pd_pga_rbb = 0;
    self->regs.reg_0x0115_en_lb_lpfh_rbb = 0;
    self->regs.reg_0x0115_en_lb_lpfl_rbb = 0;

    switch (path)
    {
    case LMS7002M_RBB_NONE:
        self->regs.reg_0x0115_pd_pga_rbb = 1;
        break;

    case LMS7002M_RBB_BYP:
        self->regs.reg_0x0118_input_ctl_pga_rbb = REG_0X0118_INPUT_CTL_PGA_RBB_BYPASS;
        break;

    case LMS7002M_RBB_LPF:
        self->regs.reg_0x0115_pd_lpfl_rbb = 0;
        self->regs.reg_0x0115_en_lb_lpfl_rbb = 1;
        self->regs.reg_0x0118_input_ctl_pga_rbb = REG_0X0118_INPUT_CTL_PGA_RBB_LPFL;
        break;

    case LMS7002M_RBB_HPF:
        self->regs.reg_0x0115_pd_lpfh_rbb = 0;
        self->regs.reg_0x0115_en_lb_lpfh_rbb = 1;
        self->regs.reg_0x0118_input_ctl_pga_rbb = REG_0X0118_INPUT_CTL_PGA_RBB_LPFH;
        break;

    case LMS7002M_RBB_BYP_LB:
        self->regs.reg_0x0118_input_ctl_pga_rbb = REG_0X0118_INPUT_CTL_PGA_RBB_TX;
        break;

    case LMS7002M_RBB_LPF_LB:
        self->regs.reg_0x0115_pd_lpfl_rbb = 0;
        self->regs.reg_0x0115_en_lb_lpfl_rbb = 1;
        self->regs.reg_0x0118_input_ctl_pga_rbb = REG_0X0118_INPUT_CTL_PGA_RBB_LPFL;
        break;

    case LMS7002M_RBB_HPF_LB:
        self->regs.reg_0x0115_pd_lpfh_rbb = 0;
        self->regs.reg_0x0115_en_lb_lpfh_rbb = 1;
        self->regs.reg_0x0118_input_ctl_pga_rbb = REG_0X0118_INPUT_CTL_PGA_RBB_LPFH;
        break;
    }

    LMS7002M_regs_spi_write(self, 0x0115);
    LMS7002M_regs_spi_write(self, 0x0118);
}

LMS7002M_API void LMS7002M_rbb_set_pga(LMS7002M_t *self, const LMS7002M_chan_t channel, const double gain)
{
    LMS7002M_set_mac_ch(self, channel);

    int G_PGA_RBB = (int)(gain + 0.5);
    if (G_PGA_RBB > 0x1f) G_PGA_RBB = 0x1f;
    if (G_PGA_RBB < 0) G_PGA_RBB = 0;
    self->regs.reg_0x0119_g_pga_rbb = G_PGA_RBB;

    self->regs.reg_0x011a_rcc_ctl_pga_rbb = (430.0*pow(0.65, (G_PGA_RBB/10.0))-110.35)/20.4516 + 16;

    if (0 <= G_PGA_RBB && G_PGA_RBB < 8) self->regs.reg_0x011a_c_ctl_pga_rbb = 3;
    if (8 <= G_PGA_RBB && G_PGA_RBB < 13) self->regs.reg_0x011a_c_ctl_pga_rbb = 2;
    if (13 <= G_PGA_RBB && G_PGA_RBB < 21) self->regs.reg_0x011a_c_ctl_pga_rbb = 1;
    if (21 <= G_PGA_RBB) self->regs.reg_0x011a_c_ctl_pga_rbb = 0;

    LMS7002M_regs_spi_write(self, 0x0119);
    LMS7002M_regs_spi_write(self, 0x011A);
}

#ifdef __cplusplus
}
#endif
