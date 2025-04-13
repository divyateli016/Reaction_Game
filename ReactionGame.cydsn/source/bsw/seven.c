/**
* \file seven.c
* \author P. Fromm
* \date 28.8.17
*
* \brief Driver for 7 segment displays
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "project.h"
#include "seven.h"
#include "string.h"



/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

#define SEVEN__A  0b00000001
#define SEVEN__B  0b00000010
#define SEVEN__C  0b00000100
#define SEVEN__D  0b00001000
#define SEVEN__E  0b00010000
#define SEVEN__F  0b00100000
#define SEVEN__G  0b01000000
#define SEVEN__DP 0b10000000


/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/
char buffer[32];
//    ABCDEFG
const static uint8_t SEVEN_DecimalValues[] = 
{
    63,     //0
     6,     //1
    91,     //2
    79,     //3
    102,     //4
    109,     //5
    125,     //6
    7,       //7
    127,     //8
    103,     //9
    128      //decimal point
};
    
//We need to store the last latch value per display
//-1 means empty
static sint8_t SEVEN__latch_value[2] = {-1,-1};
static uint8_t SEVEN__latch_pattern[2] = {0,0};

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/



/**
 * Initilasation of the seven segment display
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_Init()
{
    
    SEVEN_SEGClear(SEVEN_DSIPLAY_0);
    SEVEN_SEGClear(SEVEN_DISPLAY_1);
    
    return RC_SUCCESS;
}


/**
 * Sets value for one display
 * @param SEVEN_id_t sevenId - identifier for the segment to be set
 * @param uint8_t value - value to be set, valid range 0...15
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_SEGWRITE(SEVEN_id_t sevenId, uint8_t value)
{
    if (value > 0x0F)
    {
        return RC_ERROR_BAD_PARAM;
    }
    
    //Set the selection bit for the display
    Pin_SEVENSEL_Write((uint8_t)sevenId);
    
    //Set the bitpattern
    //As we do not have a single port, we have to do it bit by bit
    //Store the current pattern in the software latch (needed for the DP function)
    

    
    uint8_t Display = SEVEN_DecimalValues[value];
    
    SEVEN__latch_value[(uint8_t)sevenId] = value;
    SEVEN__latch_pattern[(uint8_t)sevenId] = Display;
    
    SEVENSEG_REG_Write(Display);
    return RC_SUCCESS;
    
}

/**
 * Get value for one display
 * @param SEVEN_id_t sevenId - identifier for the segment to be set
 * @param uint8_t value - current value, valid range 0...15
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
*/

RC_t SEVEN_SEGREAD(SEVEN_id_t sevenId, sint8_t* value)
{
    *value = SEVEN__latch_pattern[(uint8_t)sevenId];
    sprintf(buffer,"Dsiplay Values is %u\n",*value);
    UART_1_PutString(buffer);
    return RC_SUCCESS;
}

/*
RC_t SEVENSEG_READ()
{
    uint16_t Display1Val;
    uint16_t Display2Val;
    
    //Selecting Dsipaly to be read first and reading the control register
    Pin_SEVENSEL_Write(SEVEN_DSIPLAY_0);
   
        Display1Val = SEVENSEG_REG_Read();
        sprintf(buffer,"Dsiplay 1 value is %u\n",Display1Val);
        UART_1_PutString(buffer);
    
         Pin_SEVENSEL_Write(SEVEN_DISPLAY_1);
        Display2Val = SEVENSEG_REG_Read();
        sprintf(buffer,"Dsiplay 2 value is %u\n",Display2Val);
        UART_1_PutString(buffer);
    
}
*/


/**
 * Sets both displays
 * @param uint8_t value - value to be set, valid range 0...255
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_SetHex(uint8_t value)
{
    SEVEN_SEGWRITE(SEVEN_DISPLAY_1, value / 16);
    SEVEN_SEGWRITE(SEVEN_DSIPLAY_0, value % 16);
    
    return RC_SUCCESS;
}

/**
 * Sets decimal point for one display
 * @param SEVEN_id_t sevenId - identifier for the segment to be set
 * @param uint8_t value - value to be set, valid range 0 (OFF)...1(ON)
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_SetDP(SEVEN_id_t sevenId, uint8_t value)
{
    
    if (value > 1)
    {
        return RC_ERROR_BAD_PARAM;
    }
    
    //Restore the last display pattern
    uint8_t pattern = 0;
    if (SEVEN__latch_value[(uint8_t)sevenId] != -1)
    {
        pattern = SEVEN__latch_pattern[(uint8_t)sevenId];
    }
    
    //Set the selection bit for the display
    Pin_SEVENSEL_Write((uint8_t)sevenId);
    
    //Set the port to the pattern currently active
    SEVENSEG_REG_Write(pattern);
    
    //Set the decimal point
    SEVSEG_DP_Write(value);

    return RC_SUCCESS;
}

/**
 * Clears one display
 * @param SEVEN_id_t sevenId - identifier for the segment to be set
 * @return RC_SUCCESS if function was executed correctly, other value in case of error
 */
RC_t SEVEN_SEGClear(SEVEN_id_t sevenId)
{
    
    
    //Set the selection bit for the display
    Pin_SEVENSEL_Write(sevenId);
    
    //Clear every bit
    SEVENSEG_REG_Write(0);
    
    return RC_SUCCESS;
}
