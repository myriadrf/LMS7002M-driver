//
// SoapySDR wrapper for the LMS7002M driver.
//
// Copyright (c) 2015-2015 Fairwaves, Inc.
// Copyright (c) 2015-2015 Rice University
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
//

#pragma once
#include <cstdint>

/***********************************************************************
 * FPGA EMIOs that are controlled by sysfs GPIO
 **********************************************************************/
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

/***********************************************************************
 * FPGA register space for misc controls
 **********************************************************************/
#define FPGA_REGS 0x43C00000
#define FPGA_REGS_SIZE 1024

#define FPGA_REG_RD_SENTINEL 0 //readback a known value
#define FPGA_REG_RD_RX_CLKS 8 //sanity check clock counter
#define FPGA_REG_RD_TX_CLKS 12 //sanity check clock counter
#define FPGA_REG_RD_TIME_LO 16
#define FPGA_REG_RD_TIME_HI 20
#define FPGA_REG_RD_RX_CHA 28
#define FPGA_REG_RD_RX_CHB 32

#define FPGA_REG_WR_EXT_RST 12 //active high external reset
#define FPGA_REG_WR_TIME_LO 16
#define FPGA_REG_WR_TIME_HI 20
#define FPGA_REG_WR_TIME_LATCH 24
#define FPGA_REG_WR_TX_CHA 28
#define FPGA_REG_WR_TX_CHB 32
#define FPGA_REG_WR_TX_TEST 36

/***********************************************************************
 * Settings for the AXI DMA and framer/deframer
 **********************************************************************/
#define RX_DMA_INDEX 0
#define TX_DMA_INDEX 1
#define RX_FRAME_SIZE 1000 //buff size - hdrs
#define TX_FRAME_SIZE 1000 //buff size - hdrs

#define DATA_NUM_BUFFS 16
#define DATA_BUFF_SIZE 4096

#define CTRL_NUM_BUFFS 16
#define CTRL_BUFF_SIZE 64

#define XFER_SIZE sizeof(uint32_t)

//sanity check tags that the framers echo back in their responses
#define RX_TAG_ACTIVATE uint8_t('A')
#define RX_TAG_DEACTIVATE uint8_t('D')
#define TX_TAG_TRANSMIT uint8_t('T')

/***********************************************************************
 * Clock rates for this system
 **********************************************************************/
//the reference clock on the EVB7
#define EXT_REF_CLK (61.44e6/2)

//using an independent FPGA clock to drive the device timer
#define IF_TIME_CLK 100e6
