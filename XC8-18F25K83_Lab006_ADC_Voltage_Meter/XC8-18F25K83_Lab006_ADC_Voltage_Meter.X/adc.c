/*
 * File:   adc.c
 * Author: Pedro
 *
 * Created on 6 de julio de 2022, 02:03 PM
 */


#include "main.h"

/*******************************************************************************
 * Function:        void ADC_Init(void)
 * Description:     Inicializa el ADC
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:
 ******************************************************************************/
void ADC_Initialize(void){
    // set the ADCC to the options selected in the User Interface
    // ADLTH 0; 
    ADLTHL = 0x00;
    // ADLTH 0; 
    ADLTHH = 0x00;
    // ADUTH 0; 
    ADUTHL = 0x00;
    // ADUTH 0; 
    ADUTHH = 0x00;
    // ADSTPT 0; 
    ADSTPTL = 0x00;
    // ADSTPT 0; 
    ADSTPTH = 0x00;
    // ADACC 0; 
    ADACCU = 0x00;
    // ADRPT 0; 
    ADRPT = 0x00;
    // ADPCH ANA0; 
    ADPCH = 0x00;
    // ADACQ 0; 
    ADACQL = 0x00;
    // ADACQ 0; 
    ADACQH = 0x00;
    // ADCAP Additional uC disabled; 
    ADCAP = 0x00;
    // ADPRE 0; 
    ADPREL = 0x00;
    // ADPRE 0; 
    ADPREH = 0x00;
    // ADDSEN disabled; ADGPOL digital_low; ADIPEN disabled; ADPPOL Vss; 
    ADCON1 = 0x00;
    // ADCRS 0; ADMD Basic_mode; ADACLR disabled; ADPSIS RES; 
    ADCON2 = 0x00;
    // ADCALC First derivative of Single measurement; ADTMD disabled; ADSOI ADGO not cleared; 
    ADCON3 = 0x00;
    // ADMATH registers not updated; 
    ADSTAT = 0x00;
    // ADNREF VSS; ADPREF VDD; 
    ADREF = 0x00;
    // ADACT disabled; 
    ADACT = 0x00;
    // ADCS FOSC/4; 
    ADCLK = 0x01;
    // ADGO stop; ADFM right; ADON enabled; ADCS Frc; ADCONT disabled; 
    ADCON0 = 0x94;
    

}

uint16_t ADC_GetSingleConversion(uint8_t channel){
    ADPCH = channel; // Select the A/D channel
    __delay_us(50);
    
      // Turn on the ADC module
    ADCON0bits.ON = 1;
    
    //Disable the continuous mode.
    ADCON0bits.CONT = 0;   
    
    // Start the conversion
    ADCON0bits.GO = 1;
    
    // Wait for the conversion to finish
    while(ADCON0bits.GO);
    
    // Conversion finished, return the result
    return ((uint16_t)((ADRESH << 8) + ADRESL));
    
}

void ADC_StopConversion (void){
    ADCON0bits.ADON = 0;
    ADCON0bits.GO = 0;
    //PORTAbits.RA0 = 0;
    //LATAbits.LATA0 = 0;
}
