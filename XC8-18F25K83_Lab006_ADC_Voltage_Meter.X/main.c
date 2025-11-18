/*******************************************************************************
 *
 *          Lab006: Uso basico del ADC - Leer voltaje de un potenciometro y 
 *                  mostrarlo en una LCD con numeros grandes.
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F25K83
 * Complier:        XC8 v2.36
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Configuracion basica del ADC, para lectura de voltaje de un 
 *                  puerto analogico para ser mostrado en una LCD con numeros grandes.
 *******************************************************************************
 * Rev.         Date            Comment
 *  v1.0.0      05/10/2023      - Creación y prueba de funcionamiento
 ******************************************************************************/

#include "device_config.h" //Config fuses
#include "main.h"

#define MAX_TOTAL_DIGITS 6           

uint16_t adcValue = 0;

#define sensor_nMuestras  10
bool sensor_ready = false;
uint8_t sensor_avgCounter = 0;
uint16_t sensor_adcVoltage = 0, sensor_sumVoltage = 0, sensor_avgVoltage = 0;
float voltaje = 0.0;
uint8_t lcdNumber[15] = {0};
const float bit_voltaje = 5.0/4096.0;

// Conexiones de la LCD
LCD_t LCD = {
    .TRIS = &TRISB,
    .PORT = &PORTB,
    .RS   = 0,  // Pin RB0 para RS
    .EN   = 1,  // Pin RB1 para EN
    .D4   = 4,  // Pin RB2 para D4
    .D5   = 5,  // Pin RB3 para D5
    .D6   = 6,  // Pin RB4 para D6
    .D7   = 7   // Pin RB5 para D7
};

void DISPLAY_ShowFloatValue(float value, uint8_t start_row, uint8_t start_col);

void LCD_Initialize(void){
    if (!LCD_Init(LCD)){ } // LCD Init
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_puts("MrChunckuee!!");
    LCD_SetCursor(1, 0);
    LCD_puts("ADC - BIG Digits");
    __delay_ms(1000);
    
    LCD_Clear();
    LCD_SetFont(FONT_TRON_BOLD);
}

void main(void) {
    SYSTEM_Initialize();
    LCD_Initialize();
    while(1){
        sensor_adcVoltage = ADC_GetSingleConversion(channel_ANC7_voltagePotentiometer_GetValue());
        sensor_sumVoltage += sensor_adcVoltage;
        sensor_avgCounter ++;
        if(sensor_avgCounter > sensor_nMuestras){
            sensor_avgVoltage = sensor_sumVoltage / sensor_avgCounter;
            sensor_avgCounter = 0;
            sensor_sumVoltage = 0;
            voltaje = bit_voltaje * sensor_avgVoltage;
            sensor_ready = true;
        }
        __delay_ms(100);
        
        if(sensor_ready){
            DISPLAY_ShowFloatValue(voltaje, 0, 0);
            LCD_SetCursor(0, 14);
            LCD_putc('V');
            sensor_ready = false;
        }
    }
}

/*******************************************************************************
 * Function:        void DISPLAY_ShowFloatValue(float value, uint8_t start_row, uint8_t start_col)
 * Description:     Convierte y muestra un valor flotante limitando a MAX_TOTAL_DIGITS
 * Precondition:    None
 * Parameters:      float value. El valor decimal (e.g., 305.0023)
 *                  uint8_t start_row
 *                  uint8_t start_col
 * Return Values:   None
 * Remarks:         
 ******************************************************************************/
void DISPLAY_ShowFloatValue(float value, uint8_t start_row, uint8_t start_col) {    
    uint8_t num_integer_digits;
    uint8_t num_decimal_digits;
    unsigned long scale_factor;
    uint8_t digits[MAX_TOTAL_DIGITS];
    uint8_t current_col = start_col;
    uint8_t drawing_active = 0;
    
    if (value < 1.0f) { // Consideramos el 0, ej 0.0023
        num_integer_digits = 1; 
    }else { //Obtenemos total digitos enteros
        uint8_t count = 0;
        unsigned long temp = (unsigned long)value; 
        while (temp > 0) {
            temp /= 10; 
            count++;
        }
        num_integer_digits = count;
    }
    
    // Obtenemos total digitos decimales
    if (num_integer_digits >= MAX_TOTAL_DIGITS){
        num_decimal_digits = 0;
    } else {
        num_decimal_digits = MAX_TOTAL_DIGITS - num_integer_digits;
    }
    
    // Calculamos el factor de escala
    scale_factor = 1;
    for (uint8_t i = 0; i < num_decimal_digits; i++) {
        // Multiplicación repetida: 1 * 10 * 10...
        scale_factor *= 10; 
    }
    
    // Escalamos float value ej 3.00052 -> 300052
    // Truncamos o podemos redondear con (int)(x + 0.5f)
    //unsigned long scaled_value = (unsigned long)((value * (float)scale_factor)+ 0.5f);
    unsigned long scaled_value = (unsigned long)(value * (float)scale_factor);
    
    // Descomponer el entero escalado en dígitos
    // Se almacena de forma invertida
    for (int i = 0; i < MAX_TOTAL_DIGITS; i++) {
        digits[i] = scaled_value % 10;
        scaled_value /= 10;
    }

    // Dibujar y suprimir ceros
    for (int j = 0; j < MAX_TOTAL_DIGITS; j++) {
        
        uint8_t digit_index = (MAX_TOTAL_DIGITS - 1) - j; //Ordenar digitos
        uint8_t digit_value = digits[digit_index];
        
        const uint8_t units_index = num_decimal_digits;
        
        if (digit_value != 0 || (digit_index == units_index) || drawing_active) {
            drawing_active = 1; 

            // Insertar el punto decimal
            if (digit_index == units_index - 1 && units_index > 0) {
                LCD_SetCursor(start_row, current_col);
                LCD_putc(254); // Evita borrar la pantalla, solo borra parte superior del punto
                LCD_SetCursor(start_row+1, current_col);
                LCD_putc(223); // Caracter usado como punto, obtenido de la CGRAM
                current_col += 1;
            }
            
            LCD_DrawBigDigit(digit_value, start_row, current_col);
            current_col += 2;
        }
    }
}