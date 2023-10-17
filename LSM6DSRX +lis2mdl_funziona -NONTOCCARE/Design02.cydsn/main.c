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
int IMU_ack;

//uint8 SensorHub[6] = {LSM6DSRX_SENSOR_HUB_1, LSM6DSRX_SENSOR_HUB_2, LSM6DSRX_SENSOR_HUB_3, LSM6DSRX_SENSOR_HUB_4, LSM6DSRX_SENSOR_HUB_5, LSM6DSRX_SENSOR_HUB_6};
struct st_imu_data g_imu, g_imuNew;
uint8 Mag[6];
uint8 Accel[6];
uint8 Gyro[6];
uint8 Temp[2];
uint8 GDA;
uint8 XLDA;
uint8 SENS_HUB_ENDOP;
uint16 t0;
uint16 t1;
uint16 tempo;

int main()
{   MY_TIMER_Start();                 
    PACER_TIMER_Start();    
    SPI_IMU_Start();
	SPI_IMU_Init();
	SPI_IMU_Enable();
	SPI_IMU_ClearRxBuffer();
	SPI_IMU_ClearTxBuffer();
	SPI_IMU_ClearFIFO();							
    CyDelay(10);
  
    CyGlobalIntEnable;
    
    uint8 i;
    uint8 who;
    UART_Start();
    WriteControlRegisterSPI(LSM6DSRX_CTRL1_XL,0x40); //104 Hz (normal mode)
    WriteControlRegisterSPI(LSM6DSRX_CTRL2_G,0x40); //104 Hz (normal mode)
    
   // WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00);
    CyDelay(100);
    OneShot_ReadRoutine(EXT_SENS_ADDR,LIS2MDL_WHO_AM_I); //LIS2MDL
    OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_A,0x8C);
    OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_B,0x02);
    OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_C,0x10);
    Continuous_ReadRoutine(EXT_SENS_ADDR,LIS2MDL_OUTX_L_REG,0x04);
    
    for(;;)
    {t0 = (uint16)MY_TIMER_ReadCounter();
        //UART_PutChar('a');
       
//      ------------------------------------------------------------------------READ MAG
        do 
        {
            XLDA = ReadControlRegisterSPI(LSM6DSRX_STATUS_REG);          
        }
        while ((XLDA & 0b00000001) == 0); 
        /* 
        do 
        {
            SENS_HUB_ENDOP = ReadControlRegisterSPI(LSM6DSRX_STATUS_MASTER_MAINPAGE);   
        }
        while ((SENS_HUB_ENDOP & 0b00000001) == 0);
       
        WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x40);   
        CyDelayUs(300);  
        ReadControlRegisterSPI(LSM6DSRX_WHO_AM_I); 
        i= ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_1);  
       // UART_PutChar(i);
        i= ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_2); 
       // UART_PutChar(i);
        i= ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_3);  
       // UART_PutChar(i);
        i= ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_4);  
       // UART_PutChar(i);
        WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00);   
        CyDelayUs(300);  
        */
//      ---------------------------------------------------------------------READ AXELS
        
        i = ReadControlRegisterSPI(LSM6DSRX_OUTX_L_A);
       // UART_PutChar(i);
        i = ReadControlRegisterSPI(LSM6DSRX_OUTX_H_A);
       // UART_PutChar(i); 
        
        i= ReadControlRegisterSPI(LSM6DSRX_OUTY_L_A); 
       // UART_PutChar(i);
         i = ReadControlRegisterSPI(LSM6DSRX_OUTY_H_A);
       // UART_PutChar(i);
        
        i = ReadControlRegisterSPI(LSM6DSRX_OUTZ_L_A);
       // UART_PutChar(i);
         i= ReadControlRegisterSPI(LSM6DSRX_OUTZ_H_A); 
       // UART_PutChar(i);
    
//      ---------------------------------------------------------------------READ GYROS
        i = ReadControlRegisterSPI(LSM6DSRX_OUTX_L_G);
       // UART_PutChar(i);
        i = ReadControlRegisterSPI(LSM6DSRX_OUTX_H_G);
       // UART_PutChar(i);

        i = ReadControlRegisterSPI(LSM6DSRX_OUTY_L_G);
       // UART_PutChar(i);
        i = ReadControlRegisterSPI(LSM6DSRX_OUTY_H_G);
       // UART_PutChar(i);
        
        i = ReadControlRegisterSPI(LSM6DSRX_OUTZ_L_G);
       // UART_PutChar(i);
        i = ReadControlRegisterSPI(LSM6DSRX_OUTZ_H_G);
       // UART_PutChar(i);
        CyDelay(30);  
        t1 = (uint16)MY_TIMER_ReadCounter();     
        tempo=(t0-t1);
        
        
        i = (uint8)(tempo & 0x07);
        UART_PutChar(i);
        i = (uint8) (tempo >> 8);
        UART_PutChar(i);
        

    }
return 0;
}
/* [] END OF FILE */
