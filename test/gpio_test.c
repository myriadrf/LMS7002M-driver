//
// Test instantiating the LMS7002M through sysfs GPIO on linux
//
// Copyright (c) 2014-2015 Fairwaves, Inc.
// Copyright (c) 2014-2015 Rice University
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
//

#define MOSI_MIO 10
#define MISO_MIO 11
#define SCLK_MIO 12
#define SEN_MIO 13

#include <LMS7002M/LMS7002M.h>
#include <LMS7002M/LMS7002M_impl.h>

#include <stdio.h>
#include <stdlib.h>

#include "xilinx_user_gpio.h"

typedef struct
{
    int mosi;
    int miso;
    int sclk;
    int sen;
} my_sysgpio_config_t;

int my_sysgpio_setup(my_sysgpio_config_t *config)
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

    return ret;
}

void my_sysgpio_shutdown(my_sysgpio_config_t *config)
{
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
}

uint32_t my_sysgpio_transact(void *user, const uint32_t data, const bool readback)
{
    my_sysgpio_config_t *config = (my_sysgpio_config_t *)user;
    //printf("my_sysgpio_transact 0x%x   readback=%d   config->mosi=%d\n", data, readback, config->mosi);

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

int main(int argc, char **argv)
{
    printf("=========================================================\n");
    printf("== Test LMS7002M through syfs GPIO                       \n");
    printf("=========================================================\n");

    //setup the GPIO config (which GPIOs to use)
    my_sysgpio_config_t config;
    config.mosi = MOSI_MIO;
    config.miso = MISO_MIO;
    config.sclk = SCLK_MIO;
    config.sen = SEN_MIO;
    if (my_sysgpio_setup(&config) != 0)
    {
        printf("fail my_sysgpio_setup()\n");
        return EXIT_FAILURE;
    }

    //create and test lms....
    LMS7002M_t *lms = LMS7002M_create(my_sysgpio_transact, (void *)&config);

    LMS7002M_spi_write(lms, 0x20, 0x0000); //reset
    LMS7002M_spi_write(lms, 0x20, 0xFFFF); //reset clear
    LMS7002M_spi_write(lms, 0x21, 0x0E9F); //default, sets 4 wire mode

    for (int addr = 0x20; addr <= 0x2f; addr++)
    {
        printf("reg[0x%x]=0x%x\n", addr, LMS7002M_spi_read(lms, addr));
    }

    {
        uint32_t info = LMS7002M_spi_read(lms, 0x2f);
        int ver = (info >> 11) & 0x1f;
        int rev = (info >> 6) & 0x1f;
        int mask = (info >> 0) & 0x3f;
        printf("ver=%d, rev=%d, mask=%d\n", ver, rev, mask);
    }

    LMS7002M_destroy(lms);

    my_sysgpio_shutdown(&config);

    return EXIT_SUCCESS;
}
