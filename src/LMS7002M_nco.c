///
/// \file LMS7002M_nco.c
///
/// Numerically controlled oscillator hooks for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include <stdlib.h>
#include "LMS7002M_impl.h"

void LMS7002M_set_nco_freq(LMS7002M_t *self, const LMS7002M_dir_t direction, const LMS7002M_chan_t channel, const double freqRel)
{
    LMS7002M_set_mac_ch(self, channel);

    uint32_t freqWord = (int32_t)(freqRel*4294967296.0);
    const int freqHi = freqWord >> 16;
    const int freqLo = freqWord & 0xffff;

    if (direction == LMS_TX)
    {
        self->regs->reg_0x0240_sel = 0; //table entry 0 will be used
        self->regs->reg_0x0240_mode = REG_0X0240_MODE_FCW;

        //load 32-bit frequency word into table entry 0
        self->regs->reg_0x0242_fcw0_hi = freqHi;
        self->regs->reg_0x0243_fcw0_lo = freqLo;
    }

    if (direction == LMS_RX)
    {
        self->regs->reg_0x0440_sel = 0; //table entry 0 will be used
        self->regs->reg_0x0440_mode = REG_0X0440_MODE_FCW;

        //load 32-bit frequency word into table entry 0
        self->regs->reg_0x0442_fcw0_hi = freqHi;
        self->regs->reg_0x0443_fcw0_lo = freqLo;
    }

    //write the registers
    const int addrTop = (direction==LMS_RX)?0x0400:0x0200;
    LMS7002M_regs_spi_write(self, addrTop | 0x0040);
    LMS7002M_regs_spi_write(self, addrTop | 0x0042);
    LMS7002M_regs_spi_write(self, addrTop | 0x0043);
}
