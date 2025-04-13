/*******************************************************************************
* File Name: SEVENSEG_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "SEVENSEG.h"

/* Check for removal by optimization */
#if !defined(SEVENSEG_Sync_ctrl_reg__REMOVED)

static SEVENSEG_BACKUP_STRUCT  SEVENSEG_backup = {0u};

    
/*******************************************************************************
* Function Name: SEVENSEG_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SEVENSEG_SaveConfig(void) 
{
    SEVENSEG_backup.controlState = SEVENSEG_Control;
}


/*******************************************************************************
* Function Name: SEVENSEG_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void SEVENSEG_RestoreConfig(void) 
{
     SEVENSEG_Control = SEVENSEG_backup.controlState;
}


/*******************************************************************************
* Function Name: SEVENSEG_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SEVENSEG_Sleep(void) 
{
    SEVENSEG_SaveConfig();
}


/*******************************************************************************
* Function Name: SEVENSEG_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SEVENSEG_Wakeup(void)  
{
    SEVENSEG_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
