///
/// \file LMS7002M/LMS7002M_impl.h
///
/// Implementation details for the LMS7002M C driver.
/// This file defines the LMS7002M_t structure,
/// and the SPI transaction helper functions.
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

/*!
 * Implementation of the LMS7002M data structure.
 * This is an opaque struct not available to the public API.
 */
struct LMS7002M_struct
{
    LMS7002M_spi_transact_t spi_transact;
    void *spi_transact_handle;
    LMS7002M_regs_t regs;
};

/***********************************************************************
 * Create/destroy implementations
 **********************************************************************/
LMS7002M_API LMS7002M_t *LMS7002M_create(LMS7002M_spi_transact_t transact, void *handle)
{
    LMS7002M_t *self = (LMS7002M_t *)malloc(sizeof(LMS7002M_t));
    if (self == NULL) return NULL;
    self->spi_transact = transact;
    self->spi_transact_handle = handle;
    LMS7002M_regs_init(&self->regs);
    return self;
}

LMS7002M_API void LMS7002M_destroy(LMS7002M_t *self)
{
    free(self);
}

/***********************************************************************
 * Helper calls to format SPI transactions
 **********************************************************************/
LMS7002M_API void LMS7002M_spi_write(LMS7002M_t *self, const int addr, const int value)
{
    uint32_t data = (((uint32_t)1) << 31) | (((uint32_t)addr) << 16) | (value & 0xffff);
    self->spi_transact(self->spi_transact_handle, data, false/*no readback*/);
}

LMS7002M_API int LMS7002M_spi_read(LMS7002M_t *self, const int addr)
{
    uint32_t data = (((uint32_t)addr) << 16);
    return self->spi_transact(self->spi_transact_handle, data, true/*readback*/) & 0xffff;
}

LMS7002M_API void LMS7002M_regs_spi_write(LMS7002M_t *self, const int addr)
{
    LMS7002M_spi_write(self, addr, LMS7002M_regs_get(&self->regs, addr));
}

LMS7002M_API void LMS7002M_regs_spi_write2(LMS7002M_t *self, const int addr, const int regAddr)
{
    LMS7002M_spi_write(self, addr, LMS7002M_regs_get(&self->regs, regAddr));
}

LMS7002M_API void LMS7002M_regs_spi_read(LMS7002M_t *self, const int addr)
{
    LMS7002M_regs_set(&self->regs, addr, LMS7002M_spi_read(self, addr));
}

LMS7002M_API LMS7002M_regs_t *LMS7002M_regs(LMS7002M_t *self)
{
    return &self->regs;
}

#ifdef __cplusplus
}
#endif

/***********************************************************************
 * Other implementation includes
 **********************************************************************/
#include <LMS7002M/LMS7002M_lml.h>
#include <LMS7002M/LMS7002M_cgen.h>
#include <LMS7002M/LMS7002M_nco.h>
#include <LMS7002M/LMS7002M_sxx.h>
#include <LMS7002M/LMS7002M_rxtsp.h>
