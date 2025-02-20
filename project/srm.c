// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
* @file srm.c
*
* @brief This is the main entry to the application.
*
* Component: APPLICATION
*
*/
// </editor-fold>
 
// <editor-fold defaultstate="collapsed" desc="Disclaimer ">
 
/*******************************************************************************
* SOFTWARE LICENSE AGREEMENT
* 
* © [2024] Microchip Technology Inc. and its subsidiaries
* 
* Subject to your compliance with these terms, you may use this Microchip 
* software and any derivatives exclusively with Microchip products. 
* You are responsible for complying with third party license terms applicable to
* your use of third party software (including open source software) that may 
* accompany this Microchip software.
* 
* Redistribution of this Microchip software in source or binary form is allowed 
* and must include the above terms of use and the following disclaimer with the
* distribution and accompanying materials.
* 
* SOFTWARE IS "AS IS." NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,
* MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL 
* MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR 
* CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO
* THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE 
* POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY
* LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL
* NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR THIS
* SOFTWARE
*
* You agree that you are solely responsible for testing the code and
* determining its suitability.  Microchip has no obligation to modify, test,
* certify, or support the code.
*
*******************************************************************************/
// </editor-fold>
 
// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">

#include <stdint.h>
#include <stdbool.h>

#include <xc.h>

#include "board_service.h"
#include "diagnostics.h"
#include "mc1_service.h"
 
// </editor-fold>
 
// <editor-fold defaultstate="collapsed" desc=" Global Variables ">

uint32_t runCmdMC1,dirCmdMC1,targetVelocityMC1;

uint32_t heartBeatCount = 0;

// </editor-fold>

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">

/**
* <B> Function: int main (void)  </B>
*
* @brief main() function,entry point of the application.
*
*/
int main(void) 
{
    InitOscillator();       
    SetupGPIOPorts();
    
#ifdef ENABLE_DIAGNOSTICS
    /* Initialize Diagnostics */
    DiagnosticsInit();
#endif
    
	/* Initialize Board Service */
    BoardServiceInit();
	
    /* Initialize Peripherals */
    HAL_InitPeripherals();
    
    MCAPP_MC1ServiceInit();
    
    /* LED1 is turned on here, and toggled in Timer1 Interrupt */
    LED1 = 1; 
    
    HAL_ResetPeripherals();
    runCmdMC1  = 0;
    dirCmdMC1 = 0;
    
    while(1)
    {
        
#ifdef ENABLE_DIAGNOSTICS
        DiagnosticsStepMain();
#endif
        BoardService();
        
        if (IsPressed_Button1())
        {
            if(runCmdMC1 == 1)
            {
               runCmdMC1 = 0;  
            }
            else
            {
               runCmdMC1 = 1; 
            }   
        }
        if(IsPressed_Button2())
        {
            if(dirCmdMC1 == 0)
            {
                dirCmdMC1 = 1;
            }
            else
            {
                dirCmdMC1 = 0;
            }
        }
        /* LED2 is used as motor run Status */
        LED2 = runCmdMC1;
        
    } 
}

/**
* <B> Function: _T1Interrupt()     </B>
*
* @brief Function to handle Timer1 Interrupt. Timer1 is configured for 1 ms.
* LED1 is toggled at a rate of 2500 us as a Heartbeat LED.
*        
* @param none.
* @return none.
* 
* @example
* <CODE> _T1Interrupt();        </CODE>
*
*/
void __attribute__((__interrupt__, no_auto_psv))_T1Interrupt(void)
{
    if (heartBeatCount < HEART_BEAT_LED_COUNT)
    {
        heartBeatCount += 1;
    }
    else
    {
        heartBeatCount = 0;
        if(LED1 == 1)
        {
            LED1 = 0;
        }
        else
        {
            LED1 = 1;
        }
    }
    targetVelocityMC1 = MCAPP_MC1GetTargetVelocity();
    MCAPP_MC1InputBufferSet(runCmdMC1,dirCmdMC1, targetVelocityMC1);
    BoardServiceStepIsr(); 
    TIMER1_InterruptFlagClear();
}
// </editor-fold>

