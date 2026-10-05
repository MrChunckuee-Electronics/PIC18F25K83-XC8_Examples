/*******************************************************************************
 *
 *                  PEC11R Rotary Encoder
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F25K83
 * Complier:        XC8 v2.36
 * Author:          Pedro Sanchez (mrchunckuee_electronics)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.electronics@gmail.com
 * Description:     Rotary Encoder demo test with 16x2 LCD display.
 *******************************************************************************
 * Rev.         Date            Comment
 *  v1.0.0      30/09/2026      - Creación y prueba de funcionamiento
 ******************************************************************************/

#include "DEVICEConfig.h" //Config fuses
#include "main.h"

// Conexiones de la LCD
LCD_t LCD = {
    .TRIS = &TRISA,
    .PORT = &PORTA,
    .RS   = 0,  // RA0 for RS
    .EN   = 1,  // RA1 for EN
    .D4   = 2,  // RA2 for D4
    .D5   = 3,  // RA3 for D5
    .D6   = 4,  // RA4 for D6
    .D7   = 5   // RA5 for D7
};

void DISPLAY_Initialize(void);

void main(void){
    // Inicializacion del sistema y oscilador
    SYSTEM_Initialize();
    
    // Inicializacion de perifericos (Encoder y LCD)
    ENCODER_Initialize(0, 100, true);
    DISPLAY_Initialize();
    
    INTERRUPT_GlobalInterruptEnable();

    int16_t lastPos = -1;
    char buffer[17];

    while(1){
        // Lectura de la posicion del encoder
        int16_t currentPos = ENCODER_GetPosition();
        if(currentPos != lastPos){
            lastPos = currentPos;

            // Actualizar numero de posición
            sprintf(buffer, "%3d ", currentPos);
            LCD_SetCursor(0, 5);
            LCD_puts(buffer);

            // Actualizar sentido de giro
            LCD_SetCursor(0, 11);
            if(rotary.direction == 1){
                LCD_putrs("[CW ]");
            }
            else if(rotary.direction == -1){
                LCD_putrs("[CCW]");
            }
        }

        // Lectura del boton (debouncing cada ~5 ms)
        ENCODER_ButtonUpdate_5ms();

        // Atencion de eventos de boton
        ButtonEvent_t event = ENCODER_GetButtonEvent();
        if(event == BTN_CLICKED){
            LCD_SetCursor(1, 5);
            LCD_putrs("CLICKED     ");
            ENCODER_SetPosition(0); // Reinicia contador
        }
        else if(event == BTN_LONG_PRESSED){
            LCD_SetCursor(1, 5);
            LCD_putrs("LONG PRESS  ");
        }

        __delay_ms(5);
    }
}

/*******************************************************************************
 * Function:        void DISPLAY_Initialize(void)
 * Description:     Inicializa la pantalla LCD y dibuja la interfaz base.
 * Precondition:    SYSTEM_Initialize debe ejecutarse primero.
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 ******************************************************************************/
void DISPLAY_Initialize(void){
    if (!LCD_Initialize(LCD)){ } // LCD Init
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_puts("MrChunckuee!!");
    LCD_SetCursor(1, 0);
    LCD_puts("Rotary Encoder");
    __delay_ms(1000);
    
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_putrs("Pos: ");
    LCD_SetCursor(1, 0);
    LCD_putrs("Btn: NONE      ");
}