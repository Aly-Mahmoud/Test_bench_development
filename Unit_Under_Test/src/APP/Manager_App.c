/**
 * @file App.c
 * @author your name (you@domain.com)
 * @brief implementation of initialization functions
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/

/*--------------------------------Includes----------------------------*/
    #include "Std_Types.h"
    #include "HAL/LCD/HAL_LCD.h"
    #include "HAL/SWITCH/HAL_SWITCH.h"
    #include "APP/Manager.h"
    #include "HAL/LED/LED.h"
    #include "MCAL/USART/STM32F401cc_MCAL_USART.h"
    #include "SERVICE/COMM/UART_COMM.h"
/*---------------------------------------------------------------------*/


/*-----------------------------Stop Watch modes------------------------*/
  
/*---------------------------------------------------------------------*/

/*----------------------------Global Variables-----------------------*/
    /**
     * @brief Mode: carry the Mode of operation (Clock-Date or Stop-Watch)
     * @brief Operation_type: carry the type of running operation (check for the enumeration in Manager.h)
     * @brief StopWatch_Status: carry the status of stop Watch STOP_WATCH_STOP or STOP_WATCH_START
     */
    u32 Operation_type=0;

/*--------------------------------------------------------------------*/

/*----------------------------STATIC FUNCTION-------------------------*/


/*--------------------------------------------------------------------*/

/**
 * @brief Manager runnable that check for the system mode and its operation states
 * @note operation state must start at Init_Operation then move to Idle Operation then any state can come
 * in order to prevent any undefined behaviour since before Idle_Operation the digits not all printed yet
 */


/*-------------------------leap Year Handling------------------------*/
    


/*---------------------------------------------Modes Handlers-----------------------------------------------------*/



/*---------------------------------------------Runnables-----------------------------------------------------*/


/*-------------------------------Control Switch Runnable-----------------------------*/
    void ControlSwitches_Runnable(void)
    { 
    /*Setting Switch Data To be sent*/
        static Ctrl_Switches_Data_t Ctrl_Switches_Data [1] = 
        {
            [SWITCH_ONE]=
            {
                .DATA = 1,
                .Switch_Status = Switch_Released,
                .Switch_PrevStatus = Switch_Released
            }
        };
    /*------------------------------*/

        /*SWITCH Reading and Sending Data*/
        U8 Switches_Iter=0;

        for (Switches_Iter = 0 ;Switches_Iter < Number_Of_Switches ; Switches_Iter++)
        {
            /*Read Switch State*/
                HAL_SWITCH_enuGetSwitchState( Switches_Iter ,&Ctrl_Switches_Data[Switches_Iter].Switch_Status );
            /*---------------------*/ 

            /*Single Realise Press signal handling and sending data via uart*/
                if(Ctrl_Switches_Data[Switches_Iter].Switch_Status == Switch_Pressed)
                {
                    LED_SetStatus(TEST_LED,LED_SET_ON);
                }
                else
                {
                    LED_SetStatus(TEST_LED,LED_SET_OFF);

                }
        }

    }

