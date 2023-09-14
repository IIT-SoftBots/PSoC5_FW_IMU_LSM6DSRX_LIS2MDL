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
#include "project.h"

#include "header01.h"

int main(void)
{ 
    CyGlobalIntEnable; /* Enable global interrupts. */
SPI_IMU_Start();
SPI_IMU_Init();
SPI_IMU_Enable();
SPI_IMU_ClearRxBuffer();
SPI_IMU_ClearTxBuffer();
SPI_IMU_ClearFIFO();
CyDelay(100);
volatile uint8 CTRL3;
volatile uint8 WHO;
WriteControlRegisterSPI(LSM6DSRX_CTRL3_C,0x08);
//WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS,0x00);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {      
        WHO = ReadControlRegisterSPI(LSM6DSRX_WHO_AM_I);

        WHO = ReadControlRegisterSPI(LSM6DSRX_CTRL3_C);
        CyDelay(10);
        
        //WriteControlRegisterSPI(0x12,0x07);
        
        CyDelay(100);
        
        //CTRL3 = ReadControlRegisterSPI(LSM6DSRX_CTRL1_XL);
       // CyDelay(10);
        
     //   WriteControlRegisterSPI(LSM6DSRX_CTRL1_XL,0x50);
        
    }
}

/* [] END OF FILE */
