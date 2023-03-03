#include <msp430.h>
#include <stdint.h>
#include "leds.h"

void ledsConfig(){
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    P4DIR |= BIT7;
    P4OUT &= ~BIT7;
}
