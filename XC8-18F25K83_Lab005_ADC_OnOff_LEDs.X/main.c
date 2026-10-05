/*******************************************************************************
 *
 *          Lab005: Uso basico del ADC - Encender/Apagar LEDs 
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F25K83
 * Complier:        XC8 v2.36
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Configuracion basica del ADC, para lectura de un puerto analogico 
 *                  y encendido de LEDs (multiplexados).
 *******************************************************************************
 * Rev.         Date            Comment
 *  v1.0.0      05/10/2023      - Creación y prueba de funcionamiento
 ******************************************************************************/

#include "device_config.h" //Config fuses
#include "main.h"

void main(void) {
    SYSTEM_Initialize();
    while(1){
        SYSTEM_Process();
    }
}
