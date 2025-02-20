// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file am4096_types.h
 *
 * @brief This module initializes data structure variable type definitions of 
 * am4096 structure and enumerations
 * 
 * 
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

#ifndef AM4096_TYPES_H
#define	AM4096_TYPES_H

#ifdef	__cplusplus
extern "C" {
#endif

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">
#include <stdint.h>
#include <stdbool.h>
  
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="VARIABLE TYPE DEFINITIONS ">
typedef struct
{
    uint32_t
        allign_offset,  /* Alignment offset */
        resolution,     /* Resolution of am4096 Sensor */  
        lowerword_data, /* Position from SPI Lower Buffer */
        higherword_data,/* Position from SPI High Buffer */
        raw_position,   /* Raw position data from magnetic sensor */
        raw_position_comp,/* Estimated rotor angle after offset compensation */
        timerValue;     /* Variable to read timer value */
    float
        sin,            /* Sine component of calculated rotor angle */
        sin_prev,       /* Previous Values of Sine component of calculated rotor angle */
        cos,            /* Cosine component of calculated rotor angle */
        cos_prev,       /* Previous Values of Cosine component of calculated rotor angle */
        theta,          /* Theta from rotor angle in radians 0 to 2pi */
        speedBuffer,    /* Buffer for estimated Velocity */
        speedFilter,    /* Filter speed ouput */
        speed;          /* Estimated Velocity in rpm */
           
}MCAPP_AM4096_T;    
// </editor-fold>    
#ifdef	__cplusplus
}
#endif

#endif	/* AM4096_TYPES_H */

