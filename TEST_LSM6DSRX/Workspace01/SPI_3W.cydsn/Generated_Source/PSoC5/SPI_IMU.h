/*******************************************************************************
* File Name: SPI_IMU.h
* Version 2.50
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the SPI Master Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIM_SPI_IMU_H)
#define CY_SPIM_SPI_IMU_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define SPI_IMU_INTERNAL_CLOCK             (0u)

#if(0u != SPI_IMU_INTERNAL_CLOCK)
    #include "SPI_IMU_IntClock.h"
#endif /* (0u != SPI_IMU_INTERNAL_CLOCK) */

#define SPI_IMU_MODE                       (4u)
#define SPI_IMU_DATA_WIDTH                 (8u)
#define SPI_IMU_MODE_USE_ZERO              (0u)
#define SPI_IMU_BIDIRECTIONAL_MODE         (1u)

/* Internal interrupt handling */
#define SPI_IMU_TX_BUFFER_SIZE             (4u)
#define SPI_IMU_RX_BUFFER_SIZE             (4u)
#define SPI_IMU_INTERNAL_TX_INT_ENABLED    (0u)
#define SPI_IMU_INTERNAL_RX_INT_ENABLED    (0u)

#define SPI_IMU_SINGLE_REG_SIZE            (8u)
#define SPI_IMU_USE_SECOND_DATAPATH        (SPI_IMU_DATA_WIDTH > SPI_IMU_SINGLE_REG_SIZE)

#define SPI_IMU_FIFO_SIZE                  (4u)
#define SPI_IMU_TX_SOFTWARE_BUF_ENABLED    ((0u != SPI_IMU_INTERNAL_TX_INT_ENABLED) && \
                                                     (SPI_IMU_TX_BUFFER_SIZE > SPI_IMU_FIFO_SIZE))

#define SPI_IMU_RX_SOFTWARE_BUF_ENABLED    ((0u != SPI_IMU_INTERNAL_RX_INT_ENABLED) && \
                                                     (SPI_IMU_RX_BUFFER_SIZE > SPI_IMU_FIFO_SIZE))


/***************************************
*        Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint8 cntrPeriod;
} SPI_IMU_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  SPI_IMU_Init(void)                           ;
void  SPI_IMU_Enable(void)                         ;
void  SPI_IMU_Start(void)                          ;
void  SPI_IMU_Stop(void)                           ;

void  SPI_IMU_EnableTxInt(void)                    ;
void  SPI_IMU_EnableRxInt(void)                    ;
void  SPI_IMU_DisableTxInt(void)                   ;
void  SPI_IMU_DisableRxInt(void)                   ;

void  SPI_IMU_Sleep(void)                          ;
void  SPI_IMU_Wakeup(void)                         ;
void  SPI_IMU_SaveConfig(void)                     ;
void  SPI_IMU_RestoreConfig(void)                  ;

void  SPI_IMU_SetTxInterruptMode(uint8 intSrc)     ;
void  SPI_IMU_SetRxInterruptMode(uint8 intSrc)     ;
uint8 SPI_IMU_ReadTxStatus(void)                   ;
uint8 SPI_IMU_ReadRxStatus(void)                   ;
void  SPI_IMU_WriteTxData(uint8 txData)  \
                                                            ;
uint8 SPI_IMU_ReadRxData(void) \
                                                            ;
uint8 SPI_IMU_GetRxBufferSize(void)                ;
uint8 SPI_IMU_GetTxBufferSize(void)                ;
void  SPI_IMU_ClearRxBuffer(void)                  ;
void  SPI_IMU_ClearTxBuffer(void)                  ;
void  SPI_IMU_ClearFIFO(void)                              ;
void  SPI_IMU_PutArray(const uint8 buffer[], uint8 byteCount) \
                                                            ;

#if(0u != SPI_IMU_BIDIRECTIONAL_MODE)
    void  SPI_IMU_TxEnable(void)                   ;
    void  SPI_IMU_TxDisable(void)                  ;
#endif /* (0u != SPI_IMU_BIDIRECTIONAL_MODE) */

CY_ISR_PROTO(SPI_IMU_TX_ISR);
CY_ISR_PROTO(SPI_IMU_RX_ISR);


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 SPI_IMU_initVar;


/***************************************
*           API Constants
***************************************/

#define SPI_IMU_TX_ISR_NUMBER     ((uint8) (SPI_IMU_TxInternalInterrupt__INTC_NUMBER))
#define SPI_IMU_RX_ISR_NUMBER     ((uint8) (SPI_IMU_RxInternalInterrupt__INTC_NUMBER))

#define SPI_IMU_TX_ISR_PRIORITY   ((uint8) (SPI_IMU_TxInternalInterrupt__INTC_PRIOR_NUM))
#define SPI_IMU_RX_ISR_PRIORITY   ((uint8) (SPI_IMU_RxInternalInterrupt__INTC_PRIOR_NUM))


/***************************************
*    Initial Parameter Constants
***************************************/

#define SPI_IMU_INT_ON_SPI_DONE    ((uint8) (0u   << SPI_IMU_STS_SPI_DONE_SHIFT))
#define SPI_IMU_INT_ON_TX_EMPTY    ((uint8) (0u   << SPI_IMU_STS_TX_FIFO_EMPTY_SHIFT))
#define SPI_IMU_INT_ON_TX_NOT_FULL ((uint8) (0u << \
                                                                           SPI_IMU_STS_TX_FIFO_NOT_FULL_SHIFT))
#define SPI_IMU_INT_ON_BYTE_COMP   ((uint8) (0u  << SPI_IMU_STS_BYTE_COMPLETE_SHIFT))
#define SPI_IMU_INT_ON_SPI_IDLE    ((uint8) (0u   << SPI_IMU_STS_SPI_IDLE_SHIFT))

/* Disable TX_NOT_FULL if software buffer is used */
#define SPI_IMU_INT_ON_TX_NOT_FULL_DEF ((SPI_IMU_TX_SOFTWARE_BUF_ENABLED) ? \
                                                                        (0u) : (SPI_IMU_INT_ON_TX_NOT_FULL))

/* TX interrupt mask */
#define SPI_IMU_TX_INIT_INTERRUPTS_MASK    (SPI_IMU_INT_ON_SPI_DONE  | \
                                                     SPI_IMU_INT_ON_TX_EMPTY  | \
                                                     SPI_IMU_INT_ON_TX_NOT_FULL_DEF | \
                                                     SPI_IMU_INT_ON_BYTE_COMP | \
                                                     SPI_IMU_INT_ON_SPI_IDLE)

#define SPI_IMU_INT_ON_RX_FULL         ((uint8) (0u << \
                                                                          SPI_IMU_STS_RX_FIFO_FULL_SHIFT))
#define SPI_IMU_INT_ON_RX_NOT_EMPTY    ((uint8) (0u << \
                                                                          SPI_IMU_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define SPI_IMU_INT_ON_RX_OVER         ((uint8) (0u << \
                                                                          SPI_IMU_STS_RX_FIFO_OVERRUN_SHIFT))

/* RX interrupt mask */
#define SPI_IMU_RX_INIT_INTERRUPTS_MASK    (SPI_IMU_INT_ON_RX_FULL      | \
                                                     SPI_IMU_INT_ON_RX_NOT_EMPTY | \
                                                     SPI_IMU_INT_ON_RX_OVER)
/* Nubmer of bits to receive/transmit */
#define SPI_IMU_BITCTR_INIT            (((uint8) (SPI_IMU_DATA_WIDTH << 1u)) - 1u)


/***************************************
*             Registers
***************************************/
#if(CY_PSOC3 || CY_PSOC5)
    #define SPI_IMU_TXDATA_REG (* (reg8 *) \
                                                SPI_IMU_BSPIM_sR8_Dp_u0__F0_REG)
    #define SPI_IMU_TXDATA_PTR (  (reg8 *) \
                                                SPI_IMU_BSPIM_sR8_Dp_u0__F0_REG)
    #define SPI_IMU_RXDATA_REG (* (reg8 *) \
                                                SPI_IMU_BSPIM_sR8_Dp_u0__F1_REG)
    #define SPI_IMU_RXDATA_PTR (  (reg8 *) \
                                                SPI_IMU_BSPIM_sR8_Dp_u0__F1_REG)
#else   /* PSOC4 */
    #if(SPI_IMU_USE_SECOND_DATAPATH)
        #define SPI_IMU_TXDATA_REG (* (reg16 *) \
                                          SPI_IMU_BSPIM_sR8_Dp_u0__16BIT_F0_REG)
        #define SPI_IMU_TXDATA_PTR (  (reg16 *) \
                                          SPI_IMU_BSPIM_sR8_Dp_u0__16BIT_F0_REG)
        #define SPI_IMU_RXDATA_REG (* (reg16 *) \
                                          SPI_IMU_BSPIM_sR8_Dp_u0__16BIT_F1_REG)
        #define SPI_IMU_RXDATA_PTR (  (reg16 *) \
                                          SPI_IMU_BSPIM_sR8_Dp_u0__16BIT_F1_REG)
    #else
        #define SPI_IMU_TXDATA_REG (* (reg8 *) \
                                                SPI_IMU_BSPIM_sR8_Dp_u0__F0_REG)
        #define SPI_IMU_TXDATA_PTR (  (reg8 *) \
                                                SPI_IMU_BSPIM_sR8_Dp_u0__F0_REG)
        #define SPI_IMU_RXDATA_REG (* (reg8 *) \
                                                SPI_IMU_BSPIM_sR8_Dp_u0__F1_REG)
        #define SPI_IMU_RXDATA_PTR (  (reg8 *) \
                                                SPI_IMU_BSPIM_sR8_Dp_u0__F1_REG)
    #endif /* (SPI_IMU_USE_SECOND_DATAPATH) */
#endif     /* (CY_PSOC3 || CY_PSOC5) */

#define SPI_IMU_AUX_CONTROL_DP0_REG (* (reg8 *) \
                                        SPI_IMU_BSPIM_sR8_Dp_u0__DP_AUX_CTL_REG)
#define SPI_IMU_AUX_CONTROL_DP0_PTR (  (reg8 *) \
                                        SPI_IMU_BSPIM_sR8_Dp_u0__DP_AUX_CTL_REG)

#if(SPI_IMU_USE_SECOND_DATAPATH)
    #define SPI_IMU_AUX_CONTROL_DP1_REG  (* (reg8 *) \
                                        SPI_IMU_BSPIM_sR8_Dp_u1__DP_AUX_CTL_REG)
    #define SPI_IMU_AUX_CONTROL_DP1_PTR  (  (reg8 *) \
                                        SPI_IMU_BSPIM_sR8_Dp_u1__DP_AUX_CTL_REG)
#endif /* (SPI_IMU_USE_SECOND_DATAPATH) */

#define SPI_IMU_COUNTER_PERIOD_REG     (* (reg8 *) SPI_IMU_BSPIM_BitCounter__PERIOD_REG)
#define SPI_IMU_COUNTER_PERIOD_PTR     (  (reg8 *) SPI_IMU_BSPIM_BitCounter__PERIOD_REG)
#define SPI_IMU_COUNTER_CONTROL_REG    (* (reg8 *) SPI_IMU_BSPIM_BitCounter__CONTROL_AUX_CTL_REG)
#define SPI_IMU_COUNTER_CONTROL_PTR    (  (reg8 *) SPI_IMU_BSPIM_BitCounter__CONTROL_AUX_CTL_REG)

#define SPI_IMU_TX_STATUS_REG          (* (reg8 *) SPI_IMU_BSPIM_TxStsReg__STATUS_REG)
#define SPI_IMU_TX_STATUS_PTR          (  (reg8 *) SPI_IMU_BSPIM_TxStsReg__STATUS_REG)
#define SPI_IMU_RX_STATUS_REG          (* (reg8 *) SPI_IMU_BSPIM_RxStsReg__STATUS_REG)
#define SPI_IMU_RX_STATUS_PTR          (  (reg8 *) SPI_IMU_BSPIM_RxStsReg__STATUS_REG)

#define SPI_IMU_CONTROL_REG            (* (reg8 *) \
                                      SPI_IMU_BSPIM_BidirMode_CtrlReg__CONTROL_REG)
#define SPI_IMU_CONTROL_PTR            (  (reg8 *) \
                                      SPI_IMU_BSPIM_BidirMode_CtrlReg__CONTROL_REG)

#define SPI_IMU_TX_STATUS_MASK_REG     (* (reg8 *) SPI_IMU_BSPIM_TxStsReg__MASK_REG)
#define SPI_IMU_TX_STATUS_MASK_PTR     (  (reg8 *) SPI_IMU_BSPIM_TxStsReg__MASK_REG)
#define SPI_IMU_RX_STATUS_MASK_REG     (* (reg8 *) SPI_IMU_BSPIM_RxStsReg__MASK_REG)
#define SPI_IMU_RX_STATUS_MASK_PTR     (  (reg8 *) SPI_IMU_BSPIM_RxStsReg__MASK_REG)

#define SPI_IMU_TX_STATUS_ACTL_REG     (* (reg8 *) SPI_IMU_BSPIM_TxStsReg__STATUS_AUX_CTL_REG)
#define SPI_IMU_TX_STATUS_ACTL_PTR     (  (reg8 *) SPI_IMU_BSPIM_TxStsReg__STATUS_AUX_CTL_REG)
#define SPI_IMU_RX_STATUS_ACTL_REG     (* (reg8 *) SPI_IMU_BSPIM_RxStsReg__STATUS_AUX_CTL_REG)
#define SPI_IMU_RX_STATUS_ACTL_PTR     (  (reg8 *) SPI_IMU_BSPIM_RxStsReg__STATUS_AUX_CTL_REG)

#if(SPI_IMU_USE_SECOND_DATAPATH)
    #define SPI_IMU_AUX_CONTROLDP1     (SPI_IMU_AUX_CONTROL_DP1_REG)
#endif /* (SPI_IMU_USE_SECOND_DATAPATH) */


/***************************************
*       Register Constants
***************************************/

/* Status Register Definitions */
#define SPI_IMU_STS_SPI_DONE_SHIFT             (0x00u)
#define SPI_IMU_STS_TX_FIFO_EMPTY_SHIFT        (0x01u)
#define SPI_IMU_STS_TX_FIFO_NOT_FULL_SHIFT     (0x02u)
#define SPI_IMU_STS_BYTE_COMPLETE_SHIFT        (0x03u)
#define SPI_IMU_STS_SPI_IDLE_SHIFT             (0x04u)
#define SPI_IMU_STS_RX_FIFO_FULL_SHIFT         (0x04u)
#define SPI_IMU_STS_RX_FIFO_NOT_EMPTY_SHIFT    (0x05u)
#define SPI_IMU_STS_RX_FIFO_OVERRUN_SHIFT      (0x06u)

#define SPI_IMU_STS_SPI_DONE           ((uint8) (0x01u << SPI_IMU_STS_SPI_DONE_SHIFT))
#define SPI_IMU_STS_TX_FIFO_EMPTY      ((uint8) (0x01u << SPI_IMU_STS_TX_FIFO_EMPTY_SHIFT))
#define SPI_IMU_STS_TX_FIFO_NOT_FULL   ((uint8) (0x01u << SPI_IMU_STS_TX_FIFO_NOT_FULL_SHIFT))
#define SPI_IMU_STS_BYTE_COMPLETE      ((uint8) (0x01u << SPI_IMU_STS_BYTE_COMPLETE_SHIFT))
#define SPI_IMU_STS_SPI_IDLE           ((uint8) (0x01u << SPI_IMU_STS_SPI_IDLE_SHIFT))
#define SPI_IMU_STS_RX_FIFO_FULL       ((uint8) (0x01u << SPI_IMU_STS_RX_FIFO_FULL_SHIFT))
#define SPI_IMU_STS_RX_FIFO_NOT_EMPTY  ((uint8) (0x01u << SPI_IMU_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define SPI_IMU_STS_RX_FIFO_OVERRUN    ((uint8) (0x01u << SPI_IMU_STS_RX_FIFO_OVERRUN_SHIFT))

/* TX and RX masks for clear on read bits */
#define SPI_IMU_TX_STS_CLR_ON_RD_BYTES_MASK    (0x09u)
#define SPI_IMU_RX_STS_CLR_ON_RD_BYTES_MASK    (0x40u)

/* StatusI Register Interrupt Enable Control Bits */
/* As defined by the Register map for the AUX Control Register */
#define SPI_IMU_INT_ENABLE     (0x10u) /* Enable interrupt from statusi */
#define SPI_IMU_TX_FIFO_CLR    (0x01u) /* F0 - TX FIFO */
#define SPI_IMU_RX_FIFO_CLR    (0x02u) /* F1 - RX FIFO */
#define SPI_IMU_FIFO_CLR       (SPI_IMU_TX_FIFO_CLR | SPI_IMU_RX_FIFO_CLR)

/* Bit Counter (7-bit) Control Register Bit Definitions */
/* As defined by the Register map for the AUX Control Register */
#define SPI_IMU_CNTR_ENABLE    (0x20u) /* Enable CNT7 */

/* Bi-Directional mode control bit */
#define SPI_IMU_CTRL_TX_SIGNAL_EN  (0x01u)

/* Datapath Auxillary Control Register definitions */
#define SPI_IMU_AUX_CTRL_FIFO0_CLR         (0x01u)
#define SPI_IMU_AUX_CTRL_FIFO1_CLR         (0x02u)
#define SPI_IMU_AUX_CTRL_FIFO0_LVL         (0x04u)
#define SPI_IMU_AUX_CTRL_FIFO1_LVL         (0x08u)
#define SPI_IMU_STATUS_ACTL_INT_EN_MASK    (0x10u)

/* Component disabled */
#define SPI_IMU_DISABLED   (0u)


/***************************************
*       Macros
***************************************/

/* Returns true if componentn enabled */
#define SPI_IMU_IS_ENABLED (0u != (SPI_IMU_TX_STATUS_ACTL_REG & SPI_IMU_INT_ENABLE))

/* Retuns TX status register */
#define SPI_IMU_GET_STATUS_TX(swTxSts) ( (uint8)(SPI_IMU_TX_STATUS_REG | \
                                                          ((swTxSts) & SPI_IMU_TX_STS_CLR_ON_RD_BYTES_MASK)) )
/* Retuns RX status register */
#define SPI_IMU_GET_STATUS_RX(swRxSts) ( (uint8)(SPI_IMU_RX_STATUS_REG | \
                                                          ((swRxSts) & SPI_IMU_RX_STS_CLR_ON_RD_BYTES_MASK)) )


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define SPI_IMU_WriteByte   SPI_IMU_WriteTxData
#define SPI_IMU_ReadByte    SPI_IMU_ReadRxData
void  SPI_IMU_SetInterruptMode(uint8 intSrc)       ;
uint8 SPI_IMU_ReadStatus(void)                     ;
void  SPI_IMU_EnableInt(void)                      ;
void  SPI_IMU_DisableInt(void)                     ;

#define SPI_IMU_TXDATA                 (SPI_IMU_TXDATA_REG)
#define SPI_IMU_RXDATA                 (SPI_IMU_RXDATA_REG)
#define SPI_IMU_AUX_CONTROLDP0         (SPI_IMU_AUX_CONTROL_DP0_REG)
#define SPI_IMU_TXBUFFERREAD           (SPI_IMU_txBufferRead)
#define SPI_IMU_TXBUFFERWRITE          (SPI_IMU_txBufferWrite)
#define SPI_IMU_RXBUFFERREAD           (SPI_IMU_rxBufferRead)
#define SPI_IMU_RXBUFFERWRITE          (SPI_IMU_rxBufferWrite)

#define SPI_IMU_COUNTER_PERIOD         (SPI_IMU_COUNTER_PERIOD_REG)
#define SPI_IMU_COUNTER_CONTROL        (SPI_IMU_COUNTER_CONTROL_REG)
#define SPI_IMU_STATUS                 (SPI_IMU_TX_STATUS_REG)
#define SPI_IMU_CONTROL                (SPI_IMU_CONTROL_REG)
#define SPI_IMU_STATUS_MASK            (SPI_IMU_TX_STATUS_MASK_REG)
#define SPI_IMU_STATUS_ACTL            (SPI_IMU_TX_STATUS_ACTL_REG)

#define SPI_IMU_INIT_INTERRUPTS_MASK  (SPI_IMU_INT_ON_SPI_DONE     | \
                                                SPI_IMU_INT_ON_TX_EMPTY     | \
                                                SPI_IMU_INT_ON_TX_NOT_FULL_DEF  | \
                                                SPI_IMU_INT_ON_RX_FULL      | \
                                                SPI_IMU_INT_ON_RX_NOT_EMPTY | \
                                                SPI_IMU_INT_ON_RX_OVER      | \
                                                SPI_IMU_INT_ON_BYTE_COMP)
                                                
#define SPI_IMU_DataWidth                  (SPI_IMU_DATA_WIDTH)
#define SPI_IMU_InternalClockUsed          (SPI_IMU_INTERNAL_CLOCK)
#define SPI_IMU_InternalTxInterruptEnabled (SPI_IMU_INTERNAL_TX_INT_ENABLED)
#define SPI_IMU_InternalRxInterruptEnabled (SPI_IMU_INTERNAL_RX_INT_ENABLED)
#define SPI_IMU_ModeUseZero                (SPI_IMU_MODE_USE_ZERO)
#define SPI_IMU_BidirectionalMode          (SPI_IMU_BIDIRECTIONAL_MODE)
#define SPI_IMU_Mode                       (SPI_IMU_MODE)
#define SPI_IMU_DATAWIDHT                  (SPI_IMU_DATA_WIDTH)
#define SPI_IMU_InternalInterruptEnabled   (0u)

#define SPI_IMU_TXBUFFERSIZE   (SPI_IMU_TX_BUFFER_SIZE)
#define SPI_IMU_RXBUFFERSIZE   (SPI_IMU_RX_BUFFER_SIZE)

#define SPI_IMU_TXBUFFER       SPI_IMU_txBuffer
#define SPI_IMU_RXBUFFER       SPI_IMU_rxBuffer

#endif /* (CY_SPIM_SPI_IMU_H) */


/* [] END OF FILE */
