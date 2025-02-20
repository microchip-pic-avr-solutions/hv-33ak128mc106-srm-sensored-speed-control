// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file mc1_user_params.h
 *
 * @brief This file has definitions to be configured by the user for spinning
 * 		  motor.
 *
 * Component: APPLICATION (motor control)
 * Motor : Switched Reluctance Motor
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

#ifndef __MC1_USER_PARAMS_H
#define __MC1_USER_PARAMS_H

#ifdef __cplusplus
extern "C" {
#endif

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">
#include <stdint.h>
// </editor-fold>
       
// <editor-fold defaultstate="expanded" desc="DEFINITIONS/MACROS ">
    
/** Define macros for operational modes */
    
/* Define SPEED_CONTROL to enable Speed control, 
 * undefine SPEED_CONTROL to enable only Current control */
#define SPEED_CONTROL

/* Select sensor used for current measurement
 * Define ALLEGRO_CT110_CS for Allegro CT110 current sensor output
 * undefine ALLEGRO_CT110_CS for Shunt resistor current measurement */
#undef ALLEGRO_CT110_CS    
    
/** Board Parameters */
/* Peak measurement voltage(V) of the board */
#define MC1_PEAK_VOLTAGE                              426.0f    
/* Maximum DC Bus measurement voltage(V) of the board */
#define MC1_MAX_DC_BUS_VOLTAGE                        453.3f
/* Peak measurement current(A) of the board */
#ifdef ALLEGRO_CT110_CS
#define MC1_PEAK_CURRENT                              10.523f 
#else
#define MC1_PEAK_CURRENT                              11.0f  
#endif    
    
/* Enter the sampling time in seconds */    
#define LOOPTIME_SEC                                  0.00005f
    
/** Motor Parameters */

/* Enter the Rated Current(A) of the Motor */  
#define RATED_CURRENT             3.4f
/* Enter the Minimum speed (RPM) for the motor to run in speed control loop */
#define MINIMUM_SPEED_RPM         50 
/* Enter the Nominal(Rated) speed (RPM) for the motor to run in speed control loop */
#define NOMINAL_SPEED_RPM         1800 
/* Enter the Maximum speed (RPM) for the motor to run in Phase Advance mode of speed control loop */
#define MAXIMUM_SPEED_RPM         1800 

/* Maximum phase current(A) threshold for fault detection */  
#define PHASE_OC_THRESHOLD        3.5f
/* Enter the Minimum DC link voltage(V) required to run the motor*/    
#define MOTOR_MIN_DC_VOLT         100
/* Enter the Maximum DC link voltage(V) required to run the motor*/  
#define MOTOR_MAX_DC_VOLT         250 
    
/* Motor control parameters */   
/* Motor control angle(degree), total commutation angle */ 
#define CRTL_THETA         60
/* Theta in degrees for Clockwise rotation */
/* Note - The angle Theta should be added in ascending order, followed by the phase sequence.*/    

/* Enter the Theta 1 phase for commutation */
#define THETA_1_COMMUTATE_CW    PHASEA_COMMUTATION
/* Enter the commutation Turn-On and Turn-Off angles for Theta 1 */
#define THETA_1_ON_CW      1   /* Turn-On  theta in degree */
#define THETA_1_OFF_CW     17  /* Turn-Off theta in degree */
/* Enter the Bootstrap capacitor to be charged for Theta 1 phase commutation */
#define THETA_1_CBOOT_CW   PHASEB_CBOOT 
    
/* Enter the Theta 2 phase for commutation */
#define THETA_2_COMMUTATE_CW    PHASEB_COMMUTATION
/* Enter the commutation Turn-On and Turn-Off angles for Theta 2 */
#define THETA_2_ON_CW      17   /* Turn-On  theta in degree */
#define THETA_2_OFF_CW     34   /* Turn-Off theta in degree */
/* Enter the Bootstrap capacitor to be charged for Theta 2 phase commutation */
#define THETA_2_CBOOT_CW   PHASEC_CBOOT 
    
/* Enter the Theta 3 phase for commutation */
#define THETA_3_COMMUTATE_CW    PHASEC_COMMUTATION
/* Enter the commutation Turn-On and Turn-Off angles for Theta 3 */
#define THETA_3_ON_CW      34   /* Turn-On  theta in degree */
#define THETA_3_OFF_CW     45   /* Turn-Off theta in degree */
/* Enter the Bootstrap capacitor to be charged for Theta 3 phase commutation */
#define THETA_3_CBOOT_CW   PHASED_CBOOT
    
/* Enter the Theta 4 phase for commutation */
#define THETA_4_COMMUTATE_CW    PHASED_COMMUTATION
/* Enter the commutation Turn-On and Turn-Off angles for Theta 4 */
#define THETA_4_ON_CW      45   /* Turn-On  theta in degree */
#define THETA_4_OFF_CW     1    /* Turn-Off theta in degree */
/* Enter the Bootstrap capacitor to be charged for Theta 4 phase commutation */
#define THETA_4_CBOOT_CW   PHASEA_CBOOT    

/* Theta in degrees for Counter Clockwise rotation */
/* Note - The angle Theta should be added in deascending order, followed by the phase sequence.*/    

/* Enter the Theta 1 phase for commutation */
#define THETA_1_COMMUTATE_CCW    PHASEA_COMMUTATION
/* Enter the commutation Turn-On and Turn-Off angles for Theta 1 */
#define THETA_1_ON_CCW      50   /* Turn-On  theta in degree */
#define THETA_1_OFF_CCW     33   /* Turn-Off theta in degree */
/* Enter the Bootstrap capacitor to be charged for Theta 1 phase commutation */
#define THETA_1_CBOOT_CCW   PHASED_CBOOT 
    
/* Enter the Theta 2 phase for commutation */
#define THETA_2_COMMUTATE_CCW    PHASED_COMMUTATION
/* Enter the commutation Turn-On and Turn-Off angles for Theta 2 */
#define THETA_2_ON_CCW      33   /* Turn-On  theta in degree */
#define THETA_2_OFF_CCW     22   /* Turn-Off theta in degree */
/* Enter the Bootstrap capacitor to be charged for Theta 2 phase commutation */
#define THETA_2_CBOOT_CCW   PHASEC_CBOOT 
    
/* Enter the Theta 3 phase for commutation */
#define THETA_3_COMMUTATE_CCW    PHASEC_COMMUTATION
/* Enter the commutation Turn-On and Turn-Off angles for Theta 3 */
#define THETA_3_ON_CCW      22   /* Turn-On  theta in degree */
#define THETA_3_OFF_CCW     7    /* Turn-Off theta in degree */
/* Enter the Bootstrap capacitor to be charged for Theta 3 phase commutation */
#define THETA_3_CBOOT_CCW   PHASEB_CBOOT
    
/* Enter the Theta 4 phase for commutation */
#define THETA_4_COMMUTATE_CCW    PHASEB_COMMUTATION
/* Enter the commutation Turn-On and Turn-Off angles for Theta 4 */
#define THETA_4_ON_CCW      7    /* Turn-On  theta in degree */
#define THETA_4_OFF_CCW     50   /* Turn-Off theta in degree */
/* Enter the Bootstrap capacitor to be charged for Theta 4 phase commutation */
#define THETA_4_CBOOT_CCW   PHASEA_CBOOT   

/** SPEED CONTROL **/  
/* Sampling time for the speed control */
#define SPEED_CRTL_RATE     19
/** CURRENT CONTROL */
/* Enter the Maximum reference Current (A) for Current control mode */    
#define MAXIMUM_REF_CURRENT 0.8f 
    
// </editor-fold>

// <editor-fold defaultstate="expanded" desc="DEFINITIONS/CONSTANTS ">    

/* Hysteresis Current Controller (HCC) */
/* Enter the value for Tolerance band that follows the reference current with its phase */
#define HCC_BETA             0.005f
    
/* Velocity Control Loop - PI Coefficients */
#define SPEEDCNTR_PTERM                               0.01f
#define SPEEDCNTR_ITERM                               0.00005f
#define SPEEDCNTR_CTERM                               1.0
#define SPEEDCNTR_OUTMAX                              RATED_CURRENT
#define SPEEDCNTR_OUTMIN                              0.05f

// </editor-fold>

// <editor-fold defaultstate="expanded" desc="ENUMERATED CONSTANTS ">

typedef enum
{
    PHASEA_CBOOT = 1,   /* Bootstrap capacitor charging for Phase A */
    PHASEB_CBOOT = 2,   /* Bootstrap capacitor charging for Phase B */
    PHASEC_CBOOT = 3,   /* Bootstrap capacitor charging for Phase C */
    PHASED_CBOOT = 4,   /* Bootstrap capacitor charging for Phase D */
}MCAPP_SRM_CBOOT_ON_T;

typedef enum
{
    PHASEA_COMMUTATION = 1,   /* Commutate current in phase A */
    PHASEB_COMMUTATION = 2,   /* Commutate current in phase B */
    PHASEC_COMMUTATION = 3,   /* Commutate current in phase C */
    PHASED_COMMUTATION = 4,   /* Commutate current in phase D */ 
}MCAPP_SRM_PHASE_T;
// </editor-fold>
#ifdef __cplusplus
}
#endif

#endif	/* end of __MC1_USER_PARAMS_H */

