///
/// \file LMS7002M_vco.h
///
/// Generalized VCO tuning algorithms
///
/// \copyright
/// Copyright (c) 2016-2016 Skylark Wireless
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#pragma once
#include <LMS7002M/LMS7002M.h>

int LMS7002M_tune_vco(
    LMS7002M_t *self,
    int *vco_csw_reg,
    const int vco_csw_addr,
    int *vco_cmpho_reg,
    int *vco_cmplo_reg,
    const int vco_cmp_addr
);
