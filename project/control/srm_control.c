// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file srm_control.c
 *
 * @brief This module implements control state machine.
 *
 * Component: CONTROL ALGORITHIM
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
#include "math.h"

#include "srm_control.h"
#include "mc1_user_params.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="STATIC FUNCTIONS ">
static void MCAPP_GetControlInputs(MCAPP_SRM_CONTROL_T *);
static void MCAPP_SRMControl(MCAPP_SRM_CONTROL_T *, MCAPP_CONTROL_T *);
static void SRM_RunMotor(MCAPP_SRM_CONTROL_T *, uint32_t, uint32_t);
// </editor-fold>

/**
* <B> Function: MCAPP_SRMControlInit(MCAPP_SRM_CONTROL_T *)  </B>
*
* @brief Function to set variables for Control.
*        
* @param 
* @return none.
 * 
* @example
* <CODE> MCAPP_SRMControlInit(&pSRM); </CODE>
*
*/
void MCAPP_SRMControlInit(MCAPP_SRM_CONTROL_T *pSRM)
{
    pSRM->controlTheta              = 0;
    pSRM->controlThetaBuf           = 0;
    pSRM->warpTheta                 = 0;
    pSRM->iabcd.a                   = 0;
    pSRM->iabcd.b                   = 0;
    pSRM->iabcd.c                   = 0;
    pSRM->iabcd.d                   = 0;
    pSRM->speed                     = 0;
    pSRM->speedRateCounter          = 0;
    pSRM->theta                     = 0;
    pSRM->referenceCurrent          = 0;
    
    pSRM->ctrlParam.cBootOn         = 0;
    pSRM->ctrlParam.phaseOn         = 0;
    pSRM->ctrlParam.controlInput    = 0;
    pSRM->ctrlParam.currentInput    = 0;
    pSRM->ctrlParam.speedInput      = 0;
    
    pSRM->hccInput.currentActual    = 0;
    pSRM->hccInput.currentReference = 0;
    pSRM->hccInput.hccState.currentLowerLimit = 0;
    pSRM->hccInput.hccState.currentUpperLimit = 0;
    pSRM->hccOutput.out             = 0;
    
    pSRM->piSpeedInput.inMeasure    = 0;
    pSRM->piSpeedInput.inReference  = 0;
    pSRM->piSpeedInput.piState.integrator = 0;
    pSRM->piSpeedOutput.out = 0;
     
    pSRM->controlState = SRM_CONTROL; 
}

/**
* <B> Function: void MCAPP_SRMStateMachine (MCAPP_SRM_CONTROL_T *)  </B>
*
* @brief SRM control state machine.
*
* @param Pointer to the data structure containing control parameters.
* @return none.
* @example
* <CODE> MCAPP_SRMControl(&pSRM); </CODE>
*
*/
void MCAPP_SRMStateMachine (MCAPP_SRM_CONTROL_T *pSRM)
{
    MCAPP_CONTROL_T *pCtrlParam = &pSRM->ctrlParam;
    switch (pSRM->controlState)
    {
        case SRM_INIT:
            MCAPP_SRMControlInit(pSRM);
            pSRM->controlState = SRM_CONTROL;
            break;
            
        case SRM_CONTROL:
            /* Inputs for control */
            MCAPP_GetControlInputs(pSRM);
            
            if(pSRM->ctrlParam.speedLoop == 1)
            {
                /* PI Speed control loop */
                /* Speed Loop */
                if( pSRM->speedRateCounter > pSRM->ctrlParam.speedRate )
                {
                    pSRM->speedRateCounter = 0;

                    /* PI control for current in Speed Loop */
                    pSRM->piSpeedInput.inMeasure = pSRM->speed;
                    pSRM->piSpeedInput.inReference = pSRM->ctrlParam.speedInput;
                    MC_ControllerPIUpdate(&pSRM->piSpeedInput, 
                            &pSRM->piSpeedInput.piState , &pSRM->piSpeedOutput);

                    pSRM->referenceCurrent = pSRM->piSpeedOutput.out;
                }
                else
                {
                    pSRM->speedRateCounter++;
                }           
            }
            else
            {
                /* Current Loop */
                pSRM->referenceCurrent = pSRM->ctrlParam.currentInput;
            }
            
            /* Run motor */
            MCAPP_SRMControl(pSRM,pCtrlParam);
            SRM_RunMotor(pSRM,pCtrlParam->phaseOn,pCtrlParam->cBootOn);
            break;
                 
        case SRM_FAULT:
            
            break;
            
        default:
            pSRM->controlState = SRM_FAULT;
            break;
        
    } /* End Of switch - case */
}

/**
* <B> Function: void MCAPP_GetControlInputs (MCAPP_SRM_CONTROL_T *)  </B>
*
* @brief Function read motor control inputs.
*
* @param Pointer to the data structure containing Control parameters.
* @return none.
* @example
* <CODE> MCAPP_GetControlInputs(&pSRM); </CODE>
*
*/
static void MCAPP_GetControlInputs(MCAPP_SRM_CONTROL_T *pSRM)
{ 
    /* Motor current inputs */
    pSRM->iabcd.a = *(pSRM->pIa);
    pSRM->iabcd.b = *(pSRM->pIb);
    pSRM->iabcd.c = *(pSRM->pIc);
    pSRM->iabcd.d = *(pSRM->pId);
    pSRM->speed   = *(pSRM->pSpeed);
    pSRM->theta   = *(pSRM->pTheta);
    /* Theta buffer warp to control angle */
    pSRM->warpTheta = fmod( pSRM->theta , pSRM->ctrlParam.crtlTheta );
    
    /* Selection of control input */
    if(pSRM->ctrlParam.speedLoop == 1)
    {
        /* Speed Input from control input for speed control */
        pSRM->ctrlParam.speedInput = (float)pSRM->motor.minSpeed + 
                ((float)(pSRM->motor.maxSpeed - pSRM->motor.minSpeed)* 
                (float)(pSRM->ctrlParam.controlInput / 4095.0));
    }
    else
    {
        /* Current input from control input for current control */
        pSRM->ctrlParam.currentInput = ((float)(pSRM->ctrlParam.controlInput * 
                pSRM->maxCurrentRef) / 4095.0 );
    } 
}

/**
* <B> Function: void MCAPP_SRMControl(MCAPP_SRM_CONTROL_T *, MCAPP_CONTROL_T *)  </B>
*
* @brief Executes Speed and Current Control Loops and performs actions
*        associated with SRM control 
*
* @param Pointer to the data structure containing control parameters.
* @return none.
* @example
* <CODE> MCAPP_SRMControl(&pSRM, &pCtrlParam); </CODE>
*
*/
void MCAPP_SRMControl(MCAPP_SRM_CONTROL_T *pSRM, MCAPP_CONTROL_T *pCtrlParam)
{    
    if(pSRM->runDirection == 0)
    {
        /* Control theta buffer for offset correction */
        pSRM->controlThetaBuf = pSRM->warpTheta + pSRM->ctrlParam.cwThetaOffset;
        /* Control theta buffer warp to control angle */
        pSRM->controlTheta = fmod( pSRM->controlThetaBuf , 
                                                    pSRM->ctrlParam.crtlTheta );
        
        if(pSRM->controlTheta <= pSRM->ctrlParam.cwTheta1Commutation)
        {
            pCtrlParam->phaseOn = THETA_1_COMMUTATE_CW;
            pCtrlParam->cBootOn = THETA_1_CBOOT_CW;
        }
        else if (pSRM->controlTheta <= pSRM->ctrlParam.cwTheta2Commutation)
        {
            pCtrlParam->phaseOn = THETA_2_COMMUTATE_CW;
            pCtrlParam->cBootOn = THETA_2_CBOOT_CW;
        }
        else if (pSRM->controlTheta <= pSRM->ctrlParam.cwTheta3Commutation)
        {
            pCtrlParam->phaseOn = THETA_3_COMMUTATE_CW;
            pCtrlParam->cBootOn = THETA_3_CBOOT_CW;
        }
        else
        {
            pCtrlParam->phaseOn = THETA_4_COMMUTATE_CW;
            pCtrlParam->cBootOn = THETA_4_CBOOT_CW;
        }
    }
    else
    {
        /* Control theta buffer for offset correction */
        pSRM->controlThetaBuf = pSRM->warpTheta + pSRM->ctrlParam.ccwThetaOffset;
        /* Control theta buffer warp to control angle */
        pSRM->controlTheta = fmod( pSRM->controlThetaBuf , 
                                                    pSRM->ctrlParam.crtlTheta );
         
        if ( pSRM->controlTheta >= pSRM->ctrlParam.ccwTheta1Commutation)
        {
            pCtrlParam->phaseOn = THETA_1_COMMUTATE_CCW;
            pCtrlParam->cBootOn = THETA_1_CBOOT_CCW;
        } 
        else if ( pSRM->controlTheta >= pSRM->ctrlParam.ccwTheta2Commutation)
        {
            pCtrlParam->phaseOn = THETA_2_COMMUTATE_CCW;
            pCtrlParam->cBootOn = THETA_2_CBOOT_CCW;
        }
        else if ( pSRM->controlTheta >= pSRM->ctrlParam.ccwTheta3Commutation)
        {
            pCtrlParam->phaseOn = THETA_3_COMMUTATE_CCW;
            pCtrlParam->cBootOn = THETA_3_CBOOT_CCW;
        }
        else
        {
            pCtrlParam->phaseOn = THETA_4_COMMUTATE_CCW;
            pCtrlParam->cBootOn = THETA_4_CBOOT_CCW;
        }
    }
}

/**
* <B> Function: void SRM_RunMotor(MCAPP_SRM_CONTROL_T *)  </B>
*
* @brief Executes Boot strap capacitor charging and Inverter outputs
*
* @param Pointer to the data structure containing control parameters.
* @return none.
* @example
* <CODE> SRM_RunMotor(&pSRM, &phaseOn, &cBootOn); </CODE>
*
*/
void SRM_RunMotor(MCAPP_SRM_CONTROL_T *pSRM, uint32_t phaseOn, uint32_t cBootOn)
{   
    /* Switch case for Inverter output */
    switch (phaseOn)
    {
        case PHASEA_COMMUTATION:
            /* Demagnetize other phases */
            pSRM->PhaseD_Control(MC1_DEMAGNETIZE);
            pSRM->PhaseC_Control(MC1_DEMAGNETIZE);
            pSRM->PhaseB_Control(MC1_DEMAGNETIZE);
            /* Hysteresis Current Controller */
            pSRM->hccInput.currentReference = pSRM->referenceCurrent;
            pSRM->hccInput.currentActual    = pSRM->iabcd.a;
            MCAPP_ControllerHysteresis(&pSRM->hccInput, &pSRM->hccInput.hccState, 
                    &pSRM->hccOutput);
            pSRM->switchState = pSRM->hccOutput.out;
            if(pSRM->switchState == true)
            {               
                pSRM->PhaseA_Control(MC1_MAGNETIZE);
            }
            else
            {
                pSRM->PhaseA_Control(MC1_FREEWHEELING);
            }
            break;
        case PHASEB_COMMUTATION:
            /* Demagnetize other phases */
            pSRM->PhaseD_Control(MC1_DEMAGNETIZE);
            pSRM->PhaseC_Control(MC1_DEMAGNETIZE);
            pSRM->PhaseA_Control(MC1_DEMAGNETIZE);
            /* Hysteresis Current Controller */
            pSRM->hccInput.currentReference = pSRM->referenceCurrent;
            pSRM->hccInput.currentActual    = pSRM->iabcd.b;
            MCAPP_ControllerHysteresis(&pSRM->hccInput, &pSRM->hccInput.hccState, 
                    &pSRM->hccOutput);
            pSRM->switchState = pSRM->hccOutput.out;
            if(pSRM->switchState == true)
            {
                pSRM->PhaseB_Control(MC1_MAGNETIZE);
            }
            else
            {
                pSRM->PhaseB_Control(MC1_FREEWHEELING);
            }
        break;
        case PHASEC_COMMUTATION:
            /* Demagnetize other phases */
            pSRM->PhaseD_Control(MC1_DEMAGNETIZE);
            pSRM->PhaseB_Control(MC1_DEMAGNETIZE);
            pSRM->PhaseA_Control(MC1_DEMAGNETIZE);
            /* Hysteresis Current Controller */
            pSRM->hccInput.currentReference = pSRM->referenceCurrent;
            pSRM->hccInput.currentActual    = pSRM->iabcd.c;
            MCAPP_ControllerHysteresis(&pSRM->hccInput, &pSRM->hccInput.hccState, 
                    &pSRM->hccOutput);
            pSRM->switchState = pSRM->hccOutput.out;
            if(pSRM->switchState == true)
            {
                pSRM->PhaseC_Control(MC1_MAGNETIZE);
            }
            else
            {
                pSRM->PhaseC_Control(MC1_FREEWHEELING);
            }
        break;
        case PHASED_COMMUTATION:
            /* Demagnetize other phases */
            pSRM->PhaseC_Control(MC1_DEMAGNETIZE);
            pSRM->PhaseB_Control(MC1_DEMAGNETIZE);
            pSRM->PhaseA_Control(MC1_DEMAGNETIZE);
            /* Hysteresis Current Controller */
            pSRM->hccInput.currentReference = pSRM->referenceCurrent;
            pSRM->hccInput.currentActual    = pSRM->iabcd.d;
            MCAPP_ControllerHysteresis(&pSRM->hccInput, &pSRM->hccInput.hccState, 
                    &pSRM->hccOutput);
            pSRM->switchState = pSRM->hccOutput.out;
            if(pSRM->switchState == true)
            {
                pSRM->PhaseD_Control(MC1_MAGNETIZE); 
            }
            else
            {
                pSRM->PhaseD_Control(MC1_FREEWHEELING);
            }
        break;
    }
    
    /* Switch case for Boot Strap capacitor charging */
    switch (cBootOn)
    {
        case PHASEA_CBOOT:
            pSRM->PhaseA_Control(MC1_CHG_BOOTCAP);
            break;
            
        case PHASEB_CBOOT:
            pSRM->PhaseB_Control(MC1_CHG_BOOTCAP);
            break;
        
        case PHASEC_CBOOT:
            pSRM->PhaseC_Control(MC1_CHG_BOOTCAP);
            break;
        
        case PHASED_CBOOT:
            pSRM->PhaseD_Control(MC1_CHG_BOOTCAP);
            break;
    } 
}


