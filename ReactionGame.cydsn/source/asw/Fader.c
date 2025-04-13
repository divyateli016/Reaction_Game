#include "project.h"
#include "led.h"
#include "global.h"

/**
*enum for LED_FADER_STATE for all LEDs which will excute sequentially to control the patern
**/
typedef enum {
    LED_FADER_STATE_RED,
    LED_FADER_STATE_YELLOW,
    LED_FADER_STATE_GREEN,
    LED_FADER_STATE_DONE
} LED_FADER_State_t;

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/
static LED_FADER_State_t faderState = LED_FADER_STATE_RED;
static uint8_t redBrightness = 0;
static uint8_t yellowBrightness = 0;
static uint8_t greenBrightness = 0;


///*****************************************************************************/
///* Function implementation - global ('extern') and local ('static')          */
///*****************************************************************************/
/**
Function definition for fader implementation.
**/

RC_t LED_FADER()
{
    switch (faderState)
    {
        case LED_FADER_STATE_RED:
            PWM_LED_RED_WriteCompare(redBrightness++);
            if (redBrightness >= 255)
            {
                faderState = LED_FADER_STATE_YELLOW;
                yellowBrightness = 0;
            }
            break;

        case LED_FADER_STATE_YELLOW:
            PWM_LED_YELLOW_WriteCompare(yellowBrightness++);
            PWM_LED_RED_WriteCompare(--redBrightness);
            if (yellowBrightness >= 255)
            {
                faderState = LED_FADER_STATE_GREEN;
                greenBrightness = 0;
            }
            break;

        case LED_FADER_STATE_GREEN:
            PWM_LED_GREEN_WriteCompare(greenBrightness++);
            PWM_LED_YELLOW_WriteCompare(--yellowBrightness);
            PWM_LED_RED_WriteCompare(--redBrightness);
            if (greenBrightness >= 255)
            {
                faderState = LED_FADER_STATE_DONE;
            }
            break;

        case LED_FADER_STATE_DONE:
            // Sequence completed; optionally restart
            faderState = LED_FADER_STATE_RED;
            redBrightness = 0;
            break;
    }

    return RC_SUCCESS;
}