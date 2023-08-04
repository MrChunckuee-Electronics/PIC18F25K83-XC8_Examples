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
    
    // Change IVTBASE if required
    IVTBASEU = 0x00; // Optional
    IVTBASEH = 0x40; // Default is 0x0008
    IVTBASEL = 0x08;
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
 * Function:        void __interrupt(irq(IRQ_TMR0), base(0x4008)) TMR0_ISR(void)
 * Description:     Rutina de atencion para la interrupcion del TMR0
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:
 ******************************************************************************/
void __interrupt(irq(IRQ_TMR0), base(0x4008)) TMR0_ISR(void){
    PIR3bits.TMR0IF = 0; // Clear the interrupt flag
    TIMER0_OVR_FLAG = 1;
    WRITETIMER0(59286); 
}
