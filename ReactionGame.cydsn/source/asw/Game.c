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

#include "project.h"
#include "global.h"
#include "button.h"
#include "seven.h"
#include "CyLib.h"
#include "stdlib.h"
#include "string.h"
#include "Game.h"
#include "time.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/
enum eGAME_STATE
{
  GAME_ISIDLE,                /**< Game is in idle state >*/
  GAME_ISWAITFORRANDOMDELAY,  /**< wait for random amount of time after idle state> */
  GAME_ISWAITFORBUTTONPRESS, /* <wait for player to react with button press>*/

} ;
typedef enum eGAME_STATE GAME_STATE_t;
/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/
char strMsg[32];
static GAME_STATE_t GAME_STATE = GAME_ISIDLE;
static uint8_t gameround = 1;
uint16_t displayNumber = 0;


/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/
/**
Function prototype for random number generation for delay function
**/
RC_t GAME_generate_randomDelay(void);

/**
 Function prototype to desplay the number on seven segment display 1 or 2 randomly
**/
RC_t GAME_DisplayRandomNumber(void);

RC_t Calculate_Score(uint32_t);

/**
when the random numbers are displayes on seven segment display this function checks if the corresponding button is pressed or not
*\return boolean_t returns true if the currect button is pressed and returns false if wrong button is pressed
**/
boolean_t Check_CorrectButton(void);
/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
/**
 * @brief Starts the game and handles the specified event.
 *
 * This function initializes or continues the game logic based on the 
 * provided event. It manages game states, processes inputs, and 
 * triggers the necessary actions based on the event.
 *
 * @param ev The event that triggers the game logic. This is of type 
 *           `GAME_EVENTS_t` and represents various game-related events.
 *          
 *
 * param @return An `RC_t` value indicating the status of the operation:
 *         - `RC_SUCCESS` if the game started successfully.
 *         - `RC_FAILURE` if there was an error or the event was invalid.
 *         - Other return codes as defined in `RC_t` to signify specific 
 *           conditions or errors.
 */

RC_t GAME_Start(GAME_EVENTS_t ev)
{
    static uint32_t Starttime =0;
    static uint32_t Endtime = 0;
    uint32_t Reaction_Time = 0;
    static uint32_t totalReactiontime = 0;
    static uint16_t score = 0;
    switch(GAME_STATE)
    {
        case GAME_ISIDLE:
        {
        if(ev == buttonpress)
        {
            GAME_generate_randomDelay();
            GAME_STATE = GAME_ISWAITFORRANDOMDELAY;
            sprintf(strMsg,"Game round : %u\n",gameround);
            UART_1_PutString(strMsg);
        }
        break;
        }
        case GAME_ISWAITFORRANDOMDELAY:
        {
            if(ev == random_wait)
            {
                //Check if the random delay is completed 
                CancelAlarm(alarm_randomwait);
                GAME_DisplayRandomNumber();
               GAME_STATE = GAME_ISWAITFORBUTTONPRESS;
                 Starttime = timer;
                
                //Check if timeoout happened using alarm
                SetRelAlarm(alarm_1sectimeout,1000,0);
            }
            break;
        }
        case GAME_ISWAITFORBUTTONPRESS:
        {
            if(ev == buttonpress)
            {
                if(Check_CorrectButton())
                {
                    Endtime = timer;
                    UART_1_PutString("Correct Button is Pressed\n");
                    Reaction_Time = Endtime-Starttime;
                    sprintf(strMsg,"Reaction Time is : %u\n",Reaction_Time);
                    UART_1_PutString(strMsg);
                    totalReactiontime +=Reaction_Time;
                    score++;
                }
                else
                {
                    UART_1_PutString("Wrong Button is Pressed\n");
                    //Calculate_Score(0);
                }
            }
            else if(ev == wait_1sec)
            {
                UART_1_PutString("Too slow!\n\n");
                //Calculate_Score(0);
            }
            GAME_STATE = GAME_ISIDLE;
            gameround++;
            SEVEN_SEGClear(SEVEN_DSIPLAY_0);
            SEVEN_SEGClear(SEVEN_DISPLAY_1);
            CancelAlarm(alarm_1sectimeout);
            if(gameround<GAME_ROUNDS)
            UART_1_PutString("Please press any button to start the game\n");
            else if(gameround>GAME_ROUNDS)
            {
                sprintf(strMsg,"Total Reaction Time is: %u\n",totalReactiontime);
                UART_1_PutString(strMsg);
                sprintf(strMsg,"Total Score is : %u\n",score);
                UART_1_PutString(strMsg);
                sprintf(strMsg,"Average reaction Time is : %u\n",totalReactiontime/GAME_ROUNDS);
                UART_1_PutString(strMsg);
            }
            break;
            
        } 
    
   
    }
    return RC_SUCCESS;
}

/**
Function prototype for random number generation for delay function
**/

RC_t GAME_generate_randomDelay()
{
    char strMsg[30];
    uint32_t randomNumber = rand();
    uint32_t Randomdelay = ((randomNumber%3)+1)*1000;//Generates the delay in milisecond
    SetRelAlarm(alarm_randomwait,Randomdelay,0);
    //sprintf(strMsg,"Random delay is %u \n",Randomdelay);
    //UART_1_PutString(strMsg);
    return RC_SUCCESS;
}

/**
 Function prototype to desplay the number on seven segment display 1 or 2 randomly
**/

RC_t GAME_DisplayRandomNumber()
{
    uint16_t RandomNumber = rand();
    displayNumber = RandomNumber%2+1;
    
    //Function call to display numbers on seven seg display
    SEVEN_SEGWRITE(SEVEN_DSIPLAY_0,displayNumber);
    SEVEN_SEGWRITE(SEVEN_DISPLAY_1,displayNumber);
    
    return RC_SUCCESS;
}

boolean_t Check_CorrectButton()
{
    if(BUTTON_IsPressed(BUTTON_1) && displayNumber == 2)
    {
        return TRUE;
    }
    else if(BUTTON_IsPressed(BUTTON_2) && displayNumber ==1)
    {
        return TRUE;
    }
    else
    return FALSE;
}

RC_t Calculate_Score(uint32_t ReactionTime)
{
    static uint32_t TotalreactionTime = 0;
    static uint32_t AverageReactionTime = 0;
    static uint8_t score = 0;
    
    //Calculate the reaction time and add for correctly pressed buttons 
    if(Check_CorrectButton())
    {
        TotalreactionTime = TotalreactionTime + ReactionTime;
        score++;
        sprintf(strMsg," reaction Time is : %u",ReactionTime);
        UART_1_PutString(strMsg);
        
    }
    if(gameround>GAME_ROUNDS)
    {
        sprintf(strMsg,"Total Score is : %u",score);
        UART_1_PutString(strMsg);
        UART_1_PutString("\n\n");
        
        sprintf(strMsg,"Total reaction time is : %u \n",TotalreactionTime);
        UART_1_PutString(strMsg);
        UART_1_PutString("\n\n");
        
        AverageReactionTime = TotalreactionTime/10;
        
        sprintf(strMsg,"Average Reaction Time is %u :",AverageReactionTime);
        UART_1_PutString(strMsg);
        UART_1_PutString("\n\n");
        
    }
    return RC_SUCCESS;
}

/**
function to tract the number of rounds and returns the integer number 
**/

uint8_t Game_Rounds()
{
    return gameround;
}
/**
 * <Description>
 * \param <first para>
 * \return <return value>
 */
//RC_t FILE_function(type para)
