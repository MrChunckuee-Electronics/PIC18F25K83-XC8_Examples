/*
 * File:   mcu.c
 * Author: MrChunckuee
 *
 * Created on 1 de marzo de 2023, 11:48 PM
 */

#include "main.h"

//DECLARACION DE LAS VARIABLES
uint8_t counterTMR0;
uint8_t LED_ROTER;

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
    RTCC_Enable();
    INTERRUPT_GlobalInterruptEnable();
    IO_LEDHello();
    IO_LEDPrintChar(0);
    
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
    RTCC_Update();
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

/*******************************************************************************
 * Function:        void RTCC_Enable(void)
 * Description:     Habilita el reloj del sistema a 100 milisegundos.
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         
 ******************************************************************************/
void RTCC_Enable(void){
    T0CON0bits.MD16 = 1;        // Timer0 is configured as a 16-bit timer/counter
    T0CON0bits.OUTPS = 0b0000;   
    T0CON1bits.CS = 0b010;
    T0CON1bits.CKPS = 0b100;    //Prescaler 16  
    T0CON0bits.EN = 1;
    IPR3bits.TMR0IP = 0;        // Make TMR0 interrupt low priority
    PIE3bits.TMR0IE = 1;        // Enable TMR0 interrupt
    PIR3bits.TMR0IF = 0;        // Clear the interrupt flag
    TIMER0_OVR_FLAG = 0;
    counterTMR0 = 0;
    WRITETIMER0(53036); 
}

//Actualiza el valor del reloj en tiempo real
void RTCC_Update(void){
    if(TIMER0_OVR_FLAG){
        counterTMR0++;
        if(counterTMR0>9){ //Cada 1 segundo
            counterTMR0 = 0;
            LED4_Status_Toggle();
            LED5_Status_Toggle();
        }
        TIMER0_OVR_FLAG = 0;
    }
}