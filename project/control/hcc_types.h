// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file hcc.c
 *
 * @brief This header file lists data type of the HCC controller module
 *
 * Component: HCC CONTROLLER
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

#ifndef HCC_TYPES_H
#define	HCC_TYPES_H

#ifdef	__cplusplus
extern "C" {
#endif

// <editor-fold defaultstate="collapsed" desc="TYPE DEFINITIONS ">
    
/**
 * HCC Controller State data type
*/
typedef struct
{
    float 
    beta,/** Tolerance band that follows the reference current with its phase */
    currentUpperLimit,
    currentLowerLimit;
} MCAPP_HCCSTATE_T;
/**
 * HCC Controller Input data type
*/
typedef struct
{
    /** HCC state as input parameter to the HCC controller */
    MCAPP_HCCSTATE_T hccState;
    float 
        currentReference,
        currentActual;               
}MCAPP_HCCPARMIN_T;

/**
 * HCC Controller Output data type
*/
typedef struct
{
    /** Output of the HCC controller */
    bool out;
} MCAPP_HCCPARMOUT_T;    
// </editor-fold>
#ifdef	__cplusplus
}
#endif

#endif	/* HCC_TYPES_H */

