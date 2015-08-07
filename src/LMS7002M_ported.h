/*!
 * This is a port of enum and function definitions from the lms7api C++ project.
 */

#include "LMS7002M_impl.h"
#include "LMS7002M_parameters.h"
#include "LMS7002M_statuses.h"
#include <stdint.h>
#include <stdbool.h>

typedef double float_type;

///Reference clock used for Receiver frequency calculations
#define mRefClkSXR_MHz self->sxr_fref_mhz

///Reference clock used for Transmitter frequency calculations
#define mRefClkSXT_MHz self->sxt_fref_mhz

enum
{
    Rx, Tx
};

///@name Registers writing and reading
uint16_t Get_SPI_Reg_bits(LMS7002M_t *self, const LMS7Parameter *param);
uint16_t Get_SPI_Reg_bits_(LMS7002M_t *self, uint16_t address, uint8_t msb, uint8_t lsb);
liblms7_status Modify_SPI_Reg_bits(LMS7002M_t *self, const LMS7Parameter *param, const uint16_t new_bits_data);
liblms7_status Modify_SPI_Reg_bits_(LMS7002M_t *self, uint16_t address, uint8_t msb, uint8_t lsb, uint16_t new_bits_data);
liblms7_status SPI_write(LMS7002M_t *self, uint16_t spiAddrReg, uint16_t spiDataReg);
uint16_t SPI_read(LMS7002M_t *self, uint16_t spiAddrReg, liblms7_status *status);
liblms7_status RegistersTest(LMS7002M_t *self);
//@}

///@name Transmitter, Receiver calibrations
liblms7_status CalibrateRx(LMS7002M_t *self, float_type bandwidth_MHz);
liblms7_status CalibrateTx(LMS7002M_t *self, float_type bandwidth_MHz);
//@}

///@name Filters calibrations
typedef enum
{
    TX_LADDER, TX_REALPOLE, TX_HIGHBAND
} TxFilter;
typedef enum
{
    RX_TIA, RX_LPF_LOWBAND, RX_LPF_HIGHBAND
} RxFilter;
liblms7_status TuneTxFilter(LMS7002M_t *self, TxFilter filterType, float_type bandwidth_MHz);
liblms7_status TuneTxFilterLowBandChain(LMS7002M_t *self, float_type ladder_bw_MHz, float_type realpole_bw_MHz);
liblms7_status TuneRxFilter(LMS7002M_t *self, RxFilter filterType, float_type bandwidth_MHz);
//@}

///@name CGEN and PLL
float_type GetFrequencyCGEN_MHz();
liblms7_status SetFrequencyCGEN(LMS7002M_t *self, float_type freq_MHz);
float_type GetFrequencySX_MHz(LMS7002M_t *self, bool tx, float_type refClk_MHz);
liblms7_status SetFrequencySX(LMS7002M_t *self, bool tx, float_type freq_MHz, float_type refClk_MHz);
///VCO modules available for tuning
typedef enum
{
    VCO_CGEN, VCO_SXR, VCO_SXT
} VCO_Module;
liblms7_status TuneVCO(LMS7002M_t *self, VCO_Module module);
//@}

///@name TSP
liblms7_status LoadDC_REG_IQ(LMS7002M_t *self, bool tx, int16_t I, int16_t Q);
liblms7_status SetNCOFrequency(LMS7002M_t *self, bool tx, uint8_t index, float_type freq_MHz);
float_type GetNCOFrequency_MHz(LMS7002M_t *self, bool tx, uint8_t index);
liblms7_status SetNCOPhaseOffset(LMS7002M_t *self, bool tx, uint8_t index, float_type angle_Deg);
float_type GetNCOPhaseOffset_Rad(LMS7002M_t *self, bool tx, uint8_t index);
liblms7_status SetGFIRCoefficients(LMS7002M_t *self, bool tx, uint8_t GFIR_index, const int16_t *coef, uint8_t coefCount);
liblms7_status GetGFIRCoefficients(LMS7002M_t *self, bool tx, uint8_t GFIR_index, int16_t *coef, uint8_t coefCount);
//@}

liblms7_status SetInterfaceFrequency(LMS7002M_t *self, float_type cgen_freq_MHz, uint8_t interpolation, uint8_t decimation);
liblms7_status CaptureIQSamples(LMS7002M_t *self, int16_t *isamples, int16_t *qsamples, uint32_t framesCount, bool frameStart);

///enumeration to indicate module registers intervals
typedef enum
{
    LimeLight = 0, EN_DIR, AFE, BIAS, XBUF, CGEN, LDO, BIST, CDS,
    TRF, TBB, RFE, RBB, SX, TxTSP,
    TxNCO, TxGFIR1, TxGFIR2, TxGFIR3a, TxGFIR3b, TxGFIR3c,
    RxTSP, RxNCO, RxGFIR1, RxGFIR2, RxGFIR3a, RxGFIR3b, RxGFIR3c,
    MEMORY_SECTIONS_COUNT
} MemorySection;
liblms7_status SetDefaults(LMS7002M_t *self, MemorySection module);

extern uint16_t MemorySectionAddresses[MEMORY_SECTIONS_COUNT][2];
///@name Algorithms functions
void BackupAllRegisters(LMS7002M_t *self);
void RestoreAllRegisters(LMS7002M_t *self);
uint32_t GetRSSI(LMS7002M_t *self);
void SetRxDCOFF(LMS7002M_t *self, int8_t offsetI, int8_t offsetQ);
uint32_t FindMinRSSI_Gain(LMS7002M_t *self, const LMS7Parameter *param, uint16_t *foundValue);
uint32_t FindMinRSSI(LMS7002M_t *self, const LMS7Parameter *param, const int16_t startValue, int16_t *result, const uint8_t scanWidth, const uint8_t twoCompl, int8_t stepMult);
uint32_t FindMinRSSI_(LMS7002M_t *self, const uint16_t addr, const uint8_t msb, const uint8_t lsb, const int16_t startValue, int16_t *result, const uint8_t scanWidth, const uint8_t twoCompl, int8_t stepMult);
void CalibrateRxDC_RSSI(LMS7002M_t *self);
liblms7_status CalibrateTxSetup(LMS7002M_t *self, float_type bandwidth_MHz);
liblms7_status CalibrateRxSetup(LMS7002M_t *self, float_type bandwidth_MHz);
liblms7_status FixRXSaturation(LMS7002M_t *self);
void FilterTuning_AdjustGains(LMS7002M_t *self);
liblms7_status TuneTxFilterSetup(LMS7002M_t *self, TxFilter type, float_type cutoff_MHz);
liblms7_status TuneRxFilterSetup(LMS7002M_t *self, RxFilter type, float_type cutoff_MHz);
liblms7_status RFE_TIA_Calibration(LMS7002M_t *self, float_type TIA_freq_MHz);
liblms7_status RxLPFLow_Calibration(LMS7002M_t *self, float_type RxLPFL_freq_MHz);
liblms7_status RxLPFHigh_Calibration(LMS7002M_t *self, float_type RxLPFH_freq_MHz);

liblms7_status SPI_write_batch(LMS7002M_t *self, const uint16_t* spiAddr, const uint16_t* spiData, uint16_t cnt);
liblms7_status SPI_read_batch(LMS7002M_t *self, const uint16_t* spiAddr, uint16_t* spiData, uint16_t cnt);
liblms7_status Modify_SPI_Reg_mask(LMS7002M_t *self, const uint16_t *addr, const uint16_t *masks, const uint16_t *values, uint8_t start, uint8_t stop);
//@}

float_type GetReferenceClk_TSP_MHz(LMS7002M_t *self, bool tx);
