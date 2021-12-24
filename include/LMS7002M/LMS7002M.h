///
/// \file LMS7002M/LMS7002M.h
///
/// Main interface header for LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2014-2016 Fairwaves, Inc.
/// Copyright (c) 2014-2016 Rice University
/// Copyright (c) 2016-2017 Skylark Wireless
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <LMS7002M/LMS7002M_config.h>
#include <LMS7002M/LMS7002M_regs.h>

#ifdef __cplusplus
extern "C" {
#endif

//! direction constants
typedef enum
{
    LMS_TX = 1,
    LMS_RX = 2,
} LMS7002M_dir_t;

//! channel constants
typedef enum
{
    LMS_CHA = 'A',
    LMS_CHB = 'B',
    LMS_CHAB = 'C',
} LMS7002M_chan_t;

//! port number constants
typedef enum
{
    LMS_PORT1 = 1,
    LMS_PORT2 = 2,
} LMS7002M_port_t;

//! VCO ranges
#define LMS7002M_CGEN_VCO_LO 2.000e9
#define LMS7002M_CGEN_VCO_HI 2.700e9
#define LMS7002M_SXX_VCOL_LO 3.800e9
#define LMS7002M_SXX_VCOL_HI 5.222e9
#define LMS7002M_SXX_VCOM_LO 4.961e9
#define LMS7002M_SXX_VCOM_HI 6.754e9
#define LMS7002M_SXX_VCOH_LO 6.306e9
#define LMS7002M_SXX_VCOH_HI 7.714e9

/*!
 * Function typedef for a function that implements SPI register transactions.
 * The handle is the same pointer that the handle passed into the driver instance.
 * Example: the data may be a pointer to a /dev/spiXX file descriptor
 *
 * The readback option supplied by the driver specifies whether or not
 * it requires the result of the spi transaction to be returned.
 * The implementor of this function can use the readback parameter
 * to implement non-blocking spi transactions (as an optimization).
 *
 * \param handle handle provided data
 * \param data the 32-bit write data
 * \param readback true to readback
 * \return the 32-bit readback data
 */
typedef uint32_t (*LMS7002M_spi_transact_t)(void *handle, const uint32_t data, const bool readback);

//! The opaque instance of the LMS7002M instance
struct LMS7002M_struct;

//! Helpful typedef for the LMS7002M driver instance
typedef struct LMS7002M_struct LMS7002M_t;

/*!
 * Create an instance of the LMS7002M driver.
 * This call does not reset or initialize the LMS7002M.
 * See LMS7002M_init(...) and LMS7002M_reset(...).
 *
 * \param transact the SPI transaction function
 * \param handle arbitrary handle data for transact
 * \return a new instance of the LMS7002M driver
 */
LMS7002M_API LMS7002M_t *LMS7002M_create(LMS7002M_spi_transact_t transact, void *handle);

/*!
 * Destroy an instance of the LMS7002M driver.
 * This call simply fees the instance data,
 * it does not shutdown or have any effects on the chip.
 * Use the LMS7002M_power_down(...) call before destroy().
 *
 * \param self an instance of the LMS7002M driver
 */
LMS7002M_API void LMS7002M_destroy(LMS7002M_t *self);

//=====================================================================//
// SPI access section
//=====================================================================//

/*!
 * Perform a SPI write transaction on the given device.
 * This call can be used directly to access SPI registers,
 * rather than indirectly through the high level driver calls.
 * \param self an instance of the LMS7002M driver
 * \param addr the 16 bit register address
 * \param value the 16 bit register value
 */
LMS7002M_API void LMS7002M_spi_write(LMS7002M_t *self, const int addr, const int value);

/*!
 * Perform a SPI read transaction on the given device.
 * This call can be used directly to access SPI registers,
 * rather than indirectly through the high level driver calls.
 * \param self an instance of the LMS7002M driver
 * \param addr the 16 bit register address
 * \return the 16 bit register value
 */
LMS7002M_API int LMS7002M_spi_read(LMS7002M_t *self, const int addr);

/*!
 * Write a spi register using values from the regs structure.
 * \param self an instance of the LMS7002M driver
 * \param addr the 16 bit register address
 */
LMS7002M_API void LMS7002M_regs_spi_write(LMS7002M_t *self, const int addr);

/*!
 * Read a spi register, filling in the fields in the regs structure.
 * \param self an instance of the LMS7002M driver
 * \param addr the 16 bit register address
 */
LMS7002M_API void LMS7002M_regs_spi_read(LMS7002M_t *self, const int addr);

/*!
 * Get access to the registers structure and unpacked fields.
 * Use LMS7002M_regs_spi_write()/LMS7002M_regs_spi_read()
 * to sync the fields in this structure with the device.
 * \param self an instance of the LMS7002M driver
 * \return the pointer to the unpacked LMS7002M fields
 */
LMS7002M_API LMS7002M_regs_t *LMS7002M_regs(LMS7002M_t *self);

/*!
 * Write the entire internal register cache to the RFIC.
 * \param self an instance of the LMS7002M driver
 */
LMS7002M_API void LMS7002M_regs_to_rfic(LMS7002M_t *self);

/*!
 * Read the the entire RFIC into the internal register cache.
 * \param self an instance of the LMS7002M driver
 */
LMS7002M_API void LMS7002M_rfic_to_regs(LMS7002M_t *self);

/*!
 * Dump the known registers to an INI format like the one used by the EVB7 GUI.
 * \param self an instance of the LMS7002M driver
 * \param path the path to a .ini output file
 * \return 0 for success otherwise failure
 */
LMS7002M_API int LMS7002M_dump_ini(LMS7002M_t *self, const char *path);

/*!
 * Load registers from an INI format like the one used by the EVB7 GUI.
 * \param self an instance of the LMS7002M driver
 * \param path the path to a .ini input file
 * \return 0 for success otherwise failure
 */
LMS7002M_API int LMS7002M_load_ini(LMS7002M_t *self, const char *path);

//=====================================================================//
// LML (Lime light)
// The input and output data ports and associated muxes.
//=====================================================================//

/*!
 * Set the SPI mode (4-wire or 3-wire).
 * We recommend that you set this before any additional communication.
 * \param self an instance of the LMS7002M driver
 * \param numWires the number 3 or the number 4
 */
LMS7002M_API void LMS7002M_set_spi_mode(LMS7002M_t *self, const int numWires);

/*!
 * Perform all soft and hard resets available.
 * Call this first to put the LMS7002M into a known state.
 * \param self an instance of the LMS7002M driver
 */
LMS7002M_API void LMS7002M_reset(LMS7002M_t *self);

/*!
 * Reset all logic registers and FIFO state.
 * Use after configuring and before streaming.
 * \param self an instance of the LMS7002M driver
 * \param direction the direction LMS_TX or LMS_RX
 */
LMS7002M_API void LMS7002M_reset_lml_fifo(LMS7002M_t *self, const LMS7002M_dir_t direction);

/*!
 * Put all available hardware into disable/power-down mode.
 * Call this last before destroying the LMS7002M instance.
 * \param self an instance of the LMS7002M driver
 */
LMS7002M_API void LMS7002M_power_down(LMS7002M_t *self);

/*!
 * Configure the muxing and clocking on a lime light port.
 * This sets the data mode and direction for the DIQ pins,
 * and selects the appropriate clock and stream muxes.
 * This call is not compatible with JESD207 operation.
 *
 * The mclkDiv must be 1 for no divider, or an even value.
 * Odd divider values besides 1 (bypass) are not allowed.
 *
 * \param self an instance of the LMS7002M driver
 * \param portNo the lime light data port 1 or 2
 * \param direction the direction LMS_TX or LMS_RX
 * \param mclkDiv the output clock divider ratio
 */
LMS7002M_API void LMS7002M_configure_lml_port(LMS7002M_t *self, const LMS7002M_port_t portNo, const LMS7002M_dir_t direction, const int mclkDiv);

/*!
 * Invert the feedback clock used with the transmit pins.
 * This call inverts both FCLK1 and FCLK2 (only one of which is used).
 * \param self an instance of the LMS7002M driver
 * \param invert true to invert the clock
 */
LMS7002M_API void LMS7002M_invert_fclk(LMS7002M_t *self, const bool invert);

/*!
 * Delays the feedback clock used with the transmit pins.
 * This call Delays both FCLK1 and FCLK2 (only one of which is used).
 * \param self an instance of the LMS7002M driver
 * \param delay how much to delay the clock (0-3)
 */
LMS7002M_API void LMS7002M_delay_fclk(LMS7002M_t *self, const int delay);

/*!
 * Enable digital loopback inside the lime light.
 * This call also applies the tx fifo write clock to the rx fifo.
 * To undo the effect of this loopback, call LMS7002M_configure_lml_port().
 * \param self an instance of the LMS7002M driver
 */
LMS7002M_API void LMS7002M_setup_digital_loopback(LMS7002M_t *self);

/*!
 * Set the MAC mux for channel A/B shadow registers.
 * This call does not incur a register write if the value is unchanged.
 * This call is mostly used internally by other calls that have to set the MAC.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 */
LMS7002M_API void LMS7002M_set_mac_ch(LMS7002M_t *self, const LMS7002M_chan_t channel);

/*!
 * Set the MAC mux for direction TX/RX shadow registers.
 * For SXT and SXR, MAX is used for direction and not channel control.
 * This call does not incur a register write if the value is unchanged.
 * This call is mostly used internally by other calls that have to set the MAC.
 * \param self an instance of the LMS7002M driver
 * \param direction the direction LMS_TX or LMS_RX
 */
LMS7002M_API void LMS7002M_set_mac_dir(LMS7002M_t *self, const LMS7002M_dir_t direction);

#define LMS7002M_LML_AI 0 //!< specify CHA I for a sample position
#define LMS7002M_LML_AQ 1 //!< specify CHA Q for a sample position
#define LMS7002M_LML_BI 2 //!< specify CHB I for a sample position
#define LMS7002M_LML_BQ 3 //!< specify CHB Q for a sample position

/*!
 * Set the DIQ mux to control CHA and CHB I and Q ordering.
 * \param self an instance of the LMS7002M driver
 * \param direction the direction LMS_TX or LMS_RX
 * \param positions sample position 0-3 (see LMS7002M_LML_*)
 */
LMS7002M_API void LMS7002M_set_diq_mux(LMS7002M_t *self, const LMS7002M_dir_t direction, const int positions[4]);

//=====================================================================//
// LDO
//=====================================================================//

#define LMS7002M_LDO_ALL 0 //!< A group that represents all LDOs

/*!
 * Enable/disable a group of LDOs.
 * \param self an instance of the LMS7002M driver
 * \param enable true to enable, false to power down
 * \param group a group of LDOs see LMS7002M_LDO_*
 */
LMS7002M_API void LMS7002M_ldo_enable(LMS7002M_t *self, const bool enable, const int group);

//=====================================================================//
// XBUF
//=====================================================================//

/*!
 * Share the TX XBUF clock chain to the RX XBUF clock chain.
 * Enabled sharing when there is no clock provided to the RX input.
 * \param self an instance of the LMS7002M driver
 * \param enable true to enable sharing, false to use separate inputs
 */
LMS7002M_API void LMS7002M_xbuf_share_tx(LMS7002M_t *self, const bool enable);

/*!
 * Enable input biasing the DC voltage level for clock inputs.
 * When disabled, the input clocks should be DC coupled.
 * \param self an instance of the LMS7002M driver
 * \param enable true to enable input bias, false to disable
 */
LMS7002M_API void LMS7002M_xbuf_enable_bias(LMS7002M_t *self, const bool enable);

//=====================================================================//
// AFE (ADCs and DACs)
//=====================================================================//

/*!
 * Enable/disable individual DACs and ADCs in the AFE section.
 * Use the direction and channel parameters to specify a DAC/DAC.
 * \param self an instance of the LMS7002M driver
 * \param direction the direction LMS_TX or LMS_RX
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param enable true to enable, false to power down
 */
LMS7002M_API void LMS7002M_afe_enable(LMS7002M_t *self, const LMS7002M_dir_t direction, const LMS7002M_chan_t channel, const bool enable);

//=====================================================================//
// CGEN (clock generation)
//=====================================================================//

/*!
 * Configure the ADC/DAC clocking given the reference and the desired rate.
 * This is a helper function that may make certain non-ideal assumptions,
 * for example this calculation will always make use of fractional-N tuning.
 * Also, this function does not directly set the clock muxing (see CGEN section).
 * \param self an instance of the LMS7002M driver
 * \param fref the reference clock frequency in Hz
 * \param fout the desired data clock frequency in Hz
 * \param factual the actual clock rate in Hz (or NULL)
 * \return 0 for success or error code on failure
 */
LMS7002M_API int LMS7002M_set_data_clock(LMS7002M_t *self, const double fref, const double fout, double *factual);

//=====================================================================//
// Shared helper functions for Rx and TX tsp
//=====================================================================//

/*!
 * Set the frequency for the specified NCO.
 * Most users should use LMS7002M_xxtsp_set_freq() to handle bypasses.
 * Note: there is a size 16 table for every NCO, we are just using entry 0.
 * Math: freqHz = freqRel * sampleRate
 * \param self an instance of the LMS7002M driver
 * \param direction the direction LMS_TX or LMS_RX
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param freqRel a fractional frequency in (-0.5, 0.5)
 */
LMS7002M_API void LMS7002M_set_nco_freq(LMS7002M_t *self, const LMS7002M_dir_t direction, const LMS7002M_chan_t channel, const double freqRel);

/*!
 * Set the filter taps for one of the TSP FIR filters.
 *
 * If the taps array is NULL or the ntaps is 0,
 * then the specified filter will be bypassed,
 * otherwise, the specified filter is enabled.
 *
 * An error will be returned when the taps size is incorrect,
 * or if a non-existent filter is selected (use 1, 2, or 3).
 * Filters 1 and 2 are 40 taps, while filter 3 is 120 taps.
 *
 * \param self an instance of the LMS7002M driver
 * \param direction the direction LMS_TX or LMS_RX
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param which which FIR filter 1, 2, or 3
 * \param taps a pointer to an array of taps
 * \param ntaps the size of the taps array
 * \return 0 for success or error code on failure
 */
LMS7002M_API int LMS7002M_set_gfir_taps(
    LMS7002M_t *self,
    const LMS7002M_dir_t direction,
    const LMS7002M_chan_t channel,
    const int which,
    const short *taps,
    const size_t ntaps);

//=====================================================================//
// SXR and SXT (LO synthesizers)
//=====================================================================//

/*!
 * Enable/disable the synthesizer.
 * \param self an instance of the LMS7002M driver
 * \param direction the direction LMS_TX or LMS_RX
 * \param enable true to enable, false to power down
 */
LMS7002M_API void LMS7002M_sxx_enable(LMS7002M_t *self, const LMS7002M_dir_t direction, const bool enable);

/*!
 * The simplified tuning algorithm for the RX and TX local oscillators.
 * Each oscillator is shared between both channels A and B.
 * This is a helper function that may make certain non-ideal assumptions,
 * for example this calculation will always make use of fractional-N tuning.
 * \param self an instance of the LMS7002M driver
 * \param direction the direction LMS_TX or LMS_RX
 * \param fref the reference clock frequency in Hz
 * \param fout the desired LO frequency in Hz
 * \param factual the actual LO frequency in Hz (or NULL)
 * \return 0 for success or error code on failure
 */
LMS7002M_API int LMS7002M_set_lo_freq(LMS7002M_t *self, const LMS7002M_dir_t direction, const double fref, const double fout, double *factual);

/*!
 * Share the transmit LO to the receive chain.
 * This is useful for TDD modes which use the same LO for Rx and Tx.
 * The default is disabled. Its recommended to disable SXR when using.
 * \param self an instance of the LMS7002M driver
 * \param enable true to enable, false to power down
 */
LMS7002M_API void LMS7002M_sxt_to_sxr(LMS7002M_t *self, const bool enable);

//=====================================================================//
// TxTSP (transmit DSP chain)
//=====================================================================//

/*!
 * Initialize the TX TSP chain by:
 * Clearing configuration values, enabling the chain,
 * and bypassing IQ gain, phase, DC corrections, and filters.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param enable true to enable, false to disable
 */
LMS7002M_API void LMS7002M_txtsp_enable(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable);

/*!
 * Set the TX TSP chain interpolation.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param interp the interpolation 1, 2, 4, 8, 16, 32
 */
LMS7002M_API void LMS7002M_txtsp_set_interp(LMS7002M_t *self, const LMS7002M_chan_t channel, const size_t interp);

/*!
 * Set the TX TSP CMIX frequency.
 * Math: freqHz = TSPRate * sampleRate
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param freqRel a fractional frequency in (-0.5, 0.5)
 */
LMS7002M_API void LMS7002M_txtsp_set_freq(LMS7002M_t *self, const LMS7002M_chan_t channel, const double freqRel);

/*!
 * Test constant signal level for TX TSP chain.
 * Use LMS7002M_txtsp_enable() to restore regular mode.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param valI the I constant value
 * \param valQ the Q constant value
 */
LMS7002M_API void LMS7002M_txtsp_tsg_const(LMS7002M_t *self, const LMS7002M_chan_t channel, const int valI, const int valQ);

/*!
 * Test tone signal for TX TSP chain (TSP clk/8).
 * Use LMS7002M_txtsp_enable() to restore regular mode.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 */
LMS7002M_API void LMS7002M_txtsp_tsg_tone(LMS7002M_t *self, const LMS7002M_chan_t channel);

/*!
 * DC offset correction value for Tx TSP chain.
 * Correction values are maximum 1.0 (full scale).
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param valI the I correction value
 * \param valQ the Q correction value
 */
LMS7002M_API void LMS7002M_txtsp_set_dc_correction(
    LMS7002M_t *self,
    const LMS7002M_chan_t channel,
    const double valI,
    const double valQ);

/*!
 * IQ imbalance correction value for Tx TSP chain.
 *
 * - The gain is the ratio of I/Q, and should be near 1.0
 * - Gain values greater than 1.0 max out I and reduce Q.
 * - Gain values less than 1.0 max out Q and reduce I.
 * - A gain value of 1.0 bypasses the magnitude correction.
 * - A phase value of 0.0 bypasses the phase correction.
 *
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param phase the phase correction (radians)
 * \param gain the magnitude correction (I/Q ratio)
 */
LMS7002M_API void LMS7002M_txtsp_set_iq_correction(
    LMS7002M_t *self,
    const LMS7002M_chan_t channel,
    const double phase,
    const double gain);

//=====================================================================//
// TBB (transmit baseband chain)
//=====================================================================//

#define LMS7002M_TBB_BYP (int)'B'  //!< Bypass filters path selected
#define LMS7002M_TBB_S5  (int)'S'  //!< Low band single pole path selected
#define LMS7002M_TBB_LAD (int)'A'  //!< Low band ladder filter path selected
#define LMS7002M_TBB_LBF (int)'L'  //!< Low band (ladder + S5) path selected
#define LMS7002M_TBB_HBF (int)'H'  //!< High band filter path selected

#define LMS7002M_TBB_TSTIN_OFF 0 //!< Disable test input signal
#define LMS7002M_TBB_TSTIN_LBF 1 //!< Test signal to highband
#define LMS7002M_TBB_TSTIN_HBF 2 //!< Test signal to lowband
#define LMS7002M_TBB_TSTIN_AMP 3 //!< Test signal to current amp

#define LMS7002M_TBB_LB_DISCONNECTED 0 //!< Loopback disconnected
#define LMS7002M_TBB_LB_DAC_CURRENT 1 //!< DAC current
#define LMS7002M_TBB_LB_LB_LADDER 2 //!< low band ladder
#define LMS7002M_TBB_LB_MAIN_TBB 3 //!< TX baseband

/*!
 * Enable/disable the TX baseband.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param enable true to enable, false to power down
 */
LMS7002M_API void LMS7002M_tbb_enable(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable);

/*!
 * Select the data path for the TX baseband.
 * Use this to select loopback and filter paths.
 * Calling LMS7002M_tbb_set_filter_bw() will also
 * set the path based on the filter bandwidth setting.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param path the input path (see LMS7002M_TBB_* defines)
 */
LMS7002M_API void LMS7002M_tbb_set_path(LMS7002M_t *self, const LMS7002M_chan_t channel, const int path);

/*!
 * Configure the test input signal to the TX BB component.
 * The default is disabled (LMS7002M_TBB_TSTIN_OFF).
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param path the input path (see LMS7002M_TBB_TSTIN_* defines)
 */
LMS7002M_API void LMS7002M_tbb_set_test_in(LMS7002M_t *self, const LMS7002M_chan_t channel, const int path);

/*!
 * Enable/disable the TX BB loopback to RBB.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param mode loopback mode (see LMS7002M_TBB_LB_* defines)
 * \param swap true to swap I and Q in the loopback
 */
LMS7002M_API void LMS7002M_tbb_enable_loopback(LMS7002M_t *self, const LMS7002M_chan_t channel, const int mode, const bool swap);

/*!
 * Set the TX baseband filter bandwidth.
 * The actual bandwidth will be greater than or equal to the requested bandwidth.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param bw the complex bandwidth in Hz
 * \param bwactual the actual filter width in Hz or NULL
 * \return 0 for success or error code on failure
 */
LMS7002M_API int LMS7002M_tbb_set_filter_bw(LMS7002M_t *self, const LMS7002M_chan_t channel, const double bw, double *bwactual);

//=====================================================================//
// TRF (transmit RF frontend)
//=====================================================================//

/*!
 * Enable/disable the TX RF frontend.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param enable true to enable, false to power down
 */
LMS7002M_API void LMS7002M_trf_enable(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable);

/*!
 * Select the TX RF band (band 1 or band 2)
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param band the band number, values 1 or 2
 */
LMS7002M_API void LMS7002M_trf_select_band(LMS7002M_t *self, const LMS7002M_chan_t channel, const int band);

/*!
 * Enable/disable the TX RF loopback to RFE.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param enable true to enable the loopback
 */
LMS7002M_API void LMS7002M_trf_enable_loopback(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable);

/*!
 * Set the PAD gain (loss) for the TX RF frontend.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param gain the gain value in dB -52.0 to 0.0
 * \return the actual gain value in dB
 */
LMS7002M_API double LMS7002M_trf_set_pad(LMS7002M_t *self, const LMS7002M_chan_t channel, const double gain);

/*!
 * Set the PAD gain (loss) for the TX RF frontend (in RX loopback mode).
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param gain the gain value in dB -24.0 to 0.0
 * \return the actual gain value in dB
 */
LMS7002M_API double LMS7002M_trf_set_loopback_pad(LMS7002M_t *self, const LMS7002M_chan_t channel, const double gain);

//=====================================================================//
// RxTSP (receive DSP chain)
//=====================================================================//

/*!
 * Initialize the RX TSP chain by:
 * Clearing configuration values, enabling the chain,
 * and bypassing IQ gain, phase, DC corrections, filters, and AGC.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param enable true to enable, false to disable
 */
LMS7002M_API void LMS7002M_rxtsp_enable(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable);

/*!
 * Set the RX TSP chain decimation.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param decim the decimation 1, 2, 4, 8, 16, 32
 */
LMS7002M_API void LMS7002M_rxtsp_set_decim(LMS7002M_t *self, const LMS7002M_chan_t channel, const size_t decim);

/*!
 * Set the RX TSP CMIX frequency.
 * Math: freqHz = TSPRate * sampleRate
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param freqRel a fractional frequency in (-0.5, 0.5)
 */
LMS7002M_API void LMS7002M_rxtsp_set_freq(LMS7002M_t *self, const LMS7002M_chan_t channel, const double freqRel);

/*!
 * Test constant signal level for RX TSP chain.
 * Use LMS7002M_rxtsp_enable() to restore regular mode.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param valI the I constant value
 * \param valQ the Q constant value
 */
LMS7002M_API void LMS7002M_rxtsp_tsg_const(LMS7002M_t *self, const LMS7002M_chan_t channel, const int valI, const int valQ);

/*!
 * Test tone signal for RX TSP chain (TSP clk/8).
 * Use LMS7002M_rxtsp_enable() to restore regular mode.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 */
LMS7002M_API void LMS7002M_rxtsp_tsg_tone(LMS7002M_t *self, const LMS7002M_chan_t channel);

/*!
 * Read the digital RSSI indicator in the Rx TSP chain.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \return the RSSI as an unsigned 16-bit number
 */
LMS7002M_API uint16_t LMS7002M_rxtsp_read_rssi(LMS7002M_t *self, const LMS7002M_chan_t channel);

/*!
 * DC offset correction value for Rx TSP chain.
 * This subtracts out the average signal level.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param enabled true to enable correction
 * \param window average window length 0-7 (def 0)
 */
LMS7002M_API void LMS7002M_rxtsp_set_dc_correction(
    LMS7002M_t *self,
    const LMS7002M_chan_t channel,
    const bool enabled,
    const int window);

/*!
 * IQ imbalance correction value for Rx TSP chain.
 *
 * - The gain is the ratio of I/Q, and should be near 1.0
 * - Gain values greater than 1.0 max out I and reduce Q.
 * - Gain values less than 1.0 max out Q and reduce I.
 * - A gain value of 1.0 bypasses the magnitude correction.
 * - A phase value of 0.0 bypasses the phase correction.
 *
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param phase the phase correction (radians)
 * \param gain the magnitude correction (I/Q ratio)
 */
LMS7002M_API void LMS7002M_rxtsp_set_iq_correction(
    LMS7002M_t *self,
    const LMS7002M_chan_t channel,
    const double phase,
    const double gain);

//=====================================================================//
// RBB (receive baseband chain)
//=====================================================================//

#define LMS7002M_RBB_BYP (int)'B'  //!< Bypass filters path selected
#define LMS7002M_RBB_LBF (int)'L'  //!< Low band filter path selected
#define LMS7002M_RBB_HBF (int)'H'  //!< High band filter path selected
#define LMS7002M_RBB_LB_BYP 0      //!< Bypass filters with loopback from TXBB
#define LMS7002M_RBB_LB_LBF 1      //!< Low band filter with loopback from TXBB
#define LMS7002M_RBB_LB_HBF 2      //!< High band filter with loopback from TXBB

/*!
 * Enable/disable the RX baseband.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param enable true to enable, false to power down
 */
LMS7002M_API void LMS7002M_rbb_enable(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable);

/*!
 * Select the data path for the RX baseband.
 * Use this to select loopback and filter paths.
 * Calling LMS7002M_rbb_set_filter_bw() will also
 * set the path based on the filter bandwidth setting.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param path the input path (see LMS7002M_RBB_* defines)
 */
LMS7002M_API void LMS7002M_rbb_set_path(LMS7002M_t *self, const LMS7002M_chan_t channel, const int path);

/*!
 * Configure the test output signal from the RX BB component.
 * The default is false meaning that the RBB outputs to the ADC.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param enable true to output RBB to pad, false for ADC
 */
LMS7002M_API void LMS7002M_rbb_set_test_out(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable);

/*!
 * Set the PGA gain for the RX baseband.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param gain the gain value in dB -12.0 to 19.0
 * \return the actual gain value in dB
 */
LMS7002M_API double LMS7002M_rbb_set_pga(LMS7002M_t *self, const LMS7002M_chan_t channel, const double gain);

/*!
 * Set the RX baseband filter bandwidth.
 * The actual bandwidth will be greater than or equal to the requested bandwidth.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param bw the complex bandwidth in Hz
 * \param bwactual the actual filter width in Hz or NULL
 * \return 0 for success or error code on failure
 */
LMS7002M_API int LMS7002M_rbb_set_filter_bw(LMS7002M_t *self, const LMS7002M_chan_t channel, const double bw, double *bwactual);

//=====================================================================//
// RFE (receive RF frontend)
//=====================================================================//

#define LMS7002M_RFE_NONE (int)'N'     //!< No input path selected
#define LMS7002M_RFE_LNAH (int)'H'     //!< LNAH path selected
#define LMS7002M_RFE_LNAL (int)'L'     //!< LNAL path selected
#define LMS7002M_RFE_LNAW (int)'W'     //!< LNAW path selected
#define LMS7002M_RFE_LB1 (int)'1'      //!< loopback 1 path selected (W)
#define LMS7002M_RFE_LB2 (int)'2'      //!< loopback 2 path selected (L)

/*!
 * Enable/disable the RX RF frontend.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param enable true to enable, false to power down
 */
LMS7002M_API void LMS7002M_rfe_enable(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable);

/*!
 * Select the active input path for the RX RF frontend.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param path the input path (see LMS7002M_RFE_* defines)
 */
LMS7002M_API void LMS7002M_rfe_set_path(LMS7002M_t *self, const LMS7002M_chan_t channel, const int path);

/*!
 * Set the LNA gain for the RX RF frontend.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param gain the gain value in dB 0 to 30
 * \return the actual gain value in dB
 */
LMS7002M_API double LMS7002M_rfe_set_lna(LMS7002M_t *self, const LMS7002M_chan_t channel, const double gain);

/*!
 * Set the LNA gain for the RX RF frontend (in TX loopback mode).
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param gain the gain value in dB 0 to 40
 * \return the actual gain value in dB
 */
LMS7002M_API double LMS7002M_rfe_set_loopback_lna(LMS7002M_t *self, const LMS7002M_chan_t channel, const double gain);

/*!
 * Set the TIA gain for the RX RF frontend.
 * \param self an instance of the LMS7002M driver
 * \param channel the channel LMS_CHA or LMS_CHB
 * \param gain the gain value in dB 0 to 12
 * \return the actual gain value in dB
 */
LMS7002M_API double LMS7002M_rfe_set_tia(LMS7002M_t *self, const LMS7002M_chan_t channel, const double gain);

#ifdef __cplusplus
}
#endif
