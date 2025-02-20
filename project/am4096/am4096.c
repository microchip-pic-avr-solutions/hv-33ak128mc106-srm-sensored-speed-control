// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * am4096.c
 *
 * This file includes subroutine to configure AM4096
 * 
 * Definitions in this file are for dsPIC33AK128MC106.
 * 
 * Component: AM4096
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

// <editor-fold defaultstate="collapsed" desc="Header Files ">

#include <xc.h>
#include <stdint.h>
#include <math.h>
#include "am4096.h"
#include "spi1.h"
#include "lpf.h"
#include "mc1_user_params.h"
// </editor-fold> 

float filterCoeff = FILTER_COEFFCIENT;

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">

/**
* <B> Function: MCAPP_AM4096magInit(&magSensor) </B>
*
* @brief Function to initialize AM4096 sensor 
*        
* @param none.
* @return none.
* 
* @example
* <CODE> MCAPP_AM4096magInit(&magSensor); </CODE>
*
*/
void MCAPP_AM4096magInit(MCAPP_AM4096_T *magSensor)
{
   magSensor->allign_offset    = am4096_align_offset;
   magSensor->resolution       = am4096_resolution;
   magSensor->lowerword_data   = 0;
   magSensor->higherword_data  = 0;
   magSensor->raw_position     = 0;
   magSensor->raw_position_comp = 0;
   magSensor->__builtin_sinf = 0;
   magSensor->__builtin_cosf = 0;
   magSensor->sin_prev = 0;
   magSensor->cos_prev = 0;
   magSensor->theta = 0;
   magSensor->speed = 0;
}

 /**
* <B> Function: MCAPP_AM4096magRead(&magSensor) </B>
*
* @brief Function to read AM4096 sensor data
*        
* @param none.
* @return none.
* 
* @example
* <CODE> MCAPP_AM4096magRead(&magSensor); </CODE>
*
*/
void MCAPP_AM4096magRead(MCAPP_AM4096_T *magSensor)
{
    uint32_t        recieve_data = 0; 
    recieve_data = SPI1_WordExchange(SPI_DUMMY_DATA);
    magSensor->lowerword_data   = (uint32_t)(recieve_data&0x0FFF);
    magSensor->higherword_data  = (uint32_t)((recieve_data>>13)&0x0FFF);
    /* Check if the data received is correct */
    if(magSensor->lowerword_data == magSensor->higherword_data)
    {
       magSensor->raw_position  =  magSensor->lowerword_data;
       magSensor->raw_position_comp = (magSensor->raw_position + magSensor->allign_offset)&magSensor->resolution; 
    }
    else
    {
        magSensor->raw_position_comp = magSensor->raw_position_comp;
    }
    /* Convert sensor output to theta in radians */
    magSensor->theta = (float) ((float) (magSensor->raw_position_comp * ((float) 2 * M_PI)) / am4096_resolution);
    /* Speed measurement*/
    magSensor->speedBuffer = (cos (magSensor->theta)*(sin(magSensor->theta) - magSensor->sin_prev))/LOOPTIME_SEC - (sin(magSensor->theta)*(cos(magSensor->theta) - magSensor->cos_prev))/LOOPTIME_SEC;
    LowPassFilter(magSensor->speedBuffer,filterCoeff,&magSensor->speedFilter);
    magSensor->speed = fabsf((float) (magSensor->speedFilter * ((float) ( (float) 60 / (2 * M_PI)))));
    magSensor->sin_prev = sin(magSensor->theta);
    magSensor->cos_prev = cos(magSensor->theta);   
}

// </editor-fold> 
