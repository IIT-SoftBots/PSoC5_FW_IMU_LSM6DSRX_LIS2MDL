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
int main()
{         
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
    {
        UART_PutChar('a');
        
        
       do 
    {
        i = ReadControlRegisterSPI(LSM6DSRX_STATUS_REG);  //20
                
    }
    while ((i & 0b00000001) == 0); 
    
     
    do 
    {
        i = ReadControlRegisterSPI(LSM6DSRX_STATUS_MASTER_MAINPAGE);   
       // UART_PutChar(SENS_HUB_ENDOP);
    }
    while ((i & 0b00000001) == 0);
   // UART_PutChar(SENS_HUB_ENDOP);
  
   // WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x40);   
    
    
    //WriteControlRegisterSPI(LSM6DSRX_MASTER_CONFIG, 0x08);
    
    CyDelayUs(10);  
      
    ReadControlRegisterSPI(LSM6DSRX_WHO_AM_I); 
    
            i= ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_1);  
        
        UART_PutChar(i);
        
   
        i= ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_2);  
        
        UART_PutChar(i);

        
                i= ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_3);  
        
        UART_PutChar(i);
        
        
                i= ReadControlRegisterSPI(LSM6DSRX_SENSOR_HUB_4);  
        
        UART_PutChar(i);
        
       // WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00);   

    CyDelayUs(10);  
//      ---------------------------------------------------------------------READ AXELS
        
        i = ReadControlRegisterSPI(LSM6DSRX_OUTX_L_A);
        UART_PutChar(i);
        i = ReadControlRegisterSPI(LSM6DSRX_OUTX_H_A);
        UART_PutChar(i); 
        
        i= ReadControlRegisterSPI(LSM6DSRX_OUTY_L_A); //21
        UART_PutChar(i);
         i = ReadControlRegisterSPI(LSM6DSRX_OUTY_H_A);
        UART_PutChar(i);
        
        i = ReadControlRegisterSPI(LSM6DSRX_OUTZ_L_A);
        UART_PutChar(i);
         i= ReadControlRegisterSPI(LSM6DSRX_OUTZ_H_A); //21
        UART_PutChar(i);
    
//      ---------------------------------------------------------------------READ GYROS
        i = ReadControlRegisterSPI(LSM6DSRX_OUTX_L_G);
        UART_PutChar(i);
        i = ReadControlRegisterSPI(LSM6DSRX_OUTX_H_G);
        UART_PutChar(i);

        i = ReadControlRegisterSPI(LSM6DSRX_OUTY_L_G);
        UART_PutChar(i);
        i = ReadControlRegisterSPI(LSM6DSRX_OUTY_H_G);
        UART_PutChar(i);
        
        i = ReadControlRegisterSPI(LSM6DSRX_OUTZ_L_G);
        UART_PutChar(i);
        i = ReadControlRegisterSPI(LSM6DSRX_OUTZ_H_G);
        UART_PutChar(i);
        

        
  
    //   OneShot_ReadRoutine(EXT_SENS_ADDR,LIS2MDL_WHO_AM_I); //LIS2MDL
                
       
    
    }
return 0;
}
/* [] END OF FILE */
