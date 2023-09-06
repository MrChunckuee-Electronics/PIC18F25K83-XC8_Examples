/*
 * File:   mcu.c
 * Author: MrChunckuee
 *
 * Created on 1 de marzo de 2023, 11:48 PM
 */

#include "main.h"

//DECLARACION DE LAS VARIABLES
uint16_t counterTMR0;
uint8_t LED_ROTER, ledCounter = 0;
uint16_t bufferLEDs = 0;

bool LED1_Status =  0;
bool LED2_Status =  0;
bool LED3_Status =  0;
bool LED4_Status =  0;
bool LED5_Status =  0;
bool LED6_Status =  0;
bool LED7_Status =  0;
bool LED8_Status =  0;
bool LED9_Status =  0;
bool LED10_Status = 0;
bool LED11_Status = 0;
bool LED12_Status = 0;



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
 * Description:     Habilita el reloj del sistema a 1 milisegundo.
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         
 ******************************************************************************/
void RTCC_Enable(void){
    T0CON0bits.MD16 = 1;        // Timer0 is configured as a 16-bit timer/counter
    T0CON0bits.OUTPS = 0b0000;   
    T0CON1bits.CS = 0b010;
    T0CON1bits.CKPS = 0b0000;    //Prescaler 1:1  
    T0CON0bits.EN = 1;
    IPR3bits.TMR0IP = 0;        // Make TMR0 interrupt low priority
    PIE3bits.TMR0IE = 1;        // Enable TMR0 interrupt
    PIR3bits.TMR0IF = 0;        // Clear the interrupt flag
    TIMER0_OVR_FLAG = 0;
    counterTMR0 = 0;
    WRITETIMER0(63536); //WRITETIMER0(53036); 
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
        if(counterTMR0>999){ //Cada 1 segundo
            counterTMR0 = 0; 
            LED_Update(bufferLEDs);
        }
        MCU_SetOut(ledCounter);
        ledCounter++;
        TIMER0_OVR_FLAG = 0;
    }
}

void LED_Update(uint16_t LEDs){
    switch(LEDs){
        case 0:
            LED1_Status =  1;
            LED2_Status =  0;
            LED3_Status =  1;
            LED4_Status =  0;
            LED5_Status =  1;
            LED6_Status =  0;   
            LED7_Status =  1;
            LED8_Status =  0;
            LED9_Status =  1;
            LED10_Status = 0;
            LED11_Status = 1;
            LED12_Status = 0;
            bufferLEDs = 1;
            break;
        case 1:
            LED1_Status =  0;
            LED2_Status =  1;
            LED3_Status =  0;
            LED4_Status =  1;
            LED5_Status =  0;
            LED6_Status =  1;   
            LED7_Status =  0;
            LED8_Status =  1;
            LED9_Status =  0;
            LED10_Status = 1;
            LED11_Status = 0;
            LED12_Status = 1;
            bufferLEDs = 0;
            break;
        default:
            break;
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
 *      |      GPx      | |                      LEDs                        |
 *      | 1 | 2 | 3 | 4 | | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
 *        0   0   0   0     0   0   0   0   0   0   0   0   0    0    0    0
 *        0   1   Z   Z     1   0   0   0   0   0   0   0   0    0    0    0
 *        1   0   Z   Z     0   1   0   0   0   0   0   0   0    0    0    0
 *        Z   0   1   Z     0   0   1   0   0   0   0   0   0    0    0    0
 *        Z   1   0   Z     0   0   0   1   0   0   0   0   0    0    0    0
 *        Z   Z   0   1     0   0   0   0   1   0   0   0   0    0    0    0
 *        Z   Z   1   0     0   0   0   0   0   1   0   0   0    0    0    0
 *        0   Z   1   0     0   0   0   0   0   0   1   0   0    0    0    0
 *        1   Z   0   Z     0   0   0   0   0   0   0   1   0    0    0    0
 *        Z   0   Z   1     0   0   0   0   0   0   0   0   1    0    0    0
 *        Z   1   Z   0     0   0   0   0   0   0   0   0   0    1    0    0
 *        0   Z   Z   1     0   0   0   0   0   0   0   0   0    0    1    0
 *        1   Z   Z   0     0   0   0   0   0   0   0   0   0    0    0    1
 *        1   1   1   1     0   0   0   0   0   0   0   0   0    0    0    0
 ******************************************************************************/
void MCU_SetOut(uint8_t Out){
    switch(Out){
        case 0:     //All off
            // Config TRIS
            GPx_Output0_SetDigitalOutput();
            GPx_Output1_SetDigitalOutput();
            GPx_Output2_SetDigitalOutput();
            GPx_Output3_SetDigitalOutput();
            //set LAT
            GPx_Output0_SetLow();
            GPx_Output1_SetLow();
            GPx_Output2_SetLow();
            GPx_Output3_SetLow();
            break;
        case 1:     //LED1 on
            if(LED1_Status){
                GPx_Output0_SetDigitalOutput();
                GPx_Output1_SetDigitalOutput();
                GPx_Output2_SetDigitalInput();
                GPx_Output3_SetDigitalInput();
                GPx_Output0_SetLow();
                GPx_Output1_SetHigh();
            }
            break;
        case 2:     //LED2 on
            if(LED2_Status){
                GPx_Output0_SetDigitalOutput();
                GPx_Output1_SetDigitalOutput();
                GPx_Output2_SetDigitalInput();
                GPx_Output3_SetDigitalInput();
                GPx_Output0_SetHigh();
                GPx_Output1_SetLow();
            }
            break;
        case 3:     //LED3 on
            if(LED3_Status){
                GPx_Output0_SetDigitalInput();
                GPx_Output1_SetDigitalOutput();
                GPx_Output2_SetDigitalOutput();
                GPx_Output3_SetDigitalInput();
                GPx_Output1_SetLow();
                GPx_Output2_SetHigh();
            }
            break;
        case 4:     //LED4 on
            if(LED4_Status){
                GPx_Output0_SetDigitalInput();
                GPx_Output1_SetDigitalOutput();
                GPx_Output2_SetDigitalOutput();
                GPx_Output3_SetDigitalInput();
                GPx_Output1_SetHigh();
                GPx_Output2_SetLow();
            }
            break;
        case 5:     //LED5 on
            if(LED5_Status){
                GPx_Output0_SetDigitalInput();
                GPx_Output1_SetDigitalInput();
                GPx_Output2_SetDigitalOutput();
                GPx_Output3_SetDigitalOutput();
                GPx_Output2_SetLow();
                GPx_Output3_SetHigh();
            }
            break;
        case 6:     //LED6 on
            if(LED6_Status){
                GPx_Output0_SetDigitalInput();
                GPx_Output1_SetDigitalInput();
                GPx_Output2_SetDigitalOutput();
                GPx_Output3_SetDigitalOutput();
                GPx_Output2_SetHigh();
                GPx_Output3_SetLow();
            }
            //ledCounter = 0;
            break;
        case 7:     //LED7 on
            if(LED7_Status){
                GPx_Output0_SetDigitalOutput();
                GPx_Output1_SetDigitalInput();
                GPx_Output2_SetDigitalOutput();
                GPx_Output3_SetDigitalInput();
                GPx_Output0_SetLow();
                GPx_Output2_SetHigh();
            }
            break;
        case 8:     //LED8 on
            if(LED8_Status){
                GPx_Output0_SetDigitalOutput();
                GPx_Output1_SetDigitalInput();
                GPx_Output2_SetDigitalOutput();
                GPx_Output3_SetDigitalInput();
                GPx_Output0_SetHigh();
                GPx_Output2_SetLow();
            }
            break;
        case 9:     //LED9 on
            if(LED9_Status){
                GPx_Output0_SetDigitalInput();
                GPx_Output1_SetDigitalOutput();
                GPx_Output2_SetDigitalInput();
                GPx_Output3_SetDigitalOutput();
                GPx_Output1_SetLow();
                GPx_Output3_SetHigh();
            }
            break;
        case 10:    //LED10 on
            if(LED10_Status){
                GPx_Output0_SetDigitalInput();
                GPx_Output1_SetDigitalOutput();
                GPx_Output2_SetDigitalInput();
                GPx_Output3_SetDigitalOutput();
                GPx_Output1_SetHigh();
                GPx_Output3_SetLow();
            }
            break;
        case 11:    //LED11 on
            if(LED11_Status){
                GPx_Output0_SetDigitalOutput();
                GPx_Output1_SetDigitalInput();
                GPx_Output2_SetDigitalInput();
                GPx_Output3_SetDigitalOutput();
                GPx_Output0_SetLow();
                GPx_Output3_SetHigh();
            }
            break;
        case 12:    //LED12 on
            if(LED12_Status){
                GPx_Output0_SetDigitalOutput();
                GPx_Output1_SetDigitalInput();
                GPx_Output2_SetDigitalInput();
                GPx_Output3_SetDigitalOutput();
                GPx_Output0_SetHigh();
                GPx_Output3_SetLow();
            }
            ledCounter = 0;
            break; 
        default:
            break;
    }
    
}