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

/*!
 * Sweep though the 7 lower CSW positions given a starting point.
 * This function is invoked twice to sweep upper and lower ranges.
 */
static int LMS7002M_tune_vco_sweep(
    LMS7002M_t *self,
    int *vco_csw_reg,
    const int vco_csw_addr,
    int *vco_cmpho_reg,
    int *vco_cmplo_reg,
    const int vco_cmp_addr,
    const int start_point,
    int *lo, int *hi
)
{
    int csw_lowest = start_point+128;
    *vco_csw_reg = start_point;
    for (int i = 6; i >= 0; i--)
    {
        *vco_csw_reg |= 1 << i;
        LMS7002M_regs_spi_write(self, vco_csw_addr);
        LMS7002M_read_vco_cmp(self, vco_cmp_addr);

        LMS7_logf(LMS7_DEBUG, "i=%d, hi=%d, lo=%d", i, *vco_cmpho_reg, *vco_cmplo_reg);
        if (*vco_cmplo_reg != 0)
        {
            *vco_csw_reg &= ~(1 << i); //clear bit i
        }
        if (*vco_cmpho_reg != 0 && *vco_cmplo_reg == 0 && *vco_csw_reg < csw_lowest)
        {
            csw_lowest = *vco_csw_reg;
        }
        LMS7002M_regs_spi_write(self, vco_csw_addr);
    }

    //find the midpoint for the high and low bounds
    int csw_highest = *vco_csw_reg;
    while (csw_lowest <= csw_highest && csw_lowest > start_point)
    {
        csw_lowest--;
        *vco_csw_reg = csw_lowest;
        LMS7002M_regs_spi_write(self, vco_csw_addr);
        LMS7002M_read_vco_cmp(self, vco_cmp_addr);

        if (*vco_cmpho_reg != 0 && *vco_cmplo_reg == 0) continue;
        csw_lowest++;
        break;
    }

    *lo = csw_lowest;
    *hi = csw_highest;
    LMS7_logf(LMS7_DEBUG, "lowest CSW_VCO %i, highest CSW_VCO %i", csw_lowest, csw_highest);
    return 0;
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
    //check comparator under minimum setting
    *vco_csw_reg = 0;
    LMS7002M_regs_spi_write(self, vco_csw_addr);
    LMS7002M_read_vco_cmp(self, vco_cmp_addr);
    if (*vco_cmpho_reg == 1 && *vco_cmplo_reg == 1)
    {
        LMS7_log(LMS7_ERROR, "VCO select FAIL - too high");
        return -1;
    }

    //check comparator under maximum setting
    *vco_csw_reg = 255;
    LMS7002M_regs_spi_write(self, vco_csw_addr);
    LMS7002M_read_vco_cmp(self, vco_cmp_addr);
    if (*vco_cmpho_reg == 0 && *vco_cmplo_reg == 0)
    {
        LMS7_log(LMS7_ERROR, "VCO select FAIL - too low");
        return -1;
    }

    //search both segments of the 8-bit space
    int lo0, hi0, lo1, hi1;
    LMS7002M_tune_vco_sweep(self, vco_csw_reg, vco_csw_addr, vco_cmpho_reg, vco_cmplo_reg, vco_cmp_addr, 0, &lo0, &hi0);
    LMS7002M_tune_vco_sweep(self, vco_csw_reg, vco_csw_addr, vco_cmpho_reg, vco_cmplo_reg, vco_cmp_addr, 128, &lo1, &hi1);

    //determine overall high-low with overlap
    int csw_lowest, csw_highest;
    if (hi0 == lo1-1)
    {
        csw_lowest = lo0;
        csw_highest = hi1;
    }

    //otherwise use bigger range
    else if ((hi0-lo0) > (hi1-lo1))
    {
        csw_lowest = lo0;
        csw_highest = hi0;
    }
    else
    {
        csw_lowest = lo1;
        csw_highest = hi1;
    }

    //set the midpoint of the search
    *vco_csw_reg = (csw_highest+csw_lowest)/2;
    LMS7002M_regs_spi_write(self, vco_csw_addr);
    LMS7_logf(LMS7_DEBUG, "lowest CSW_VCO %i, highest CSW_VCO %i, CSW_VCO %i", csw_lowest, csw_highest, *vco_csw_reg);

    //check that the vco selection was successful
    LMS7002M_read_vco_cmp(self, vco_cmp_addr);
    if (*vco_cmpho_reg != 0 && *vco_cmplo_reg == 0)
    {
        LMS7_log(LMS7_DEBUG, "VCO OK");
    }
    else
    {
        LMS7_log(LMS7_DEBUG, "VCO select FAIL");
        return -1;
    }
    return 0;
}
