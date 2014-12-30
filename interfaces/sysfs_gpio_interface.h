///
/// \file sysfs_gpio_interface.h
///
/// A SPI transaction interface through linux GPIO.
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

/*!
 * Configuration values for the sysfs GPIO interface.
 * Specifies GPIO indexes for 4-wire SPI mode.
 */
typedef struct
{
    int mosi;
    int miso;
    int sclk;
    int sen;
} sysfs_gpio_config_t;

/*!
 * Initialize a GPIO interface given the sysfs GPIO indexes.
 * The result is the handle to pass into LMS7002M_create().
 * \param config the configuration struct with GPIO indexes
 * \return the transaction handle or NULL for error
 */
static inline void *sysfs_gpio_interface_open(const sysfs_gpio_config_t *config);

/*!
 * Close an open sysfs GPIO interface using the handle.
 */
static inline void sysfs_gpio_interface_close(void *handle);

/*!
 * The SPI transaction implementation - pass this to LMS7002M_create().
 */
static inline uint32_t sysfs_gpio_interface_transact(void *handle, const uint32_t data, const bool readback);

/***********************************************************************
 * Implementation details below
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xilinx_user_gpio.h"

static inline void *sysfs_gpio_interface_open(const sysfs_gpio_config_t *config)
{
    int ret = 0;

    //export makes available
    ret |= gpio_export(config->mosi);
    ret |= gpio_export(config->miso);
    ret |= gpio_export(config->sclk);
    ret |= gpio_export(config->sen);

    //set direction
    ret |= gpio_set_dir(config->mosi, 1);
    ret |= gpio_set_dir(config->miso, 0);
    ret |= gpio_set_dir(config->sclk, 1);
    ret |= gpio_set_dir(config->sen, 1);

    //set idle state
    ret |= gpio_set_value(config->sen, 1);
    ret |= gpio_set_value(config->sclk, 0);

    if (ret != 0) return NULL;

    void *handle = malloc(sizeof(sysfs_gpio_config_t));
    memcpy(handle, config, sizeof(sysfs_gpio_config_t));
    return handle;
}

static inline void sysfs_gpio_interface_close(void *handle)
{
    sysfs_gpio_config_t *config = (sysfs_gpio_config_t *)handle;

    //all inputs
    gpio_set_dir(config->mosi, 0);
    gpio_set_dir(config->miso, 0);
    gpio_set_dir(config->sclk, 0);
    gpio_set_dir(config->sen, 0);

    //unexport all
    gpio_unexport(config->mosi);
    gpio_unexport(config->miso);
    gpio_unexport(config->sclk);
    gpio_unexport(config->sen);

    free(config);
}

static inline uint32_t sysfs_gpio_interface_transact(void *handle, const uint32_t data, const bool readback)
{
    sysfs_gpio_config_t *config = (sysfs_gpio_config_t *)handle;

    uint32_t out = 0;

    //drop the enable line to begin transaction
    gpio_set_value(config->sen, 0);

    for (int bit = 31; bit >= 0; bit--)
    {
        //set the data out
        gpio_set_value(config->mosi, (data >> bit) & 0x1);

        //rising edge of the clock
        gpio_set_value(config->sclk, 1);

        //read the data in
        int val = 0;
        if (readback) gpio_get_value(config->miso, &val);
        out |= (((uint32_t)val) << bit);

        //falling edge of the clock
        gpio_set_value(config->sclk, 0);
    }

    //restore the enable to end the transaction
    gpio_set_value(config->sen, 1);

    return out;
}
