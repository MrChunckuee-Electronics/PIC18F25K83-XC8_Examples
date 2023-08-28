/* 
 * File:   isr_manager.h
 * Author: mrchu
 *
 * Created on 2 de julio de 2023, 07:27 PM
 */

#ifndef ISR_MANAGER_H
#define	ISR_MANAGER_H

#ifdef	__cplusplus
extern "C" {
#endif


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will enable high priority global interrupts.
 * @Example
    INTERRUPT_GlobalInterruptHighEnable();
 */
#define INTERRUPT_GlobalInterruptHighEnable() (INTCON0bits.GIEH = 1)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will disable high priority global interrupts.
 * @Example
    INTERRUPT_GlobalInterruptHighDisable();
 */
#define INTERRUPT_GlobalInterruptHighDisable() (INTCON0bits.GIEH = 0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will enable low priority global interrupts.
 * @Example
    INTERRUPT_GlobalInterruptLowEnable();
 */
#define INTERRUPT_GlobalInterruptLowEnable() (INTCON0bits.GIEL = 1)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will disable low priority global interrupts.
 * @Example
    INTERRUPT_GlobalInterruptLowDisable();
 */
#define INTERRUPT_GlobalInterruptLowDisable() (INTCON0bits.GIEL = 0)
    
    
bool TIMER0_OVR_FLAG;

void INTERRUPT_GlobalInterruptEnable(void);
void INTERRUPT_GlobalInterruptDisable(void);
    

#ifdef	__cplusplus
}
#endif

#endif	/* ISR_MANAGER_H */

