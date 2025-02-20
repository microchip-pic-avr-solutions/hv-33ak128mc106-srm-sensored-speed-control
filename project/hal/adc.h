// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file adc.h
 *
 * @brief This header file lists the functions and definitions - to configure 
 * and enable ADC Module and its features 
 * 
 * Definitions in this file are for dsPIC33AK128MC106
 *
 * Component: ADC
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

#ifndef _ADC_H
#define _ADC_H
        
// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">
        
#include <xc.h>
#include <stdint.h>

#include "mc1_user_params.h"
// </editor-fold>

#ifdef __cplusplus  // Provide C++ Compatability
    extern "C" {
#endif
        
// <editor-fold defaultstate="expanded" desc="DEFINITIONS/CONSTANTS ">
#ifdef ALLEGRO_CT110_CS  
#define ADCBUF_IA     (int16_t)(2048 - AD1CH0DATA)<<4
#define ADCBUF_IB     (int16_t)(2048 - AD2CH0DATA)<<4
#define ADCBUF_IC     (int16_t)(2048 - AD2CH1DATA)<<4
#define ADCBUF_ID     (int16_t)(2048 - AD1CH1DATA)<<4
        
#else     
#define ADCBUF_IA     (int16_t)(AD1CH0DATA - 2048)<<4
#define ADCBUF_IB     (int16_t)(AD2CH0DATA - 2048)<<4
#define ADCBUF_IC     (int16_t)(AD2CH1DATA - 2048)<<4
#define ADCBUF_ID     (int16_t)(AD1CH1DATA - 2048)<<4
#endif 

#define ADCBUF_VDC    (int16_t)AD1CH2DATA         
#define ADCBUF_IBUS   (int16_t)((AD2CH2DATA- 2048)<<4)     

#define ADCBUF_VA     (int16_t)AD2CH3DATA 
#define ADCBUF_VB     (int16_t)AD1CH3DATA 
#define ADCBUF_VC     (int16_t)AD2CH4DATA 
#define ADCBUF_VD     (int16_t)AD1CH4DATA 
               
#define ADCBUF_POT    (int16_t)AD1CH5DATA
/*Maximum count in 12-bit ADC*/
#define MAX_POT_COUNT  4096.0f

 /* POT (AD1CH5) is the ADC Interrupt source */
#define MC1_EnableADCInterrupt()        _AD1CH5IE = 1
#define MC1_DisableADCInterrupt()       _AD1CH5IE = 0
#define MC1_ADC_INTERRUPT               _AD1CH5Interrupt
#define MC1_ClearADCIF()                  _AD1CH5IF = 0                  
#define MC1_ClearADCIF_ReadADCBUF()     AD1CH5DATA  
// </editor-fold>
        
// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">
        
void InitializeADCs(void);

// </editor-fold>

#ifdef __cplusplus  // Provide C++ Compatibility
    }
#endif
    
#endif      // end of __ADC_H

