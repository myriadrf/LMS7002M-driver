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
#include "xilinx_user_gpio.h"
#include "xilinx_user_mem.h"

/*
 * for testing with gpio...
#define MOSI_MIO 10
#define MISO_MIO 11
#define SCLK_MIO 12
#define SEN_MIO 13
*/

#define EMIO_OFFSET 54
#define RESET_EMIO    (EMIO_OFFSET+0)
#define DIG_RST_EMIO  (EMIO_OFFSET+1)
#define RXEN_EMIO     (EMIO_OFFSET+2)
#define TXEN_EMIO     (EMIO_OFFSET+3)
#define DIO_DIR_CTRL1_EMIO   (EMIO_OFFSET+4)
#define DIO_DIR_CTRL2_EMIO   (EMIO_OFFSET+5)
#define IQSEL1_DIR_EMIO      (EMIO_OFFSET+6)
#define IQSEL2_DIR_EMIO      (EMIO_OFFSET+7)

#define FPGA_REGS 0x43C00000

#define FPGA_REG_RD_SENTINEL 0 //readback a known value
#define FPGA_REG_RD_RX_CLKS 8 //sanity check clock counter
#define FPGA_REG_RD_TX_CLKS 12 //sanity check clock counter
#define FPGA_REG_RD_DATA_A 20 //RXA data for loopback test
#define FPGA_REG_RD_DATA_B 24 //RXB data for loopback test

#define FPGA_REG_WR_RX_DUAL_CH 0 //0 for SDR mode, 1 for DDR mode
#define FPGA_REG_WR_TX_DUAL_CH 4 //0 for SDR mode, 1 for DDR mode
#define FPGA_REG_WR_DATA_A 20 //TXA data for loopback test
#define FPGA_REG_WR_DATA_B 24 //TXB data for loopback test

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

    //map FPGA registers
    void *regs = xumem_map_phys(FPGA_REGS, 1024);
    if (regs == NULL)
    {
        printf("failed to map registers\n");
        return EXIT_FAILURE;
    }
    printf("Read sentinel 0x%x\n", xumem_read32(regs, FPGA_REG_RD_SENTINEL));

    //perform reset
    gpio_export(RESET_EMIO);
    gpio_set_dir(RESET_EMIO, 1);
    gpio_set_value(RESET_EMIO, 0);
    gpio_set_value(RESET_EMIO, 1);

    void *handle = spidev_interface_open(argv[1]);
    if (handle == NULL) return EXIT_FAILURE;

    //create and test lms....
    printf("Create LMS7002M instance\n");
    LMS7002M_t *lms = LMS7002M_create(spidev_interface_transact, handle);
    if (lms == NULL) return EXIT_FAILURE;
    LMS7002M_reset(lms);

    //set 4-wire spi mode
    LMS7002M_regs(lms)->reg_0x0021_spimode = REG_0X0021_SPIMODE_4WIRE;
    LMS7002M_regs_spi_write(lms, 0x0021);

    //read info register
    LMS7002M_regs_spi_read(lms, 0x002f);
    printf("rev 0x%x\n", LMS7002M_regs(lms)->reg_0x002f_rev);
    printf("ver 0x%x\n", LMS7002M_regs(lms)->reg_0x002f_ver);

    //turn the clocks on
    LMS7002M_set_data_clock(lms, 61.44e6/2, 61e6);

    printf("FPGA_REG_RD_RX_CLKS = 0x%x\n", xumem_read32(regs, FPGA_REG_RD_RX_CLKS));
    printf("FPGA_REG_RD_TX_CLKS = 0x%x\n", xumem_read32(regs, FPGA_REG_RD_TX_CLKS));

    //power down and clean up
    LMS7002M_power_down(lms);
    LMS7002M_destroy(lms);

    spidev_interface_close(handle);

    printf("Done!\n");
    return EXIT_SUCCESS;
}
