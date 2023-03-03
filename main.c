#include <msp430.h>
#include <stdint.h>
#include <stdio.h>
#include "libs/leds.h"
#include "libs/timers.h"
#include "libs/i2c.h"
#include "libs/lcd.h"
#include "libs/uart.h"
#include "libs/adc.h"

char comando;   // Command sent via UART.

float convertToVoltage(float);  // Convert ADC12 analog conversion to voltage.

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer.

    // Configure everything needed.
    i2cConfig();
    lcdInit();
    ledsConfig();
    timerConfig();
    uartInit();


    __enable_interrupt();   // Enable interruptions.

    while(1){
        // Initialize variables to read ADC12 analog conversion.
        volatile float readx;
        volatile float ready;

        // Initialize char strings to convert ADC12 analog conversion to voltage.
        char voltageReadingx[8];
        char voltageReadingy[8];

        // Read analog x and y axis.
        readx = analogReadx(3);
        ready = analogReadx(4);

        // Convert the analog readings to voltage.
        readx = convertToVoltage(readx);
        ready = convertToVoltage(ready);

        // Convert the readings to a LCD printable string.
        sprintf(voltageReadingx, "%.2fV", readx);
        sprintf(voltageReadingy, "%.2fV", ready);

        // Print on the LCD the voltage values of the x and y axis of the analog.
        lcdPrint("x:");
        lcdPrint(voltageReadingx);
        lcdNextLine();
        lcdPrint("y:");
        lcdPrint(voltageReadingy);
        __delay_cycles(500000);
        lcdResetDisplay();

        // Conditions to control LEDs PWM period and Duty Cycle based on command sent via UART.
        if (comando == 'f'){
            TA1CCR0 = (int)(2560/readx) - 1;
            TA2CCR0 = (int)(2560/ready) - 1;
            TA1CCR1 = (int)(1280/(readx) - 1);
            TA2CCR1 = (int)(1280/(ready) - 1);
        }
        else if (comando == 'l'){
            TA1CCR0 = 2560 - 1;
            TA2CCR0 = 2560 - 1;
            TA1CCR1 = (int)(1280/readx) - 1;
            TA2CCR1 = (int)(1280/ready) - 1;
        }
    }
}

float convertToVoltage(float adc_value){
    return adc_value / 1023.0 * 3.3;
}

// Timer A1 interruption.
#pragma vector = TIMER1_A1_VECTOR
__interrupt void TA1_CCIFG(){
    switch(TA1IV){
    case TA1IV_TACCR1:
        P1OUT &= ~BIT0;
        break;
    case TA1IV_TAIFG:
        P1OUT |= BIT0;
        break;
    }
}

// Timer A2 interruption.
#pragma vector = TIMER2_A1_VECTOR
__interrupt void TA2_CCIFG(){
    switch(TA2IV){
    case TA2IV_TACCR1:
        P4OUT &= ~BIT7;
        break;
    case TA2IV_TAIFG:
        P4OUT |= BIT7;
        break;
    }
}

// UART interruption.
#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
    switch(UCA1IV){
    case 0:
        break;
    case 2:
        comando = UCA1RXBUF;
        P1OUT ^= BIT0;
        break;
    default:
        break;
    }
}
