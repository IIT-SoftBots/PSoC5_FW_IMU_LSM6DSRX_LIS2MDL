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
#include <project.h>
#include "interrupts.h"
int IMU_ack;

uint8 Mag[6];
uint8 Accel[6];
uint8 Gyro[6];
uint8 Temp[2];
uint8 GDA;
uint8 XLDA;
uint8 SENS_HUB_ENDOP;
uint16 t0;
uint16 t1;
uint16 tempo[100];
uint8 j;
float o;
uint8 l;
uint8 flag_int = 0;

    uint8 i;
    uint8 who;

CY_ISR(isr_Acc_Handler){

LED_Write(1);
//CyDelay(50);
        //i = ReadControlRegisterSPI(LSM6DSRX_WHO_AM_I);

        
        i = ReadControlRegisterSPI(LSM6DSRX_OUTX_L_A);
        UART_PutChar(i);
        i = ReadControlRegisterSPI(LSM6DSRX_OUTX_H_A);
        UART_PutChar(i);
        UART_PutChar('a');
Acc_ClearInterrupt();
}


int main()
{      
    SPI_IMU_Start();
	SPI_IMU_Init();
	SPI_IMU_Enable();
	SPI_IMU_ClearRxBuffer();
	SPI_IMU_ClearTxBuffer();
	SPI_IMU_ClearFIFO();							
    UART_Start();
    CyDelay(10);
    CyGlobalIntEnable;
    isr_Acc_StartEx(isr_Acc_Handler);
    CyDelay(20);
    
    WriteControlRegisterSPI(LSM6DSRX_INT1_CTRL,0x01); //104 Hz (normal mode)
    WriteControlRegisterSPI(LSM6DSRX_CTRL6_C,0x00); //104 Hz (normal mode)
    WriteControlRegisterSPI(LSM6DSRX_CTRL1_XL,0x00); //104 Hz (normal mode)7
    CyDelay(1);
    WriteControlRegisterSPI(LSM6DSRX_CTRL1_XL,0x70); //104 Hz (normal mode)7
  //  WriteControlRegisterSPI(LSM6DSRX_CTRL3_C,0x40); //104 Hz (normal mode)

    for(;;)
    {   
       /* do{
        XLDA = ReadControlRegisterSPI(LSM6DSRX_STATUS_REG);}
        while ((XLDA & 0x01) == 0);*/
       // i = ReadControlRegisterSPI(LSM6DSRX_OUTZ_L_A);
       // UART_PutChar(i);
      //  i = ReadControlRegisterSPI(LSM6DSRX_OUTZ_H_A);
        //UART_PutChar(i);
        //CyDelay(1);
       // UART_PutChar('a');
    }
    
return 0;   
}
/* [] END OF FILE */
