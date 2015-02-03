///
/// \file LMS7002M/LMS7002M_nco.h
///
/// Numerically controlled oscillator hooks for the LMS7002M C driver.
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

LMS7002M_API void LMS7002M_set_nco_freq(LMS7002M_t *self, const LMS7002M_dir_t direction, const LMS7002M_chan_t channel, const double freqRel)
{
    LMS7002M_set_mac_ch(self, channel);

    self->regs.reg_0x0240_sel = 0; //table entry 0 will be used
    self->regs.reg_0x0240_mode = REG_0X0240_MODE_FCW;

    //load 32-bit frequency word into table entry 0
    uint32_t freqWord = (int32_t)(freqRel*4294967296.0);
    self->regs.reg_0x0242_fcw0_hi = freqWord >> 16;
    self->regs.reg_0x0243_fcw0_lo = freqWord & 0xffff;

    //write the registers
    const int addrTop = (direction==LMS_RX)?0x0400:0x0200;
    LMS7002M_regs_spi_write2(self, addrTop | 0x0040, 0x0240);
    LMS7002M_regs_spi_write2(self, addrTop | 0x0042, 0x0242);
    LMS7002M_regs_spi_write2(self, addrTop | 0x0043, 0x0243);
}

#ifdef __cplusplus
}
#endif
