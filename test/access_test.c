//
// Test instantiating the LMS7002M through spidev on linux
//
// Copyright (c) 2014-2015 Fairwaves, Inc.
// Copyright (c) 2014-2015 Rice University
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
//

#include <LMS7002M/LMS7002M.h>
#include <LMS7002M/LMS7002M_logger.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "spidev_interface.h"
#include "sysfs_gpio_interface.h"
#include "xilinx_user_gpio.h"
#include "xilinx_user_mem.h"

//signal handle for ctrl+c
static bool user_exit = false;
void sig_handler(int s)
{
    user_exit = true;
}

/*
 * for testing with gpio...
#define MOSI_MIO 10
#define MISO_MIO 11
#define SCLK_MIO 12
#define SEN_MIO 13
*/

#define REF_FREQ (61.44e6/2)

#define EMIO_OFFSET 54
#define RESET_EMIO    (EMIO_OFFSET+0)
#define DIG_RST_EMIO  (EMIO_OFFSET+1)
#define RXEN_EMIO     (EMIO_OFFSET+2)
#define TXEN_EMIO     (EMIO_OFFSET+3)
#define DIO_DIR_CTRL1_EMIO   (EMIO_OFFSET+4)
#define DIO_DIR_CTRL2_EMIO   (EMIO_OFFSET+5)
#define IQSEL1_DIR_EMIO      (EMIO_OFFSET+6)
#define IQSEL2_DIR_EMIO      (EMIO_OFFSET+7)

#define SET_EMIO_OUT_LVL(emio, lvl) \
    gpio_export(emio); \
    gpio_set_dir(emio, 1); \
    gpio_set_value(emio, lvl)

#define CLEANUP_EMIO(emio) \
    gpio_set_dir(emio, 0); \
    gpio_unexport(emio)

#define FPGA_REGS 0x43C00000

#define FPGA_REG_RD_SENTINEL 0 //readback a known value
#define FPGA_REG_RD_RX_CLKS 8 //sanity check clock counter
#define FPGA_REG_RD_TX_CLKS 12 //sanity check clock counter
#define FPGA_REG_RD_DATA_A 28 //RXA data for loopback test
#define FPGA_REG_RD_DATA_B 32 //RXB data for loopback test

#define FPGA_REG_WR_EXT_RST 12 //active high external reset
//#define FPGA_REG_WR_RX_STORE_OK 8 //can register RX samples (for test)
#define FPGA_REG_WR_DATA_A 28 //TXA data for loopback test
#define FPGA_REG_WR_DATA_B 32 //TXB data for loopback test
#define FPGA_REG_WR_TX_TEST 36

static inline double estimate_clock_rate(void *regs, int offset)
{
    uint32_t t0 = xumem_read32(regs, offset);
    sleep(1);
    uint32_t t1 = xumem_read32(regs, offset);
    return ((double)(t1 - t0));
}

int main(int argc, char **argv)
{
    LMS7_set_log_level(LMS7_DEBUG);

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
    SET_EMIO_OUT_LVL(RESET_EMIO, 0);
    SET_EMIO_OUT_LVL(RESET_EMIO, 1);

    void *handle = spidev_interface_open(argv[1]);
    if (handle == NULL) return EXIT_FAILURE;
    int ret = 0;

    //create and test lms....
    printf("Create LMS7002M instance\n");
    LMS7002M_t *lms = LMS7002M_create(spidev_interface_transact, handle);
    if (lms == NULL) return EXIT_FAILURE;
    LMS7002M_set_spi_mode(lms, 4); //set 4-wire spi mode first
    LMS7002M_reset(lms);

    //read info register
    LMS7002M_regs_spi_read(lms, 0x002f);
    printf("rev 0x%x\n", LMS7002M_regs(lms)->reg_0x002f_rev);
    printf("ver 0x%x\n", LMS7002M_regs(lms)->reg_0x002f_ver);

    //turn the clocks on
    double actualRate = 0.0;
    ret = LMS7002M_set_data_clock(lms, REF_FREQ, 61.44e6, &actualRate);
    if (ret != 0)
    {
        printf("clock tune failure %d\n", ret);
        return EXIT_FAILURE;
    }

    //configure data port directions and data clock rates
    LMS7002M_configure_lml_port(lms, LMS_PORT1, LMS_TX, 2);
    LMS7002M_configure_lml_port(lms, LMS_PORT2, LMS_RX, 2);
    //LMS7002M_invert_fclk(lms, true); //makes it read in I, Q
    //LMS7002M_setup_digital_loopback(lms);

    //external reset now that clocks are on
    xumem_write32(regs, FPGA_REG_WR_EXT_RST, 1);
    xumem_write32(regs, FPGA_REG_WR_EXT_RST, 0);

    //readback clock counters, are they alive?
    /*
    printf("RX CLK RATE %f MHz\n", estimate_clock_rate(regs, FPGA_REG_RD_RX_CLKS)/1e6);
    printf("TX CLK RATE %f MHz\n", estimate_clock_rate(regs, FPGA_REG_RD_TX_CLKS)/1e6);
    */

    //port output enables
    SET_EMIO_OUT_LVL(RXEN_EMIO, 1);
    SET_EMIO_OUT_LVL(TXEN_EMIO, 1);

    /*
    xumem_write32(regs, FPGA_REG_WR_TX_TEST, 1); //enable fpga registers to TX
    xumem_write32(regs, FPGA_REG_WR_DATA_A, 0xAAAABBBB);
    xumem_write32(regs, FPGA_REG_WR_DATA_B, 0xCCCCDDDD);
    //xumem_write32(regs, FPGA_REG_WR_RX_STORE_OK, 1);
    //sleep(1);
    //xumem_write32(regs, FPGA_REG_WR_RX_STORE_OK, 0);
    sleep(1);
    printf("FPGA_REG_RD_DATA_A = 0x%x\n", xumem_read32(regs, FPGA_REG_RD_DATA_A));
    printf("FPGA_REG_RD_DATA_B = 0x%x\n", xumem_read32(regs, FPGA_REG_RD_DATA_B));
    */

    //enable components
    LMS7002M_afe_enable(lms, LMS_TX, LMS_CHA, true);
    LMS7002M_afe_enable(lms, LMS_TX, LMS_CHB, true);
    LMS7002M_afe_enable(lms, LMS_RX, LMS_CHA, true);
    LMS7002M_afe_enable(lms, LMS_RX, LMS_CHB, true);
    LMS7002M_rxtsp_enable(lms, LMS_CHAB, true);
    LMS7002M_txtsp_enable(lms, LMS_CHAB, true);
    LMS7002M_rbb_enable(lms, LMS_CHAB, true);
    LMS7002M_tbb_enable(lms, LMS_CHAB, true);
    LMS7002M_rfe_enable(lms, LMS_CHAB, true);
    LMS7002M_trf_enable(lms, LMS_CHAB, true);
    LMS7002M_sxx_enable(lms, LMS_RX, true);
    LMS7002M_sxx_enable(lms, LMS_TX, true);

    //setup defaults along the chain
    LMS7002M_rfe_select_input(lms, LMS_CHAB, LMS7002M_RFE_LNAH);
    LMS7002M_trf_select_band(lms, LMS_CHAB, 2);

    LMS7002M_rfe_set_lna(lms, LMS_CHAB, 40.0);
    LMS7002M_rfe_set_tia(lms, LMS_CHAB, 12.0);
    LMS7002M_rbb_set_pga(lms, LMS_CHAB, 19.0);

    LMS7002M_rbb_set_filter_bw(lms, LMS_CHAB, 200e6);
    LMS7002M_tbb_set_filter_bw(lms, LMS_CHAB, 200e6);

    //tune the frontends
    ret = LMS7002M_set_lo_freq(lms, LMS_TX, REF_FREQ, 2.500e9, &actualRate);
    printf("%d - Actual TX LO freq %f MHz\n", ret, actualRate/1e6);

    ret = LMS7002M_set_lo_freq(lms, LMS_RX, REF_FREQ, 2.500e9, &actualRate);
    printf("%d - Actual RX LO freq %f MHz\n", ret, actualRate/1e6);

    //inject test signal into TBB
    const bool TBB_TEST_ON = false;
    if (TBB_TEST_ON) LMS7002M_tbb_set_test_in(lms, LMS_CHAB, LMS7002M_TBB_TSTIN_AMP);
    else LMS7002M_tbb_set_test_in(lms, LMS_CHAB, LMS7002M_TBB_TSTIN_OFF);

    //output test signal from RBB
    const bool RBB_TEST_ON = true;
    LMS7002M_rbb_set_test_out(lms, LMS_CHAB, RBB_TEST_ON);

    //setup tx dsp signal generator
    //LMS7002M_txtsp_tsg_tone(lms, LMS_CHAB);
    //LMS7002M_txtsp_tsg_const(lms, LMS_CHAB, 1 << 14, 1 << 14);
    //LMS7002M_txtsp_set_freq(lms, LMS_CHAB, 0.01/*relative*/);

    //connect tx baseband to rx baseband loopback
    //LMS7002M_tbb_set_path(lms, LMS_CHAB, LMS7002M_TBB_BYP);
    //LMS7002M_tbb_set_test_in(lms, LMS_CHAB, LMS7002M_TBB_TSTIN_OFF);
    //OR EXTERNAL DEBUG: LMS7002M_tbb_set_test_in(self, LMS_CHAB, LMS7002M_TBB_TSTIN_AMP);
    //LMS7002M_tbb_set_iamp(lms, LMS_CHAB, 10.0);
    //LMS7002M_tbb_enable_loopback(lms, LMS_CHAB, LMS7002M_TBB_LB_MAIN_TBB, false/*noswap*/);

    //rx baseband loopback to output pad
    //LMS7002M_rbb_set_path(lms, LMS_CHAB, LMS7002M_RBB_BYP_LB);
    //LMS7002M_rbb_set_pga(lms, LMS_CHAB, 10.0);
    //LMS7002M_rbb_set_test_out(lms, LMS_CHAB, true);

    //LMS7002M_load_ini(lms, "/root/src/TxTSP_test_2.ini");
    //LMS7002M_load_ini(lms, "/root/src/RFE_RBB_SXR_test_1.ini");

    printf("Debug setup!\n");
    printf("Press ctrl+c to exit\n");
    signal(SIGINT, sig_handler);
    while (!user_exit) sleep(1);

    //power down and clean up
    printf("Power down!\n");
    LMS7002M_power_down(lms);
    LMS7002M_destroy(lms);

    //back to inputs
    CLEANUP_EMIO(RESET_EMIO);
    CLEANUP_EMIO(RXEN_EMIO);
    CLEANUP_EMIO(TXEN_EMIO);

    spidev_interface_close(handle);

    printf("Done!\n");
    return EXIT_SUCCESS;
}
