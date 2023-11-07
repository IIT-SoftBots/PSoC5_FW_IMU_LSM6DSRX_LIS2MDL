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
/********************************** *********************************************
* Function Name: Write Control Register
*********************************************************************************/

void WriteControlRegisterSPI(uint8 address, uint8 dta){
	
	SPI_IMU_ClearRxBuffer();
	SPI_IMU_ClearTxBuffer();
	SPI_IMU_ClearFIFO();
	SPI_IMU_WriteByte(LSM6DSRX_WCR | address);
	while(!( SPI_IMU_ReadStatus() & SPI_IMU_STS_TX_FIFO_EMPTY));		
	SPI_IMU_WriteByte(dta);
	while(!( SPI_IMU_ReadStatus() & SPI_IMU_STS_TX_FIFO_EMPTY));
}

/*******************************************************************************
* Function Name: Read Control Register
*********************************************************************************/
uint8 ReadControlRegisterSPI(uint8 address){
	uint8 controlreg = 0;
	SPI_IMU_WriteByte(LSM6DSRX_RCR | address);
    while(!( SPI_IMU_ReadStatus() & SPI_IMU_STS_TX_FIFO_EMPTY));
    SPI_IMU_WriteByte(0x00);
	while(!( SPI_IMU_ReadStatus() & SPI_IMU_STS_SPI_DONE));
	controlreg = SPI_IMU_ReadByte();        //real data
	return controlreg;
}


/* [] END OF FILE */
