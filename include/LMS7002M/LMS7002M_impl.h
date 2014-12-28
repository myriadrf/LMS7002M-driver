/*!
 * Implementation details for the LMS7002M C driver.
 * Probably split this into multiple headers later.
 */

#include <stdlib.h>

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
    void *spi_transact_user;
};

/***********************************************************************
 * Helper calls to format SPI transactions
 **********************************************************************/
LMS7002M_API void LMS7002M_spi_write(LMS7002M_t *self, const int addr, const int value)
{
    uint32_t data = (((uint32_t)1) << 31) | (((uint32_t)addr) << 16) | (value & 0xffff);
    self->spi_transact(self->spi_transact_user, data, false/*no readback*/);
}

LMS7002M_API int LMS7002M_spi_read(LMS7002M_t *self, const int addr)
{
    uint32_t data = (((uint32_t)addr) << 16);
    return self->spi_transact(self->spi_transact_user, data, true/*readback*/) & 0xffff;
}

/***********************************************************************
 * Create/destroy implementations
 **********************************************************************/
LMS7002M_API LMS7002M_t *LMS7002M_create(LMS7002M_spi_transact_t transact, void *user)
{
    LMS7002M_t *self = malloc(sizeof(LMS7002M_t));
    self->spi_transact = transact;
    self->spi_transact_user = user;
}

LMS7002M_API void LMS7002M_destroy(LMS7002M_t *self)
{
    free(self);
}

#ifdef __cplusplus
}
#endif
