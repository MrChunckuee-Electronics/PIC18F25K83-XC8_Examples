/*
 * File:   isr_manager.c
 * Author: mrchu
 *
 * Created on 2 de julio de 2023, 07:27 PM
 */

#include "main.h"

/*******************************************************************************
 * Function:        void INTERRUPT_GlobalInterruptEnable(void)
 * Description:     This function initializes the interrupt service routines
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:
 ******************************************************************************/
void INTERRUPT_GlobalInterruptEnable(void)
{
    INTCON0bits.IPEN = 1; //Interrupt Priority Enable bit, Enable priority level on interrupt
    
    // Assign peripheral interrupt priority vectors
    
    // TMR0 - low priority
    IPR3bits.TMR0IP = 0;   
    
    INTERRUPT_GlobalInterruptHighEnable(); 
    INTERRUPT_GlobalInterruptLowEnable(); 
}

/*******************************************************************************
 * Function:        void ISR_DeInit(void)
 * Description:     This function disabled the interrupt service routines
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:
 ******************************************************************************/
void INTERRUPT_GlobalInterruptDisable(void)
{
    INTERRUPT_GlobalInterruptHighDisable();
    INTERRUPT_GlobalInterruptLowDisable();
}


/*******************************************************************************
 * Function:        void __interrupt() INTERRUPT_InterruptManagerHigh (void)
 * Description:     Rutina de atencion para las interripciones de alta prioridad
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:
 ******************************************************************************/
void __interrupt() INTERRUPT_InterruptManagerHigh (void)
{
   // interrupt handler
}

/*******************************************************************************
 * Function:        void __interrupt(low_priority) INTERRUPT_InterruptManagerLow (void)
 * Description:     Rutina de atencion para las interripciones de baja prioridad
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:
 ******************************************************************************/
void __interrupt(low_priority) INTERRUPT_InterruptManagerLow (void)
{
    // interrupt handler
    if(PIE3bits.TMR0IE == 1 && PIR3bits.TMR0IF == 1)
    {
        PIR3bits.TMR0IF = 0;
        TIMER0_OVR_FLAG = 1;
        WRITETIMER0(53036); 
    }
    else
    {
        //Unhandled Interrupt
    }
}
