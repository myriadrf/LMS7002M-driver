///
/// \file LMS7002M_xbuf.c
///
/// XBUF clock buffer config for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include "LMS7002M_impl.h"

void LMS7002M_xbuf_share_tx(LMS7002M_t *self, const bool enable)
{
    self->regs->reg_0x0085_en_out2_xbuf_tx = enable?1:0;
    self->regs->reg_0x0085_en_tbufin_xbuf_rx = enable?1:0;
    LMS7002M_regs_spi_write(self, 0x0085);
}

LMS7002M_API void LMS7002M_xbuf_enable_bias(LMS7002M_t *self, const bool enable)
{
    self->regs->reg_0x0085_slfb_xbuf_rx = enable?1:0;
    self->regs->reg_0x0085_slfb_xbuf_tx = enable?1:0;
    LMS7002M_regs_spi_write(self, 0x0085);
}
