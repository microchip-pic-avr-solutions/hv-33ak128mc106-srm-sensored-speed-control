// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file port_config.c
 *
 * @brief This module initializes the GPIO pins as analog/digital,input or 
 * output etc. Also to PPS functionality to Re-mappable input or output pins.
 * 
 * Definitions in this file are for dsPIC33AK128MC106
 *
 * Component: PORTS
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

#include "port_config.h"

// </editor-fold>

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">

/**
* <B> Function: SetupGPIOPorts() </B>
*
* @brief Function initialize all ports as input and digital pins
*        
* @param none.
* @return none.
* 
* @example
* <CODE> SetupGPIOPorts(); </CODE>
*
*/
void SetupGPIOPorts(void)
{
    /* Reset all PORTx register (all inputs) */
    
    #ifdef TRISA
        TRISA = 0xFFFF;
        LATA  = 0x0000;
    #endif
    #ifdef ANSELA
        ANSELA = 0x0000;
    #endif

    #ifdef TRISB
        TRISB = 0xFFFF;
        LATB  = 0x0000;
    #endif
    #ifdef ANSELB
        ANSELB = 0x0000;
    #endif

    #ifdef TRISC
        TRISC = 0xFFFF;
        LATC  = 0x0000;
    #endif
    #ifdef ANSELC
        ANSELC = 0x0000;
    #endif

    #ifdef TRISD
        TRISD = 0xFFFF;
        LATD  = 0x0000;
    #endif
    #ifdef ANSELD
        ANSELD = 0x0000;
    #endif

    MapGPIOHWFunction();

}
/**
* <B> Function: MapGPIOHWFunction() </B>
*
* @brief Function maps port pins as input or output, analog or digital
*        
* @param none.
* @return none.
* 
* @example
* <CODE> MapGPIOHWFunction(); </CODE>
*
*/
void MapGPIOHWFunction(void)
{  
    /* Current measurements */
    /* External amplifier inputs */
    /* M1_IA_EXT             PIN12: OA1OUT/AD1AN0/CMP1A/RP2/RA2  */
    ANSELAbits.ANSELA2 = 1;
    TRISAbits.TRISA2 = 1;   
    /* M1_IB_EXT             PIN20: OA2OUT/AD2AN1/CMP2A/RP16/RB0 */
    ANSELBbits.ANSELB0 = 1;
    TRISBbits.TRISB0 = 1;   
    /* M1_IC_EXT             PIN7: AD2AN9/ISRC3/IBIAS3/RP9/RA8   */
    ANSELAbits.ANSELA8 = 1;
    TRISAbits.TRISA8 = 1;   
    /* M1_ID_EXT             PIN15: OA3OUT/AD1AN3/CMP3A/RP5/INT0/RA5 */
    ANSELAbits.ANSELA5 = 1;
    TRISAbits.TRISA5 = 1; 
    /* M1_IBUS_EXT           PIN30: AD2ANN2/AD2AN8/RP24/IOMF0/RB7 */
    ANSELBbits.ANSELB7 = 1;
    TRISBbits.TRISB7 = 1;   
    
    /* Potentiometer  input - used as Speed Reference */
    /* POT1                  PIN06: AD1AN10/RP11/RA11 */
    ANSELAbits.ANSELA11 = 1;
    TRISAbits.TRISA11 = 1;   // 
    
    /* Voltage measurements */
    /* VBUS                  PIN02: AD1AN6/RP7/IOMONF1/RA7 */
    ANSELAbits.ANSELA7 = 1;
    TRISAbits.TRISA7 = 1;   
    /* M1_VA                 PIN24: AD2AN10/RP26/RB9 */
    ANSELBbits.ANSELB9 = 1;
    TRISBbits.TRISB9 = 1;  
    /* M1_VB                 PIN23: AD1AN11/RP25/RB8 */
    ANSELBbits.ANSELB8 = 1;
    TRISBbits.TRISB8 = 1;   
    /* M1_VC                 PIN09: AD2ANN3/AD2AN7/RP11/RA10 */
    ANSELAbits.ANSELA10 = 1;
    TRISAbits.TRISA10 = 1;    
    /* M1_VD                 PIN29: AD1ANN2/AD1AN8/RP23/RB6 */
    ANSELBbits.ANSELB6 = 1;
    TRISBbits.TRISB6 = 1;    
    
    /* Digital SIGNALS */   
    /* DIGITAL INPUT/OUTPUT PINS */

    /* Inverter Control - PWM Outputs
       PWM1L : PIN #54  TDI/RP51/PWM1L/IOMOND5/RD3
       PWM1H : PIN #53  TDO/RP50/PWM1H/IOMOND4/RD2
       PWM2L : PIN #52  TCK/RP49/PWM2L/IOMOND3/RD1
       PWM2H : PIN #51  RP48/PWM2H/IOMOND2/RD0
       PWM3L : PIN #44  RP36/PWM3L/IOMOND1/RC4
       PWM3H : PIN #43  PGED3/RP35/PWM3H/IOMOND0/RC3
       PWM4L : PIN #42  RP38/PWM4L/RC5
       PWM4H : PIN #41  PGEC3/RP35/PWM4H/RC2 */
    TRISDbits.TRISD3 = 0 ;          
    TRISDbits.TRISD2 = 0 ;         
    TRISDbits.TRISD1 = 0 ;          
    TRISDbits.TRISD0 = 0 ;           
    TRISCbits.TRISC4 = 0 ;          
    TRISCbits.TRISC3 = 0 ;  
    TRISCbits.TRISC5 = 0 ;
    TRISCbits.TRISC2 = 0 ;
     
    /* Debug LEDs */
    /* LED1                  PIN30: RP54/ASCL1/RD5 */
    TRISDbits.TRISD5 = 0;
    /* LED2                  PIN32: RP42/IOMD10/SDO2/IOMF10/PCI19/RC9 */
    TRISCbits.TRISC9 = 0;

    /* Push button Switches */
    /* SW1                   PIN:49 - RP57/IOMONF7/RD9 */
    TRISDbits.TRISD9 = 1;             
    /* SW2 :                 PIN:50 - RP58/RD10 */
    TRISDbits.TRISD10 = 1;            
    
    /* Configuring M1_FAULT1 (DIM:040) - Pin #32 :  RP28/SDI2/RB11 as PCI9 */
    _PCI9R = 28;            /* Fault1 is combined signal for OV/OC fault */
    /* Configuring M1_FAULT2 (DIM:041) - Pin #31 :  RP27/SCK2/RB10 as PCI10 */
    _PCI10R = 27;            /* Fault2 is combined signal for OC fault 
                                from Allegro current sensor */
    
    /* SPI1 pin configurations */
    /* SPI1 CLK              PIN56: RP55/ASDA1/RD6 */
    TRISDbits.TRISD6 = 0;   /* DIM112: RD6 as Output port */
    RPOR13bits.RP55R = 14;  /* RD6 - SPI CLK */
    /* SPI1 SDI              PIN57:  RP56/ASCL2/IOMD7/IOMF4/RD7 */
    TRISDbits.TRISD7 = 1;   /* DIM110: RD7 as Input port */
    RPINR10bits.SDI1R = 56; /* RD7 - SPI Data In */
    
	/** Diagnostic Interface
        Re-map UART Channels to the device pins connected to the following 
        pins on the Motor Control Development Board.
        UART_RX : DIM:054 - PIN #46 : RP44/IOMD8/IOMF8/RC11 (Input)
        UART_TX : DIM:052 - PIN #45 : RP43/IOMD9/IOMF9/RC10(Output)   */
    
    _U1RXR = 44;
    _RP43R = 9;
    
}
/**
* <B> Function: OpampConfig() </B>
*
* @brief Function to configure and enable the Op-Amp Module
*        
* @param none.
* @return none.
* 
* @example
* <CODE> OpampConfig(); </CODE>
*
*/
void OpampConfig (void)
{
    /** AMPxCON1 :AMPx Control Register 1*/
    AMP1CON1 = 0x0000;
    /** Bit 15 = AMPEN Op Amp Enable/On bit 
        1 Enables op amp module ; 
        0 Disables op amp module */
    AMP1CON1bits.AMPEN = 0;
    /** Bit 14 = HPEN High-Power Enable bit  
        1 Enables Op Amp High-Power (high bandwidth) mode ; 
        0 Disables Op Amp High-Power mode */    
    AMP1CON1bits.HPEN = 0;
    /** Bit 13 = UGE Unity Gain Buffer Enable bit 
        1 Enables Unity Gain mode ; 
        0 Disables Unity Gain mode */
    AMP1CON1bits.UGE = 0;
    /** Bits 12:11 = DIFFCON[1:0] Differential Input Mode Control bits
        11 Reserved, do not use; 
        10 Turn NMOS differential input pair off
        01 Turn PMOS differential input pair off 
        00 Use both NMOS and PMOS differential input pair */
    AMP1CON1bits.DIFFCON = 0;
    /** Bit 9 = IMONEN Enable Input Monitor bit
        1 Enables positive input to ADC ; 
        0 Disables positive input to ADC */    
    AMP1CON1bits.IMONEN = 0;
    /** Bit 8 = OMONEN Enable Output Monitor bit
        1 Enables output to ADC; 
        0 Disables output to ADC */     
    AMP1CON1bits.OMONEN = 1;
    
    /** AMPxCON1 :AMPx Control Register 1*/
    AMP2CON1 = 0x0000;
    /** Bit 15 = AMPEN Op Amp Enable/On bit 
        1 Enables op amp module ; 
        0 Disables op amp module */
    AMP2CON1bits.AMPEN = 0;
    /** Bit 14 = HPEN High-Power Enable bit  
        1 Enables Op Amp High-Power (high bandwidth) mode ; 
        0 Disables Op Amp High-Power mode */    
    AMP2CON1bits.HPEN = 0;
    /** Bit 13 = UGE Unity Gain Buffer Enable bit 
        1 Enables Unity Gain mode ; 
        0 Disables Unity Gain mode */
    AMP2CON1bits.UGE = 0;
    /** Bits 12:11 = DIFFCON[1:0] Differential Input Mode Control bits
        11 Reserved, do not use; 
        10 Turn NMOS differential input pair off
        01 Turn PMOS differential input pair off 
        00 Use both NMOS and PMOS differential input pair */
    AMP2CON1bits.DIFFCON = 0;
    /** Bit 9 = IMONEN Enable Input Monitor bit
        1 Enables positive input to ADC ; 
        0 Disables positive input to ADC */    
    AMP2CON1bits.IMONEN = 0;
    /** Bit 8 = OMONEN Enable Output Monitor bit
        1 Enables output to ADC; 
        0 Disables output to ADC */     
    AMP2CON1bits.OMONEN = 1;
    
    /** AMPxCON1 :AMPx Control Register 1*/
    AMP2CON1 = 0x0000;
    /** Bit 15 = AMPEN Op Amp Enable/On bit 
        1 Enables op amp module ; 
        0 Disables op amp module */
    AMP2CON1bits.AMPEN = 0;
    /** Bit 14 = HPEN High-Power Enable bit  
        1 Enables Op Amp High-Power (high bandwidth) mode ; 
        0 Disables Op Amp High-Power mode */    
    AMP2CON1bits.HPEN = 0;
    /** Bit 13 = UGE Unity Gain Buffer Enable bit 
        1 Enables Unity Gain mode ; 
        0 Disables Unity Gain mode */
    AMP2CON1bits.UGE = 0;
    /** Bits 12:11 = DIFFCON[1:0] Differential Input Mode Control bits
        11 Reserved, do not use; 
        10 Turn NMOS differential input pair off
        01 Turn PMOS differential input pair off 
        00 Use both NMOS and PMOS differential input pair */
    AMP2CON1bits.DIFFCON = 0;
    /** Bit 9 = IMONEN Enable Input Monitor bit
        1 Enables positive input to ADC ; 
        0 Disables positive input to ADC */    
    AMP2CON1bits.IMONEN = 0;
    /** Bit 8 = OMONEN Enable Output Monitor bit
        1 Enables output to ADC; 
        0 Disables output to ADC */     
    AMP2CON1bits.OMONEN = 1;
    
    /** AMPxCON1 :AMPx Control Register 1*/
    AMP3CON1 = 0x0000;
    /** Bit 15 = AMPEN Op Amp Enable/On bit 
        1 Enables op amp module ; 
        0 Disables op amp module */
    AMP3CON1bits.AMPEN = 0;
    /** Bit 14 = HPEN High-Power Enable bit  
        1 Enables Op Amp High-Power (high bandwidth) mode ; 
        0 Disables Op Amp High-Power mode */    
    AMP3CON1bits.HPEN = 0;
    /** Bit 13 = UGE Unity Gain Buffer Enable bit 
        1 Enables Unity Gain mode ; 
        0 Disables Unity Gain mode */
    AMP3CON1bits.UGE = 0;
    /** Bits 12:11 = DIFFCON[1:0] Differential Input Mode Control bits
        11 Reserved, do not use; 
        10 Turn NMOS differential input pair off
        01 Turn PMOS differential input pair off 
        00 Use both NMOS and PMOS differential input pair */
    AMP3CON1bits.DIFFCON = 0;
    /** Bit 9 = IMONEN Enable Input Monitor bit
        1 Enables positive input to ADC ; 
        0 Disables positive input to ADC */    
    AMP3CON1bits.IMONEN = 0;
    /** Bit 8 = OMONEN Enable Output Monitor bit
        1 Enables output to ADC; 
        0 Disables output to ADC */     
    AMP3CON1bits.OMONEN = 1;
    
    /** Bit 15 = AMPEN Op Amp Enable/On bit 
        1 Enables op amp module ; 
        0 Disables op amp module */
    AMP1CON1bits.AMPEN = 1;
    /** Bit 15 = AMPEN Op Amp Enable/On bit 
        1 Enables op amp module ; 
        0 Disables op amp module */
    AMP2CON1bits.AMPEN = 1;
    /** Bit 15 = AMPEN Op Amp Enable/On bit 
        1 Enables op amp module ; 
        0 Disables op amp module */
    AMP3CON1bits.AMPEN = 1;
}

// </editor-fold>