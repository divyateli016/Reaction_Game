/*******************************************************************************
* File Name: SEVSEG_A.h  
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

#if !defined(CY_PINS_SEVSEG_A_H) /* Pins SEVSEG_A_H */
#define CY_PINS_SEVSEG_A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SEVSEG_A_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SEVSEG_A__PORT == 15 && ((SEVSEG_A__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SEVSEG_A_Write(uint8 value);
void    SEVSEG_A_SetDriveMode(uint8 mode);
uint8   SEVSEG_A_ReadDataReg(void);
uint8   SEVSEG_A_Read(void);
void    SEVSEG_A_SetInterruptMode(uint16 position, uint16 mode);
uint8   SEVSEG_A_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SEVSEG_A_SetDriveMode() function.
     *  @{
     */
        #define SEVSEG_A_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SEVSEG_A_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SEVSEG_A_DM_RES_UP          PIN_DM_RES_UP
        #define SEVSEG_A_DM_RES_DWN         PIN_DM_RES_DWN
        #define SEVSEG_A_DM_OD_LO           PIN_DM_OD_LO
        #define SEVSEG_A_DM_OD_HI           PIN_DM_OD_HI
        #define SEVSEG_A_DM_STRONG          PIN_DM_STRONG
        #define SEVSEG_A_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SEVSEG_A_MASK               SEVSEG_A__MASK
#define SEVSEG_A_SHIFT              SEVSEG_A__SHIFT
#define SEVSEG_A_WIDTH              1u

/* Interrupt constants */
#if defined(SEVSEG_A__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SEVSEG_A_SetInterruptMode() function.
     *  @{
     */
        #define SEVSEG_A_INTR_NONE      (uint16)(0x0000u)
        #define SEVSEG_A_INTR_RISING    (uint16)(0x0001u)
        #define SEVSEG_A_INTR_FALLING   (uint16)(0x0002u)
        #define SEVSEG_A_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SEVSEG_A_INTR_MASK      (0x01u) 
#endif /* (SEVSEG_A__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SEVSEG_A_PS                     (* (reg8 *) SEVSEG_A__PS)
/* Data Register */
#define SEVSEG_A_DR                     (* (reg8 *) SEVSEG_A__DR)
/* Port Number */
#define SEVSEG_A_PRT_NUM                (* (reg8 *) SEVSEG_A__PRT) 
/* Connect to Analog Globals */                                                  
#define SEVSEG_A_AG                     (* (reg8 *) SEVSEG_A__AG)                       
/* Analog MUX bux enable */
#define SEVSEG_A_AMUX                   (* (reg8 *) SEVSEG_A__AMUX) 
/* Bidirectional Enable */                                                        
#define SEVSEG_A_BIE                    (* (reg8 *) SEVSEG_A__BIE)
/* Bit-mask for Aliased Register Access */
#define SEVSEG_A_BIT_MASK               (* (reg8 *) SEVSEG_A__BIT_MASK)
/* Bypass Enable */
#define SEVSEG_A_BYP                    (* (reg8 *) SEVSEG_A__BYP)
/* Port wide control signals */                                                   
#define SEVSEG_A_CTL                    (* (reg8 *) SEVSEG_A__CTL)
/* Drive Modes */
#define SEVSEG_A_DM0                    (* (reg8 *) SEVSEG_A__DM0) 
#define SEVSEG_A_DM1                    (* (reg8 *) SEVSEG_A__DM1)
#define SEVSEG_A_DM2                    (* (reg8 *) SEVSEG_A__DM2) 
/* Input Buffer Disable Override */
#define SEVSEG_A_INP_DIS                (* (reg8 *) SEVSEG_A__INP_DIS)
/* LCD Common or Segment Drive */
#define SEVSEG_A_LCD_COM_SEG            (* (reg8 *) SEVSEG_A__LCD_COM_SEG)
/* Enable Segment LCD */
#define SEVSEG_A_LCD_EN                 (* (reg8 *) SEVSEG_A__LCD_EN)
/* Slew Rate Control */
#define SEVSEG_A_SLW                    (* (reg8 *) SEVSEG_A__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SEVSEG_A_PRTDSI__CAPS_SEL       (* (reg8 *) SEVSEG_A__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SEVSEG_A_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SEVSEG_A__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SEVSEG_A_PRTDSI__OE_SEL0        (* (reg8 *) SEVSEG_A__PRTDSI__OE_SEL0) 
#define SEVSEG_A_PRTDSI__OE_SEL1        (* (reg8 *) SEVSEG_A__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SEVSEG_A_PRTDSI__OUT_SEL0       (* (reg8 *) SEVSEG_A__PRTDSI__OUT_SEL0) 
#define SEVSEG_A_PRTDSI__OUT_SEL1       (* (reg8 *) SEVSEG_A__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SEVSEG_A_PRTDSI__SYNC_OUT       (* (reg8 *) SEVSEG_A__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SEVSEG_A__SIO_CFG)
    #define SEVSEG_A_SIO_HYST_EN        (* (reg8 *) SEVSEG_A__SIO_HYST_EN)
    #define SEVSEG_A_SIO_REG_HIFREQ     (* (reg8 *) SEVSEG_A__SIO_REG_HIFREQ)
    #define SEVSEG_A_SIO_CFG            (* (reg8 *) SEVSEG_A__SIO_CFG)
    #define SEVSEG_A_SIO_DIFF           (* (reg8 *) SEVSEG_A__SIO_DIFF)
#endif /* (SEVSEG_A__SIO_CFG) */

/* Interrupt Registers */
#if defined(SEVSEG_A__INTSTAT)
    #define SEVSEG_A_INTSTAT            (* (reg8 *) SEVSEG_A__INTSTAT)
    #define SEVSEG_A_SNAP               (* (reg8 *) SEVSEG_A__SNAP)
    
	#define SEVSEG_A_0_INTTYPE_REG 		(* (reg8 *) SEVSEG_A__0__INTTYPE)
#endif /* (SEVSEG_A__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SEVSEG_A_H */


/* [] END OF FILE */
