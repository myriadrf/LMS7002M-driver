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

/*!
 * Implementation of the LMS7002M data structure.
 * This is an opaque struct not available to the public API.
 */
struct LMS7002M_struct
{
    LMS7002M_spi_transact_t spi_transact;
    void *spi_transact_handle;

    //register shadows per channel (actual data)
    LMS7002M_regs_t _regs[2];

    //active register shadow ptr based on MIMO channel setting
    LMS7002M_regs_t *regs;

    double cgen_freq; //!< last written CGEN frequency in Hz
    double sxr_freq; //!< last written RX frequency in Hz
    double sxt_freq; //!< last written TX frequency in Hz

    double cgen_fref; //!< last written CGEN ref frequency in Hz
    double sxr_fref; //!< last written RX ref frequency in Hz
    double sxt_fref; //!< last written TX ref frequency in Hz
};
