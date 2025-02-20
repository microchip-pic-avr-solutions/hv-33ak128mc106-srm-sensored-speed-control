// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file mc1_service.c
 *
 * @brief This module implements motor control.
 *
 * Component: MOTOR CONTROL APPLICATION
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

#include <libq.h>

#include "board_service.h"
#include "diagnostics.h"
#include "mc1_init.h"
#include "mc_app_types.h"
#include "mc1_service.h"

// </editor-fold>

// <editor-fold defaultstate="expanded" desc="VARIABLES ">

MC1APP_DATA_T mc1;
MC1APP_DATA_T *pMC1Data = &mc1;

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="STATIC FUNCTIONS ">
extern void MCAPP_FaultDetect(MCAPP_FAULT_DETECT_T *, MCAPP_MEASURE_T *);
static void MC1APP_StateMachine(MC1APP_DATA_T *);
static void MCAPP_MC1ReceivedDataProcess(MC1APP_DATA_T *);
// </editor-fold>

/**
* <B> Function: _PWMInterrupt()     </B>
*
* @brief Function to handle PWM Fault Interrupt from PCI
*        
* @param none.
* @return none.
* 
* @example
* <CODE> _PWMInterrupt();        </CODE>
*
*/
void __attribute__((__interrupt__,no_auto_psv)) _PWMInterrupt()
{
    LED2 = 0;
    pMC1Data->HAL_PWMDisableOutputs();
    HAL_ResetPeripherals();
    if( MC1_OV_OC_FAULT == 1)
    {
        pMC1Data->pfaultDetect->faultStatus = MC1_OV_OC_FAULT_DETECT;
    }
    if( MC1_CS_OC_FAULT == 1)
    {
        pMC1Data->pfaultDetect->faultStatus = MC1_OVERCURRENT_FAULT_DETECT;
    }
    ClearPWMPCIFault();
    ClearPWMIF(); 
}

/**
* <B> Function: void MC1APP_StateMachine (MC1APP_DATA_T *)  </B>
*
* @brief Application state machine.
*
* @param Pointer to the data structure containing Application parameters.
* @return none.
* @example
* <CODE> MC1APP_StateMachine(&pMCData); </CODE>
*
*/
static void MC1APP_StateMachine(MC1APP_DATA_T *pMCData)
{
    MCAPP_MEASURE_T *pMotorInputs = pMCData->pMotorInputs;
    MCAPP_CONTROL_SCHEME_T *pControlScheme = pMCData->pControlScheme;
    MCAPP_FAULT_DETECT_T *pfaultDetect = pMCData->pfaultDetect;;
    
    switch(pMCData->appState)
    {
    case MCAPP_INIT:
        
        pMCData->HAL_PWMDisableOutputs();

        /* Stop the motor */
        pMCData->runCmd = 0;
        
        pMCData->MCAPP_ControlSchemeInit(pControlScheme);
        pMCData->MCAPP_InputsInit(pMotorInputs);
        pMCData->MCAPP_PositionSensorInit(&pMotorInputs->detectRotorPosition);
        
        pMCData->appState = MCAPP_CMD_WAIT;

        break;
        
    case MCAPP_CMD_WAIT:
        if(pMCData->runCmd == 1)
        {
            pMCData->appState = MCAPP_OFFSET;
        }
       break;
       
    case MCAPP_OFFSET:

        /* Measure Initial Offsets */
        pMCData->MCAPP_MeasureOffset(pMotorInputs);

        if(pMCData->MCAPP_IsOffsetMeasurementComplete(pMotorInputs))
        {
            pMCData->appState = MCAPP_RUN;
        }

        break;
            
    case MCAPP_RUN:
        
        /* Compensate motor current offsets */
        pMCData->MCAPP_GetProcessedInputs(pMotorInputs);
        
        pMCData->MCAPP_PositionSensorRead(&pMotorInputs->detectRotorPosition);
        
        pMCData->MCAPP_ControlStateMachine(pControlScheme);
        
        /* Check for Phase currents faults */
        MCAPP_FaultDetect(pfaultDetect,pMotorInputs);
        
        /* Check for control scheme faults */
        if(pControlScheme->faultStatus == 1) 
        {
            pMCData->appState = MCAPP_FAULT;
            break;
        }
        
        if (pMCData->runCmd == 0)
        {
            /* Exit loop if motor not run */
            pMCData->appState = MCAPP_STOP;
        }
        break;

    case MCAPP_STOP:
        pMCData->HAL_PWMDisableOutputs();
        pMCData->appState = MCAPP_INIT;
        
        break;
        
    case MCAPP_FAULT:
        pMCData->HAL_PWMDisableOutputs();
        break;
        
    default:
        pMCData->HAL_PWMDisableOutputs();
        break;     

    } /* end of switch-case */

    /* Fault Handler */
    if(pfaultDetect->faultStatus > 0)
    {
        pMCData->HAL_PWMDisableOutputs();
        pMCData->appState = MCAPP_FAULT;
    }
}

/**
* <B> Function: MC1_ADC_INTERRUPT()  </B>
*
* @brief ADC interrupt vector ,and it performs following actions:
*        (1) Reads DC BUS voltage and updates appropriate variables.
*        (2) Reads motor 1 phase currents,bus current and phase voltage
*            feedbacks from ADC data buffers.
*        (3) Executes SRM Control based on the rotor position and current feedbacks.
*        (4) Software Over current faults are detected and handled. 
*/
void __attribute__((__interrupt__, no_auto_psv))MC1_ADC_INTERRUPT(void)
{   
    pMC1Data->HAL_MotorInputsRead(pMC1Data->pMotorInputs);
    
    MC1APP_StateMachine(pMC1Data);
    
    #ifdef ENABLE_DIAGNOSTICS
        DiagnosticsStepIsr();
    #endif

    MC1_ClearADCIF_ReadADCBUF();
    MC1_ClearADCIF();
}

void MCAPP_MC1ServiceInit(void)
{
    MCAPP_MC1ParamsInit(pMC1Data);
}

void MCAPP_MC1InputBufferSet(uint32_t runCmd,uint32_t chgDirCmd, float potentiometerInput)
{
    MC1APP_DATA_T   *pMCData = pMC1Data;
    
    pMCData->runCmdBuffer = runCmd;
    
    pMCData->dirCmdBuffer = chgDirCmd;
    
    pMCData->potInput = potentiometerInput;
    
    MCAPP_MC1ReceivedDataProcess(pMCData);
}

float MCAPP_MC1GetTargetVelocity(void)
{
    float potValueNormalized;
    
    if(pMC1Data->motorInputs.potValue > POT_SATURATION_COUNTS)
    {
        pMC1Data->motorInputs.potValue = POT_SATURATION_COUNTS;
    }
     
    potValueNormalized   = (float)(pMC1Data->motorInputs.potValue * POT_SCALE_FACTOR);
    
    return potValueNormalized;
}

static void MCAPP_MC1ReceivedDataProcess(MC1APP_DATA_T *pMCData)
{

    MCAPP_CONTROL_SCHEME_T *pControlScheme = pMCData->pControlScheme;
    MCAPP_MEASURE_T *pMotorInputs = pMCData->pMotorInputs;
    
    if(pMCData->runCmd == 1)
    {
        pControlScheme->ctrlParam.controlInput = pMCData->potInput;
    }
    else
    {
        pMCData->dirCmd  = pMCData->dirCmdBuffer; 
    }
    
    if( (pMotorInputs->measureVdc.value >= pMotorInputs->measureVdc.dcMinRun) && 
                                            (pControlScheme->faultStatus == 0) )
    {
        pMCData->runCmd = pMCData->runCmdBuffer;
    }  
 
    pControlScheme->runDirection = pMCData->dirCmd;
    
    if(pMotorInputs->measureVdc.value > pMotorInputs->measureVdc.dcMaxStop)
    {
        pMCData->runCmd = 0;
    }
}
 

 