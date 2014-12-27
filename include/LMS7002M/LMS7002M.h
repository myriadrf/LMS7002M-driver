#pragma once

#define LMS7002M_API

/*!
 * Function typedef for a function that implements SPI register writes.
 * The data is the same pointer that the user passed into the driver instance.
 * Example: the data may be a pointer to a /dev/spiXX file descriptor
 *
 * \param data user provided data
 * \param addr the register address
 * \param value the new register value
 */
typedef void (*LMS7002M_spi_write_reg_t)(void *data, int addr, int value);

/*!
 * Function typedef for a function that implements SPI register reads.
 * The data is the same pointer that the user passed into the driver instance.
 * Example: the data may be a pointer to a /dev/spiXX file descriptor
 *
 * \param data user provided data
 * \param addr the register address
 * \return the register value
 */
typedef int (*LMS7002M_spi_read_reg_t)(void *data, int addr);

//! The opaque instance of the LMS7002M instance
struct LMS7002M_struct;

//! Helpful typedef for the LMS7002M driver instance
typedef LMS7002M_struct LMS7002M_t;

/*!
 * Create an instance of the LMS7002M driver.
 * This call does not reset or initialize the LMS7002M.
 * See LMS7002M_init(...) and LMS7002M_reset(...).
 *
 * \param write the SPI register write function
 * \param read the SPI register read function
 * \param data arbitrary user data for callbacks
 * \return a new instance of the LMS7002M driver
 */
LMS7002M_API LMS7002M_t *LMS7002M_create(LMS7002M_spi_write_reg_t write, LMS7002M_spi_read_reg_t read, void *data);

/*!
 * Destroy an instance of the LMS7002M driver.
 * This call simply fees the instance data,
 * it does not shutdown or have any effects on the chip.
 * Use the LMS7002M_powerdown(...) call before destroy().
 *
 * \param self an instance of the LMS7002M driver
 */
LMS7002M_API void LMS7002M_destroy(LMS7002M_t *self);
