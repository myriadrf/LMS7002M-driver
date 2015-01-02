///
/// \file LMS7002M/LMS7002M_lml.h
///
/// Lime-light config for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2014-2015 Fairwaves, Inc.
/// Copyright (c) 2014-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#pragma once
#include <stdlib.h>
#include <LMS7002M/LMS7002M.h>

#ifdef __cplusplus
extern "C" {
#endif

LMS7002M_API void LMS7002M_reset(LMS7002M_t *self)
{
    LMS7002M_spi_write(self, 0x0020, 0x0);
    LMS7002M_regs_spi_write(self, 0x0020);
}

LMS7002M_API void LMS7002M_power_down(LMS7002M_t *self)
{
    self->regs.reg_0x0020_rxen_a = 0;
    self->regs.reg_0x0020_rxen_b = 0;
    self->regs.reg_0x0020_txen_a = 0;
    self->regs.reg_0x0020_txen_b = 0;
    LMS7002M_regs_spi_write(self, 0x0020);
}

#ifdef __cplusplus
}
#endif
