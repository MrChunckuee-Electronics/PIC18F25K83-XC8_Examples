/*
 * File:   mcu.c
 * Author: MrChunckuee
 *
 * Created on 1 de marzo de 2023, 11:48 PM
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
}

/*******************************************************************************
 * Function:        void SYSTEM_Process(void)
 * Description:     Funcion de procesos.
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         
 ******************************************************************************/
void SYSTEM_Process(void){
    IO_LEDHello();
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
    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;
    
    //Configura entras/salidas
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    
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
    // NOSC HFINTOSC; NDIV 1; 
    OSCCON1 = 0x60;
    // CSWHOLD may proceed; SOSCPWR Low power; 
    OSCCON3 = 0x00;
    // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 
    OSCEN = 0x00;
    // HFFRQ 64_MHz; 
    OSCFRQ = 0x08;
    // TUN 0; 
    OSCTUNE = 0x00;
}

/*******************************************************************************
 * Function:        void IO_LEDHello(void)
 * Description:     Barrido de LEDs, test demo
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 ******************************************************************************/
void IO_LEDHello(void){
    uint8_t LED_COUNTER;
    for(LED_COUNTER=1; LED_COUNTER<5; LED_COUNTER++){
        IO_LEDPrintChar(LED_COUNTER);
        Delay_ms(250);
    }
    for(LED_COUNTER=4; LED_COUNTER>0; LED_COUNTER--){
        IO_LEDPrintChar(LED_COUNTER);
        Delay_ms(250);
    }
}

/*******************************************************************************
 * Function:        void MCU_LEDPrintChar(unsigned char LEDCHAR)
 * Description:     Imprime LEDCHAR en los leds de salida.
 * Precondition:    None
 * Parameters:      LEDCHAR combinación seleccionada
 * Return Values:   None
 * Remarks:         None
 ******************************************************************************/
void IO_LEDPrintChar(uint8_t LEDCHAR){
    switch(LEDCHAR){
        case 0:
            LED2_Status_SetLow();
            LED3_Status_SetLow();
            LED4_Status_SetLow();
            LED5_Status_SetLow();
            break;
        case 1: 
            LED2_Status_SetHigh();
            LED3_Status_SetLow();
            LED4_Status_SetLow();
            LED5_Status_SetLow();
            break;
        case 2: 
            LED2_Status_SetLow();
            LED3_Status_SetHigh();
            LED4_Status_SetLow();
            LED5_Status_SetLow();
            break;
        case 3: 
            LED2_Status_SetLow();
            LED3_Status_SetLow();
            LED4_Status_SetHigh();
            LED5_Status_SetLow();
            break;
        case 4: 
            LED2_Status_SetLow();
            LED3_Status_SetLow();
            LED4_Status_SetLow();
            LED5_Status_SetHigh();
            break;
        default:
            LED2_Status_SetLow();
            LED3_Status_SetLow();
            LED4_Status_SetLow();
            LED5_Status_SetLow();
            break; 
    }
}