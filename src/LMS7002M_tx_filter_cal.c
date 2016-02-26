///
/// \file LMS7002M_tx_filter_cal.c
///
/// Tx filter calibration functions for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2016-2016 Fairwaves, Inc.
/// Copyright (c) 2016-2016 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include "LMS7002M_impl.h"
#include "LMS7002M_filter_cal.h"
#include <LMS7002M/LMS7002M_logger.h>
#include <LMS7002M/LMS7002M_time.h>
#include <string.h> //memcpy

/***********************************************************************
 * Re-tune the CORDICs based on the bandwidth
 **********************************************************************/
static void setup_tx_cal_tone(LMS7002M_t *self, const LMS7002M_chan_t channel, const double bw)
{
    LMS7002M_set_mac_ch(self, channel);
    const double txtsp_rate = self->cgen_freq;
    const double tx_nco_freq = bw;
    LMS7002M_txtsp_set_freq(self, channel, tx_nco_freq/txtsp_rate);

    const double rxtsp_rate = self->cgen_freq/4;
    const double rx_nco_freq = tx_nco_freq-1e6;
    LMS7002M_rxtsp_set_freq(self, channel, rx_nco_freq/rxtsp_rate);
}

/***********************************************************************
 * Tx calibration loop
 **********************************************************************/
static int tx_cal_loop(
    LMS7002M_t *self, const LMS7002M_chan_t channel, const double bw,
    int *reg_ptr, const int reg_addr, const int reg_max, const char *reg_name)
{
    int status = 0;
    LMS7002M_set_mac_ch(self, channel);

    //--- cgen already set prior ---//

    //--- gain selection ---//
    const int rssi_value_50k = cal_gain_selection(self, channel);

    //--- setup calibration tone ---//
    setup_tx_cal_tone(self, channel, bw);

    //--- calibration loop ---//
    uint16_t rssi_value = cal_read_rssi(self, channel);
    const int adjust = (rssi_value < rssi_value_50k*0.7071)?-1:+1;
    while (true)
    {
        LMS7002M_regs(self)->reg_0x010a_ccal_lpflad_tbb += adjust;
        LMS7002M_regs_spi_write(self, 0x010a);
        LMS7002M_regs_spi_write(self, reg_addr);

        rssi_value = cal_read_rssi(self, channel);
        if (rssi_value > rssi_value_50k*0.7071 && adjust < 0) break;
        if (rssi_value < rssi_value_50k*0.7071 && adjust > 0) break;

        if (LMS7002M_regs(self)->reg_0x010a_ccal_lpflad_tbb == 0 ||
            LMS7002M_regs(self)->reg_0x010a_ccal_lpflad_tbb == 31) continue;

        *reg_ptr -= adjust*5;
        LMS7002M_regs(self)->reg_0x010a_ccal_lpflad_tbb = 16;

        if (*reg_ptr < 0 || *reg_ptr > reg_max)
        {
            LMS7_logf(LMS7_ERROR, "failed to cal %s -> %d", reg_name, *reg_ptr);
            status = -1;
            goto done;
        }
    }
    LMS7_logf(LMS7_DEBUG, "%s = %d", reg_name, *reg_ptr);
    done:
    return status;
}

/***********************************************************************
 * Prepare for TX filter self-calibration
 **********************************************************************/
static int tx_cal_init(LMS7002M_t *self, const LMS7002M_chan_t channel)
{
    int status = 0;
    LMS7002M_set_mac_ch(self, channel);

    //--- rfe ---
    LMS7002M_regs(self)->reg_0x010c_en_g_rfe = 0;
    LMS7002M_regs_spi_write(self, 0x010c);

    //--- rbb ---
    set_addrs_to_default(self, channel, 0x0115, 0x011B);
    LMS7002M_regs(self)->reg_0x0115_pd_lpfl_rbb = 1;
    LMS7002M_regs(self)->reg_0x0118_input_ctl_pga_rbb = 3;
    LMS7002M_regs(self)->reg_0x0119_ict_pga_out_rbb = 20;
    LMS7002M_regs(self)->reg_0x0119_ict_pga_in_rbb = 20;
    LMS7002M_regs(self)->reg_0x011a_c_ctl_pga_rbb = 3;
    LMS7002M_regs_spi_write(self, 0x0115);
    LMS7002M_regs_spi_write(self, 0x0118);
    LMS7002M_regs_spi_write(self, 0x0119);
    LMS7002M_regs_spi_write(self, 0x011a);

    //--- trf ---
    LMS7002M_regs(self)->reg_0x0100_en_g_trf = 0;
    LMS7002M_regs_spi_write(self, 0x0100);

    //--- tbb ---
    set_addrs_to_default(self, channel, 0x0105, 0x010B);
    LMS7002M_regs(self)->reg_0x0108_cg_iamp_tbb = 1;
    LMS7002M_regs(self)->reg_0x0108_ict_iamp_frp_tbb = 1;
    LMS7002M_regs(self)->reg_0x0108_ict_iamp_gg_frp_tbb = 6;
    LMS7002M_regs_spi_write(self, 0x0108);

    //--- afe ---
    LMS7002M_afe_enable(self, LMS_RX, channel, true);
    LMS7002M_afe_enable(self, LMS_TX, channel, true);
    LMS7002M_set_mac_ch(self, channel);

    //--- bias -- must write to chA ---//
    LMS7002M_set_mac_ch(self, LMS_CHA);
    const int rp_calib_bias = LMS7002M_regs(self)->reg_0x0084_rp_calib_bias;
    set_addrs_to_default(self, channel, 0x0083, 0x0084);
    LMS7002M_regs(self)->reg_0x0084_rp_calib_bias = rp_calib_bias;
    LMS7002M_set_mac_ch(self, channel);

    //--- TxTSP ---
    set_addrs_to_default(self, channel, 0x0200, 0x020c);
    LMS7002M_regs(self)->reg_0x0200_tsgmode = 1;
    LMS7002M_regs(self)->reg_0x0200_insel = 1;
    LMS7002M_regs(self)->reg_0x0208_gfir3_byp = 1;
    LMS7002M_regs(self)->reg_0x0208_gfir2_byp = 1;
    LMS7002M_regs(self)->reg_0x0208_gfir1_byp = 1;
    LMS7002M_regs_spi_write(self, 0x0200);
    LMS7002M_regs_spi_write(self, 0x0208);
    LMS7002M_txtsp_tsg_const(self, channel, 0x7fff, 0x8000);

    //--- RxTSP ---
    set_addrs_to_default(self, channel, 0x0400, 0x040f);
    LMS7002M_regs(self)->reg_0x040a_agc_mode = 1;
    LMS7002M_regs(self)->reg_0x040c_gfir3_byp = 1;
    LMS7002M_regs(self)->reg_0x040c_gfir2_byp = 1;
    LMS7002M_regs(self)->reg_0x040c_gfir1_byp = 1;
    LMS7002M_regs(self)->reg_0x040a_agc_avg = 7;
    LMS7002M_regs(self)->reg_0x040c_cmix_gain = 1;
    LMS7002M_regs_spi_write(self, 0x040a);
    LMS7002M_regs_spi_write(self, 0x040c);

    //--- initial cal tone ---//
    setup_tx_cal_tone(self, channel, 50e3);

    return status;
}

/***********************************************************************
 * Perform TBB LPFS5 filter calibration
 **********************************************************************/
static int rx_cal_tbb_lpfs5(LMS7002M_t *self, const LMS7002M_chan_t channel, const double bw)
{
    int status = 0;
    LMS7002M_set_mac_ch(self, channel);

    //--- check filter bounds ---//
    if (bw < 0.8e6 || bw > 3.2e6)
    {
        LMS7_logf(LMS7_ERROR, "LPFS5 bandwidth not in range[0.8 to 3.2 MHz]");
        status = -1;
        goto done;
    }

    //--- setup rcal, path ---//
    const double f = bw/1e6;
    const double p1 = 1.93821841029921E-15;
    const double p2 = -0.0429694461214244;
    const double p3 = 0.253501254059498;
    const double p4 = 88.9545445989649;
    const double p5 = -48.0847491316861;
    const int rcal_lpfs5_tbb = (int)(f*f*f*f*p1 + f*f*f*p2 + f*f*p3 + f*p4 + p5);
    LMS7002M_regs(self)->reg_0x010a_rcal_lpfs5_tbb = rcal_lpfs5_tbb;
    LMS7002M_regs(self)->reg_0x0105_loopb_tbb = 3;
    LMS7002M_regs(self)->reg_0x0105_pd_lpfh_tbb = 1;
    LMS7002M_regs(self)->reg_0x0105_pd_lpfs5_tbb = 0;
    LMS7002M_regs(self)->reg_0x010a_bypladder_tbb = 1;
    LMS7002M_regs_spi_write(self, 0x0105);
    LMS7002M_regs_spi_write(self, 0x010a);

    //--- calibration ---//
    status = tx_cal_loop(self, channel, bw,
        &LMS7002M_regs(self)->reg_0x010a_rcal_lpfs5_tbb,
        0x010a, 255, "rcal_lpfs5_tbb");

    done:
    return status;
}

/***********************************************************************
 * Perform TBB LPFLAD filter calibration
 **********************************************************************/
static int rx_cal_tbb_lpflad(LMS7002M_t *self, const LMS7002M_chan_t channel, const double bw)
{
    int status = 0;
    LMS7002M_set_mac_ch(self, channel);

    //--- check filter bounds ---//
    if (bw < 2e6 || bw > 16e6)
    {
        LMS7_logf(LMS7_ERROR, "LPFLAD bandwidth not in range[2 to 16 MHz]");
        status = -1;
        goto done;
    }

    //--- setup rcal, path ---//
    const double f = bw/1e6;
    const double p1 = 1.29858903647958E-16;
    const double p2 = -0.000110746929967704;
    const double p3 = 0.00277593485991029;
    const double p4 = 21.0384293169607;
    const double p5 = -48.4092606238297;
    const int rcal_lpflad_tbb = (int)(f*f*f*f*p1 + f*f*f*p2 + f*f*p3 + f*p4 + p5);
    LMS7002M_regs(self)->reg_0x0109_rcal_lpflad_tbb = rcal_lpflad_tbb;
    LMS7002M_regs(self)->reg_0x0105_loopb_tbb = 2;
    LMS7002M_regs(self)->reg_0x0105_pd_lpfh_tbb = 1;
    LMS7002M_regs(self)->reg_0x0105_pd_lpflad_tbb = 0;
    LMS7002M_regs_spi_write(self, 0x0105);
    LMS7002M_regs_spi_write(self, 0x0109);

    //--- calibration ---//
    status = tx_cal_loop(self, channel, bw,
        &LMS7002M_regs(self)->reg_0x0109_rcal_lpflad_tbb,
        0x0109, 255, "rcal_lpflad_tbb");

    done:
    return status;
}

/***********************************************************************
 * Perform TBB LPFH filter calibration
 **********************************************************************/
static int rx_cal_tbb_lpfh(LMS7002M_t *self, const LMS7002M_chan_t channel, const double bw)
{
    int status = 0;
    LMS7002M_set_mac_ch(self, channel);

    //--- check filter bounds ---//
    if (bw < 28e6 || bw > 60e6)
    {
        LMS7_logf(LMS7_ERROR, "LPFH bandwidth not in range[28 to 60 MHz]");
        status = -1;
        goto done;
    }

    //--- setup rcal, path ---//
    const double f = bw/1e6;
    const double p1 = 1.10383261611112E-06;
    const double p2 = -0.000210800032517545;
    const double p3 = 0.0190494874803309;
    const double p4 = 1.43317445923528;
    const double p5 = -47.6950779298333;
    const int rcal_lpfh_tbb = (int)(f*f*f*f*p1 + f*f*f*p2 + f*f*p3 + f*p4 + p5);
    LMS7002M_regs(self)->reg_0x0109_rcal_lpfh_tbb = rcal_lpfh_tbb;
    LMS7002M_regs(self)->reg_0x0105_loopb_tbb = 3;
    LMS7002M_regs_spi_write(self, 0x0105);
    LMS7002M_regs_spi_write(self, 0x0109);

    //--- calibration ---//
    status = tx_cal_loop(self, channel, bw,
        &LMS7002M_regs(self)->reg_0x0109_rcal_lpfh_tbb,
        0x0109, 255, "rcal_lpfh_tbb");

    done:
    return status;
}

/***********************************************************************
 * Tx calibration dispatcher
 **********************************************************************/
int LMS7002M_tbb_set_filter_bw(LMS7002M_t *self, const LMS7002M_chan_t channel, double bw, double *bwactual)
{
    LMS7002M_set_mac_ch(self, channel);
    int status = 0;
    if (bw < 0.8) bw = 0.8; //real pole starts at 0.8
    if (bw > 16e6) bw = 28e6; //ladder stops at 16e6, high-band starts at 28e6
    const int path = (bw < 2e6)?LMS7002M_TBB_S5:(bw <= 16e6)?LMS7002M_TBB_LAD:LMS7002M_RBB_HBF;

    ////////////////////////////////////////////////////////////////////
    // Save register map
    ////////////////////////////////////////////////////////////////////
    LMS7002M_regs_t saved_map[2];
    memcpy(saved_map, self->_regs, sizeof(saved_map));

    ////////////////////////////////////////////////////////////////////
    // Clocking configuration
    ////////////////////////////////////////////////////////////////////
    status = cal_setup_cgen(self, bw);
    if (status != 0)
    {
        LMS7_logf(LMS7_ERROR, "cal_setup_cgen() faled");
        goto done;
    }

    ////////////////////////////////////////////////////////////////////
    // Load initial calibration state
    ////////////////////////////////////////////////////////////////////
    status = tx_cal_init(self, channel);
    if (status != 0)
    {
        LMS7_logf(LMS7_ERROR, "tx_cal_init() failed");
        goto done;
    }

    ////////////////////////////////////////////////////////////////////
    // TBB LPF calibration
    ////////////////////////////////////////////////////////////////////
    if (path == LMS7002M_TBB_S5)  status = rx_cal_tbb_lpfs5(self, channel, bw);
    if (path == LMS7002M_TBB_LAD) status = rx_cal_tbb_lpflad(self, channel, bw);
    if (path == LMS7002M_RBB_HBF) status = rx_cal_tbb_lpfh(self, channel, bw);
    if (status != 0)
    {
        LMS7_logf(LMS7_ERROR, "rx_cal_tbb_lpf() failed");
        goto done;
    }

    done:

    ////////////////////////////////////////////////////////////////////
    // stash tbb calibration results
    ////////////////////////////////////////////////////////////////////
    LMS7002M_set_mac_ch(self, channel);
    const int rcal_lpflad_tbb = LMS7002M_regs(self)->reg_0x0109_rcal_lpflad_tbb;
    const int ccal_lpflad_tbb = LMS7002M_regs(self)->reg_0x010a_ccal_lpflad_tbb;
    const int rcal_lpfs5_tbb = LMS7002M_regs(self)->reg_0x010a_rcal_lpfs5_tbb;
    const int rcal_lpfh_tbb = LMS7002M_regs(self)->reg_0x0109_rcal_lpfh_tbb;

    ////////////////////////////////////////////////////////////////////
    // restore original register values
    ////////////////////////////////////////////////////////////////////
    memcpy(self->_regs, saved_map, sizeof(saved_map));
    LMS7002M_regs_to_rfic(self);
    LMS7002M_set_mac_ch(self, channel);

    ////////////////////////////////////////////////////////////////////
    // apply tbb calibration results
    ////////////////////////////////////////////////////////////////////
    LMS7002M_set_mac_ch(self, channel);
    LMS7002M_regs(self)->reg_0x0109_rcal_lpflad_tbb = rcal_lpflad_tbb;
    LMS7002M_regs(self)->reg_0x010a_ccal_lpflad_tbb = ccal_lpflad_tbb;
    LMS7002M_regs(self)->reg_0x010a_rcal_lpfs5_tbb = rcal_lpfs5_tbb;
    LMS7002M_regs(self)->reg_0x0109_rcal_lpfh_tbb = rcal_lpfh_tbb;
    LMS7002M_regs(self)->reg_0x0108_ict_iamp_frp_tbb = 1;
    LMS7002M_regs(self)->reg_0x0108_ict_iamp_gg_frp_tbb = 6;
    LMS7002M_regs_spi_write(self, 0x0108);
    LMS7002M_regs_spi_write(self, 0x0109);
    LMS7002M_regs_spi_write(self, 0x010a);

    ////////////////////////////////////////////////////////////////////
    // set the filter selection
    ////////////////////////////////////////////////////////////////////
    LMS7002M_tbb_set_path(self, channel, path);

    if (bwactual != NULL) *bwactual = bw;
    return status;
}
