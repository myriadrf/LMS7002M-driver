///
/// \file LMS7002M_dccal.c
///
/// Analog DC calibrations the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2018-2018 Skylark Wireless
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include "LMS7002M_impl.h"
#include <LMS7002M/LMS7002M_time.h>

int LMS7002M_dc_cal(LMS7002M_t *self, const LMS7002M_dir_t direction, const LMS7002M_chan_t channel)
{
    if (direction == LMS_RX)
    {
        LMS7002M_trf_enable(self, channel, false);
        LMS7002M_rxtsp_set_dc_correction(self, channel, false, 0);

        //these regs are global register space
        LMS7002M_set_mac_ch(self, LMS_CHAB);
        self->regs->reg_0x05c0_dcmode = 1;
        LMS7002M_spi_write(self, 0x05c2, 0xff00); //invert cmp, and zero cal start
        if (channel == LMS_CHA)
        {
            self->regs->reg_0x05c0_pd_dcdac_rxa = 0;
            self->regs->reg_0x05c0_pd_dccmp_rxa = 0;
            self->regs->reg_0x05c2_dccal_start_rxai = 1;
            self->regs->reg_0x05c2_dccal_start_rxaq = 1;
        }
        if (channel == LMS_CHB)
        {
            self->regs->reg_0x05c0_pd_dcdac_rxb = 0;
            self->regs->reg_0x05c0_pd_dccmp_rxb = 0;
            self->regs->reg_0x05c2_dccal_start_rxbi = 1;
            self->regs->reg_0x05c2_dccal_start_rxbq = 1;
        }
        LMS7002M_regs_spi_write(self, 0x05c0);
        LMS7002M_regs_spi_write(self, 0x05c2);

        //wait for completion
        bool cal_running = true;
        for (size_t i = 0; i < 100; i++)
        {
            LMS7_sleep_for(LMS7_time_tps()/1000); //1 ms -> ticks
            cal_running = (LMS7002M_spi_read(self, 0x05c1) & 0xf000) != 0;
            if (!cal_running) break;
        }

        //restore
        LMS7002M_trf_enable(self, channel, true);
        LMS7002M_rxtsp_set_dc_correction(self, channel, true, 7);

        if (cal_running) return -2;
    }
    return 0;
}
