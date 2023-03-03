#include <msp430.h>
#include <stdint.h>
#include "timers.h"

void timerConfig(){
    TA0CTL = TASSEL_1 | MC_1;
    TA0CCR0 = 128 - 1;  // 2 gatilhos (256/2)
    TA0CCR1 = 64 - 1;
    TA0CCTL1 = OUTMOD_6;

    TA1CTL = TASSEL_1 | MC_1 | TAIE;
    TA1CCTL1 = CCIE;
    TA1CCR0 = 2560 - 1;
    TA1CCR1 = 128 - 1;

    TA2CTL = TASSEL_1 | MC_1 | TAIE;
    TA2CCTL1 = CCIE;
    TA2CCR0 = 2560 - 1;
    TA2CCR1 = 128 - 1;
}
