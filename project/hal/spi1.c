// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file spi.c
 *
 * @brief This module configures and enables the SPI Module 
 * 
 * Definitions in this file are for dsPIC33AK128MC106
 *
 * Component: SPI
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

#ifdef __XC16__  // See comments at the top of this header file
    #include <xc.h>
#endif // __XC16__

#include <stdint.h>
#include <stdbool.h>
#include "spi1.h"

// </editor-fold> 

// <editor-fold defaultstate="collapsed" desc="FUNCTION DECLARATIONS ">

/**
* <B> Function: SPI1_Initialize() </B>
*
* @brief Function to configure SPI peripheral.
*        
* @param none.
* @return none.
* 
* @example
* <CODE> SPI1_Initialize(); </CODE>
*
*/
void SPI1_Initialize (void)
{
    SPI1CON1 = 0;
    SPI1CON1bits.FRMSYPW = 1;
    SPI1CON1bits.DISSDO = 1;
    SPI1CON1bits.MODE32 = 1;
    SPI1CON1bits.CKP = 1;
    SPI1CON1bits.MSTEN = 1;
    SPI1CON1bits.ENHBUF = 1;
    
    SPI1CON2 = 0;
    SPI1CON2bits.WLENGTH = 25;
    SPI1STAT = 0;
    SPI1BRG = 12;       // 50 / 13 = 3.84MHz
    SPI1IMSK = 0;
    SPI1URDT = 0;
   
    SPI1CON1bits.ON = 1;
}

/**
* <B> Function: SPI1_WordExchange() </B>
*
* @brief Function for SPI word exchange.
*        
* @param none.
* @return none.
* 
* @example
* <CODE> SPI1_WordExchange(); </CODE>
*
*/
uint32_t SPI1_WordExchange(uint32_t wordData)
{
    uint32_t ret;
    SPI1BUF = wordData;
    while(SPI1STATbits.SPIRBF == 0);
    ret = SPI1BUF; /* Read SPIRBF */
    return(ret);
}

// </editor-fold> 

/**
 End of File
*/

