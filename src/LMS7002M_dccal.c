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
#include <LMS7002M/LMS7002M_logger.h>

void LMS7002M_dc_cal_enable(LMS7002M_t *self, const LMS7002M_dir_t direction, const LMS7002M_chan_t channel, const bool enable)
{
    //these regs are global register space
    LMS7002M_set_mac_ch(self, LMS_CHAB);
    self->regs->reg_0x05c0_dcmode = REG_0X05C0_DCMODE_AUTOMATIC;
    if (direction == LMS_RX && channel == LMS_CHA)
    {
        self->regs->reg_0x05c0_pd_dcdac_rxa = enable?0:1;
        self->regs->reg_0x05c0_pd_dccmp_rxa = enable?0:1;
    }
    if (direction == LMS_RX && channel == LMS_CHB)
    {
        self->regs->reg_0x05c0_pd_dcdac_rxb = enable?0:1;
        self->regs->reg_0x05c0_pd_dccmp_rxb = enable?0:1;
    }
    if (direction == LMS_TX && channel == LMS_CHA)
    {
        self->regs->reg_0x05c0_pd_dcdac_txa = enable?0:1;
        self->regs->reg_0x05c0_pd_dccmp_txa = enable?0:1;
    }
    if (direction == LMS_TX && channel == LMS_CHB)
    {
        self->regs->reg_0x05c0_pd_dcdac_txb = enable?0:1;
        self->regs->reg_0x05c0_pd_dccmp_txb = enable?0:1;
    }
    LMS7002M_regs_spi_write(self, 0x05c0);
}

/*
int LMS7002M_dc_cal(LMS7002M_t *self, const LMS7002M_dir_t direction, const LMS7002M_chan_t channel)
{
    //these regs are global register space
    LMS7002M_set_mac_ch(self, LMS_CHAB);
    self->regs->reg_0x05c0_dcmode = REG_0X05C0_DCMODE_AUTOMATIC;
    LMS7002M_spi_write(self, 0x05c2, 0xff00); //invert cmp, and zero cal start

    if (direction == LMS_RX && channel == LMS_CHA)
    {
        self->regs->reg_0x05c0_pd_dcdac_rxa = 0;
        self->regs->reg_0x05c0_pd_dccmp_rxa = 0;
        self->regs->reg_0x05c2_dccal_start_rxai = 1;
        self->regs->reg_0x05c2_dccal_start_rxaq = 1;
    }
    if (direction == LMS_RX && channel == LMS_CHB)
    {
        self->regs->reg_0x05c0_pd_dcdac_rxb = 0;
        self->regs->reg_0x05c0_pd_dccmp_rxb = 0;
        self->regs->reg_0x05c2_dccal_start_rxbi = 1;
        self->regs->reg_0x05c2_dccal_start_rxbq = 1;
    }
    if (direction == LMS_TX && channel == LMS_CHA)
    {
        self->regs->reg_0x05c0_pd_dcdac_txa = 0;
        self->regs->reg_0x05c0_pd_dccmp_txa = 0;
        self->regs->reg_0x05c2_dccal_start_txai = 1;
        self->regs->reg_0x05c2_dccal_start_txaq = 1;
    }
    if (direction == LMS_TX && channel == LMS_CHB)
    {
        self->regs->reg_0x05c0_pd_dcdac_txb = 0;
        self->regs->reg_0x05c0_pd_dccmp_txb = 0;
        self->regs->reg_0x05c2_dccal_start_txbi = 1;
        self->regs->reg_0x05c2_dccal_start_txbq = 1;
    }
    LMS7002M_regs_spi_write(self, 0x05c0);
    LMS7002M_regs_spi_write(self, 0x05c2);

    if (direction == LMS_RX)
    {
        LMS7002M_trf_enable(self, channel, false);
        LMS7002M_rxtsp_set_dc_correction(self, channel, false, 0);
        LMS7002M_set_mac_ch(self, LMS_CHAB);

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
*/

static int dc_val_addr(const LMS7002M_dir_t direction, const LMS7002M_chan_t channel, const bool real)
{
    int ofs = 0;
    if (!real) ofs += 1;
    if (channel == LMS_CHB)  ofs += 2;
    if (direction == LMS_RX) ofs += 4;
    return ofs + 0x05C3;
}

double LMS7002M_dc_cal_read(
    LMS7002M_t *self,
    const LMS7002M_dir_t direction,
    const LMS7002M_chan_t channel,
    const bool real)
{
    //these regs are global register space
    LMS7002M_set_mac_ch(self, LMS_CHAB);
    const int addr = dc_val_addr(direction, channel, real);
    const int mask = (direction == LMS_RX)?0x3f:0x3ff;
    const int smask = (mask << 1) & (~mask);

    int val = LMS7002M_spi_read(self, addr);

    //trigger a read 0->1
    LMS7002M_spi_write(self, addr, val & ~(1 << 14));
    LMS7002M_spi_write(self, addr, val | (1 << 14));

    //read the value from the register
    val = LMS7002M_spi_read(self, addr);
    const int sign = (val & smask) != 0;
    const int mag = val & mask;

    //convert into a 1.0 scaled float
    double out = mag; //to float
    if (sign != 0) out *= -1; //sign
    return out/(mask); //scale
}

void LMS7002M_dc_cal_write(
    LMS7002M_t *self,
    const LMS7002M_dir_t direction,
    const LMS7002M_chan_t channel,
    const bool real,
    const double val)
{
    //these regs are global register space
    LMS7002M_set_mac_ch(self, LMS_CHAB);
    const int addr = dc_val_addr(direction, channel, real);
    const int mask = (direction == LMS_RX)?0x3f:0x3ff;
    const int smask = (mask << 1) & (~mask);

    //convert into sign and magnitude
    const int scaled = (int)(val*(mask));
    const int sign = (scaled < 0)?smask:0;
    const int mag = sign?(-scaled):scaled;

    //trigger a write 0->1
    LMS7002M_spi_write(self, addr, mag | sign);
    LMS7002M_spi_write(self, addr, mag | sign | (1 << 15));
}
