
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

#include <project.h>
#include "globals.h"
#include <stdlib.h>
#include <stdio.h>

void WriteControlRegisterIMU(uint8 address, uint8 dta);

//LSM6DSRX Register definition
#define LSM6DSRX_INT1_CTRL              0x0D
#define LSM6DSRX_INT2_CTRL              0x0E
#define LSM6DSRX_WHO_AM_I               0x0F
#define LSM6DSRX_CTRL1_XL               0x10
#define LSM6DSRX_CTRL2_G                0x11      
#define LSM6DSRX_CTRL3_C                0x12
#define LSM6DSRX_CTRL4_C                0x13
#define LSM6DSRX_CTRL5_C                0x14
#define LSM6DSRX_CTRL6_C                0x15
#define LSM6DSRX_CTRL7_G                0x16
#define LSM6DSRX_CTRL8_XL               0x17
#define LSM6DSRX_CTRL9_XL               0x18
#define LSM6DSRX_CTRL10_C               0x19
#define LSM6DSRX_ALL_INT_SRC

#define LSM6DSRX_STATUS_REG             0x1E
#define LSM6DSRX_OUT_TEMP1              0x20
#define LSM6DSRX_OUT_TEMP2              0x21
#define LSM6DSRX_OUTX_L_G               0x22
#define LSM6DSRX_OUTX_H_G               0x23
#define LSM6DSRX_OUTY_L_G               0x24
#define LSM6DSRX_OUTY_H_G               0x25
#define LSM6DSRX_OUTZ_L_G               0x26
#define LSM6DSRX_OUTZ_H_G               0x27
#define LSM6DSRX_OUTX_L_A               0x28
#define LSM6DSRX_OUTX_H_A               0x29
#define LSM6DSRX_OUTY_L_A               0x2A
#define LSM6DSRX_OUTY_H_A               0x2B
#define LSM6DSRX_OUTZ_L_A               0x2C
#define LSM6DSRX_OUTZ_H_A               0x2D
#define LSM6DSRX_TIMESTAMP0             0x40
#define LSM6DSRX_TIMESTAMP1             0x41
#define LSM6DSRX_TIMESTAMP2             0x42
#define LSM6DSRX_TIMESTAMP3             0x43

#define LSM6DSRX_MD1_CFG                0x5E
#define LSM6DSRX_MD2_CFG                0x5F

#define LSM6DSRX_INTERNAL_FREQ_FINE     0x63

#define LSM6DSRX_X_OFS_USR              0x73
#define LSM6DSRX_Y_OFS_USR              0x74
#define LSM6DSRX_Z_OFS_USR              0x75


/* [] END OF FILE */
