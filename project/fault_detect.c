// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
* @file mc1_fault_detect.c
*
* @brief Module to detect when motor is in fault condition
*
* Component: supervisory
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

#include "fault_detect.h"
#include "mc1_init.h"

// </editor-fold>

void MCAPP_FaultDetect(MCAPP_FAULT_DETECT_T *pfaultDetect,MCAPP_MEASURE_T *pMotorInputs)
{   
    /* Over Current Protection*/
    /* Phase A Over Current Protection*/
    if(pMotorInputs->iabcd.a > pfaultDetect->PhaseA_OC_Threshold)
    {
        pfaultDetect->faultStatus = MC1_PHASEA_OVERCURRENT_FAULT_DETECT;
    }
    /* Phase B Over Current Protection*/
    if(pMotorInputs->iabcd.b > pfaultDetect->PhaseB_OC_Threshold)
    {
        pfaultDetect->faultStatus = MC1_PHASEB_OVERCURRENT_FAULT_DETECT;
    }
    /* Phase C Over Current Protection*/
    if(pMotorInputs->iabcd.c > pfaultDetect->PhaseC_OC_Threshold)
    {
        pfaultDetect->faultStatus = MC1_PHASEC_OVERCURRENT_FAULT_DETECT;
    }
    /* Phase D Over Current Protection*/
    if(pMotorInputs->iabcd.d > pfaultDetect->PhaseD_OC_Threshold)
    {
        pfaultDetect->faultStatus = MC1_PHASED_OVERCURRENT_FAULT_DETECT;
    }  
}
