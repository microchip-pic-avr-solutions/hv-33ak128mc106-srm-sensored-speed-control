// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file adc.c
 *
 * @brief This module configures and enables the ADC Module 
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

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">

#include <xc.h>
#include <stdint.h>

#include "adc.h"

// </editor-fold>

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">
/**
* <B> Function: InitializeADCs() </B>
*
* @brief Function initializes and enable the ADC Module
*        
* @param none.
* @return none.
* 
* @example
* <CODE> InitializeADCs(); </CODE>
*
*/
void InitializeADCs(void)
{
    /* Channel Configuration for IA*/
    /*ADC1 Channel 0 for IA : OA1OUT/AD1AN0/CMP1A/RP3/RA2 */
    AD1CH0CONbits.PINSEL = 0;       
    AD1CH0CONbits.SAMC = 3;         
    AD1CH0CONbits.LEFT = 0;
    AD1CH0CONbits.DIFF = 0;

    /* Channel Configuration for IB*/
    /*ADC2 Channel 0 for IB : OA2OUT/AD2AN1/CMP2A/RP17/INT0/RB0 */    
    AD2CH0CONbits.PINSEL = 1;      
    AD2CH0CONbits.SAMC = 3;        
    AD2CH0CONbits.LEFT = 0;
    AD2CH0CONbits.DIFF = 0;
    
    /* Channel Configuration for IC*/
    /*ADC2 Channel 1 for IC : AD2AN9/ISRC3/IBIAS3/RP9/RA8 */    
    AD2CH1CONbits.PINSEL = 9;      
    AD2CH1CONbits.SAMC = 3;        
    AD2CH1CONbits.LEFT = 0;
    AD2CH1CONbits.DIFF = 0;
    
    /* Channel Configuration for ID*/
    /*ADC1 Channel 1 for ID : OA3OUT/AD1AN3/CMP3A/RP6/RA5 */ 
    AD1CH1CONbits.PINSEL = 3;      
    AD1CH1CONbits.SAMC = 3;      
    AD1CH1CONbits.LEFT = 0;
    AD1CH1CONbits.DIFF = 0;
    
    /* Channel Configuration for VBUS*/
    /*ADC1 Channel 2 for VBUS : AD1AN6/RP8/IOMF1/RA7 */ 
    AD1CH2CONbits.PINSEL = 6;        
    AD1CH2CONbits.SAMC = 1;         
    AD1CH2CONbits.LEFT = 0;
    AD1CH2CONbits.DIFF = 0;
    
    /* Channel Configuration for IBUS*/
    /*ADC2 Channel 2 for IBUS : AD2ANN2/AD2AN8/RP24/IOMF0/RB7 */ 
    AD2CH2CONbits.PINSEL = 8;      
    AD2CH2CONbits.SAMC = 1;      
    AD2CH2CONbits.LEFT = 0;
    AD2CH2CONbits.DIFF = 0;

    /* Channel Configuration for VA*/
    /*ADC2 Channel 3 for VA : AD2AN10/RP26/RB9 */ 
    AD2CH3CONbits.PINSEL = 10;        
    AD2CH3CONbits.SAMC = 1;         
    AD2CH3CONbits.LEFT = 0;
    AD2CH3CONbits.DIFF = 0; 
    
    /* Channel Configuration for VB*/
    /*ADC1 Channel 3 for VB : AD1AN11/RP25/RB8 */ 
    AD1CH3CONbits.PINSEL = 11;      
    AD1CH3CONbits.SAMC = 1;      
    AD1CH3CONbits.LEFT = 0;
    AD1CH3CONbits.DIFF = 0;
    
    /* Channel Configuration for VC*/
    /*ADC2 Channel 4 for VC : AD2ANN3/AD2AN7/RP11/RA10 */ 
    AD2CH4CONbits.PINSEL = 7;        
    AD2CH4CONbits.SAMC = 1;         
    AD2CH4CONbits.LEFT = 0;
    AD2CH4CONbits.DIFF = 0; 
    
    /* Channel Configuration for VD*/
    /*ADC1 Channel 4 for VD : AD1ANN2/AD1AN8/RP23/RB6 */ 
    AD1CH4CONbits.PINSEL = 8;        
    AD1CH4CONbits.SAMC = 1;         
    AD1CH4CONbits.LEFT = 0;
    AD1CH4CONbits.DIFF = 0; 
    
    /* Channel Configuration for POT*/
    /*ADC1 Channel 5 for POT : AD1AN10/RP12/RA11 */     
    AD1CH5CONbits.PINSEL = 10;      
    AD1CH5CONbits.SAMC = 2;         
    AD1CH5CONbits.LEFT = 0;
    AD1CH5CONbits.DIFF = 0;

    /* Turn on the ADC Core 1 */   
    AD1CONbits.ON = 1;     
    /* Waiting till the ADC Core 1 is ready*/
    while(AD1CONbits.ADRDY == 0);  
    
    /* Turn on the ADC Core 2 */
    AD2CONbits.ON = 1;             
    /* Waiting till the ADC Core 2 is ready*/
    while(AD2CONbits.ADRDY == 0);   
    

    /*AD1CH1 - POT used for ADC Interrupt */
    /* Set ADC interrupt priority IPL 7  */ 
    _AD1CH5IP = 7;
    /* Clear ADC interrupt flag */
    _AD1CH5IF = 0;
    /* Disable the AD1CH1 interrupt  */
    _AD1CH5IE = 0;

    
    /*Selecting the Trigger Sources for ADC Channels*/  

    /*PWM1 ADC Trigger 1 for IA - AD1CH0*/
    AD1CH0CONbits.TRG1SRC = 4;      
    /*PWM1 ADC Trigger 1 for IB - AD2CH0*/
    AD2CH0CONbits.TRG1SRC = 4; 
    /*PWM1 ADC Trigger 1 for IC - AD2CH1*/
    AD2CH1CONbits.TRG1SRC = 4;
    /*PWM1 ADC Trigger 1 for ID - AD1CH1*/
    AD1CH1CONbits.TRG1SRC = 4;
    /*PWM1 ADC Trigger 1 for VBUS - AD1CH2*/
    AD1CH2CONbits.TRG1SRC = 4;
    /*PWM1 ADC Trigger 1 for IBUS - AD2CH2*/
    AD2CH2CONbits.TRG1SRC = 4;
    /*PWM1 ADC Trigger 1 for VA - AD2CH3*/
    AD2CH3CONbits.TRG1SRC = 4;
    /*PWM1 ADC Trigger 1 for VB - AD1CH3*/
    AD1CH3CONbits.TRG1SRC = 4;
    /*PWM1 ADC Trigger 1 for VC - AD2CH4*/
    AD2CH4CONbits.TRG1SRC = 4;
    /*PWM1 ADC Trigger 1 for VD - AD1CH4*/
    AD1CH4CONbits.TRG1SRC = 4;
    
    /*PWM1 ADC Trigger 1 for POT - AD1CH5*/
    AD1CH5CONbits.TRG1SRC = 4;      

}

// </editor-fold>