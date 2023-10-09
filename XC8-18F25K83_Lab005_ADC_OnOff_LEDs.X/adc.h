/* 
 * File:   adc.h
 * Author: Pedro
 *
 * Created on 6 de julio de 2022, 02:03 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

void ADC_Initialize(void);
uint16_t ADC_GetSingleConversion(uint8_t channel);
void ADC_StopConversion (void);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

