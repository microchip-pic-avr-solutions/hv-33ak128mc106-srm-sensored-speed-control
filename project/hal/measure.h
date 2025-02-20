// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file measure.h
 *
 * @brief This header file lists the functions and definitions
 * for signal conditioning of measured analog feedback signals.
 *
 * Component: ANALOG SIGNAL MEASURE
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

#ifndef __MEASURE_H
#define __MEASURE_H

#ifdef __cplusplus
extern "C" {
#endif

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">

#include <stdint.h>
#include "am4096.h"
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="DEFINITIONS ">

#define OFFSET_COUNT_BITS   (int16_t)10
#define OFFSET_COUNT_MAX    (int16_t)(1 << OFFSET_COUNT_BITS)

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="VARIABLE TYPE DEFINITIONS ">

typedef struct
{
    float
        Ia,             /* A phase Current Feedback */
        Ib,             /* B phase Current Feedback */
        Ic,             /* C phase Current Feedback */
        Id,             /* D phase Current Feedback */
        Ibus;           /* BUS current Feedback */
    
    int32_t
        offsetIa,       /* A phase current offset */
        offsetIb,       /* B phase current offset */
        offsetIc,       /* C phase current offset */
        offsetId,       /* D phase current offset */
        offsetIbus,     /* BUS current offset */
        sumIa,          /* Accumulation of Ia */
        sumIb,          /* Accumulation of Ib */
        sumIc,          /* Accumulation of Ic */
        sumId,          /* Accumulation of Id */
        sumIbus;        /* Accumulation of Ibus */
        
        
    uint32_t
        counter,        /* counter */
        status;         /* flag to indicate offset measurement completion */ 
} MCAPP_MEASURE_CURRENT_T;

typedef struct
{
    float
        value,          /* Measured value of DC Bus Voltage. */
        dcMinRun,       /* Minimum voltage for the motor to run */
        dcMaxStop;      /* Maximum voltage at which the motor would stop */
} MCAPP_MEASURE_VDC_T;

typedef struct
{
    int32_t
        Va,             /* A phase Voltage */
        Vb,             /* B phase Voltage */
        Vc,             /* C phase Voltage */
        Vd,             /* D phase Voltage */
        status,         /* Status if phase voltages are available */
        samplingFactor; /* Ratio of sampling time to ADC interrupt */
}MCAPP_MEASURE_PHASEVOLT_T;

typedef struct
{
    /** Phase A component */
    float   a;
    /** Phase B component */
    float   b;
    /** Phase C component */
    float   c;
    /** Phase D component */
    float   d;

} MC_ABCD_T;

typedef struct
{
    int32_t 
        potValue;       /* Measure potentiometer */       
    
    float    
        motorCurrent,   /* Motor current  */
        dcBusVoltage,   /* Measure DC BUS voltage */
        potValueScaled, /* Scaled potentiometer value */ 
        adcCurrentScale,/* Scale for current in real value */
        adcVoltageScale;/* Scale for voltage in real value */
            
    
    MCAPP_MEASURE_CURRENT_T
        measureCurrent; /* Current measurement parameters */
    MCAPP_MEASURE_VDC_T
        measureVdc;     /* DC Bus Sensing parameters */
    MCAPP_MEASURE_PHASEVOLT_T
        measurePhaseVolt;  /* Phase voltage measurement parameters */  
    MCAPP_AM4096_T
        detectRotorPosition;/* Rotor position detection from sensors */
    
   MC_ABCD_T 
        vabcd,          /* Vabcd */
        iabcd;          /* Iabcd */
}MCAPP_MEASURE_T;

/**
 * Duty-cycle data type
*/
typedef struct
{
    /** Duty cycle for phase #1 */
    float dutycycle1;

    /** Duty cycle for phase #2 */
    float dutycycle2;

    /** Duty cycle for phase #3 */
    float dutycycle3;
    
    /** Duty cycle for phase #4 */
    float dutycycle4;
    
    float pwmduty;
    
} MC_DUTYCYCLEOUT_T;

// </editor-fold>

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">

void MCAPP_MeasureCurrentOffset (MCAPP_MEASURE_T *);
void MCAPP_MeasureCurrentCalibrate (MCAPP_MEASURE_T *);
void MCAPP_MeasureCurrentInit (MCAPP_MEASURE_T *);
void MCAPP_MeasureMotorInputs(MCAPP_MEASURE_T *);
uint32_t MCAPP_MeasureCurrentOffsetStatus (MCAPP_MEASURE_T *);

// </editor-fold>

#ifdef __cplusplus
}
#endif

#endif /* end of __MEASURE_H */
