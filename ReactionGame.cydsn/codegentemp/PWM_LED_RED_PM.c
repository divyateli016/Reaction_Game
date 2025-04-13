/*******************************************************************************
* File Name: PWM_LED_RED_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_LED_RED.h"

static PWM_LED_RED_backupStruct PWM_LED_RED_backup;


/*******************************************************************************
* Function Name: PWM_LED_RED_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_LED_RED_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_LED_RED_SaveConfig(void) 
{

    #if(!PWM_LED_RED_UsingFixedFunction)
        #if(!PWM_LED_RED_PWMModeIsCenterAligned)
            PWM_LED_RED_backup.PWMPeriod = PWM_LED_RED_ReadPeriod();
        #endif /* (!PWM_LED_RED_PWMModeIsCenterAligned) */
        PWM_LED_RED_backup.PWMUdb = PWM_LED_RED_ReadCounter();
        #if (PWM_LED_RED_UseStatus)
            PWM_LED_RED_backup.InterruptMaskValue = PWM_LED_RED_STATUS_MASK;
        #endif /* (PWM_LED_RED_UseStatus) */

        #if(PWM_LED_RED_DeadBandMode == PWM_LED_RED__B_PWM__DBM_256_CLOCKS || \
            PWM_LED_RED_DeadBandMode == PWM_LED_RED__B_PWM__DBM_2_4_CLOCKS)
            PWM_LED_RED_backup.PWMdeadBandValue = PWM_LED_RED_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_LED_RED_KillModeMinTime)
             PWM_LED_RED_backup.PWMKillCounterPeriod = PWM_LED_RED_ReadKillTime();
        #endif /* (PWM_LED_RED_KillModeMinTime) */

        #if(PWM_LED_RED_UseControl)
            PWM_LED_RED_backup.PWMControlRegister = PWM_LED_RED_ReadControlRegister();
        #endif /* (PWM_LED_RED_UseControl) */
    #endif  /* (!PWM_LED_RED_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_LED_RED_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_LED_RED_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_LED_RED_RestoreConfig(void) 
{
        #if(!PWM_LED_RED_UsingFixedFunction)
            #if(!PWM_LED_RED_PWMModeIsCenterAligned)
                PWM_LED_RED_WritePeriod(PWM_LED_RED_backup.PWMPeriod);
            #endif /* (!PWM_LED_RED_PWMModeIsCenterAligned) */

            PWM_LED_RED_WriteCounter(PWM_LED_RED_backup.PWMUdb);

            #if (PWM_LED_RED_UseStatus)
                PWM_LED_RED_STATUS_MASK = PWM_LED_RED_backup.InterruptMaskValue;
            #endif /* (PWM_LED_RED_UseStatus) */

            #if(PWM_LED_RED_DeadBandMode == PWM_LED_RED__B_PWM__DBM_256_CLOCKS || \
                PWM_LED_RED_DeadBandMode == PWM_LED_RED__B_PWM__DBM_2_4_CLOCKS)
                PWM_LED_RED_WriteDeadTime(PWM_LED_RED_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_LED_RED_KillModeMinTime)
                PWM_LED_RED_WriteKillTime(PWM_LED_RED_backup.PWMKillCounterPeriod);
            #endif /* (PWM_LED_RED_KillModeMinTime) */

            #if(PWM_LED_RED_UseControl)
                PWM_LED_RED_WriteControlRegister(PWM_LED_RED_backup.PWMControlRegister);
            #endif /* (PWM_LED_RED_UseControl) */
        #endif  /* (!PWM_LED_RED_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_LED_RED_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_LED_RED_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_LED_RED_Sleep(void) 
{
    #if(PWM_LED_RED_UseControl)
        if(PWM_LED_RED_CTRL_ENABLE == (PWM_LED_RED_CONTROL & PWM_LED_RED_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_LED_RED_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_LED_RED_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_LED_RED_UseControl) */

    /* Stop component */
    PWM_LED_RED_Stop();

    /* Save registers configuration */
    PWM_LED_RED_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_LED_RED_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_LED_RED_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_LED_RED_Wakeup(void) 
{
     /* Restore registers values */
    PWM_LED_RED_RestoreConfig();

    if(PWM_LED_RED_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_LED_RED_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
