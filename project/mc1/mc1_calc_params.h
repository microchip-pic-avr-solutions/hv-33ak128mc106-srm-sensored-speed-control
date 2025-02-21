// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file mc1_calc_params.h
 *
 * @brief This file has definitions used in the application to run motor 1,
 *        calculated based on associated user parameter header file
 *        mc1_user_params.h.
 *
 * Component: BOARD
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

#ifndef __MC1_CALC_PARAMS_H
#define __MC1_CALC_PARAMS_H

#ifdef __cplusplus
extern "C" {
#endif

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">

#include <stdint.h>

#include "board_service.h"

#include "mc1_user_params.h"
#include "math.h"

// </editor-fold>

// <editor-fold defaultstate="expanded" desc="DEFINITIONS/MACROS ">
    
#define MC1_LOOPTIME_TCY              LOOPTIME_TCY 
    
#define MC1_LOOPTIME_SEC              LOOPTIME_SEC

#define LOOPTIME_MICROSEC             (LOOPTIME_SEC * 1000000.0f)    
    
#define ADC_VOLTAGE_SCALE             (float)(MC1_PEAK_VOLTAGE/4095.0f)
#define ADC_VDC_VOLTAGE_SCALE         (float)(MC1_MAX_DC_BUS_VOLTAGE/4095.0f)
    
#define ADC_CURRENT_SCALE             (float)(MC1_PEAK_CURRENT/32768.0f)
#define ADC_CURRENT_SCALE_INVERSE     (float)((32768.0f/ MC1_PEAK_CURRENT) 
    
/* Convert degrees to radians */    
#define M_PI_RAD                      (float) M_PI / 180

/* Commutation angles in radians */ 
#define RAD_CRTL_THETA                (float) (M_PI_RAD * CRTL_THETA)
#define RAD_THETA_1_ON_CW             (float) (M_PI_RAD * THETA_1_ON_CW)
#define RAD_THETA_1_OFF_CW            (float) (M_PI_RAD * THETA_1_OFF_CW)
#define RAD_THETA_2_ON_CW             (float) (M_PI_RAD * THETA_2_ON_CW)
#define RAD_THETA_2_OFF_CW            (float) (M_PI_RAD * THETA_2_OFF_CW)
#define RAD_THETA_3_ON_CW             (float) (M_PI_RAD * THETA_3_ON_CW)
#define RAD_THETA_3_OFF_CW            (float) (M_PI_RAD * THETA_3_OFF_CW)
#define RAD_THETA_4_ON_CW             (float) (M_PI_RAD * THETA_4_ON_CW)
#define RAD_THETA_4_OFF_CW            (float) (M_PI_RAD * THETA_4_OFF_CW)
#define RAD_THETA_1_ON_CCW            (float) (M_PI_RAD * THETA_1_ON_CCW)
#define RAD_THETA_1_OFF_CCW           (float) (M_PI_RAD * THETA_1_OFF_CCW)
#define RAD_THETA_2_ON_CCW            (float) (M_PI_RAD * THETA_2_ON_CCW)
#define RAD_THETA_2_OFF_CCW           (float) (M_PI_RAD * THETA_2_OFF_CCW)
#define RAD_THETA_3_ON_CCW            (float) (M_PI_RAD * THETA_3_ON_CCW)
#define RAD_THETA_3_OFF_CCW           (float) (M_PI_RAD * THETA_3_OFF_CCW)
#define RAD_THETA_4_ON_CCW            (float) (M_PI_RAD * THETA_4_ON_CCW)
#define RAD_THETA_4_OFF_CCW           (float) (M_PI_RAD * THETA_4_OFF_CCW)
// </editor-fold>

#ifdef __cplusplus
}
#endif

#endif	/* end of __MC1_CALC_PARAMS_H */
