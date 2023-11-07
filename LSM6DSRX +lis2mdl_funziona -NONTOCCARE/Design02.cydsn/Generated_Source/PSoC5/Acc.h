/*******************************************************************************
* File Name: Acc.h  
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

#if !defined(CY_PINS_Acc_H) /* Pins Acc_H */
#define CY_PINS_Acc_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Acc_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Acc__PORT == 15 && ((Acc__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Acc_Write(uint8 value);
void    Acc_SetDriveMode(uint8 mode);
uint8   Acc_ReadDataReg(void);
uint8   Acc_Read(void);
void    Acc_SetInterruptMode(uint16 position, uint16 mode);
uint8   Acc_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Acc_SetDriveMode() function.
     *  @{
     */
        #define Acc_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Acc_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Acc_DM_RES_UP          PIN_DM_RES_UP
        #define Acc_DM_RES_DWN         PIN_DM_RES_DWN
        #define Acc_DM_OD_LO           PIN_DM_OD_LO
        #define Acc_DM_OD_HI           PIN_DM_OD_HI
        #define Acc_DM_STRONG          PIN_DM_STRONG
        #define Acc_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Acc_MASK               Acc__MASK
#define Acc_SHIFT              Acc__SHIFT
#define Acc_WIDTH              1u

/* Interrupt constants */
#if defined(Acc__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Acc_SetInterruptMode() function.
     *  @{
     */
        #define Acc_INTR_NONE      (uint16)(0x0000u)
        #define Acc_INTR_RISING    (uint16)(0x0001u)
        #define Acc_INTR_FALLING   (uint16)(0x0002u)
        #define Acc_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Acc_INTR_MASK      (0x01u) 
#endif /* (Acc__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Acc_PS                     (* (reg8 *) Acc__PS)
/* Data Register */
#define Acc_DR                     (* (reg8 *) Acc__DR)
/* Port Number */
#define Acc_PRT_NUM                (* (reg8 *) Acc__PRT) 
/* Connect to Analog Globals */                                                  
#define Acc_AG                     (* (reg8 *) Acc__AG)                       
/* Analog MUX bux enable */
#define Acc_AMUX                   (* (reg8 *) Acc__AMUX) 
/* Bidirectional Enable */                                                        
#define Acc_BIE                    (* (reg8 *) Acc__BIE)
/* Bit-mask for Aliased Register Access */
#define Acc_BIT_MASK               (* (reg8 *) Acc__BIT_MASK)
/* Bypass Enable */
#define Acc_BYP                    (* (reg8 *) Acc__BYP)
/* Port wide control signals */                                                   
#define Acc_CTL                    (* (reg8 *) Acc__CTL)
/* Drive Modes */
#define Acc_DM0                    (* (reg8 *) Acc__DM0) 
#define Acc_DM1                    (* (reg8 *) Acc__DM1)
#define Acc_DM2                    (* (reg8 *) Acc__DM2) 
/* Input Buffer Disable Override */
#define Acc_INP_DIS                (* (reg8 *) Acc__INP_DIS)
/* LCD Common or Segment Drive */
#define Acc_LCD_COM_SEG            (* (reg8 *) Acc__LCD_COM_SEG)
/* Enable Segment LCD */
#define Acc_LCD_EN                 (* (reg8 *) Acc__LCD_EN)
/* Slew Rate Control */
#define Acc_SLW                    (* (reg8 *) Acc__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Acc_PRTDSI__CAPS_SEL       (* (reg8 *) Acc__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Acc_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Acc__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Acc_PRTDSI__OE_SEL0        (* (reg8 *) Acc__PRTDSI__OE_SEL0) 
#define Acc_PRTDSI__OE_SEL1        (* (reg8 *) Acc__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Acc_PRTDSI__OUT_SEL0       (* (reg8 *) Acc__PRTDSI__OUT_SEL0) 
#define Acc_PRTDSI__OUT_SEL1       (* (reg8 *) Acc__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Acc_PRTDSI__SYNC_OUT       (* (reg8 *) Acc__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Acc__SIO_CFG)
    #define Acc_SIO_HYST_EN        (* (reg8 *) Acc__SIO_HYST_EN)
    #define Acc_SIO_REG_HIFREQ     (* (reg8 *) Acc__SIO_REG_HIFREQ)
    #define Acc_SIO_CFG            (* (reg8 *) Acc__SIO_CFG)
    #define Acc_SIO_DIFF           (* (reg8 *) Acc__SIO_DIFF)
#endif /* (Acc__SIO_CFG) */

/* Interrupt Registers */
#if defined(Acc__INTSTAT)
    #define Acc_INTSTAT            (* (reg8 *) Acc__INTSTAT)
    #define Acc_SNAP               (* (reg8 *) Acc__SNAP)
    
	#define Acc_0_INTTYPE_REG 		(* (reg8 *) Acc__0__INTTYPE)
#endif /* (Acc__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Acc_H */


/* [] END OF FILE */
