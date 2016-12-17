///
/// \file LMS7002M_vco.c
///
/// Generalized VCO tuning algorithms
///
/// \copyright
/// Copyright (c) 2016-2016 Skylark Wireless
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include <stdlib.h>
#include "LMS7002M_impl.h"
#include "LMS7002M_vco.h"
#include <LMS7002M/LMS7002M_time.h>
#include <LMS7002M/LMS7002M_logger.h>

static void LMS7002M_read_vco_cmp(LMS7002M_t *self, const int vco_cmp_addr)
{
    //an initial read forces spi writes to be flushed
    //any read will do, the address does not matter
    LMS7002M_regs_spi_read(self, vco_cmp_addr);

    //sleep while the comparator value settles
    LMS7_sleep_for(LMS7_time_tps()/1000); //1 ms -> ticks

    //final read of the comparator after settling
    LMS7002M_regs_spi_read(self, vco_cmp_addr);
}

int LMS7002M_tune_vco(
    LMS7002M_t *self,
    int *vco_csw_reg,
    const int vco_csw_addr,
    int *vco_cmpho_reg,
    int *vco_cmplo_reg,
    const int vco_cmp_addr
)
{
    int csw_lowest = -1;
    *vco_csw_reg = 0;
    for (int i = 7; i >= 0; i--)
    {
        *vco_csw_reg |= 1 << i;
        LMS7002M_regs_spi_write(self, vco_csw_addr);
        LMS7002M_read_vco_cmp(self, vco_cmp_addr);

        LMS7_logf(LMS7_DEBUG, "i=%d, hi=%d, lo=%d", i, *vco_cmpho_reg, *vco_cmplo_reg);
        if (*vco_cmplo_reg != 0)
        {
            *vco_csw_reg &= ~(1 << i); //clear bit i
        }
        if (*vco_cmpho_reg != 0 && *vco_cmplo_reg == 0 && csw_lowest < 0)
        {
            csw_lowest = *vco_csw_reg;
        }
        LMS7002M_regs_spi_write(self, vco_csw_addr);
    }

    //find the midpoint for the high and low bounds
    if (csw_lowest >= 0)
    {
        int csw_highest = *vco_csw_reg;
        if (csw_lowest == csw_highest)
        {
            while (csw_lowest >= 0)
            {
                *vco_csw_reg = csw_lowest;
                LMS7002M_regs_spi_write(self, vco_csw_addr);
                LMS7002M_read_vco_cmp(self, vco_cmp_addr);

                if (*vco_cmpho_reg == 0 && *vco_cmplo_reg == 0) break;
                else csw_lowest--;
            }
            if (csw_lowest < 0) csw_lowest = 0;
        }
        csw_lowest += 1;

        LMS7_logf(LMS7_INFO, "lowest CSW_VCO %i, highest CSW_VCO %i", csw_lowest, csw_highest);
        *vco_csw_reg = (csw_highest+csw_lowest)/2;
        LMS7002M_regs_spi_write(self, vco_csw_addr);
    }

    //check that the vco selection was successful
    LMS7002M_read_vco_cmp(self, vco_cmp_addr);
    if (*vco_cmpho_reg != 0 && *vco_cmplo_reg == 0)
    {
        LMS7_log(LMS7_INFO, "VCO OK");
    }
    else
    {
        LMS7_log(LMS7_ERROR, "VCO select FAIL");
        return -1;
    }
    return 0;
}
