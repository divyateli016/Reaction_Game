/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
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

#include "Glower.h"
#include "project.h"
#include "led.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/
//Red Green Blue TimeInMS 

const Glower_t RG_glowtable_1[] = {
    {255, 0,   0,   500},  // 500ms red
    {0,   255, 0,   500},  // 500ms green
    {0,   0,   255, 500},  // 500ms blue
    {0,   0,   0,   100},  // 100ms off
    {255, 255, 255, 100},  // 100ms white
    {0,   0,   0,   100},  // 100ms off
    {255, 255, 255, 100},  // 100ms white
    {255, 0,   255, 100}   // 100ms magenta
};
/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
/**
RC_t RG_GLOW_t()
{
   uint8_t index=0;
    while(1)
    {
        Pin_RGB_RED_Write(RG_glowtable_1[index].red);
        Pin_RGB_GREEN_Write(RG_glowtable_1[index].green);
        Pin_RGB_BLUE_Write(RG_glowtable_1[index].blue);
        CyDelay(RG_glowtable_1[index].TimeInMS);
        
        index++;
        if(index>sizeof(RG_glowtable_1)/sizeof(Glower_t))
        index = 0;
    }
    return RC_SUCCESS;
        
}
**/
/**
 * <RGB_Glower is the function which defines the colour of RGB LED with pre defined values declared as gloabl variables>
 * \return <return RC_SUCCESS after successful execution of the program>
 */
//RC_t FILE_function(type para)
RC_t RGB_GLOW_t()
{
  static uint8_t index=0;
    //while(1)
    {
        Pin_RGB_RED_Write(RG_glowtable_1[index].red);
        Pin_RGB_GREEN_Write(RG_glowtable_1[index].green);
        Pin_RGB_BLUE_Write(RG_glowtable_1[index].blue);
        //CyDelay(RG_glowtable_1[index].TimeInMS);
        SetRelAlarm(alarm_glower,RG_glowtable_1[index].TimeInMS,0);
        
        index++;
        if(index>=8)
        index = 0;
    }
    return RC_SUCCESS;
        
}
