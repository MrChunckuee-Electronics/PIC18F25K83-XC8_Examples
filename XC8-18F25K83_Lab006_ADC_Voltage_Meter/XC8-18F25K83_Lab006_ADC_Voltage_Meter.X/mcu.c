/*
 * File:   mcu.c
 * Author: mrchu
 *
 * Created on 27 de septiembre de 2025, 07:37 PM
 */

#include "main.h"

/*******************************************************************************
 * Function:        void SYSTEM_Initialize(void)
 * Description:     Funcion de inicializacion.
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         Inicializa las funciones correspondientes para que el sitema 
 *                  comience de forma adecuada.
 ******************************************************************************/
void SYSTEM_Initialize(void){
    MCU_Initialize();
    OSCILLATOR_Initialize();
    ADC_Initialize();  
}

/*******************************************************************************
 * Function:        void MCU_Initialize(void)
 * Description:     Inicializa puertos 
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         
 ******************************************************************************/
void MCU_Initialize(void){
    //Configura pines digitales/analogicas
    ANSELA = 0b00000000;
    ANSELB = 0b00000000; 
    ANSELC = 0b10000000;
    
    //Configura entras/salidas
    TRISA = 0b00000000;
    TRISB = 0b00000000;
    TRISC = 0b10000000;
    
    //Limpia los puertos de entrada salida al comenzar el funcionamiento del mcu
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
}

/*******************************************************************************
 * Function:        void OSCILLATOR_Initialize(void)
 * Description:     Configuracion de oscilador
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         
 ******************************************************************************/
void OSCILLATOR_Initialize(void){
    // NOSC HFINTOSC; NDIV 4; 
    OSCCON1 = 0x62;
    // CSWHOLD may proceed; SOSCPWR Low power; 
    OSCCON3 = 0x00;
    // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 
    OSCEN = 0x00;
    // HFFRQ 32_MHz; 
    OSCFRQ = 0x06;
    // TUN 0; 
    OSCTUNE = 0x00;
}