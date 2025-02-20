// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
* @file srm_types.h
*
* @brief This module has variable type definitions of data structure
* holding SRM control parameters and enumerated constants.
*
* Component: SRM control
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

#ifndef SRM_TYPES_H
#define	SRM_TYPES_H

#ifdef	__cplusplus
extern "C" {
#endif

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">

#include <stdint.h>
#include <stdbool.h>
#include "measure.h"
#include "srm_control_types.h"
#include "motor_params.h"
#include "hcc.h"
#include "pi.h"
// </editor-fold>

// <editor-fold defaultstate="expanded" desc="ENUMERATED CONSTANTS ">

typedef enum
{
    SRM_INIT = 0,           /* Initialize control parameters */
    SRM_CONTROL = 1,        /* Speed or Current control*/
    SRM_FAULT = 2,          /* Motor is in Fault */       
}SRM_CONTROL_STATE_T;

typedef enum
{
    MC1_DEMAGNETIZE  = 0,       /* Demagnetize the phase current by turning off both the switches */
    MC1_MAGNETIZE    = 1,       /* Magnetize   the phase current by turning on  both the switches */
    MC1_FREEWHEELING = 2,       /* Freewheeling the phase current by turning on only the lower switch */
    MC1_CHG_BOOTCAP  = 3,       /* Charge the Bootstrap Capacitor */
            
}MCAPP_SRM_PHASE_CRTL_T;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="VARIABLE TYPE DEFINITIONS ">

typedef struct
{
    uint32_t
        faultStatus,        /* Fault Status */
        runDirection,       /* Variable for motor run direction */
        controlState,       /* State variable for control state machine */
        speedRateCounter;   /* Index counter for PI speed loop */
    bool
        switchState;        /* Variable for switch ON or OFF */
    float
        *pIa,               /* Pointer for Ia */
        *pIb,               /* Pointer for Ib */
        *pIc,               /* Pointer for Ic */
        *pId,               /* Pointer for Id */
        *pSpeed,            /* Pointer for Speed */
        speed,              /* variable for speed */
        referenceCurrent,   /* Reference current for control */
        theta,              /* theta mechanical 0 to 2pi*/        
        *pTheta,            /* Pointer for theta */
        warpTheta,          /* variable for warp theta */
        controlTheta,       /* warp theta used for control */
        controlThetaBuf,    /* Buffer variable for theta used for offset correction */
        maxCurrentRef;      /* Maximum current reference limit for current control */
    
    /* Parameters for HCC control */
    MCAPP_HCCPARMIN_T hccInput;
    MCAPP_HCCPARMOUT_T hccOutput;
    
    /* Parameters for PI Speed controllers */ 
    MC_PIPARMIN_T   piSpeedInput;
    MC_PIPARMOUT_T  piSpeedOutput;
    
    MC_ABCD_T
        iabcd,              /* Iabcd */
        vabcd;              /* Vabcd */
            
    MCAPP_CONTROL_T
        ctrlParam;          /* Parameters for control references */
    
    MCAPP_MOTOR_T
        motor;              /* Pointer for Motor Parameters */
        
    /* Function pointers for PWM control */
    void (*PhaseA_Control) (uint32_t);
    void (*PhaseB_Control) (uint32_t);
    void (*PhaseC_Control) (uint32_t);
    void (*PhaseD_Control) (uint32_t);
    
}MCAPP_SRM_CONTROL_T;

// </editor-fold>

#ifdef	__cplusplus
}
#endif

#endif	/* SRM_TYPES_H */

