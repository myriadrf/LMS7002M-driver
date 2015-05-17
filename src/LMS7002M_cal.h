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

void Modify_SPI_Reg_bits (LMS7002M_t *self, unsigned short SPI_reg_addr, unsigned char MSB_bit, unsigned char LSB_bit, unsigned short new_bits_data);
unsigned short Get_SPI_Reg_bits (LMS7002M_t *self, unsigned short SPI_reg_addr, unsigned char MSB_bit, unsigned char LSB_bit);

void MIMO_Ctrl (LMS7002M_t *self, unsigned char ch);
float Resistor_calibration (LMS7002M_t *self);
void Set_NCO_Freq (LMS7002M_t *self, float Freq_MHz, float refClk_MHz, bool Rx);

void Set_cal_path_RBB (LMS7002M_t *self, unsigned char path_no);
void Set_cal_path_TBB (LMS7002M_t *self, unsigned char path_no);
void Algorithm_A_RBB(LMS7002M_t *self);
unsigned short Algorithm_B_RBB(LMS7002M_t *self);
void Algorithm_F_RBB(LMS7002M_t *self, unsigned char Band_id);

void Algorithm_A_TBB(LMS7002M_t *self);
unsigned short Algorithm_B_TBB(LMS7002M_t *self);
void Algorithm_C_TBB(LMS7002M_t *self, unsigned char Band_id);
int Algorithm_D_TBB(LMS7002M_t *self, unsigned char Band_id);
void Algorithm_E_TBB(LMS7002M_t *self, unsigned char Band_id);

//RBB
int Calibration_LowBand_RBB (LMS7002M_t *self, unsigned char ch);
int Calibration_HighBand_RBB (LMS7002M_t *self, unsigned char ch);

//TBB
int Calibration_LowBand_TBB (LMS7002M_t *self, unsigned char ch);
int Calibration_HighBand_TBB (LMS7002M_t *self, unsigned char ch);
