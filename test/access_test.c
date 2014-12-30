//
// Test instantiating the LMS7002M through spidev on linux
//
// Copyright (c) 2014-2015 Fairwaves, Inc.
// Copyright (c) 2014-2015 Rice University
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
//

#include <LMS7002M/LMS7002M.h>
#include <LMS7002M/LMS7002M_impl.h>

#include <stdio.h>
#include <stdlib.h>

#include "spidev_interface.h"
#include "sysfs_gpio_interface.h"

/*
 * for testing with gpio...
#define MOSI_MIO 10
#define MISO_MIO 11
#define SCLK_MIO 12
#define SEN_MIO 13
*/

int main(int argc, char **argv)
{
    printf("=========================================================\n");
    printf("== Test LMS7002M access                                  \n");
    printf("=========================================================\n");
    if (argc < 2)
    {
        printf("Usage %s /dev/spidevXXXXXX\n", argv[0]);
        return EXIT_FAILURE;
    }

    void *handle = spidev_interface_open(argv[1]);
    if (handle == NULL) return EXIT_FAILURE;

    //create and test lms....
    LMS7002M_t *lms = LMS7002M_create(spidev_interface_transact, handle);

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

    spidev_interface_close(handle);

    return EXIT_SUCCESS;
}
