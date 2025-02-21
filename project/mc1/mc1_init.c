// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file mc1_init.c
 *
 * @brief This module initializes data structure holding motor control
 * parameters required to run motor 1.
 * In this application to initialize variable required to run the application.
 *
 * Component: APPLICATION (Motor Control 1 - mc1)
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
#include <string.h>

#include "mc1_init.h"
#include "mc1_calc_params.h"
#include "mc_app_types.h"
#include "hcc_types.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="STATIC FUNCTIONS ">
static void MCAPP_MC1ControlSchemeConfig(MC1APP_DATA_T *);
static void MCAPP_MC1FeedbackConfig(MC1APP_DATA_T *);
static void MCAPP_MC1OutputConfig(MC1APP_DATA_T *);
// </editor-fold>

/**
* <B> Function: MCAPP_MC1ParamsInit (MC1APP_DATA_T *)  </B>
*
* @brief Function to reset variables used for current offset measurement.
*
* @param Pointer to the Application data structure required for 
* controlling motor 1.
* @return none.
* @example
* <CODE> MCAPP_MC1ParamsInit(&mc1); </CODE>
*
*/
void MCAPP_MC1ParamsInit(MC1APP_DATA_T *pMCData)
{    
    /* Reset all variables in the data structure to '0' */
    memset(pMCData,0,sizeof(MC1APP_DATA_T));

    pMCData->pControlScheme = &pMCData->controlScheme;
    pMCData->pMotorInputs = &pMCData->motorInputs;
    pMCData->pMotor = &pMCData->motor;
    pMCData->pPWMDuty = &pMCData->PWMDuty;
	pMCData->pfaultDetect = &pMCData->fault_detect;
    
    /* Configure Feedbacks */
    MCAPP_MC1FeedbackConfig(pMCData);
    
    /* Configure Control Scheme */
    MCAPP_MC1ControlSchemeConfig(pMCData);

    
    /* Configure Outputs */
    MCAPP_MC1OutputConfig(pMCData);
    
    /* Set motor control state as 'MTR_INIT' */
    pMCData->appState = MCAPP_INIT;
}

void MCAPP_MC1FeedbackConfig(MC1APP_DATA_T *pMCData)
{
    pMCData->HAL_MotorInputsRead = HAL_MC1MotorInputsRead;
    
    pMCData->motorInputs.measureVdc.dcMinRun = MOTOR_MIN_DC_VOLT ;
    
    pMCData->motorInputs.measureVdc.dcMaxStop = MOTOR_MAX_DC_VOLT;
    
}

void MCAPP_MC1ControlSchemeConfig(MC1APP_DATA_T *pMCData)
{
	MCAPP_CONTROL_SCHEME_T *pControlScheme;
    MCAPP_MEASURE_T *pMotorInputs;
    MCAPP_MOTOR_T *pMotor;
    MCAPP_FAULT_DETECT_T *pfault_detect;
    
    pControlScheme = pMCData->pControlScheme;
    pMotorInputs = pMCData->pMotorInputs;
    pMotor = pMCData->pMotor;
    pfault_detect = pMCData->pfaultDetect;

    
    /* Configure Inputs */  
    pControlScheme->pIa = &pMotorInputs->iabcd.a;
    pControlScheme->pIb = &pMotorInputs->iabcd.b;
    pControlScheme->pIc = &pMotorInputs->iabcd.c;
    pControlScheme->pId = &pMotorInputs->iabcd.d; 
    pControlScheme->pTheta = &pMotorInputs->detectRotorPosition.theta;
    pControlScheme->pSpeed = &pMotorInputs->detectRotorPosition.speed;
    pMotorInputs->adcCurrentScale = (float) (ADC_CURRENT_SCALE);
    pMotorInputs->adcVoltageScale = (float) (ADC_VOLTAGE_SCALE);
    /* Initialize motor parameters */    
    pMotor->cwTheta1On         =   (float) (RAD_THETA_1_ON_CW);
    pMotor->cwTheta1Off        =   (float) (RAD_THETA_1_OFF_CW);
    pMotor->cwTheta2On         =   (float) (RAD_THETA_2_ON_CW);
    pMotor->cwTheta2Off        =   (float) (RAD_THETA_2_OFF_CW);
    pMotor->cwTheta3On         =   (float) (RAD_THETA_3_ON_CW);
    pMotor->cwTheta3Off        =   (float) (RAD_THETA_3_OFF_CW);
    pMotor->cwTheta4On         =   (float) (RAD_THETA_4_ON_CW);
    pMotor->cwTheta4Off        =   (float) (RAD_THETA_4_OFF_CW);
            
    pMotor->ccwTheta1On        =   (float) (RAD_THETA_1_ON_CCW);
    pMotor->ccwTheta1Off       =   (float) (RAD_THETA_1_OFF_CCW);
    pMotor->ccwTheta2On        =   (float) (RAD_THETA_2_ON_CCW);
    pMotor->ccwTheta2Off       =   (float) (RAD_THETA_2_OFF_CCW);
    pMotor->ccwTheta3On        =   (float) (RAD_THETA_3_ON_CCW);
    pMotor->ccwTheta3Off       =   (float) (RAD_THETA_3_OFF_CCW);
    pMotor->ccwTheta4On        =   (float) (RAD_THETA_4_ON_CCW);
    pMotor->ccwTheta4Off       =   (float) (RAD_THETA_4_OFF_CCW);
    
    pMotor->minSpeed           =   (float) (MINIMUM_SPEED_RPM);
    pMotor->nominalSpeed       =   (float) (NOMINAL_SPEED_RPM);
    pMotor->maxSpeed           =   (float) (MAXIMUM_SPEED_RPM);
    pMotor->ratedCurrent       =   (float) (RATED_CURRENT);   
    
    /* Initialize SRM control parameters */
#ifdef  SPEED_CONTROL
    pControlScheme->ctrlParam.speedLoop = 1; /* Speed control mode */
#else
    pControlScheme->ctrlParam.speedLoop = 0; /* Current control mode */
#endif
    pControlScheme->ctrlParam.speedRate    = SPEED_CRTL_RATE;
    pControlScheme->ctrlParam.crtlTheta    = RAD_CRTL_THETA;
    
    pControlScheme->ctrlParam.cwThetaOffset = 
                       pControlScheme->ctrlParam.crtlTheta - pMotor->cwTheta1On;
    pControlScheme->ctrlParam.cwTheta1Commutation =  pMotor->cwTheta1Off - 
                                                             pMotor->cwTheta1On;
    pControlScheme->ctrlParam.cwTheta2Commutation =  pMotor->cwTheta2Off - 
                                                             pMotor->cwTheta1On;
    pControlScheme->ctrlParam.cwTheta3Commutation =  pMotor->cwTheta3Off - 
                                                             pMotor->cwTheta1On;
    pControlScheme->ctrlParam.cwTheta4Commutation =  pMotor->cwTheta4Off - 
                                                             pMotor->cwTheta1On;
    
    pControlScheme->ctrlParam.ccwThetaOffset = 
                      pControlScheme->ctrlParam.crtlTheta - pMotor->ccwTheta1On;        
    pControlScheme->ctrlParam.ccwTheta1Commutation =  pMotor->ccwTheta1Off + 
                                       pControlScheme->ctrlParam.ccwThetaOffset;
    pControlScheme->ctrlParam.ccwTheta2Commutation =  pMotor->ccwTheta2Off +
                                       pControlScheme->ctrlParam.ccwThetaOffset;
    pControlScheme->ctrlParam.ccwTheta3Commutation =  pMotor->ccwTheta3Off + 
                                       pControlScheme->ctrlParam.ccwThetaOffset;
    pControlScheme->ctrlParam.ccwTheta4Commutation =  pMotor->ccwTheta4Off + 
                                       pControlScheme->ctrlParam.ccwThetaOffset;
    
    pControlScheme->motor.minSpeed      = pMotor->minSpeed;
    pControlScheme->motor.nominalSpeed  = pMotor->nominalSpeed;
    pControlScheme->motor.maxSpeed      = pMotor->maxSpeed;
    pControlScheme->maxCurrentRef       = (float) (MAXIMUM_REF_CURRENT);
    
    /* Initialize HCC controller */
    pControlScheme->hccInput.hccState.beta           =   HCC_BETA;
    
    /* Initialize PI controller used for speed control */
    pControlScheme->piSpeedInput.piState.kp          =   SPEEDCNTR_PTERM;
    pControlScheme->piSpeedInput.piState.ki          =   SPEEDCNTR_ITERM;
    pControlScheme->piSpeedInput.piState.kc          =   SPEEDCNTR_CTERM;
    pControlScheme->piSpeedInput.piState.outMax      =   SPEEDCNTR_OUTMAX;
    pControlScheme->piSpeedInput.piState.outMin      =   SPEEDCNTR_OUTMIN;
    pControlScheme->piSpeedInput.piState.integrator  =   0;
    
    /* Output Initializations */  
    pControlScheme->PhaseA_Control  =   PWM1_OverrideEnableDataSet;
    pControlScheme->PhaseB_Control  =   PWM2_OverrideEnableDataSet;
    pControlScheme->PhaseC_Control  =   PWM3_OverrideEnableDataSet;
    pControlScheme->PhaseD_Control  =   PWM4_OverrideEnableDataSet;
    
    /* Initialize fault detection parameters*/
    pfault_detect->PhaseA_OC_Threshold = PHASE_OC_THRESHOLD;
    pfault_detect->PhaseB_OC_Threshold = PHASE_OC_THRESHOLD;
    pfault_detect->PhaseC_OC_Threshold = PHASE_OC_THRESHOLD;
    pfault_detect->PhaseD_OC_Threshold = PHASE_OC_THRESHOLD;
    
    /* Initialize application structure */
    pMCData->MCAPP_ControlSchemeInit = MCAPP_SRMControlInit;
    pMCData->MCAPP_ControlStateMachine = MCAPP_SRMStateMachine;
    
    pMCData->MCAPP_InputsInit = MCAPP_MeasureCurrentInit;
    pMCData->MCAPP_MeasureOffset = MCAPP_MeasureCurrentOffset;
    pMCData->MCAPP_GetProcessedInputs = MCAPP_MeasureMotorInputs;

    pMCData->MCAPP_IsOffsetMeasurementComplete = MCAPP_MeasureCurrentOffsetStatus;
    pMCData->MCAPP_PositionSensorInit = MCAPP_AM4096magInit;
    pMCData->MCAPP_PositionSensorRead = MCAPP_AM4096magRead;   
    
}
void MCAPP_MC1OutputConfig(MC1APP_DATA_T *pMCData)
{
    pMCData->HAL_PWMSetDutyCycles  = HAL_MC1PWMSetDutyCycles;
    pMCData->HAL_PWMEnableOutputs  = HAL_MC1PWMEnableOutputs;
    pMCData->HAL_PWMDisableOutputs = HAL_MC1PWMDisableOutputs;
}

