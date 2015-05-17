///
/// \file LMS7002M_impl.h
///
/// Implementation struct for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2014-2015 Fairwaves, Inc.
/// Copyright (c) 2014-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#pragma once
#include <LMS7002M/LMS7002M.h>

enum {MIMO_A, MIMO_B, MIMO_BOTH};

enum {//RBB Band_id
	RBB_1_4MHZ, RBB_3_0MHZ, RBB_5_0MHZ, RBB_10_0MHZ, RBB_15_0MHZ, RBB_20MHZ, //Low Band
	RBB_37_0MHZ, RBB_66_0MHZ, RBB_108_0MHZ, //High Band
	RBB_ALL
};

enum {//TBB Band_id
	TBB_11_0MHZ,//Low Band //not all
	TBB_18_5MHZ, TBB_38_0MHZ, TBB_54_0MHZ, //High Band
	TBB_ALL
};

/*!
 * Implementation of the LMS7002M data structure.
 * This is an opaque struct not available to the public API.
 */
struct LMS7002M_struct
{
    LMS7002M_spi_transact_t spi_transact;
    void *spi_transact_handle;
    LMS7002M_regs_t regs;

    double cgen_freq; //!< last written CGEN frequency in Hz
    double sxr_freq; //!< last written RX frequency in Hz
    double sxt_freq; //!< last written TX frequency in Hz

    double cgen_fref; //!< last written CGEN ref frequency in Hz
    double sxr_fref; //!< last written RX ref frequency in Hz
    double sxt_fref; //!< last written TX ref frequency in Hz

    //Calibrated and corrected control values
    unsigned short RBB_CBANK[MIMO_BOTH][RBB_ALL];
    unsigned char RBB_RBANK[MIMO_BOTH], TBB_CBANK[MIMO_BOTH], TBB_RBANK[MIMO_BOTH][TBB_ALL];
    unsigned char MIMO_ch;
};
