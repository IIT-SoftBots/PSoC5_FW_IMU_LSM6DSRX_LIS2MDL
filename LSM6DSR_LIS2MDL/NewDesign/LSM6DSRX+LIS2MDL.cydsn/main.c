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


uint8 Mag[6];
uint8 XLDA,GDA;
uint8 i,j,k,l,m,n,o,p,q,r,s,t;
uint8 who,tempoLSB,tempoMSB;
uint16 t0,t1,tempo;

int main()
{         
    //Timer_Start();
    SPI_IMU_Start();
	SPI_IMU_Init();
	
	SPI_IMU_ClearRxBuffer();
	SPI_IMU_ClearTxBuffer();
	SPI_IMU_ClearFIFO();							
    //CyDelay(10);
  SPI_IMU_Enable();
    CyGlobalIntEnable;

    
    UART_Start();
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS,0b00000000); //Enable I2C master mode with external sensor
    //WriteControlRegisterSPI(LSM6DSRX_INT1_CTRL,0x01); //104 Hz (normal mode)
    WriteControlRegisterSPI(LSM6DSRX_CTRL1_XL,0x60); //104 Hz (normal mode)
    
    //WriteControlRegisterSPI(LSM6DSRX_INT1_CTRL,0x02); //104 Hz (normal mode)
    WriteControlRegisterSPI(LSM6DSRX_CTRL2_G,0x50); //104 Hz (normal mode)
    //CyDelay(10);
    
  //  OneShot_ReadRoutine(EXT_SENS_ADDR,LIS2MDL_WHO_AM_I); //LIS2MDL
  //  OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_A,0x8C);
  //  OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_B,0x02);
  //  OneShot_WriteRoutine(EXT_SENS_ADDR,LIS2MDL_CFG_REG_C,0x10);
    //Continuous_ReadRoutine(EXT_SENS_ADDR,LIS2MDL_OUTX_L_REG,0x06);
    WriteControlRegisterSPI(LSM6DSRX_FUNC_CFG_ACCESS,0b00000000); //Enable I2C master mode with external sensor
    
    for(;;)
    {   
        

        UART_PutChar('k');
        // OneShot_ReadRoutine1(EXT_SENS_ADDR,LIS2MDL_OUTX_L_REG,0x06);            
        CyDelay(1);
        ReadControlRegisterSPI(LSM6DSRX_WHO_AM_I);
        j = ReadControlRegisterSPI(LSM6DSRX_STATUS_REG);  //
        GDA = (j>>1) & 0b00000001;
        XLDA = j & 0b00000001;
        
  
         if (XLDA && GDA)
        {
            i = ReadControlRegisterSPI(LSM6DSRX_OUTX_L_A);
            j = ReadControlRegisterSPI(LSM6DSRX_OUTX_H_A);
            k = ReadControlRegisterSPI(LSM6DSRX_OUTY_L_A);
            l = ReadControlRegisterSPI(LSM6DSRX_OUTY_H_A);
            m = ReadControlRegisterSPI(LSM6DSRX_OUTZ_L_A);
            n = ReadControlRegisterSPI(LSM6DSRX_OUTZ_H_A);
           
            UART_PutChar(i);
            UART_PutChar(j);
            UART_PutChar(k);
            UART_PutChar(l);
            UART_PutChar(m);
            UART_PutChar(n);
            
            o = ReadControlRegisterSPI(LSM6DSRX_OUTX_L_G);
            p = ReadControlRegisterSPI(LSM6DSRX_OUTX_H_G);
            q = ReadControlRegisterSPI(LSM6DSRX_OUTY_L_G);
            r = ReadControlRegisterSPI(LSM6DSRX_OUTY_H_G);
            s = ReadControlRegisterSPI(LSM6DSRX_OUTZ_L_G);
            t = ReadControlRegisterSPI(LSM6DSRX_OUTZ_H_G);
            UART_PutChar(o);
            UART_PutChar(p);
            UART_PutChar(q);
            UART_PutChar(r);
            UART_PutChar(s);
            UART_PutChar(t);
        }
    }
         
        
       // tempo=(t0-t1)/1;
       // t0=(uint16)Timer_ReadCounter();
        //tempoLSB=(uint8)(tempo&0xFF);
      //tempoMSB=(uint8)((tempo>>8)&0xFF);
      //  UART_PutChar(tempoLSB);
        //UART_PutChar(tempoMSB);
        
        //MY_TIMER_REG_Write(0x01);
       // MY_TIMER_REG_Write(0x00); 
        
    
   
    return 0;
    
}
/* [] END OF FILE */
