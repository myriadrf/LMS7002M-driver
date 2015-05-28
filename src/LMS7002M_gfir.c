///
/// \file LMS7002M_gfir.c
///
/// FIR filter config for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include <stdlib.h>
#include "LMS7002M_impl.h"

int LMS7002M_set_gfir_taps(
    LMS7002M_t *self,
    const LMS7002M_dir_t direction,
    const LMS7002M_chan_t channel,
    const int which,
    const short *taps,
    const size_t ntaps)
{
    LMS7002M_set_mac_ch(self, channel);

    //bypass the filter for null/empty filter taps
    const bool bypass = (taps == NULL) || (ntaps == 0);
    if (direction == LMS_RX)
    {
        if (which == 1) self->regs->reg_0x040c_gfir1_byp = bypass?1:0;
        if (which == 2) self->regs->reg_0x040c_gfir2_byp = bypass?1:0;
        if (which == 3) self->regs->reg_0x040c_gfir3_byp = bypass?1:0;
        LMS7002M_regs_spi_write(self, 0x040c);
    }
    if (direction == LMS_TX)
    {
        if (which == 1) self->regs->reg_0x0208_gfir1_byp = bypass?1:0;
        if (which == 2) self->regs->reg_0x0208_gfir2_byp = bypass?1:0;
        if (which == 3) self->regs->reg_0x0208_gfir3_byp = bypass?1:0;
        LMS7002M_regs_spi_write(self, 0x0208);
    }

    //bypass programed, skip writing taps
    if (bypass) return 0;

    //bounds check
    if (which < 1) return -1;
    if (which > 3) return -1;
    if (which == 1 && ntaps != 5*8) return -2;
    if (which == 2 && ntaps != 5*8) return -2;
    if (which == 3 && ntaps != 3*5*8) return -2;

    //taps configuration logic from LMS7002_MainControl::LoadGFIRCoefficients
    if (which == 1)
    {
        int addr = (direction == LMS_RX)?0x0480:0x0280;
        for (int k=0; k<5; ++k)
        {
            for (int i=0; i<8; ++i)
            {
                LMS7002M_spi_write(self, addr, taps[k*8+i]);
                ++addr;
            }
        }
    }
    else if (which == 2)
    {
        int addr = (direction == LMS_RX)?0x04c0:0x02c0;
        for (int k=0; k<5; ++k)
        {
            for (int i=0; i<8; ++i)
            {
                LMS7002M_spi_write(self, addr, taps[k*8+i]);
                ++addr;
            }
        }
    }
    else if (which == 3)
    {
        int addr = (direction == LMS_RX)?0x0500:0x0300;
        int coefIndex = 0;
        unsigned short coefValue = 0;
        for (int n=0; n<3; ++n)
        {
            for (int k=0; k<5; ++k)
            {
                for (int i=0; i<8; ++i)
                {
                    coefValue = taps[coefIndex];
                    ++coefIndex;

                    LMS7002M_spi_write(self, addr, coefValue);
                    ++addr;
                }
            }
            addr += 24; //skip reserved
        }
    }

    return 0; //OK
}
