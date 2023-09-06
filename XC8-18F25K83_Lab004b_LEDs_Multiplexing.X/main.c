/*******************************************************************************
 *
 *          Lab004b: LEDs - Multiplexing otuputs (4 salidas - 12 LEDs)
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F25K83
 * Complier:        XC8 v2.36
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Probando TIP #2 Input/Output Multiplexing del documento 
 *                  "Compiled Tips and Tricks Guide" de Microchip.
 *******************************************************************************
 * Rev.         Date            Comment
 *  v1.0.0      27/08/2023      - Creación y prueba de funcionamiento 
 *  v1.0.1      06/09/2023      - Implementacion para controlar 12 LEDs a eleccion
 ******************************************************************************/

#include "device_config.h" //Config fuses
#include "main.h"

void main(void) {
    SYSTEM_Initialize();
    while(1){
        SYSTEM_Process();
    }
}
