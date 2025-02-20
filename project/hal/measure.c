// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file measure.c
 *
 * @brief This module has functions for signal conditioning of measured
 *        analog feedback signals.
 *
 * Component: MEASURE
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

#include "measure.h"
#include "mc1_user_params.h"

// </editor-fold>

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">

/**
* <B> Function: MCAPP_MeasureCurrentInit(MCAPP_MEASURE_T *)  </B>
*
* @brief Function to reset variables used for current offset measurement.
*        
* @param Pointer to the data structure containing measured currents.
* @return none.
 * 
* @example
* <CODE> MCAPP_MeasureCurrentInit(&current); </CODE>
*
*/
void MCAPP_MeasureCurrentInit(MCAPP_MEASURE_T *pMotorInputs)
{
    MCAPP_MEASURE_CURRENT_T *pCurrent;
    
    pCurrent = &pMotorInputs->measureCurrent;
    pCurrent->offsetIa = 0;
    pCurrent->offsetIb = 0;
    pCurrent->offsetIc = 0;
    pCurrent->offsetId = 0;
    pCurrent->counter = 0;
    pCurrent->sumIa = 0;
    pCurrent->sumIb = 0;
    pCurrent->sumIc = 0;
    pCurrent->sumId = 0;
    pCurrent->sumIbus = 0;
    pCurrent->status = 0;  
}

/**
* <B> Function: MCAPP_MeasureCurrentOffset(MCAPP_MEASURE_T *)  </B>
*
* @brief Function to compute current offset after measuring specified number of
*        current samples and averaging them.
*        
* @param Pointer to the data structure containing measured current.
* @return none.
 * 
* @example
* <CODE> MCAPP_MeasureCurrentOffset(&current); </CODE>
*
*/
void MCAPP_MeasureCurrentOffset(MCAPP_MEASURE_T *pMotorInputs)
{
    MCAPP_MEASURE_CURRENT_T *pCurrent;
    
    pCurrent = &pMotorInputs->measureCurrent;
    
    pCurrent->sumIa   += pCurrent->Ia;
    pCurrent->sumIb   += pCurrent->Ib;
    pCurrent->sumIc   += pCurrent->Ic;
    pCurrent->sumId   += pCurrent->Id;
    pCurrent->sumIbus += pCurrent->Ibus;
    pCurrent->counter++;

    if (pCurrent->counter >= OFFSET_COUNT_MAX)
    {
        pCurrent->offsetIa   = (int32_t)(pCurrent->sumIa >> OFFSET_COUNT_BITS);
        pCurrent->offsetIb   = (int32_t)(pCurrent->sumIb >> OFFSET_COUNT_BITS);
        pCurrent->offsetIc   = (int32_t)(pCurrent->sumIc >> OFFSET_COUNT_BITS);
        pCurrent->offsetId   = (int32_t)(pCurrent->sumId >> OFFSET_COUNT_BITS);
        pCurrent->offsetIbus =
            (int32_t)(pCurrent->sumIbus >> OFFSET_COUNT_BITS);

        pCurrent->counter = 0;
        pCurrent->sumIa   = 0;
        pCurrent->sumIb   = 0;
        pCurrent->sumIc   = 0;
        pCurrent->sumId   = 0;
        pCurrent->sumIbus = 0;
        pCurrent->status  = 1;
    }
}

/**
* <B> Function: MCAPP_MeasureCurrentCalibrate(MCAPP_MEASURE_T *)  </B>
*
* @brief Function to compensate offset from measured current samples.
*        
* @param Pointer to the data structure containing measured current.
* @return none.
 * 
* @example
* <CODE> MCAPP_MeasureCurrentCalibrate(&current); </CODE>
*
*/
void MCAPP_MeasureCurrentCalibrate(MCAPP_MEASURE_T *pMotorInputs)
{
    MCAPP_MEASURE_CURRENT_T *pCurrent;
    
    pCurrent = &pMotorInputs->measureCurrent;
    
    pCurrent->Ia   = pCurrent->Ia - pCurrent->offsetIa;
    pCurrent->Ib   = pCurrent->Ib  - pCurrent->offsetIb;
    pCurrent->Ic   = pCurrent->Ic  - pCurrent->offsetIc;
    pCurrent->Id   = pCurrent->Id  - pCurrent->offsetId;
	pCurrent->Ibus = pCurrent->Ibus - pCurrent->offsetIbus;
}

/**
* <B> Function: MCAPP_MeasureInputs(MCAPP_MEASURE_T *)  </B>
*
* @brief Function to convert measured quantities to real values.
*        
* @param Pointer to the data structure containing measured current and voltage.
* @return none.
 * 
* @example
* <CODE> MCAPP_MeasureMotorInputs(&pMotorInputs); </CODE>
*
*/
void MCAPP_MeasureMotorInputs(MCAPP_MEASURE_T *pMotorInputs)
{ 
    /* Measure the offset and compensate the current values */
    MCAPP_MeasureCurrentCalibrate(pMotorInputs); 
    
    pMotorInputs->iabcd.a = (float) (pMotorInputs->measureCurrent.Ia * 
                                                pMotorInputs->adcCurrentScale);
    pMotorInputs->iabcd.b = (float) (pMotorInputs->measureCurrent.Ib * 
                                                pMotorInputs->adcCurrentScale);
    pMotorInputs->iabcd.c = (float) (pMotorInputs->measureCurrent.Ic * 
                                                pMotorInputs->adcCurrentScale);
    pMotorInputs->iabcd.d = (float) (pMotorInputs->measureCurrent.Id * 
                                                pMotorInputs->adcCurrentScale);

    pMotorInputs->motorCurrent = (float) (pMotorInputs->measureCurrent.Ibus * 
                                                pMotorInputs->adcCurrentScale);
    
    pMotorInputs->vabcd.a = (float) (pMotorInputs->measurePhaseVolt.Va * 
                                                pMotorInputs->adcVoltageScale);
    pMotorInputs->vabcd.b = (float) (pMotorInputs->measurePhaseVolt.Vb * 
                                                pMotorInputs->adcVoltageScale);
    pMotorInputs->vabcd.c = (float) (pMotorInputs->measurePhaseVolt.Vc * 
                                                pMotorInputs->adcVoltageScale);
    pMotorInputs->vabcd.d = (float) (pMotorInputs->measurePhaseVolt.Vd * 
                                                pMotorInputs->adcVoltageScale);   
}

/**
* <B> Function: MCAPP_MeasureCurrentOffsetStatus(MCAPP_MEASURE_CURRENT_T *)  </B>
*
* @brief Function to compensate offset from measured current samples.
*        
* @param Pointer to the data structure containing measured current.
* @return status bit after computing offset.
 * 
* @example
* <CODE> MCAPP_MeasureCurrentOffsetStatus(&current); </CODE>
*
*/
uint32_t MCAPP_MeasureCurrentOffsetStatus (MCAPP_MEASURE_T *pMotorInputs)
{
    return pMotorInputs->measureCurrent.status;
}
