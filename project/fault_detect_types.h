/**
 * fault_detect_types.h
 *
 * Module for Detecting Motor Faults
 * 
 * Component: supervisory
 */

/* *********************************************************************
 *
 * Motor Control Application Framework
 * R7/RC37 (commit 116330, build on 2023 Feb 09)
 *
 * (c) 2017 - 2023 Microchip Technology Inc. and its subsidiaries. You may use
 * this software and any derivatives exclusively with Microchip products.
 *
 * This software and any accompanying information is for suggestion only.
 * It does not modify Microchip's standard warranty for its products.
 * You agree that you are solely responsible for testing the software and
 * determining its suitability.  Microchip has no obligation to modify,
 * test, certify, or support the software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE, OR ITS INTERACTION WITH
 * MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY
 * APPLICATION.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL,
 * PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF
 * ANY KIND WHATSOEVER RELATED TO THE USE OF THIS SOFTWARE, THE
 * motorBench(R) DEVELOPMENT SUITE TOOL, PARAMETERS AND GENERATED CODE,
 * HOWEVER CAUSED, BY END USERS, WHETHER MICROCHIP'S CUSTOMERS OR
 * CUSTOMER'S CUSTOMERS, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
 * CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
 * OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
 * SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF
 * THESE TERMS.
 *
 * *****************************************************************************/

#ifndef __FAULT_DETECT_TYPES_H
#define __FAULT_DETECT_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Fault flag types 
 */  
typedef enum
{
    MC1_OV_OC_FAULT_DETECT                  = 0x01,  /* Hardware DC bus Overvoltage and Overcurrent indicator */
    MC1_OVERCURRENT_FAULT_DETECT            = 0x02,  /* Allegro Overcurrent fault indicator */
    MC1_PHASEA_OVERCURRENT_FAULT_DETECT     = 0x03,  /* Phase A Overcurrent fault indicator */
    MC1_PHASEB_OVERCURRENT_FAULT_DETECT     = 0x04,  /* Phase B Overcurrent fault indicator */
    MC1_PHASEC_OVERCURRENT_FAULT_DETECT     = 0x05,  /* Phase C Overcurrent fault indicator */
    MC1_PHASED_OVERCURRENT_FAULT_DETECT     = 0x06   /* Phase D Overcurrent fault indicator */
} MC1_FAULT_DETECT_FLAG;

// <editor-fold defaultstate="collapsed" desc="VARIABLE TYPE DEFINITIONS ">

typedef struct
{
    float
        PhaseA_OC_Threshold,
        PhaseB_OC_Threshold,
        PhaseC_OC_Threshold,
        PhaseD_OC_Threshold; 
    
    uint32_t
        faultStatus;        /* Fault Status */  
}MCAPP_FAULT_DETECT_T;

#ifdef __cplusplus
}
#endif

#endif /* __FAULT_DETECT_TYPES_H */
