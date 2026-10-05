/* 
 * File:   mcu.h
 * Author: mrchu
 *
 * Created on 27 de septiembre de 2025, 07:36 PM
 */

#ifndef MCU_H
#define	MCU_H

#ifdef	__cplusplus
extern "C" {
#endif


    /*********** P R O T O T Y P E S **********************************************/
    void SYSTEM_Initialize(void);
    void MCU_Initialize(void);
    void OSCILLATOR_Initialize(void);
    

#ifdef	__cplusplus
}
#endif

#endif	/* MCU_H */

