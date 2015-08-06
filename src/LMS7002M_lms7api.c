/*!
 * This is a C port of function implementations from the lms7api C++ project.
 */

#include "LMS7002M_lms7api.h"

#define VECTOR_MAX 1024

///Reference clock used for Receiver frequency calculations
float_type mRefClkSXR_MHz;
///Reference clock used for Transmitter frequency calculations
float_type mRefClkSXT_MHz;

uint16_t MemorySectionAddresses[MEMORY_SECTIONS_COUNT][2];

void LMS7002M_lms7api_init(void)
{
    mRefClkSXR_MHz = 30.72;
    mRefClkSXT_MHz = 30.72;

    //memory intervals for registers tests and calibration algorithms
    MemorySectionAddresses[LimeLight][0] = 0x0020;
    MemorySectionAddresses[LimeLight][1] = 0x002F;
    MemorySectionAddresses[EN_DIR][0] = 0x0081;
    MemorySectionAddresses[EN_DIR][1] = 0x0081;
    MemorySectionAddresses[AFE][0] = 0x0082;
    MemorySectionAddresses[AFE][1] = 0x0082;
    MemorySectionAddresses[BIAS][0] = 0x0084;
    MemorySectionAddresses[BIAS][1] = 0x0084;
    MemorySectionAddresses[XBUF][0] = 0x0085;
    MemorySectionAddresses[XBUF][1] = 0x0085;
    MemorySectionAddresses[CGEN][0] = 0x0086;
    MemorySectionAddresses[CGEN][1] = 0x008C;
    MemorySectionAddresses[LDO][0] = 0x0092;
    MemorySectionAddresses[LDO][1] = 0x00A7;
    MemorySectionAddresses[BIST][0] = 0x00A8;
    MemorySectionAddresses[BIST][1] = 0x00AC;
    MemorySectionAddresses[CDS][0] = 0x00AD;
    MemorySectionAddresses[CDS][1] = 0x00AE;
    MemorySectionAddresses[TRF][0] = 0x0100;
    MemorySectionAddresses[TRF][1] = 0x0104;
    MemorySectionAddresses[TBB][0] = 0x0105;
    MemorySectionAddresses[TBB][1] = 0x010A;
    MemorySectionAddresses[RFE][0] = 0x010C;
    MemorySectionAddresses[RFE][1] = 0x0114;
    MemorySectionAddresses[RBB][0] = 0x0115;
    MemorySectionAddresses[RBB][1] = 0x011A;
    MemorySectionAddresses[SX][0] = 0x011C;
    MemorySectionAddresses[SX][1] = 0x0124;
    MemorySectionAddresses[TxTSP][0] = 0x0200;
    MemorySectionAddresses[TxTSP][1] = 0x020C;
    MemorySectionAddresses[TxNCO][0] = 0x0240;
    MemorySectionAddresses[TxNCO][1] = 0x0261;
    MemorySectionAddresses[TxGFIR1][0] = 0x0280;
    MemorySectionAddresses[TxGFIR1][1] = 0x02A7;
    MemorySectionAddresses[TxGFIR2][0] = 0x02C0;
    MemorySectionAddresses[TxGFIR2][1] = 0x02E7;
    MemorySectionAddresses[TxGFIR3a][0] = 0x0300;
    MemorySectionAddresses[TxGFIR3a][1] = 0x0327;
    MemorySectionAddresses[TxGFIR3b][0] = 0x0340;
    MemorySectionAddresses[TxGFIR3b][1] = 0x0367;
    MemorySectionAddresses[TxGFIR3c][0] = 0x0380;
    MemorySectionAddresses[TxGFIR3c][1] = 0x03A7;
    MemorySectionAddresses[RxTSP][0] = 0x0400;
    MemorySectionAddresses[RxTSP][1] = 0x040F;
    MemorySectionAddresses[RxNCO][0] = 0x0440;
    MemorySectionAddresses[RxNCO][1] = 0x0461;
    MemorySectionAddresses[RxGFIR1][0] = 0x0480;
    MemorySectionAddresses[RxGFIR1][1] = 0x04A7;
    MemorySectionAddresses[RxGFIR2][0] = 0x04C0;
    MemorySectionAddresses[RxGFIR2][1] = 0x04E7;
    MemorySectionAddresses[RxGFIR3a][0] = 0x0500;
    MemorySectionAddresses[RxGFIR3a][1] = 0x0527;
    MemorySectionAddresses[RxGFIR3b][0] = 0x0540;
    MemorySectionAddresses[RxGFIR3b][1] = 0x0567;
    MemorySectionAddresses[RxGFIR3c][0] = 0x0580;
    MemorySectionAddresses[RxGFIR3c][1] = 0x05A7;
}

/**	@return Current CLKGEN frequency in MHz
    Returned frequency depends on reference clock used for Receiver
*/
float_type GetFrequencyCGEN_MHz(LMS7002M_t *self)
{
    float_type dMul = (mRefClkSXR_MHz/2.0)/(Get_SPI_Reg_bits(self, LMS7param(DIV_OUTCH_CGEN))+1); //DIV_OUTCH_CGEN
    uint16_t gINT = Get_SPI_Reg_bits_(self, 0x0088, 13, 0); //read whole register to reduce SPI transfers
    uint32_t gFRAC = ((gINT & 0xF) * 65536) | Get_SPI_Reg_bits_(self, 0x0087, 15, 0);
    return dMul * (((gINT>>4) + 1 + gFRAC/1048576.0));
}

/** @brief Returns TSP reference frequency
    @param tx TxTSP or RxTSP selection
    @return TSP reference frequency in MHz
*/
float_type GetReferenceClk_TSP_MHz(LMS7002M_t *self, bool tx)
{
    float_type cgenFreq = GetFrequencyCGEN_MHz(self);
	float_type clklfreq = cgenFreq/(1 << Get_SPI_Reg_bits(self, LMS7param(CLKH_OV_CLKL_CGEN)) );
    if(Get_SPI_Reg_bits(self, LMS7param(EN_ADCCLKH_CLKGN)) == 0)
        return tx ? clklfreq : cgenFreq/4.0;
    else
        return tx ? cgenFreq : clklfreq/4.0;
}

#define CLKGEN_VCO_HIGH 2700
/** @brief Sets CLKGEN frequency, calculations use receiver'r reference clock
    @param freq_MHz desired frequency in MHz
    @return 0-succes, other-cannot deliver desired frequency
*/
liblms7_status SetFrequencyCGEN(LMS7002M_t *self, const float_type freq_MHz)
{
    float_type dFvco;
    float_type dFrac;
    int16_t iHdiv;

    //VCO frequency selection according to F_CLKH
	iHdiv = (int16_t)((CLKGEN_VCO_HIGH/2)/freq_MHz)-1;
	dFvco = 2*(iHdiv+1) * freq_MHz;

    //Integer division
    uint16_t gINT = (uint16_t)(dFvco/mRefClkSXR_MHz - 1);

    //Fractional division
    dFrac = dFvco/mRefClkSXR_MHz - (uint32_t)(dFvco/mRefClkSXR_MHz);
    uint32_t gFRAC = (uint32_t)(dFrac * 1048576);

    Modify_SPI_Reg_bits(self, LMS7param(INT_SDM_CGEN), gINT); //INT_SDM_CGEN
    Modify_SPI_Reg_bits_(self, 0x0087, 15, 0, gFRAC&0xFFFF); //INT_SDM_CGEN[15:0]
    Modify_SPI_Reg_bits_(self, 0x0088, 3, 0, gFRAC>>16); //INT_SDM_CGEN[19:16]
    Modify_SPI_Reg_bits(self, LMS7param(DIV_OUTCH_CGEN), iHdiv); //DIV_OUTCH_CGEN

    return TuneVCO(self, VCO_CGEN);
}

/** @brief Performs VCO tuning operations for CLKGEN, SXR, SXT modules
    @param module module selection for tuning 0-cgen, 1-SXR, 2-SXT
    @return 0-success, other-failure
*/
liblms7_status TuneVCO(LMS7002M_t *self, VCO_Module module) // 0-cgen, 1-SXR, 2-SXT
{
	int8_t i;
	uint8_t cmphl; //comparators
	int16_t csw_lowest = -1;
	uint16_t addrVCOpd; // VCO power down address
	uint16_t addrCSW_VCO;
	uint16_t addrCMP; //comparator address
	uint8_t lsb; //SWC lsb index
	uint8_t msb; //SWC msb index

	uint8_t ch = (uint8_t)Get_SPI_Reg_bits(self, LMS7param(MAC)); //remember used channel

	if(module != VCO_CGEN) //set addresses to SX module
	{
        Modify_SPI_Reg_bits(self, LMS7param(MAC), module);
        addrVCOpd = LMS7param(PD_VCO)->address;
        addrCSW_VCO = LMS7param(CSW_VCO)->address;
        lsb = LMS7param(CSW_VCO)->lsb;
        msb = LMS7param(CSW_VCO)->msb;
        addrCMP = LMS7param(VCO_CMPHO)->address;
	}
	else //set addresses to CGEN module
    {
        addrVCOpd = LMS7param(PD_VCO_CGEN)->address;
        addrCSW_VCO = LMS7param(CSW_VCO_CGEN)->address;
        lsb = LMS7param(CSW_VCO_CGEN)->lsb;
        msb = LMS7param(CSW_VCO_CGEN)->msb;
        addrCMP = LMS7param(VCO_CMPHO_CGEN)->address;
    }
	// Initialization
	Modify_SPI_Reg_bits_(self, addrVCOpd, 2, 1, 0); //activate VCO comparator and SDM
	if(module == VCO_CGEN)
        Modify_SPI_Reg_bits(self, LMS7param(SPDUP_VCO_CGEN), 1); //SHORT_NOISEFIL=1 SPDUP_VCO_ Short the noise filter resistor to speed up the settling time
	else
        Modify_SPI_Reg_bits(self, LMS7param(SPDUP_VCO_CGEN), 1); //SHORT_NOISEFIL=1 SPDUP_VCO_ Short the noise filter resistor to speed up the settling time
	Modify_SPI_Reg_bits_(self, addrCSW_VCO , msb, lsb , 0); //Set SWC_VCO<7:0>=<00000000>

	i=7;
	while(i>=0)
	{
        Modify_SPI_Reg_bits_(self, addrCSW_VCO, lsb + i, lsb + i, 1); // CSW_VCO<i>=1
        cmphl = (uint8_t)Get_SPI_Reg_bits_(self, addrCMP, 13, 12);
        if ( (cmphl&0x01) == 1) // reduce CSW
            Modify_SPI_Reg_bits_(self, addrCSW_VCO, lsb + i, lsb + i, 0); // CSW_VCO<i>=0
        if( cmphl == 2 && csw_lowest < 0)
            csw_lowest = Get_SPI_Reg_bits_(self, addrCSW_VCO, msb, lsb);
		--i;
	}
	if(csw_lowest >= 0)
    {
        uint16_t csw_highest = Get_SPI_Reg_bits_(self, addrCSW_VCO, msb, lsb);
        if(csw_lowest == csw_highest)
        {
            while(csw_lowest>=0)
            {
                Modify_SPI_Reg_bits_(self, addrCSW_VCO, msb, lsb, csw_lowest);
                if(Get_SPI_Reg_bits_(self, addrCMP, 13, 12) == 0)
                    break;
                else
                    --csw_lowest;
            }
        }
        Modify_SPI_Reg_bits_(self, addrCSW_VCO, msb, lsb, csw_lowest+(csw_highest-csw_lowest)/2);
    }
    if (module == VCO_CGEN)
        Modify_SPI_Reg_bits(self, LMS7param(SPDUP_VCO_CGEN), 0); //SHORT_NOISEFIL=1 SPDUP_VCO_ Short the noise filter resistor to speed up the settling time
    else
        Modify_SPI_Reg_bits(self, LMS7param(SPDUP_VCO_CGEN), 0); //SHORT_NOISEFIL=1 SPDUP_VCO_ Short the noise filter resistor to speed up the settling time
	cmphl = (uint8_t)Get_SPI_Reg_bits_(self, addrCMP, 13, 12);
    Modify_SPI_Reg_bits(self, LMS7param(MAC), ch); //restore previously used channel
	if(cmphl == 2)
        return LIBLMS7_SUCCESS;
    else
        return LIBLMS7_FAILURE;
}

/** @brief Returns given parameter value from chip register
    @param param LMS7002M control parameter
    @return parameter value
*/
uint16_t Get_SPI_Reg_bits(LMS7002M_t *self, const LMS7Parameter *param)
{
	return Get_SPI_Reg_bits_(self, param->address, param->msb, param->lsb);
}

/** @brief Returns given parameter value from chip register
    @param address register address
    @param msb most significant bit index
    @param lsb least significant bit index
    @return parameter value
*/
uint16_t Get_SPI_Reg_bits_(LMS7002M_t *self, uint16_t address, uint8_t msb, uint8_t lsb)
{
    return (SPI_read(self, address, NULL) & (~(~0<<(msb+1)))) >> lsb; //shift bits to LSB
}

/** @brief Change given parameter value
    @param param LMS7002M control parameter
    @param new_bits_data new parameter value
*/
liblms7_status Modify_SPI_Reg_bits(LMS7002M_t *self, const LMS7Parameter *param, const uint16_t new_bits_data)
{
    return Modify_SPI_Reg_bits_(self, param->address, param->msb, param->lsb, new_bits_data);
}

/** @brief Change given parameter value
    @param address register address
    @param new_bits_data new parameter value
*/
liblms7_status Modify_SPI_Reg_bits_(LMS7002M_t *self, const uint16_t address, const uint8_t msb, const uint8_t lsb, const uint16_t new_bits_data)
{
    uint16_t spiDataReg = SPI_read(self, address, NULL); //read current SPI reg data
    uint16_t spiMask = (~(~0 << (msb - lsb + 1))) << (lsb); // creates bit mask
    spiDataReg = (spiDataReg & (~spiMask)) | ((new_bits_data << lsb) & spiMask) ;//clear bits
    return SPI_write(self, address, spiDataReg); //write modified data back to SPI reg
}

/** @brief Modifies given registers with values applied using masks
    @param addr array of register addresses
    @param masks array of applied masks
    @param values array of values to be written
    @param start starting index of given arrays
    @param stop end index of given arrays
*/
liblms7_status Modify_SPI_Reg_mask(LMS7002M_t *self, const uint16_t *addr, const uint16_t *masks, const uint16_t *values, uint8_t start, uint8_t stop)
{
    liblms7_status status;
    uint16_t reg_data;
    uint16_t addresses[VECTOR_MAX];
    uint16_t data[VECTOR_MAX];
    size_t count = 0;
    while (start <= stop)
    {
        reg_data = SPI_read(self, addr[start], &status); //read current SPI reg data
        reg_data &= ~masks[start];//clear bits
        reg_data |= (values[start] & masks[start]);
        addresses[count] = addr[start];
        data[count] = reg_data;
        ++start;
        count++;
    }
    if (status != LIBLMS7_SUCCESS)
        return status;
    SPI_write_batch(self, addresses, data, count);
    return status;
}

/** @brief Loads given DC_REG values into registers
    @param tx TxTSP or RxTSP selection
    @param I DC_REG I value
    @param Q DC_REG Q value
*/
liblms7_status LoadDC_REG_IQ(LMS7002M_t *self, bool tx, int16_t I, int16_t Q)
{
    if(tx)
    {
        Modify_SPI_Reg_bits(self, LMS7param(DC_REG_TXTSP), I);
        Modify_SPI_Reg_bits(self, LMS7param(TSGDCLDI_TXTSP), 0);
        Modify_SPI_Reg_bits(self, LMS7param(TSGDCLDI_TXTSP), 1);
        Modify_SPI_Reg_bits(self, LMS7param(TSGDCLDI_TXTSP), 0);
        Modify_SPI_Reg_bits(self, LMS7param(DC_REG_TXTSP), Q);
        Modify_SPI_Reg_bits(self, LMS7param(TSGDCLDQ_TXTSP), 0);
        Modify_SPI_Reg_bits(self, LMS7param(TSGDCLDQ_TXTSP), 1);
        Modify_SPI_Reg_bits(self, LMS7param(TSGDCLDQ_TXTSP), 0);
        Modify_SPI_Reg_bits(self, LMS7param(DC_BYP_TXTSP), 0); //DC_BYP
    }
    else
    {
        Modify_SPI_Reg_bits(self, LMS7param(DC_REG_RXTSP), I);
        Modify_SPI_Reg_bits(self, LMS7param(TSGDCLDI_RXTSP), 0);
        Modify_SPI_Reg_bits(self, LMS7param(TSGDCLDI_RXTSP), 1);
        Modify_SPI_Reg_bits(self, LMS7param(TSGDCLDI_RXTSP), 0);
        Modify_SPI_Reg_bits(self, LMS7param(DC_REG_TXTSP), Q);
        Modify_SPI_Reg_bits(self, LMS7param(TSGDCLDQ_RXTSP), 0);
        Modify_SPI_Reg_bits(self, LMS7param(TSGDCLDQ_RXTSP), 1);
        Modify_SPI_Reg_bits(self, LMS7param(TSGDCLDQ_RXTSP), 0);
        Modify_SPI_Reg_bits(self, LMS7param(DC_BYP_TXTSP), 0); //DC_BYP
    }
    return LIBLMS7_SUCCESS;
}

/** @brief Sets chosen NCO's frequency
    @param tx transmitter or receiver selection
    @param index NCO index from 0 to 15
    @param freq_MHz desired NCO frequency
    @return 0-success, other-failure
*/
liblms7_status SetNCOFrequency(LMS7002M_t *self, bool tx, uint8_t index, float_type freq_MHz)
{
    if(index > 15)
        return LIBLMS7_INDEX_OUT_OF_RANGE;
    float_type refClk_MHz = GetReferenceClk_TSP_MHz(self, tx);
    uint16_t addr = tx ? 0x0240 : 0x0440;
	uint32_t fcw = (uint32_t)((freq_MHz/refClk_MHz)*4294967296);
    SPI_write(self, addr+2+index, (fcw >> 16)); //NCO frequency control word register MSB part.
    SPI_write(self, addr+3+index, fcw); //NCO frequency control word register LSB part.
    return LIBLMS7_SUCCESS;
}

/** @brief Write given data value to whole register
    @param spiAddrReg SPI address
    @param spiDataReg new register value
    @return 0-succes, other-failure
*/
liblms7_status SPI_write(LMS7002M_t *self, uint16_t spiAddrReg, uint16_t spiDataReg)
{
    LMS7002M_spi_write(self, spiAddrReg, spiDataReg); //write modified data back to SPI reg

    //apply new value to the local register struct
    LMS7002M_regs_set(self->regs, spiAddrReg, spiDataReg);

    return LIBLMS7_SUCCESS;
}

/** @brief Reads whole register value from given address
    @param spiAddrReg SPI address
    @param status operation status(optional)
    @return register value
*/
uint16_t SPI_read(LMS7002M_t *self, uint16_t spiAddrReg, liblms7_status *status)
{
    uint16_t data = LMS7002M_spi_read(self, spiAddrReg);
    if (status != NULL) *status = LIBLMS7_SUCCESS;
    return data;
}

/** @brief Batches multiple register writes into least ammount of transactions
    @param spiAddrReg spi register addresses to be written
    @param spiDataReg registers data to be written
    @param cnt number of registers to write
    @return 0-success, other-failure
*/
liblms7_status SPI_write_batch(LMS7002M_t *self, const uint16_t* spiAddrReg, const uint16_t* spiDataReg, uint16_t cnt)
{
    for (size_t i = 0; i < cnt; i++)
    {
        SPI_write(self, spiAddrReg[i], spiDataReg[i]);
    }
    return LIBLMS7_SUCCESS;
}

/** @brief Batches multiple register reads into least amount of transactions
    @param spiAddr SPI addresses to read
    @param spiData array for read data
    @param cnt number of registers to read
    @return 0-success, other-failure
*/
liblms7_status SPI_read_batch(LMS7002M_t *self, const uint16_t* spiAddr, uint16_t* spiData, uint16_t cnt)
{
    for (size_t i = 0; i < cnt; i++)
    {
        spiData[i] = SPI_read(self, spiAddr[i], NULL);
    }
    return LIBLMS7_SUCCESS;
}

/** @brief Flips the CAPTURE bit and returns digital RSSI value
*/
uint32_t GetRSSI(LMS7002M_t *self)
{
    Modify_SPI_Reg_bits(self, LMS7param(CAPTURE), 0);
    Modify_SPI_Reg_bits(self, LMS7param(CAPTURE), 1);
    return (Get_SPI_Reg_bits_(self, 0x040F, 15, 0) << 2) | Get_SPI_Reg_bits_(self, 0x040E, 1, 0);
}

const uint16_t moduleAddresses[] = {0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F, 0x0081, 0x0082, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009A, 0x009B, 0x009C, 0x009D, 0x009E, 0x009F, 0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x0100, 0x0101, 0x0102, 0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x0108, 0x0109, 0x010A, 0x010C, 0x010D, 0x010E, 0x010F, 0x0110, 0x0111, 0x0112, 0x0113, 0x0114, 0x0115, 0x0116, 0x0117, 0x0118, 0x0119, 0x011A, 0x011C, 0x011D, 0x011E, 0x011F, 0x0120, 0x0121, 0x0122, 0x0123, 0x0124, 0x0200, 0x0201, 0x0202, 0x0203, 0x0204, 0x0205, 0x0206, 0x0207, 0x0208, 0x0209, 0x020A, 0x020B, 0x020C, 0x0240, 0x0241, 0x0242, 0x0243, 0x0244, 0x0245, 0x0246, 0x0247, 0x0248, 0x0249, 0x024A, 0x024B, 0x024C, 0x024D, 0x024E, 0x024F, 0x0250, 0x0251, 0x0252, 0x0253, 0x0254, 0x0255, 0x0256, 0x0257, 0x0258, 0x0259, 0x025A, 0x025B, 0x025C, 0x025D, 0x025E, 0x025F, 0x0260, 0x0261, 0x0280, 0x0281, 0x0282, 0x0283, 0x0284, 0x0285, 0x0286, 0x0287, 0x0288, 0x0289, 0x028A, 0x028B, 0x028C, 0x028D, 0x028E, 0x028F, 0x0290, 0x0291, 0x0292, 0x0293, 0x0294, 0x0295, 0x0296, 0x0297, 0x0298, 0x0299, 0x029A, 0x029B, 0x029C, 0x029D, 0x029E, 0x029F, 0x02A0, 0x02A1, 0x02A2, 0x02A3, 0x02A4, 0x02A5, 0x02A6, 0x02A7, 0x02C0, 0x02C1, 0x02C2, 0x02C3, 0x02C4, 0x02C5, 0x02C6, 0x02C7, 0x02C8, 0x02C9, 0x02CA, 0x02CB, 0x02CC, 0x02CD, 0x02CE, 0x02CF, 0x02D0, 0x02D1, 0x02D2, 0x02D3, 0x02D4, 0x02D5, 0x02D6, 0x02D7, 0x02D8, 0x02D9, 0x02DA, 0x02DB, 0x02DC, 0x02DD, 0x02DE, 0x02DF, 0x02E0, 0x02E1, 0x02E2, 0x02E3, 0x02E4, 0x02E5, 0x02E6, 0x02E7, 0x0300, 0x0301, 0x0302, 0x0303, 0x0304, 0x0305, 0x0306, 0x0307, 0x0308, 0x0309, 0x030A, 0x030B, 0x030C, 0x030D, 0x030E, 0x030F, 0x0310, 0x0311, 0x0312, 0x0313, 0x0314, 0x0315, 0x0316, 0x0317, 0x0318, 0x0319, 0x031A, 0x031B, 0x031C, 0x031D, 0x031E, 0x031F, 0x0320, 0x0321, 0x0322, 0x0323, 0x0324, 0x0325, 0x0326, 0x0327, 0x0340, 0x0341, 0x0342, 0x0343, 0x0344, 0x0345, 0x0346, 0x0347, 0x0348, 0x0349, 0x034A, 0x034B, 0x034C, 0x034D, 0x034E, 0x034F, 0x0350, 0x0351, 0x0352, 0x0353, 0x0354, 0x0355, 0x0356, 0x0357, 0x0358, 0x0359, 0x035A, 0x035B, 0x035C, 0x035D, 0x035E, 0x035F, 0x0360, 0x0361, 0x0362, 0x0363, 0x0364, 0x0365, 0x0366, 0x0367, 0x0380, 0x0381, 0x0382, 0x0383, 0x0384, 0x0385, 0x0386, 0x0387, 0x0388, 0x0389, 0x038A, 0x038B, 0x038C, 0x038D, 0x038E, 0x038F, 0x0390, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D, 0x039E, 0x039F, 0x03A0, 0x03A1, 0x03A2, 0x03A3, 0x03A4, 0x03A5, 0x03A6, 0x03A7, 0x0400, 0x0401, 0x0402, 0x0403, 0x0404, 0x0405, 0x0406, 0x0407, 0x0408, 0x0409, 0x040A, 0x040B, 0x040C, 0x040D, 0x040E, 0x040F, 0x0440, 0x0441, 0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447, 0x0448, 0x0449, 0x044A, 0x044B, 0x044C, 0x044D, 0x044E, 0x044F, 0x0450, 0x0451, 0x0452, 0x0453, 0x0454, 0x0455, 0x0456, 0x0457, 0x0458, 0x0459, 0x045A, 0x045B, 0x045C, 0x045D, 0x045E, 0x045F, 0x0460, 0x0461, 0x0480, 0x0481, 0x0482, 0x0483, 0x0484, 0x0485, 0x0486, 0x0487, 0x0488, 0x0489, 0x048A, 0x048B, 0x048C, 0x048D, 0x048E, 0x048F, 0x0490, 0x0491, 0x0492, 0x0493, 0x0494, 0x0495, 0x0496, 0x0497, 0x0498, 0x0499, 0x049A, 0x049B, 0x049C, 0x049D, 0x049E, 0x049F, 0x04A0, 0x04A1, 0x04A2, 0x04A3, 0x04A4, 0x04A5, 0x04A6, 0x04A7, 0x04C0, 0x04C1, 0x04C2, 0x04C3, 0x04C4, 0x04C5, 0x04C6, 0x04C7, 0x04C8, 0x04C9, 0x04CA, 0x04CB, 0x04CC, 0x04CD, 0x04CE, 0x04CF, 0x04D0, 0x04D1, 0x04D2, 0x04D3, 0x04D4, 0x04D5, 0x04D6, 0x04D7, 0x04D8, 0x04D9, 0x04DA, 0x04DB, 0x04DC, 0x04DD, 0x04DE, 0x04DF, 0x04E0, 0x04E1, 0x04E2, 0x04E3, 0x04E4, 0x04E5, 0x04E6, 0x04E7, 0x0500, 0x0501, 0x0502, 0x0503, 0x0504, 0x0505, 0x0506, 0x0507, 0x0508, 0x0509, 0x050A, 0x050B, 0x050C, 0x050D, 0x050E, 0x050F, 0x0510, 0x0511, 0x0512, 0x0513, 0x0514, 0x0515, 0x0516, 0x0517, 0x0518, 0x0519, 0x051A, 0x051B, 0x051C, 0x051D, 0x051E, 0x051F, 0x0520, 0x0521, 0x0522, 0x0523, 0x0524, 0x0525, 0x0526, 0x0527, 0x0540, 0x0541, 0x0542, 0x0543, 0x0544, 0x0545, 0x0546, 0x0547, 0x0548, 0x0549, 0x054A, 0x054B, 0x054C, 0x054D, 0x054E, 0x054F, 0x0550, 0x0551, 0x0552, 0x0553, 0x0554, 0x0555, 0x0556, 0x0557, 0x0558, 0x0559, 0x055A, 0x055B, 0x055C, 0x055D, 0x055E, 0x055F, 0x0560, 0x0561, 0x0562, 0x0563, 0x0564, 0x0565, 0x0566, 0x0567, 0x0580, 0x0581, 0x0582, 0x0583, 0x0584, 0x0585, 0x0586, 0x0587, 0x0588, 0x0589, 0x058A, 0x058B, 0x058C, 0x058D, 0x058E, 0x058F, 0x0590, 0x0591, 0x0592, 0x0593, 0x0594, 0x0595, 0x0596, 0x0597, 0x0598, 0x0599, 0x059A, 0x059B, 0x059C, 0x059D, 0x059E, 0x059F, 0x05A0, 0x05A1, 0x05A2, 0x05A3, 0x05A4, 0x05A5, 0x05A6, 0x05A7 };
const uint16_t defaultValues[] =   {0xFFFD, 0x0E9F, 0x07DF, 0x5559, 0xE4E4, 0x0101, 0x0101, 0xE4E4, 0x0101, 0x0101, 0x0086, 0x0010, 0xFFFF, 0xFFFF, 0x0000, 0x3840, 0x0000, 0x800B, 0x0400, 0x0001, 0x4901, 0x0000, 0x0530, 0x00A0, 0x0514, 0x2100, 0x067B, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6565, 0x658C, 0x6565, 0x658C, 0x6565, 0x658C, 0x658C, 0x6565, 0x6565, 0x6565, 0x6565, 0x6565, 0x6565, 0x0001, 0x6565, 0x0000, 0x8000, 0x0000, 0x0040, 0x2000, 0x03FF, 0x0000, 0x3409, 0x7800, 0x3180, 0x0A12, 0x0088, 0x0007, 0x318C, 0x318C, 0x9426, 0x61C1, 0x104C, 0x88FD, 0x009E, 0x2040, 0x3042, 0x0BF4, 0x0083, 0xC0E6, 0x03C3, 0x008D, 0x0009, 0x8180, 0x280C, 0x018C, 0x18CB, 0x2E02, 0xAD43, 0x0400, 0x0780, 0x3640, 0xB9FF, 0x3404, 0x033F, 0x067B, 0x0000, 0x0081, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0080, 0x4000, 0x7FFF, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0081, 0x07FF, 0x07FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7FFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

/** @brief Sets given module registers to default values
    @return 0-success, other-failure
*/
liblms7_status SetDefaults(LMS7002M_t *self, MemorySection module)
{
    liblms7_status status = LIBLMS7_SUCCESS;
    uint16_t i;
    uint16_t addrs[VECTOR_MAX];
    uint16_t values[VECTOR_MAX];
    size_t count = 0;
    for (i = 0; i<sizeof(moduleAddresses) / 2; ++i)
    {
        if (moduleAddresses[i] > MemorySectionAddresses[module][1])
            break;
        if (moduleAddresses[i] >= MemorySectionAddresses[module][0] && moduleAddresses[i] <= MemorySectionAddresses[module][1])
        {
            addrs[count] = moduleAddresses[i];
            values[count] = defaultValues[i];
            count++;
            //status = SPI_write(moduleAddresses[i], defaultValues[i]);
        }   
        //if (status != LIBLMS7_SUCCESS)
            //return status;
    }
    status = SPI_write_batch(self, addrs, values, count);
    return status;
}

const uint16_t backupAddrs[] = {
    0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028,
    0x0029, 0x002A, 0x002B, 0x002C, 0x002E, 0x0081, 0x0082, 0x0084, 0x0085,
    0x0086, 0x0087, 0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x0092, 0x0093, 0x0094,
    0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009A, 0x009B, 0x009C, 0x009D, 0x009E,
    0x009F, 0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8,
    0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x0100, 0x0101, 0x0102, 0x0103,
    0x0104, 0x0105, 0x0106, 0x0107, 0x0108, 0x0109, 0x010A, 0x010C, 0x010D, 0x010E,
    0x010F, 0x0110, 0x0111, 0x0112, 0x0113, 0x0114, 0x0115, 0x0116, 0x0117, 0x0118,
    0x0119, 0x011A, 0x011C, 0x011D, 0x011E, 0x011F, 0x0120, 0x0121, 0x0122, 0x0123,
    0x0124, 0x0200, 0x0201, 0x0202, 0x0203, 0x0204, 0x0205, 0x0206, 0x0207, 0x0208,
    0x0240, 0x0242, 0x0243, 0x0400, 0x0401, 0x0402,
    0x0403, 0x0404, 0x0405, 0x0406, 0x0407, 0x0408, 0x0409, 0x040A, 0x040B, 0x040C,
    0x0440, 0x0442, 0x0443 };
uint16_t backupRegs[sizeof(backupAddrs) / 2];
uint16_t backupSXAddr[] = { 0x011C, 0x011D, 0x011E, 0x011F, 0x01200, 0x0121, 0x0122, 0x0123, 0x0124 };
uint16_t backupRegsSXR[sizeof(backupSXAddr) / 2];
uint16_t backupRegsSXT[sizeof(backupSXAddr) / 2];

/** @brief Stores chip current registers state into memory for later restoration
*/
void BackupAllRegisters(LMS7002M_t *self)
{
    uint8_t gCHAR = (uint8_t)Get_SPI_Reg_bits(self, LMS7param(MAC));
    //uint8_t gIter;
    SPI_read_batch(self, backupAddrs, backupRegs, sizeof(backupAddrs) / sizeof(uint16_t));
    Modify_SPI_Reg_bits(self, LMS7param(MAC), 1); // channel A
    SPI_read_batch(self, backupRegsSXR, backupSXAddr, sizeof(backupRegsSXR) / sizeof(uint16_t));
    Modify_SPI_Reg_bits(self, LMS7param(MAC), 2); // channel B
    SPI_read_batch(self, backupRegsSXT, backupSXAddr, sizeof(backupRegsSXR) / sizeof(uint16_t));
    /*
    for (gIter = 0; gIter<sizeof(backupAddrs) / 2; ++gIter)
        backupRegs[gIter] = SPI_read(backupAddrs[gIter]);
    Modify_SPI_Reg_bits(LMS7param(MAC), 1); // channel A
    for (gIter = 0; gIter<sizeof(backupRegsSXR) / 2; ++gIter)
        backupRegsSXR[gIter] = SPI_read(backupSXAddr[gIter]);
    Modify_SPI_Reg_bits(LMS7param(MAC), 2); // channel B
    for (gIter = 0; gIter<sizeof(backupRegsSXT) / 2; ++gIter)
        backupRegsSXT[gIter] = SPI_read(backupSXAddr[gIter]);
        */
    Modify_SPI_Reg_bits(self, LMS7param(MAC), gCHAR);
}

/** @brief Sets chip registers to state that was stored in memory using BackupAllRegisters()
*/
void RestoreAllRegisters(LMS7002M_t *self)
{
    uint8_t gCHAR = (uint8_t)Get_SPI_Reg_bits(self, LMS7param(MAC));
    //uint8_t gIter;
    SPI_write_batch(self, backupAddrs, backupRegs, sizeof(backupAddrs) / sizeof(uint16_t));
    Modify_SPI_Reg_bits(self, LMS7param(MAC), 1); // channel A
    SPI_write_batch(self, backupRegsSXR, backupSXAddr, sizeof(backupRegsSXR) / sizeof(uint16_t));
    Modify_SPI_Reg_bits(self, LMS7param(MAC), 2); // channel B
    SPI_write_batch(self, backupRegsSXT, backupSXAddr, sizeof(backupRegsSXR) / sizeof(uint16_t));
    /*
    for (gIter = 0; gIter<sizeof(backupAddrs) / 2; ++gIter)
        SPI_write(backupAddrs[gIter], backupRegs[gIter]);
    Modify_SPI_Reg_bits(LMS7param(MAC), 1); // channel A
    for (gIter = 0; gIter<sizeof(backupRegsSXR) / 2; ++gIter)
        SPI_write(backupSXAddr[gIter], backupRegsSXR[gIter]);
    Modify_SPI_Reg_bits(LMS7param(MAC), 2); // channel B
    for (gIter = 0; gIter<sizeof(backupRegsSXT) / 2; ++gIter)
        SPI_write(backupSXAddr[gIter], backupRegsSXT[gIter]);
    */
    Modify_SPI_Reg_bits(self, LMS7param(MAC), gCHAR);
}
