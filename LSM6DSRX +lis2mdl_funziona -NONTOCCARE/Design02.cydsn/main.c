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
    
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS, 0x00);
   CyDelay(100);
    OneShot_ReadRoutine(EXT_SENS_ADDR,LIS2MDL_WHO_AM_I); //LIS2MDL
    OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_A,0x8C);
    OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_B,0x02);
    OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_C,0x10);
    //Continuous_ReadRoutine(EXT_SENS_ADDR,LIS2MDL_OUTX_L_REG,0x06);
    
    for(;;)
    {
        UART_PutChar('a');
        CyDelay(10);
        
        OneShot_ReadRoutine1(EXT_SENS_ADDR,LIS2MDL_OUTX_L_REG,0x06);
  
    //    OneShot_ReadRoutine(EXT_SENS_ADDR,LIS2MDL_WHO_AM_I); //LIS2MDL
                CyDelay(100);
       
        
   // OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_A,0x07);
   //  who = OneShot_ReadRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_A);
      // UART_PutChar(who);
       // who = OneShot_ReadRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_A);
      //  UART_PutChar(who);
      //  OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_A,0x07);
  
        //OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_A,0x07);
        //who= OneShot_ReadRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_A);
        //UART_PutChar(who);
        /*
        for (i = 0; i < 6; i++)
        {
            UART_PutChar(Mag[i]);
        }*/
      
     //Read(0x01);
    //UART_PutChar(Mag[0]);
        
    
    }
return 0;
}
/* [] END OF FILE */
