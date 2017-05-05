///
/// \file LMS7002M_ldo.c
///
/// LDO config for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2016 Fairwaves, Inc.
/// Copyright (c) 2015-2016 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include "LMS7002M_impl.h"

void LMS7002M_ldo_enable(LMS7002M_t *self, const bool enable, const int group)
{
    //LDO is a global register space
    LMS7002M_set_mac_ch(self, LMS_CHAB);

    //TODO, we can implement more groups, for now only 1
    if (group != LMS7002M_LDO_ALL) return;

    const int val = enable?1:0;

    self->regs->reg_0x0092_en_ldo_dig= val;
    self->regs->reg_0x0092_en_ldo_diggn= val;
    self->regs->reg_0x0092_en_ldo_digsxr= val;
    self->regs->reg_0x0092_en_ldo_digsxt= val;
    self->regs->reg_0x0092_en_ldo_divgn= val;
    self->regs->reg_0x0092_en_ldo_divsxr= val;
    self->regs->reg_0x0092_en_ldo_divsxt= val;
    self->regs->reg_0x0092_en_ldo_lna12= val;
    self->regs->reg_0x0092_en_ldo_lna14= val;
    self->regs->reg_0x0092_en_ldo_mxrfe= val;
    self->regs->reg_0x0092_en_ldo_rbb= val;
    self->regs->reg_0x0092_en_ldo_rxbuf= val;
    self->regs->reg_0x0092_en_ldo_tbb= val;
    self->regs->reg_0x0092_en_ldo_tia12= val;
    self->regs->reg_0x0092_en_ldo_tia14= val;
    self->regs->reg_0x0092_en_g_ldo= val;

    self->regs->reg_0x0093_en_ldo_afe= val;
    self->regs->reg_0x0093_en_ldo_cpgn= val;
    self->regs->reg_0x0093_en_ldo_cpsxr= val;
    self->regs->reg_0x0093_en_ldo_tlob= val;
    self->regs->reg_0x0093_en_ldo_tpad= val;
    self->regs->reg_0x0093_en_ldo_txbuf= val;
    self->regs->reg_0x0093_en_ldo_vcogn= val;
    self->regs->reg_0x0093_en_ldo_vcosxr= val;
    self->regs->reg_0x0093_en_ldo_vcosxt= val;
    self->regs->reg_0x0093_en_ldo_cpsxt= val;

    self->regs->reg_0x00a6_en_g_ldop = 1;
    self->regs->reg_0x00a6_pd_ldo_digip1 = enable?0:1;
    self->regs->reg_0x00a6_pd_ldo_digip2 = enable?0:1;
    self->regs->reg_0x00a6_pd_ldo_spibuf = enable?0:1;

    LMS7002M_regs_spi_write(self, 0x0092);
    LMS7002M_regs_spi_write(self, 0x0093);
    LMS7002M_regs_spi_write(self, 0x00a6);
}
