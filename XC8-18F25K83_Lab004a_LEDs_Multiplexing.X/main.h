/* 
 * File:   main.h
 * Author: MrChunckuee
 *
 * Created on 1 de marzo de 2023, 11:44 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif


/*********** I N C L U D E S **************************************************/
#include <xc.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "mcu.h"
#include "isr_manager.h"
    
/*********** G E N E R A L     D E F I N E S **********************************/
#define _XTAL_FREQ        8000000
#define Delay_ms(x)       __delay_ms(x)
    
/*********** P O R T   D E F I N E S ******************************************/
#define pinCtrlOutput_LED2      LATCbits.LATC2
#define pinCtrlOutput_LED3      LATCbits.LATC3
#define pinCtrlOutput_LED4      LATCbits.LATC4
#define pinCtrlOutput_LED5      LATCbits.LATC5

#define LED2_Status_SetHigh()   do { pinCtrlOutput_LED2 = true; } while(0)
#define LED2_Status_SetLow()    do { pinCtrlOutput_LED2 = false; } while(0)
#define LED2_Status_Toggle()    do { pinCtrlOutput_LED2 = ~pinCtrlOutput_LED2; } while(0)
    
#define LED3_Status_SetHigh()   do { pinCtrlOutput_LED3 = true; } while(0)
#define LED3_Status_SetLow()    do { pinCtrlOutput_LED3 = false; } while(0)
#define LED3_Status_Toggle()    do { pinCtrlOutput_LED3 = ~pinCtrlOutput_LED3; } while(0)
    
#define LED4_Status_SetHigh()   do { pinCtrlOutput_LED4 = true; } while(0)
#define LED4_Status_SetLow()    do { pinCtrlOutput_LED4 = false; } while(0)
#define LED4_Status_Toggle()    do { pinCtrlOutput_LED4 = ~pinCtrlOutput_LED4; } while(0)
    
#define LED5_Status_SetHigh()   do { pinCtrlOutput_LED5 = true; } while(0)
#define LED5_Status_SetLow()    do { pinCtrlOutput_LED5 = false; } while(0)
#define LED5_Status_Toggle()    do { pinCtrlOutput_LED5 = ~pinCtrlOutput_LED5; } while(0)
    

// Outputs for multiplexing LEDs
#define GPx_Output0_TRIS                 TRISBbits.TRISB0
#define GPx_Output0_LAT                  LATBbits.LATB0
#define GPx_Output0_SetHigh()            do { GPx_Output0_LAT = 1; } while(0)
#define GPx_Output0_SetLow()             do { GPx_Output0_LAT = 0; } while(0)
#define GPx_Output0_SetDigitalInput()    do { GPx_Output0_TRIS = 1; } while(0)
#define GPx_Output0_SetDigitalOutput()   do { GPx_Output0_TRIS = 0; } while(0)
    
#define GPx_Output1_TRIS                 TRISBbits.TRISB1
#define GPx_Output1_LAT                  LATBbits.LATB1
#define GPx_Output1_SetHigh()            do { GPx_Output1_LAT = 1; } while(0)
#define GPx_Output1_SetLow()             do { GPx_Output1_LAT = 0; } while(0)
#define GPx_Output1_SetDigitalInput()    do { GPx_Output1_TRIS = 1; } while(0)
#define GPx_Output1_SetDigitalOutput()   do { GPx_Output1_TRIS = 0; } while(0)
    
#define GPx_Output2_TRIS                 TRISBbits.TRISB2
#define GPx_Output2_LAT                  LATBbits.LATB2
#define GPx_Output2_SetHigh()            do { GPx_Output2_LAT = 1; } while(0)
#define GPx_Output2_SetLow()             do { GPx_Output2_LAT = 0; } while(0)
#define GPx_Output2_SetDigitalInput()    do { GPx_Output2_TRIS = 1; } while(0)
#define GPx_Output2_SetDigitalOutput()   do { GPx_Output2_TRIS = 0; } while(0)

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

