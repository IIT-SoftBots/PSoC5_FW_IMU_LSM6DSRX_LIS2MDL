/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "header01.h"
#include "globals.h"

void WriteControlRegisterSPI(uint8 address, uint8 dta){
    
	SPI_IMU_ClearRxBuffer();
	SPI_IMU_ClearTxBuffer();
	SPI_IMU_ClearFIFO();
    SPI_IMU_TxEnable();
    
	SPI_IMU_WriteByte(LSM6DSRX_WCR | address);
    SPI_IMU_TxDisable();
	while(!( SPI_IMU_ReadStatus() & SPI_IMU_STS_TX_FIFO_EMPTY));	
    SPI_IMU_TxEnable();
	SPI_IMU_WriteByte(dta);
    SPI_IMU_TxDisable();
	while(!( SPI_IMU_ReadStatus() & SPI_IMU_STS_TX_FIFO_EMPTY));
    
}

/*******************************************************************************
* Function Name: Read Control Register
*********************************************************************************/
uint8 ReadControlRegisterSPI(uint8 address){
    SPI_IMU_ClearRxBuffer();
	SPI_IMU_ClearTxBuffer();
	SPI_IMU_ClearFIFO();
    SPI_IMU_TxEnable();
    
	uint8 controlreg = 0;
	SPI_IMU_WriteByte(LSM6DSRX_RCR | address);
 SPI_IMU_TxDisable();
    while(!( SPI_IMU_ReadStatus() & SPI_IMU_STS_TX_FIFO_EMPTY));
    while(!( SPI_IMU_ReadStatus() & SPI_IMU_STS_TX_FIFO_EMPTY));
	while(!( SPI_IMU_ReadStatus() & SPI_IMU_STS_SPI_DONE));   
    
    
	controlreg = SPI_IMU_ReadByte();        //real data    
	return controlreg;
}
/* [] END OF FILE */
