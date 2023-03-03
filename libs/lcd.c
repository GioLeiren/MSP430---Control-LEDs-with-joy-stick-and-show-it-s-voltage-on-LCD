#include <msp430.h>
#include <stdio.h>
#include "i2c.h"
#include "lcd.h"

// Incializar LCD modo 4 bits
void lcdInit(void){
    //modo 8 bits
    lcdWrNib(0x3, 0);
    lcdWrNib(0x3, 0);
    lcdWrNib(0x3, 0);

    //modo 4 bits
    lcdWrNib(0x2, 0);

    //numero de linhas
    lcdWrByte(0x28, 0);

    //ativar display e cursor
    lcdWrByte(0x0F, 0);

    //limpar display
    lcdWrByte(0x01, 0);
}


// Escrever
void lcdWrNib(uint8_t nib, uint8_t isChar)
{
    nib = nib << 4;
    i2cSend(0x27, nib | BIT3 |  0   | isChar);
    i2cSend(0x27, nib | BIT3 | BIT2 | isChar);
    i2cSend(0x27, nib | BIT3 |  0   | isChar);
}

void lcdWrByte(uint8_t byte, uint8_t isChar){
    lcdWrNib(byte >> 4, isChar);
    lcdWrNib(byte & 0xF, isChar);
}

void lcdPrint(char * str){
    while(*str){
        lcdWrByte(*str++, 1);
    }

}

void lcdNextLine(void){
    lcdWrByte(0xC0, 0);
}

void lcdResetDisplay(void){
    lcdWrByte(0x80, 0);
    lcdWrByte(0x01, 0);
}
