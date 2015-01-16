///
/// \file LMS7002M/LMS7002M_lml.h
///
/// Lime-light config for the LMS7002M C driver.
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

LMS7002M_API void LMS7002M_set_spi_mode(LMS7002M_t *self, const int numWires)
{
    if (numWires == 3) self->regs.reg_0x0021_spimode = REG_0X0021_SPIMODE_3WIRE;
    if (numWires == 4) self->regs.reg_0x0021_spimode = REG_0X0021_SPIMODE_4WIRE;
    LMS7002M_regs_spi_write(self, 0x0021);
}

LMS7002M_API void LMS7002M_reset(LMS7002M_t *self)
{
    LMS7002M_spi_write(self, 0x0020, 0x0);
    LMS7002M_regs_spi_write(self, 0x0020);
}

LMS7002M_API void LMS7002M_power_down(LMS7002M_t *self)
{
    self->regs.reg_0x0020_rxen_a = 0;
    self->regs.reg_0x0020_rxen_b = 0;
    self->regs.reg_0x0020_txen_a = 0;
    self->regs.reg_0x0020_txen_b = 0;
    LMS7002M_regs_spi_write(self, 0x0020);
}

LMS7002M_API void LMS7002M_configure_lml_port(LMS7002M_t *self, const LMS7002M_port_t portNo, const LMS7002M_dir_t direction, const int mclkDiv)
{
    //set TRXIQ on both ports
    if (portNo == LMS_PORT1)
    {
        self->regs.reg_0x0023_lml_mode1 = REG_0X0023_LML_MODE1_TRXIQ;
        self->regs.reg_0x0023_lml_txnrxiq1 = (direction==LMS_TX)?
            REG_0X0023_LML_TXNRXIQ1_RXIQ:REG_0X0023_LML_TXNRXIQ1_TXIQ; //WARNING: TX/RX perspective swap
    }
    if (portNo == LMS_PORT2)
    {
        self->regs.reg_0x0023_lml_mode2 = REG_0X0023_LML_MODE2_TRXIQ;
        self->regs.reg_0x0023_lml_txnrxiq2 = (direction==LMS_TX)?
            REG_0X0023_LML_TXNRXIQ2_RXIQ:REG_0X0023_LML_TXNRXIQ2_TXIQ; //WARNING: TX/RX perspective swap
    }

    //delayed mclk is used for RX read clock -- needs small delay set
    self->regs.reg_0x002b_mclk2dly = 1; //1X delay
    self->regs.reg_0x002b_mclk1dly = 1; //1X delay

    //set the FIFO rd and wr clock muxes based on direction
    if (direction == LMS_TX)
    {
        self->regs.reg_0x002a_txrdclk_mux = REG_0X002A_TXRDCLK_MUX_TXTSPCLK;
        self->regs.reg_0x002a_txwrclk_mux = (portNo==LMS_PORT1)?REG_0X002A_TXWRCLK_MUX_FCLK1:REG_0X002A_TXWRCLK_MUX_FCLK2;
    }
    if (direction == LMS_RX)
    {
        self->regs.reg_0x002a_rxrdclk_mux = (portNo==LMS_PORT1)?REG_0X002A_RXRDCLK_MUX_MCLK1:REG_0X002A_RXRDCLK_MUX_MCLK2;
        self->regs.reg_0x002a_rxwrclk_mux = REG_0X002A_RXWRCLK_MUX_RXTSPCLK;
    }

    //data stream muxes
    if (direction == LMS_TX)
    {
        self->regs.reg_0x002a_tx_mux = (portNo==LMS_PORT1)?REG_0X002A_TX_MUX_PORT1:REG_0X002A_TX_MUX_PORT2;
    }
    if (direction == LMS_RX)
    {
        self->regs.reg_0x002a_rx_mux = REG_0X002A_RX_MUX_RXTSP;
    }

    //clock mux (outputs to mclk pin)
    if (portNo == LMS_PORT1)
    {
        self->regs.reg_0x002b_mclk1src = (direction==LMS_TX)?
            ((mclkDiv==1)?REG_0X002B_MCLK1SRC_TXTSPCLKA:REG_0X002B_MCLK1SRC_TXTSPCLKA_DIV):
            ((mclkDiv==1)?REG_0X002B_MCLK1SRC_RXTSPCLKA:REG_0X002B_MCLK1SRC_RXTSPCLKA_DIV);
    }
    if (portNo == LMS_PORT2)
    {
        self->regs.reg_0x002b_mclk2src = (direction==LMS_TX)?
            ((mclkDiv==1)?REG_0X002B_MCLK2SRC_TXTSPCLKA:REG_0X002B_MCLK2SRC_TXTSPCLKA_DIV):
            ((mclkDiv==1)?REG_0X002B_MCLK2SRC_RXTSPCLKA:REG_0X002B_MCLK2SRC_RXTSPCLKA_DIV);
    }

    //clock divider (outputs to mclk pin)
    if (direction == LMS_TX)
    {
        self->regs.reg_0x002b_txdiven = (mclkDiv > 1)?1:0;
        self->regs.reg_0x002c_txtspclk_div = (mclkDiv/2)-1;
    }
    if (direction == LMS_RX)
    {
        self->regs.reg_0x002b_rxdiven = (mclkDiv > 1)?1:0;
        self->regs.reg_0x002c_rxtspclk_div = (mclkDiv/2)-1;
    }

    LMS7002M_regs_spi_write(self, 0x0023);
    LMS7002M_regs_spi_write(self, 0x002A);
    LMS7002M_regs_spi_write(self, 0x002B);
    LMS7002M_regs_spi_write(self, 0x002C);
}

LMS7002M_API void LMS7002M_invert_fclk(LMS7002M_t *self, const bool invert)
{
    self->regs.reg_0x002b_fclk1_inv = invert?1:0;
    self->regs.reg_0x002b_fclk2_inv = invert?1:0;
    LMS7002M_regs_spi_write(self, 0x002B);
}

LMS7002M_API void LMS7002M_setup_digital_loopback(LMS7002M_t *self)
{
    self->regs.reg_0x002a_rx_mux = REG_0X002A_RX_MUX_TXFIFO;
    //self->regs.reg_0x002a_rx_mux = REG_0X002A_RX_MUX_LFSR;
    if (self->regs.reg_0x002a_txwrclk_mux == REG_0X002A_TXWRCLK_MUX_FCLK1)
    {
        self->regs.reg_0x002a_rxwrclk_mux = REG_0X002A_RXWRCLK_MUX_FCLK1;
    }
    if (self->regs.reg_0x002a_txwrclk_mux == REG_0X002A_TXWRCLK_MUX_FCLK2)
    {
        self->regs.reg_0x002a_rxwrclk_mux = REG_0X002A_RXWRCLK_MUX_FCLK2;
    }
    LMS7002M_regs_spi_write(self, 0x002A);
}

LMS7002M_API void LMS7002M_set_mac_ch(LMS7002M_t *self, const LMS7002M_chan_t channel)
{
    const int newValue = (channel == LMS_CHA)?REG_0X0020_MAC_CHA:REG_0X0020_MAC_CHB;
    if (self->regs.reg_0x0020_mac == newValue) return;
    self->regs.reg_0x0020_mac = newValue;
    LMS7002M_regs_spi_write(self, 0x0020);
}

LMS7002M_API void LMS7002M_set_mac_dir(LMS7002M_t *self, const LMS7002M_dir_t direction)
{
    //SPI Regs r19 p10:
    //The special case is frequency synthesizers SXR and SXT. Register addresses are the
    //same for SXR and SXT. To control SXT we have to set MAC[1:0] to the "01" and MAC[1:0]
    //to the "10" for SXR.
    const int newValue = (direction == LMS_TX)?1:2;
    if (self->regs.reg_0x0020_mac == newValue) return;
    self->regs.reg_0x0020_mac = newValue;
    LMS7002M_regs_spi_write(self, 0x0020);
}

#ifdef __cplusplus
}
#endif
