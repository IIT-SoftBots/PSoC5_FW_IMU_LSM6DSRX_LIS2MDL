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
#include "interrupts.h"
#include "globals.h"
CY_ISR(isr_Acc_Handler){
flag_int=1;
   
    // Set cycles interrupt flag
    LED_Write(1);
    CyDelay(5);
LED_Write(0);
CyDelay(50);

}

CY_ISR(isr_Gyro_Handler){

    // Set cycles interrupt flag
    


}


/* [] END OF FILE */
