/*******************************************************************************
* File Name: ck.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ck_H) /* Pins ck_H */
#define CY_PINS_ck_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ck_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ck__PORT == 15 && ((ck__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ck_Write(uint8 value);
void    ck_SetDriveMode(uint8 mode);
uint8   ck_ReadDataReg(void);
uint8   ck_Read(void);
void    ck_SetInterruptMode(uint16 position, uint16 mode);
uint8   ck_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ck_SetDriveMode() function.
     *  @{
     */
        #define ck_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ck_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ck_DM_RES_UP          PIN_DM_RES_UP
        #define ck_DM_RES_DWN         PIN_DM_RES_DWN
        #define ck_DM_OD_LO           PIN_DM_OD_LO
        #define ck_DM_OD_HI           PIN_DM_OD_HI
        #define ck_DM_STRONG          PIN_DM_STRONG
        #define ck_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ck_MASK               ck__MASK
#define ck_SHIFT              ck__SHIFT
#define ck_WIDTH              1u

/* Interrupt constants */
#if defined(ck__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ck_SetInterruptMode() function.
     *  @{
     */
        #define ck_INTR_NONE      (uint16)(0x0000u)
        #define ck_INTR_RISING    (uint16)(0x0001u)
        #define ck_INTR_FALLING   (uint16)(0x0002u)
        #define ck_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ck_INTR_MASK      (0x01u) 
#endif /* (ck__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ck_PS                     (* (reg8 *) ck__PS)
/* Data Register */
#define ck_DR                     (* (reg8 *) ck__DR)
/* Port Number */
#define ck_PRT_NUM                (* (reg8 *) ck__PRT) 
/* Connect to Analog Globals */                                                  
#define ck_AG                     (* (reg8 *) ck__AG)                       
/* Analog MUX bux enable */
#define ck_AMUX                   (* (reg8 *) ck__AMUX) 
/* Bidirectional Enable */                                                        
#define ck_BIE                    (* (reg8 *) ck__BIE)
/* Bit-mask for Aliased Register Access */
#define ck_BIT_MASK               (* (reg8 *) ck__BIT_MASK)
/* Bypass Enable */
#define ck_BYP                    (* (reg8 *) ck__BYP)
/* Port wide control signals */                                                   
#define ck_CTL                    (* (reg8 *) ck__CTL)
/* Drive Modes */
#define ck_DM0                    (* (reg8 *) ck__DM0) 
#define ck_DM1                    (* (reg8 *) ck__DM1)
#define ck_DM2                    (* (reg8 *) ck__DM2) 
/* Input Buffer Disable Override */
#define ck_INP_DIS                (* (reg8 *) ck__INP_DIS)
/* LCD Common or Segment Drive */
#define ck_LCD_COM_SEG            (* (reg8 *) ck__LCD_COM_SEG)
/* Enable Segment LCD */
#define ck_LCD_EN                 (* (reg8 *) ck__LCD_EN)
/* Slew Rate Control */
#define ck_SLW                    (* (reg8 *) ck__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ck_PRTDSI__CAPS_SEL       (* (reg8 *) ck__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ck_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ck__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ck_PRTDSI__OE_SEL0        (* (reg8 *) ck__PRTDSI__OE_SEL0) 
#define ck_PRTDSI__OE_SEL1        (* (reg8 *) ck__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ck_PRTDSI__OUT_SEL0       (* (reg8 *) ck__PRTDSI__OUT_SEL0) 
#define ck_PRTDSI__OUT_SEL1       (* (reg8 *) ck__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ck_PRTDSI__SYNC_OUT       (* (reg8 *) ck__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ck__SIO_CFG)
    #define ck_SIO_HYST_EN        (* (reg8 *) ck__SIO_HYST_EN)
    #define ck_SIO_REG_HIFREQ     (* (reg8 *) ck__SIO_REG_HIFREQ)
    #define ck_SIO_CFG            (* (reg8 *) ck__SIO_CFG)
    #define ck_SIO_DIFF           (* (reg8 *) ck__SIO_DIFF)
#endif /* (ck__SIO_CFG) */

/* Interrupt Registers */
#if defined(ck__INTSTAT)
    #define ck_INTSTAT            (* (reg8 *) ck__INTSTAT)
    #define ck_SNAP               (* (reg8 *) ck__SNAP)
    
	#define ck_0_INTTYPE_REG 		(* (reg8 *) ck__0__INTTYPE)
#endif /* (ck__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ck_H */


/* [] END OF FILE */
