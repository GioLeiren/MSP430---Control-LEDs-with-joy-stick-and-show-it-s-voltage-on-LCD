#include <msp430.h>
#include <stdint.h>
#include "adc.h"

// Read analog input.
float analogReadx(uint8_t pinx){
    ADC12CTL0 &= ~ADC12ENC;
    ADC12CTL0 |= ADC12SHT0_4 | ADC12ON;

    ADC12CTL1 = ADC12CSTARTADD_0 | ADC12SHS_0 |
            ADC12SHP | ADC12SSEL_0 |
            ADC12CONSEQ_0;

    ADC12CTL2 = ADC12TCOFF | ADC12RES_2;

    P6SEL |= 1 << pinx;

    ADC12MCTL0 = pinx;

    ADC12CTL0 |= ADC12ENC;
    ADC12CTL0 &= ~ADC12SC;
    ADC12CTL0 |= ADC12SC;

    while (!(ADC12IFG & ADC12IFG0));

    return ADC12MEM0;
}

float analogReady(uint8_t piny){
    ADC12CTL0 &= ~ADC12ENC;
    ADC12CTL0 |= ADC12SHT0_4 | ADC12ON;

    ADC12CTL1 = ADC12CSTARTADD_0 | ADC12SHS_0 |
            ADC12SHP | ADC12SSEL_0 |
            ADC12CONSEQ_0;

    ADC12CTL2 = ADC12TCOFF | ADC12RES_2;

    P6SEL |= 1 << piny;

    ADC12MCTL0 = piny;

    ADC12CTL0 |= ADC12ENC;
    ADC12CTL0 &= ~ADC12SC;
    ADC12CTL0 |= ADC12SC;

    while (!(ADC12IFG & ADC12IFG0));

    return ADC12MEM0;
}
