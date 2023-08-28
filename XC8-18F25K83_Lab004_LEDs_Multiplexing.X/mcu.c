/*
 * File:   mcu.c
 * Author: MrChunckuee
 *
 * Created on 1 de marzo de 2023, 11:48 PM
 */

#include "main.h"

//DECLARACION DE LAS VARIABLES
uint8_t counterTMR0;
uint8_t LED_ROTER, ledCounter = 0;

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

/*******************************************************************************
 * Function:        void RTCC_Update(void)
 * Description:     Actualiza el valor del reloj en tiempo real.
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         
 ******************************************************************************/
void RTCC_Update(void){
    if(TIMER0_OVR_FLAG){
        counterTMR0++;
        if(counterTMR0>9){ //Cada 1 segundo
            counterTMR0 = 0;
            ledCounter++;
            MCU_SetOut(ledCounter);
        }
        TIMER0_OVR_FLAG = 0;
    }
}

/*******************************************************************************
 * Function:        void MCU_SetOut(void)
 * Description:     Controla el encendido de los LEDs.
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         Probando TIP #2 Input/Output Multiplexing del documento 
 *                  "Compiled Tips ?N Tricks Guide" de Microchip.
 *                  
 *                  TIP #2 Input/Output Multiplexing
 *                      Individual diodes and some combination of diodes can be 
 *                      enabled by driving I/Os high and low or switching to 
 *                      inputs (Z). The number of diodes (D) that can be controlled 
 *                      depends on the number of I/Os (GP) used.
 *                          The equation is: D = GP x (GP - 1).
 * 
 * 
 *      |   GPx     ||          LEDs         |
 *      | 1 | 2 | 3 || 1 | 2 | 3 | 4 | 5 | 6 |
 *        0   0   0    0   0   0   0   0   0
 *        0   1   Z    1   0   0   0   0   0 
 *        1   0   Z    0   1   0   0   0   0
 *        Z   0   1    0   0   1   0   0   0
 *        Z   1   0    0   0   0   1   0   0
 *        0   Z   1    0   0   0   0   1   0
 *        1   Z   0    0   0   0   0   0   1
 *        0   0   1    0   0   1   0   1   0
 *        0   1   0    1   0   0   1   0   0
 *        0   1   1    1   0   0   0   1   0
 *        1   0   0    0   1   0   0   0   1
 *        1   0   1    0   1   1   0   0   0
 *        1   1   0    0   0   0   1   0   1
 *        1   1   1    0   0   0   0   0   0
 ******************************************************************************/
void MCU_SetOut(uint8_t Out){
    switch(Out){
        case 0:     //GPx = 000
            // Config TRIS
            GPx_Output0_SetDigitalOutput();
            GPx_Output1_SetDigitalOutput();
            GPx_Output2_SetDigitalOutput();
            //set LAT
            GPx_Output0_SetLow();
            GPx_Output1_SetLow();
            GPx_Output2_SetLow();
            break;
        case 1:     //GPx = 01Z
            GPx_Output0_SetDigitalOutput();
            GPx_Output1_SetDigitalOutput();
            GPx_Output2_SetDigitalInput();
            GPx_Output0_SetLow();
            GPx_Output1_SetHigh();
            break;
        case 2:     //GPx = 10Z
            GPx_Output0_SetDigitalOutput();
            GPx_Output1_SetDigitalOutput();
            GPx_Output2_SetDigitalInput();
            GPx_Output0_SetHigh();
            GPx_Output1_SetLow();
            break;
        case 3:     //GPx = Z01
            GPx_Output0_SetDigitalInput();
            GPx_Output1_SetDigitalOutput();
            GPx_Output2_SetDigitalOutput();
            GPx_Output1_SetLow();
            GPx_Output2_SetHigh();
            break;
        case 4:     //GPx = Z10
            GPx_Output0_SetDigitalInput();
            GPx_Output1_SetDigitalOutput();
            GPx_Output2_SetDigitalOutput();
            GPx_Output1_SetHigh();
            GPx_Output2_SetLow();
            break;
        case 5:     //GPx = 0Z1
            GPx_Output0_SetDigitalOutput();
            GPx_Output1_SetDigitalInput();
            GPx_Output2_SetDigitalOutput();
            GPx_Output0_SetLow();
            GPx_Output2_SetHigh();
            break;
        case 6:     //GPx = 1Z0
            GPx_Output0_SetDigitalOutput();
            GPx_Output1_SetDigitalInput();
            GPx_Output2_SetDigitalOutput();
            GPx_Output0_SetHigh();
            GPx_Output2_SetLow();
            break;
        case 7:     //GPx = 001
            GPx_Output0_SetDigitalOutput();
            GPx_Output1_SetDigitalOutput();
            GPx_Output2_SetDigitalOutput();
            GPx_Output0_SetLow();
            GPx_Output1_SetLow();
            GPx_Output2_SetHigh();
            break;
        case 8:     //GPx = 010
            GPx_Output0_SetDigitalOutput();
            GPx_Output1_SetDigitalOutput();
            GPx_Output2_SetDigitalOutput();
            GPx_Output0_SetLow();
            GPx_Output1_SetHigh();
            GPx_Output2_SetLow();
            break;
        case 9:     //GPx = 011
            GPx_Output0_SetDigitalOutput();
            GPx_Output1_SetDigitalOutput();
            GPx_Output2_SetDigitalOutput();
            GPx_Output0_SetLow();
            GPx_Output1_SetHigh();
            GPx_Output2_SetHigh();
            break;
        case 10:    //GPx = 100
            GPx_Output0_SetDigitalOutput();
            GPx_Output1_SetDigitalOutput();
            GPx_Output2_SetDigitalOutput();
            GPx_Output0_SetHigh();
            GPx_Output1_SetLow();
            GPx_Output2_SetLow();
            break;
        case 11:    //GPx = 101
            GPx_Output0_SetDigitalOutput();
            GPx_Output1_SetDigitalOutput();
            GPx_Output2_SetDigitalOutput();
            GPx_Output0_SetHigh();
            GPx_Output1_SetLow();
            GPx_Output2_SetHigh();
            break;
        case 12:    //GPx = 110
            GPx_Output0_SetDigitalOutput();
            GPx_Output1_SetDigitalOutput();
            GPx_Output2_SetDigitalOutput();
            GPx_Output0_SetHigh();
            GPx_Output1_SetHigh();
            GPx_Output2_SetLow();
            break;
        case 13:    //GPx = 111
            GPx_Output0_SetDigitalOutput();
            GPx_Output1_SetDigitalOutput();
            GPx_Output2_SetDigitalOutput();
            GPx_Output0_SetLow();
            GPx_Output1_SetLow();
            GPx_Output2_SetLow();
            ledCounter = 0;
            break;  
        default:
            break;
    }
}