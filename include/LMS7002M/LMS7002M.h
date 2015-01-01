///
/// \file LMS7002M/LMS7002M.h
///
/// Main interface header for LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2014-2015 Fairwaves, Inc.
/// Copyright (c) 2014-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <LMS7002M/LMS7002M_regs.h>

/*!
 * API export macro to declare linkage for driver functions:
 * We want to support including implementation headers for private use
 * or building this into a library -- so define LMS7002M_API accordingly.
 */
#ifndef LMS7002M_API
#define LMS7002M_API static inline
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Function typedef for a function that implements SPI register transactions.
 * The handle is the same pointer that the handle passed into the driver instance.
 * Example: the data may be a pointer to a /dev/spiXX file descriptor
 *
 * The readback option supplied by the driver specifies whether or not
 * it requires the result of the spi transaction to be returned.
 * The implementor of this function can use the readback parameter
 * to implement non-blocking spi transactions (as an optimization).
 *
 * \param handle handle provided data
 * \param data the 32-bit write data
 * \param readback true to readback
 * \return the 32-bit readback data
 */
typedef uint32_t (*LMS7002M_spi_transact_t)(void *handle, const uint32_t data, const bool readback);

//! The opaque instance of the LMS7002M instance
struct LMS7002M_struct;

//! Helpful typedef for the LMS7002M driver instance
typedef struct LMS7002M_struct LMS7002M_t;

/*!
 * Create an instance of the LMS7002M driver.
 * This call does not reset or initialize the LMS7002M.
 * See LMS7002M_init(...) and LMS7002M_reset(...).
 *
 * \param transact the SPI transaction function
 * \param handle arbitrary handle data for transact
 * \return a new instance of the LMS7002M driver
 */
LMS7002M_API LMS7002M_t *LMS7002M_create(LMS7002M_spi_transact_t transact, void *handle);

/*!
 * Destroy an instance of the LMS7002M driver.
 * This call simply fees the instance data,
 * it does not shutdown or have any effects on the chip.
 * Use the LMS7002M_power_down(...) call before destroy().
 *
 * \param self an instance of the LMS7002M driver
 */
LMS7002M_API void LMS7002M_destroy(LMS7002M_t *self);

/*!
 * Perform a SPI write transaction on the given device.
 * This call can be used directly to access SPI registers,
 * rather than indirectly through the high level driver calls.
 * \param self an instance of the LMS7002M driver
 * \param addr the 16 bit register address
 * \param value the 16 bit register value
 */
LMS7002M_API void LMS7002M_spi_write(LMS7002M_t *self, const int addr, const int value);

/*!
 * Perform a SPI read transaction on the given device.
 * This call can be used directly to access SPI registers,
 * rather than indirectly through the high level driver calls.
 * \param self an instance of the LMS7002M driver
 * \param addr the 16 bit register address
 * \return the 16 bit register value
 */
LMS7002M_API int LMS7002M_spi_read(LMS7002M_t *self, const int addr);

/*!
 * Write a spi register using values from the regs structure.
 * \param self an instance of the LMS7002M driver
 * \param addr the 16 bit register address
 */
LMS7002M_API void LMS7002M_regs_spi_write(LMS7002M_t *self, const int addr);

/*!
 * Read a spi register, filling in the fields in the regs structure.
 * \param self an instance of the LMS7002M driver
 * \param addr the 16 bit register address
 */
LMS7002M_API void LMS7002M_regs_spi_read(LMS7002M_t *self, const int addr);

/*!
 * Get access to the registers structure and unpacked fields.
 * Use LMS7002M_regs_spi_write()/LMS7002M_regs_spi_read()
 * to sync the fields in this structure with the device.
 * \param self an instance of the LMS7002M driver
 * \return the pointer to the unpacked LMS7002M fields
 */
LMS7002M_API LMS7002M_regs_t *LMS7002M_regs(LMS7002M_t *self);

/*!
 * Perform all soft and hard resets available.
 * Call this first to put the LMS7002M into a known state.
 * \param self an instance of the LMS7002M driver
 */
LMS7002M_API void LMS7002M_reset(LMS7002M_t *self);

/*!
 * Put all available hardware into disable/power-down mode.
 * Call this last before destroying the LMS7002M instance.
 * \param self an instance of the LMS7002M driver
 */
LMS7002M_API void LMS7002M_power_down(LMS7002M_t *self);

#ifdef __cplusplus
}
#endif
