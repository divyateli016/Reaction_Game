/*******************************************************************************
* File Name: SEVSEG_G.h  
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

#if !defined(CY_PINS_SEVSEG_G_H) /* Pins SEVSEG_G_H */
#define CY_PINS_SEVSEG_G_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SEVSEG_G_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SEVSEG_G__PORT == 15 && ((SEVSEG_G__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SEVSEG_G_Write(uint8 value);
void    SEVSEG_G_SetDriveMode(uint8 mode);
uint8   SEVSEG_G_ReadDataReg(void);
uint8   SEVSEG_G_Read(void);
void    SEVSEG_G_SetInterruptMode(uint16 position, uint16 mode);
uint8   SEVSEG_G_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SEVSEG_G_SetDriveMode() function.
     *  @{
     */
        #define SEVSEG_G_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SEVSEG_G_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SEVSEG_G_DM_RES_UP          PIN_DM_RES_UP
        #define SEVSEG_G_DM_RES_DWN         PIN_DM_RES_DWN
        #define SEVSEG_G_DM_OD_LO           PIN_DM_OD_LO
        #define SEVSEG_G_DM_OD_HI           PIN_DM_OD_HI
        #define SEVSEG_G_DM_STRONG          PIN_DM_STRONG
        #define SEVSEG_G_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SEVSEG_G_MASK               SEVSEG_G__MASK
#define SEVSEG_G_SHIFT              SEVSEG_G__SHIFT
#define SEVSEG_G_WIDTH              1u

/* Interrupt constants */
#if defined(SEVSEG_G__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SEVSEG_G_SetInterruptMode() function.
     *  @{
     */
        #define SEVSEG_G_INTR_NONE      (uint16)(0x0000u)
        #define SEVSEG_G_INTR_RISING    (uint16)(0x0001u)
        #define SEVSEG_G_INTR_FALLING   (uint16)(0x0002u)
        #define SEVSEG_G_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SEVSEG_G_INTR_MASK      (0x01u) 
#endif /* (SEVSEG_G__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SEVSEG_G_PS                     (* (reg8 *) SEVSEG_G__PS)
/* Data Register */
#define SEVSEG_G_DR                     (* (reg8 *) SEVSEG_G__DR)
/* Port Number */
#define SEVSEG_G_PRT_NUM                (* (reg8 *) SEVSEG_G__PRT) 
/* Connect to Analog Globals */                                                  
#define SEVSEG_G_AG                     (* (reg8 *) SEVSEG_G__AG)                       
/* Analog MUX bux enable */
#define SEVSEG_G_AMUX                   (* (reg8 *) SEVSEG_G__AMUX) 
/* Bidirectional Enable */                                                        
#define SEVSEG_G_BIE                    (* (reg8 *) SEVSEG_G__BIE)
/* Bit-mask for Aliased Register Access */
#define SEVSEG_G_BIT_MASK               (* (reg8 *) SEVSEG_G__BIT_MASK)
/* Bypass Enable */
#define SEVSEG_G_BYP                    (* (reg8 *) SEVSEG_G__BYP)
/* Port wide control signals */                                                   
#define SEVSEG_G_CTL                    (* (reg8 *) SEVSEG_G__CTL)
/* Drive Modes */
#define SEVSEG_G_DM0                    (* (reg8 *) SEVSEG_G__DM0) 
#define SEVSEG_G_DM1                    (* (reg8 *) SEVSEG_G__DM1)
#define SEVSEG_G_DM2                    (* (reg8 *) SEVSEG_G__DM2) 
/* Input Buffer Disable Override */
#define SEVSEG_G_INP_DIS                (* (reg8 *) SEVSEG_G__INP_DIS)
/* LCD Common or Segment Drive */
#define SEVSEG_G_LCD_COM_SEG            (* (reg8 *) SEVSEG_G__LCD_COM_SEG)
/* Enable Segment LCD */
#define SEVSEG_G_LCD_EN                 (* (reg8 *) SEVSEG_G__LCD_EN)
/* Slew Rate Control */
#define SEVSEG_G_SLW                    (* (reg8 *) SEVSEG_G__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SEVSEG_G_PRTDSI__CAPS_SEL       (* (reg8 *) SEVSEG_G__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SEVSEG_G_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SEVSEG_G__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SEVSEG_G_PRTDSI__OE_SEL0        (* (reg8 *) SEVSEG_G__PRTDSI__OE_SEL0) 
#define SEVSEG_G_PRTDSI__OE_SEL1        (* (reg8 *) SEVSEG_G__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SEVSEG_G_PRTDSI__OUT_SEL0       (* (reg8 *) SEVSEG_G__PRTDSI__OUT_SEL0) 
#define SEVSEG_G_PRTDSI__OUT_SEL1       (* (reg8 *) SEVSEG_G__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SEVSEG_G_PRTDSI__SYNC_OUT       (* (reg8 *) SEVSEG_G__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SEVSEG_G__SIO_CFG)
    #define SEVSEG_G_SIO_HYST_EN        (* (reg8 *) SEVSEG_G__SIO_HYST_EN)
    #define SEVSEG_G_SIO_REG_HIFREQ     (* (reg8 *) SEVSEG_G__SIO_REG_HIFREQ)
    #define SEVSEG_G_SIO_CFG            (* (reg8 *) SEVSEG_G__SIO_CFG)
    #define SEVSEG_G_SIO_DIFF           (* (reg8 *) SEVSEG_G__SIO_DIFF)
#endif /* (SEVSEG_G__SIO_CFG) */

/* Interrupt Registers */
#if defined(SEVSEG_G__INTSTAT)
    #define SEVSEG_G_INTSTAT            (* (reg8 *) SEVSEG_G__INTSTAT)
    #define SEVSEG_G_SNAP               (* (reg8 *) SEVSEG_G__SNAP)
    
	#define SEVSEG_G_0_INTTYPE_REG 		(* (reg8 *) SEVSEG_G__0__INTTYPE)
#endif /* (SEVSEG_G__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SEVSEG_G_H */


/* [] END OF FILE */
