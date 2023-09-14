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


void InitIMU() {
    InitAxelGyro();
    //InitMag();
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS,0b01000000); //Enable I2C master mode with external sensor
    //CyDelay(10);//Enable I2C master mode with external sensor
}



 void OneShot_ReadRoutine1(uint8 address, uint8 subaddress,uint8 slave_config){
    uint8 XLDA;
    uint8 SENS_HUB_ENDOP;
    uint8 i;
 
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x40);  //18ms
    CyDelayUs(10);
    WriteControlRegisterSPI(LSM6DSRX_SLV0_ADD, address | 0x01); //28ms
    CyDelayUs(10);
    WriteControlRegisterSPI(LSM6DSRX_SLV0_SUBADD, subaddress); //10
    CyDelayUs(10);
           
    WriteControlRegisterSPI(LSM6DSRX_SLV0_CONFIG, slave_config); //ODR = 288Hz, FSR=+/-2g, LPF2 disabled //17
     CyDelayUs(10);
    WriteControlRegisterSPI(LSM6DSRX_MASTER_CONFIG, 0x4C); //ODR = 288Hz, FSR=+/-2g, LPF2 disabled  //10
    CyDelayUs(10);  
                
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00);   //17
    CyDelayUs(10); 
    ReadControlRegisterSPI(LSM6DSRX_OUTX_H_A); //21
    CyDelayUs(10);
    
        
    
    do 
    {
        XLDA = ReadControlRegisterSPI(LSM6DSRX_STATUS_REG);  //20
                
    }
    while ((XLDA & 0b00000001) == 0); 
    
     
    do 
    {
        SENS_HUB_ENDOP = ReadControlRegisterSPI(LSM6DSRX_STATUS_MASTER_MAINPAGE);
         
    }
    while ((SENS_HUB_ENDOP & 0b00000001) == 0);
         


    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x40);   
    CyDelayUs(10);
    WriteControlRegisterSPI(LSM6DSRX_MASTER_CONFIG, 0x08); 
     
        
    CyDelayUs(10);
    CyDelayUs(300);  
      
    ReadControlRegisterSPI(LSM6DSRX_WHO_AM_I);  
     CyDelayUs(10);

    for (i=0; i < slave_config; i++)
    {
        Mag[i]= ReadControlRegisterSPI(SensorHub[i]);  
        UART_PutChar(Mag[i]);
     }
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00); 
      CyDelayUs(10);
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00); 
    CyDelayUs(10);  
        
    
    
}


/*
void Read( uint8 slave_config){
    uint8 XLDA;
    uint8 SENS_HUB_ENDOP;
    uint8 i;
    ReadControlRegisterSPI(LSM6DSRX_WHO_AM_I); 
    do 
    {
        XLDA = ReadControlRegisterSPI(LSM6DSRX_STATUS_REG);        
    }
    while ((XLDA & 0b00000001) == 0);

    do 
    {
        SENS_HUB_ENDOP = ReadControlRegisterSPI(LSM6DSRX_STATUS_MASTER_MAINPAGE);
    }
    while ((SENS_HUB_ENDOP & 0b00000001) == 0);

    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x40); 
    CyDelay(1);
    WriteControlRegisterSPI(LSM6DSRX_MASTER_CONFIG, 0x08); 
    CyDelay(1);
    CyDelayUs(300);   
    for (i=0; i < slave_config; i++)
    {
        Mag[i]= ReadControlRegisterSPI(SensorHub[i]);    
    }
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00); 
}
*/

void OneShot_WriteRoutine (uint8 address, uint8 subaddress, uint8 data){
    uint8 WR_ONCE_DONE;
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x40);
    
    WriteControlRegisterSPI(LSM6DSRX_SLV0_ADD, address | 0x00);
    
    WriteControlRegisterSPI(LSM6DSRX_SLV0_SUBADD, subaddress); 
    
    WriteControlRegisterSPI(LSM6DSRX_SLV0_CONFIG, 0x00); //ODR = 288Hz, FSR=+/-2g, LPF2 disabled
    
     
    WriteControlRegisterSPI(LSM6DSRX_DATAWRITE_SLV0, data); //ODR = 288Hz, FSR=+/-2g, LPF2 disabled
    
    WriteControlRegisterSPI(LSM6DSRX_MASTER_CONFIG, 0x4C); //ODR = 288Hz, FSR=+/-2g, LPF2 disabled
    
        do 
    {
        WR_ONCE_DONE = ReadControlRegisterSPI(LSM6DSRX_STATUS_MASTER);
    }
    while ((WR_ONCE_DONE & 0b10000000) == 0);
    
    WriteControlRegisterSPI(LSM6DSRX_MASTER_CONFIG, 0x08); 
    CyDelayUs(300);   
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00); 
    
}

