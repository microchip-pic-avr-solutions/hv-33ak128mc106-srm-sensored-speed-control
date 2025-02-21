// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file board_service.c
 *
 * @brief This module implements the board service routines 
 * 
 * Definitions in this file are for dsPIC33AK128MC106
 *
 * Component: BOARD SERVICE
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
#include <stdbool.h>

#include "board_service.h"
#include "mc1_user_params.h"

#include "spi1.h"

#include "delay.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="VARIABLES">
BUTTON_T buttonStartStop;
BUTTON_T buttonChangeDirection;

uint16_t boardServiceISRCounter = 0;

/* PWM Switching Array */
const uint32_t pwmCtrlState[4] = { PWM_DISABLE, PWM_FULL_ON,  PWM_HALF_ON,  CHG_BOOT_CAP };
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="STATIC FUNCTIONS ">

static void ButtonGroupInitialize(void);
static void ButtonScan(BUTTON_T * ,bool);

// </editor-fold>

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">
/**
* <B> Function: IsPressed_Button1() </B>
*
* @brief Function monitors the actuation of push button
*        
* @param none.
* @return boolean for button actuation.
* 
* @example
* <CODE> IsPressed_Button1(); </CODE>
*
*/
bool IsPressed_Button1(void)
{
    if (buttonStartStop.status)
    {
        buttonStartStop.status = false;
        return true;
    }
    else
    {
        return false;
    }
}

/**
* <B> Function: IsPressed_Button2() </B>
*
* @brief Function monitors the actuation of push button
*        
* @param none.
* @return boolean for button actuation.
* 
* @example
* <CODE> IsPressed_Button2(); </CODE>
*
*/
bool IsPressed_Button2(void)
{
    if (buttonChangeDirection.status)
    {
        buttonChangeDirection.status = false;
        return true;
    }
    else
    {
        return false;
    }
}

/**
* <B> Function: BoardServiceStepIsr() </B>
*
* @brief Function to increment the board service routine counter
*        
* @param none.
* @return none.
* 
* @example
* <CODE> BoardServiceStepIsr(); </CODE>
*
*/
void BoardServiceStepIsr(void)
{
    if (boardServiceISRCounter <  BOARD_SERVICE_TICK_COUNT)
    {
        boardServiceISRCounter += 1;
    }
}

/**
* <B> Function: BoardService() </B>
*
* @brief Function to reset the board service routine counter 
*        
* @param none.
* @return none.
* 
* @example
* <CODE> BoardService(); </CODE>
*
*/
void BoardService(void)
{
    if (boardServiceISRCounter ==  BOARD_SERVICE_TICK_COUNT)
    {
        /* Button scanning loop for Button 1 to start Motor A */
        ButtonScan(&buttonStartStop,BUTTON_START_STOP);

        /* Button scanning loop for SW2 to enter into filed
            weakening mode */
        ButtonScan(&buttonChangeDirection,BUTTON_SPEED_HALF_DOUBLE);

        boardServiceISRCounter = 0;
    }
}

/**
* <B> Function: BoardServiceInit() </B>
*
* @brief Function to initialize the board service routine
*        
* @param none.
* @return none.
* 
* @example
* <CODE> BoardServiceInit(); </CODE>
*
*/
void BoardServiceInit(void)
{
    ButtonGroupInitialize();
    boardServiceISRCounter = BOARD_SERVICE_TICK_COUNT;
}

/**
* <B> Function: ButtonScan() </B>
*
* @brief Function to monitor the push button actuation with de-bounce delay
*        
* @param none.
* @return none.
* 
* @example
* <CODE> ButtonScan(); </CODE>
*
*/
void ButtonScan(BUTTON_T *pButton,bool button) 
{
    if (button == true) 
    {
        if (pButton->debounceCount < BUTTON_DEBOUNCE_COUNT) 
        {
            pButton->debounceCount--;
            pButton->state = BUTTON_DEBOUNCE;
        }
    } 
    else 
    {
        if (pButton->debounceCount < BUTTON_DEBOUNCE_COUNT) 
        {
            pButton->state = BUTTON_NOT_PRESSED;
        } 
        else 
        {
            pButton->state = BUTTON_PRESSED;
            pButton->status = true;
        }
        pButton->debounceCount = 0;
    }
}

/**
* <B> Function: ButtonGroupInitialize() </B>
*
* @brief Function to initialize the push button states
*        
* @param none.
* @return none.
* 
* @example
* <CODE> ButtonGroupInitialize(); </CODE>
*
*/
void ButtonGroupInitialize(void)
{
    buttonStartStop.state = BUTTON_NOT_PRESSED;
    buttonStartStop.debounceCount = 0;
    buttonStartStop.state = false;

    buttonChangeDirection.state = BUTTON_NOT_PRESSED;
    buttonChangeDirection.debounceCount = 0;
    buttonChangeDirection.state = false;

}

/**
* <B> Function: InitPeripherals() </B>
*
* @brief Function to initialize the peripherals(Op-Amp, ADC and PMW)
*        
* @param none.
* @return none.
* 
* @example
* <CODE> InitPeripherals(); </CODE>
*
*/
void HAL_InitPeripherals(void)
{
    __delay_ms(400);
    InitializeADCs();
    
    InitPWMGenerators(); 
    
    /*Clearing and enabling PWM Interrupt to handle PCI Fault*/
    ClearPWMIF();
    EnablePWMIF();
    
    TIMER1_Initialize();
    TIMER1_InputClockSet();
    TIMER1_PeriodSet(TIMER1_PERIOD_COUNT);
    TIMER1_InterruptPrioritySet(5);
    TIMER1_InterruptFlagClear();
    TIMER1_InterruptEnable(); 
    TIMER1_ModuleStart();
    
    SPI1_Initialize();
    /* Make sure ADC does not generate interrupt while initializing parameters*/
    MC1_DisableADCInterrupt();  
}

void HAL_ResetPeripherals(void)
{
	   
    MC1_ClearADCIF_ReadADCBUF();
    MC1_ClearADCIF();
    MC1_EnableADCInterrupt();
    HAL_MC1PWMDisableOutputs();
}

/**
* <B> Function: HAL_MC1PWMEnableOutputs() </B>
*
* @brief Function to enable the PWM outputs by disabling the override feature
*        
* @param none.
* @return none.
* 
* @example
* <CODE> HAL_MC1PWMEnableOutputs(); </CODE>
*
*/
void HAL_MC1PWMEnableOutputs(void)
{   
    /* Set PWM Duty Cycles */
    MC1_PWM_PDC4 = 0;
    MC1_PWM_PDC3 = 0;
    MC1_PWM_PDC2 = 0;
    MC1_PWM_PDC1 = 0;
    
    /*  0 = PWM Generator provides data for the PWM4H pin */
    PG4IOCONbits.OVRENH = 0; 
    /*  0 = PWM Generator provides data for the PWM4L pin */
    PG4IOCONbits.OVRENL = 0;
    
    /*  0 = PWM Generator provides data for the PWM3H pin */
    PG3IOCONbits.OVRENH = 0; 
    /*  0 = PWM Generator provides data for the PWM3L pin */
    PG3IOCONbits.OVRENL = 0; 
    
    /*  0 = PWM Generator provides data for the PWM2H pin */
    PG2IOCONbits.OVRENH = 0;
    /*  0 = PWM Generator provides data for the PWM2L pin */
    PG2IOCONbits.OVRENL = 0; 
    
    /*  0 = PWM Generator provides data for the PWM1H pin */
    PG1IOCONbits.OVRENH = 0;  
    /*  0 = PWM Generator provides data for the PWM1L pin */
    PG1IOCONbits.OVRENL = 0;     
}

/**
* <B> Function: HAL_MC1PWMDisableOutputs() </B>
*
* @brief Function to disable the PWM outputs by overriding to zero
*        
* @param none.
* @return none.
* 
* @example
* <CODE> HAL_MC1PWMDisableOutputs(); </CODE>
*
*/

void HAL_MC1PWMDisableOutputs(void)
{
    /* Set PWM Duty Cycles */
    MC1_PWM_PDC4 = 0;
    MC1_PWM_PDC3 = 0;
    MC1_PWM_PDC2 = 0;
    MC1_PWM_PDC1 = 0;
    
    /** Set Override Data on all PWM outputs */
    /* 0b00 = State for PWM4H,L, if Override is Enabled */
    PG4IOCONbits.OVRDAT = 0;
    /* 0b00 = State for PWM3H,L, if Override is Enabled */
    PG3IOCONbits.OVRDAT = 0;
    /* 0b00 = State for PWM2H,L, if Override is Enabled */
    PG2IOCONbits.OVRDAT = 0; 
    /* 0b00 = State for PWM1H,L, if Override is Enabled */
    PG1IOCONbits.OVRDAT = 0;  
    
    /* 1 = OVRDAT<1> provides data for output on PWM3H */
    PG4IOCONbits.OVRENH = 1; 
    /* 1 = OVRDAT<0> provides data for output on PWM3L */
    PG4IOCONbits.OVRENL = 1; 

    /* 1 = OVRDAT<1> provides data for output on PWM3H */
    PG3IOCONbits.OVRENH = 1; 
    /* 1 = OVRDAT<0> provides data for output on PWM3L */
    PG3IOCONbits.OVRENL = 1; 
    
    /* 1 = OVRDAT<1> provides data for output on PWM2H */
    PG2IOCONbits.OVRENH = 1;
    /* 1 = OVRDAT<0> provides data for output on PWM2L */
    PG2IOCONbits.OVRENL = 1; 
    
    /* 1 = OVRDAT<1> provides data for output on PWM1H */
    PG1IOCONbits.OVRENH = 1;  
    /* 1 = OVRDAT<0> provides data for output on PWM1L */
    PG1IOCONbits.OVRENL = 1;     
}

/**
 * Writes four unique duty cycle values to the PWM duty cycle registers
 * corresponding to Motor #1.
 * Summary: Writes to the PWM duty cycle registers corresponding to Motor #1.
 * @param pdc Pointer to the array that holds duty cycle values
 * @example
 * <code>
 * HAL_PwmSetDutyCycles_Motor1(&pdcMotor1);
 * </code>
 */
void HAL_MC1PWMSetDutyCycles(MC_DUTYCYCLEOUT_T *pdc)
{
    
    pdc->dutycycle1 = (float)pdc->pwmduty;
    pdc->dutycycle2 = pdc->pwmduty;
    pdc->dutycycle3 = pdc->pwmduty;
    pdc->dutycycle4 = pdc->pwmduty;
    
    if(pdc->dutycycle4 < MIN_DUTY)
    {
        pdc->dutycycle4 = MIN_DUTY;
    }
    if(pdc->dutycycle3 < MIN_DUTY)
    {
        pdc->dutycycle3 = MIN_DUTY;
    }
    if(pdc->dutycycle2 < MIN_DUTY)
    {
        pdc->dutycycle2 = MIN_DUTY;
    }
    if(pdc->dutycycle1 < MIN_DUTY)
    {
        pdc->dutycycle1 = MIN_DUTY;
    }
    
    MC1_PWM_PDC4 = pdc->dutycycle4;
    MC1_PWM_PDC3 = pdc->dutycycle3;
    MC1_PWM_PDC2 = pdc->dutycycle2;
    MC1_PWM_PDC1 = pdc->dutycycle1;
}

/**
* <B> Function: HAL_MC1MotorInputsRead(MCAPP_MEASURE_T *) </B>
*
* @brief Function to read buffer values to variables.
*        
* @param Pointer to the data structure containing measured parameters.
* @return none.
* 
* @example
* <CODE> HAL_MC1MotorInputsRead(&motorInputs); </CODE>
*
*/
void HAL_MC1MotorInputsRead(MCAPP_MEASURE_T *pMotorInputs)
{
    pMotorInputs->measureCurrent.Ia   = ADCBUF_IA ;
    pMotorInputs->measureCurrent.Ib   = ADCBUF_IB ;
    pMotorInputs->measureCurrent.Ic   = ADCBUF_IC ;
    pMotorInputs->measureCurrent.Id   = ADCBUF_ID ;
    pMotorInputs->measureCurrent.Ibus = ADCBUF_IBUS;
    pMotorInputs->dcBusVoltage        = ADCBUF_VDC;
    pMotorInputs->measurePhaseVolt.Va = ADCBUF_VA;
    pMotorInputs->measurePhaseVolt.Vb = ADCBUF_VB;
    pMotorInputs->measurePhaseVolt.Vc = ADCBUF_VC;
    pMotorInputs->measurePhaseVolt.Vd = ADCBUF_VD;
    pMotorInputs->potValue            = ADCBUF_POT;
    
    pMotorInputs->dcBusVoltage = (float) ((pMotorInputs->dcBusVoltage) * ADC_VDC_VOLTAGE_SCALE);
    pMotorInputs->measureVdc.value    = (float) (pMotorInputs->dcBusVoltage);
}

/**
* <B> Function: ClearPWMPCIFault() </B>
*
* @brief Function to clear the PCI Fault by Software Termination
*        
* @param none.
* @return none.
* 
* @example
* <CODE> ClearPWMPCIFault(); </CODE>
*
*/
void ClearPWMPCIFault(void)
{
    /*write of ?1? to SWTERM bit will produce a PCI Fault termination event*/
    PG1FPCIbits.SWTERM = 1;
    PG2FPCIbits.SWTERM = 1;
    PG3FPCIbits.SWTERM = 1;
    PG4FPCIbits.SWTERM = 1;
    
    PG1CLPCIbits.SWTERM = 1;
    PG2CLPCIbits.SWTERM = 1;
    PG3CLPCIbits.SWTERM = 1;
    PG4CLPCIbits.SWTERM = 1;
    
}

/* Functions for PWMs ON and OFF  using override */
/**
* <B> Function: PWM1_OverrideEnableDataSet(uint32_t) </B>
*
* @brief Function to override PWM1.
*        
* @param none.
* @return none.
* 
* @example
* <CODE> PWM1_OverrideEnableDataSet(data); </CODE>
*
*/
void PWM1_OverrideEnableDataSet(uint32_t data)
{
    uint32_t dataBuffer;
    dataBuffer = PG1IOCON & 0xFFFFC3FF;
    PG1IOCON = dataBuffer | pwmCtrlState[data];
}
/**
* <B> Function: PWM2_OverrideEnableDataSet(uint32_t) </B>
*
* @brief Function to override PWM2.
*        
* @param none.
* @return none.
* 
* @example
* <CODE> PWM2_OverrideEnableDataSet(data); </CODE>
*
*/
void PWM2_OverrideEnableDataSet(uint32_t data)
{
    uint32_t dataBuffer;
    dataBuffer = PG2IOCON & 0xFFFFC3FF;
    PG2IOCON = dataBuffer | pwmCtrlState[data];
}
/**
* <B> Function: PWM3_OverrideEnableDataSet(uint32_t) </B>
*
* @brief Function to override PWM3.
*        
* @param none.
* @return none.
* 
* @example
* <CODE> PWM3_OverrideEnableDataSet(data); </CODE>
*
*/
void PWM3_OverrideEnableDataSet(uint32_t data)
{
    uint32_t dataBuffer;
    dataBuffer = PG3IOCON & 0xFFFFC3FF;
    PG3IOCON = dataBuffer | pwmCtrlState[data];
}
/**
* <B> Function: PWM4_OverrideEnableDataSet(uint32_t) </B>
*
* @brief Function to override PWM4.
*        
* @param none.
* @return none.
* 
* @example
* <CODE> PWM4_OverrideEnableDataSet(data); </CODE>
*
*/
void PWM4_OverrideEnableDataSet(uint32_t data)
{
    uint32_t dataBuffer;
    dataBuffer = PG4IOCON & 0xFFFFC3FF;
    PG4IOCON = dataBuffer | pwmCtrlState[data];
}
// </editor-fold>