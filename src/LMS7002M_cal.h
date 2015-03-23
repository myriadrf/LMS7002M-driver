///
/// \file LMS7002M_cal.h
///
/// Calibration algorithms for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include <stdlib.h>
#include "LMS7002M_impl.h"

#define CAL_BACKUP_SIZE 20
void Save_config_CAL(LMS7002M_t *self, int *backup);
void Restore_config_CAL(LMS7002M_t *self, int *backup);

int Get_SPI_Reg_bits(LMS7002M_t *self, const int addr, const int bitHigh, const int bitLow);
void Modify_SPI_Reg_bits(LMS7002M_t *self, const int addr, const int bitHigh, const int bitLow, const int value);
void Resistor_calibration(LMS7002M_t *self, float *ratio);

void Algorithm_A_RBB(LMS7002M_t *self, const LMS7002M_chan_t ch);
unsigned char Algorithm_B_RBB(LMS7002M_t *self, unsigned short *LowFreqAmp, const LMS7002M_chan_t ch);
void Set_cal_path_RBB(LMS7002M_t *self, const int path);
void Set_NCO_Freq(LMS7002M_t *self, const double freq, const LMS7002M_chan_t ch);
unsigned char Algorithm_F_RBB(LMS7002M_t *self, unsigned char Band_id, unsigned short LowFreqAmp, const LMS7002M_chan_t ch);

void Algorithm_A_TBB(LMS7002M_t *self);
static inline  unsigned char Algorithm_B_TBB(LMS7002M_t *self, unsigned short *LowFreqAmp, const LMS7002M_chan_t ch)
{
    return Algorithm_B_RBB(self, LowFreqAmp, ch);
}
unsigned char Algorithm_C_TBB(LMS7002M_t *self, unsigned char Band_id, unsigned short LowFreqAmp, const LMS7002M_chan_t ch);
unsigned char Algorithm_D_TBB(LMS7002M_t *self, unsigned char Band_id, unsigned short LowFreqAmp, const LMS7002M_chan_t ch);
unsigned char Algorithm_E_TBB(LMS7002M_t *self, unsigned char Band_id, const LMS7002M_chan_t ch);
