/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "global.h"
#include "derivate.h"
#include "button.h"
#include "Game.h"
#include "CyLib.h"
#include "stdlib.h"
#include "seven.h"
#include "Fader.h"
#include "Glower.h"

volatile uint32_t timer=0;
uint8_t DisplyedValue;//used to read the values from Display

ISR(systick_handler)
{
    CounterTick(cnt_systick);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    srand((uint32_t)CySysTickGetValue());
    EE_systick_set_period(MILLISECONDS_TO_TICKS(1,BCLK__BUS_CLK__HZ));
    EE_systick_enable_int();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
   
    
    
    

    for(;;)
    {
        /* Place your application code here. */
       
         StartOS(OSDEFAULTAPPMODE);
       
    }
}
/*
void unhandledException() 
{ 
    //Ooops, something terrible happened.... 
    //check the call stack to see how we got here... 
    __asm("bkpt"); 
}
*/

TASK(tsk_init)
{
    LED_Init();
    SEVEN_Init();
    UART_1_Start();

    EE_system_init();
    EE_systick_start();
    
    
    srand(CySysTickGetValue());
    UART_1_PutString("Reaction Game Press any button to continue\r\n");
   SetRelAlarm(alarm_timer,1,1);//timer task is tested with this alarm to check timer is incrementing or not
   SetRelAlarm(alarm_fader,2,2);
    SetRelAlarm(alarm_glower,10,10);


/*     
    SEVEN_SEGWRITE(SEVEN_DSIPLAY_0,0);
     SEVEN_SEGREAD(SEVEN_DSIPLAY_0,&DisplyedValue);
     SEVEN_SEGWRITE(SEVEN_DISPLAY_1,1);
    SEVEN_SEGREAD(SEVEN_DISPLAY_1,&DisplyedValue);
  */ 
     //Task Activation 
    ActivateTask(tsk_Game);
     TerminateTask();
}

TASK(tsk_Game)
{
    //Variable to handle the multiple events masks
   EventMaskType ev; 
    while(Game_Rounds()<=GAME_ROUNDS)
    {
        WaitEvent(ev_button | ev_waitrandom | ev_wait1s);
        GetEvent(tsk_Game,&ev);
        ClearEvent(ev);
        
        //Start the Game state Machine 
        GAME_Start(ev);
        
    }
    TerminateTask();
}

TASK(tsk_timer)
{
    timer++;
    //UART_1_PutString("Timer is incremented ");
    //generate_randomDelay(); 
    //SEVENSEG_READ();
    TerminateTask();
}
TASK(tsk_fader)
{
    LED_FADER();
    TerminateTask();
}

TASK(tsk_glower)
{
    RGB_GLOW_t();
    TerminateTask();
}

/**TASK(tsk_arcadian)
{
    static uint32_t tickTime = 0; 
    
    LED_FADER(tickTime);
    RGB_GLOW_t(tickTime);
    
    tickTime += 1;
    
    TerminateTask();
}*/


ISR2(isr_Button)
{
    if(BUTTON_IsPressed(BUTTON_1) || BUTTON_IsPressed(BUTTON_2))
    
    /*Led is used to check the functionality of Interrupt**/
    //Pin_ledred_Write(~Pin_ledred_Read());
    SetEvent((tsk_Game),ev_button);
    
}

TASK(tsk_background)
{
    while(1)
    {
        //do something with low prioroty
        __asm("nop");
    }
}

/* [] END OF FILE */
