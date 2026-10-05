/*
 * File:   INTERRUPTManager.c
 * Author: mrchunckuee_electronics
 *
 * Created on September 28, 2026, 12:39 AM
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
 * Function:        void __interrupt(high_priority) INTERRUPT_InterruptManagerHigh (void)
 * Description:     Rutina de atencion para las interripciones de alta prioridad
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:
 ******************************************************************************/
void __interrupt(high_priority) INTERRUPT_InterruptManagerHigh (void)
{
    // Check if Interrupt-On-Change triggered the interrupt
    if (PIE0bits.IOCIE && PIR0bits.IOCIF){
        ENCODER_ISR_Handler();
    }
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

}