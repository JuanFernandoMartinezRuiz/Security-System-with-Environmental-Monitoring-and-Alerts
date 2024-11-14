#include <xc.h>
#include "KEYPAD.h"
#include "CONFIG.h"

void keypad_init(void){
    PTECLADO &= ~(1<<PB0) & ~(1<<PB1) & ~(1<<PB2) & ~(1<<PB3);   // FILAS - SALIDA
    PTECLADO |= (1<<PB4) | (1<<PB5) | (1<<PB6) | (1<<PB7);       // COLUMNAS - ENTRADA
    OPTION_REGbits.nRBPU = 0;   // PORTB pull-ups are enabled by individual port latch values
    WPUB = 0xFF;                // Enable weak pull-ups on PORTB for columns
    ANSELH = 0;                 // Disable analog inputs on high ports
}

char keypad_getkey(void){
    char letras[4][4] = { {'1','2','3','A'},
                          {'4','5','6','B'},
                          {'7','8','9','C'},
                          {'*','0','#','D'} };
    int i = 0;
    char valor = 0;

    for(i = 0; i < 4; i++){
        if(i == 0){
            FILAS = (1 << COL4) | (1 << COL3) | (1 << COL2) | (0 << ROW1);
            __delay_us(100);
            if (!(COLUMNAS & (1 << COL1))){ valor = letras[0][0]; }  // '1'
            if (!(COLUMNAS & (1 << COL2))){ valor = letras[0][1]; }  // '2'
            if (!(COLUMNAS & (1 << COL3))){ valor = letras[0][2]; }  // '3'
            if (!(COLUMNAS & (1 << COL4))){ valor = letras[0][3]; }  // 'A'
        }
        if(i == 1){
            FILAS = (1 << COL4) | (1 << COL3) | (1 << COL2) | (1 << ROW1) | (0 << ROW2);
            __delay_us(100);
            if (!(COLUMNAS & (1 << COL1))){ valor = letras[1][0]; }  // '4'
            if (!(COLUMNAS & (1 << COL2))){ valor = letras[1][1]; }  // '5'
            if (!(COLUMNAS & (1 << COL3))){ valor = letras[1][2]; }  // '6'
            if (!(COLUMNAS & (1 << COL4))){ valor = letras[1][3]; }  // 'B'
        }
        if(i == 2){
            FILAS = (1 << COL4) | (1 << COL3) | (1 << COL2) | (1 << ROW1) | (1 << ROW2) | (0 << ROW3);
            __delay_us(100);
            if (!(COLUMNAS & (1 << COL1))){ valor = letras[2][0]; }  // '7'
            if (!(COLUMNAS & (1 << COL2))){ valor = letras[2][1]; }  // '8'
            if (!(COLUMNAS & (1 << COL3))){ valor = letras[2][2]; }  // '9'
            if (!(COLUMNAS & (1 << COL4))){ valor = letras[2][3]; }  // 'C'
        }
        if(i == 3){
            FILAS = (1 << COL4) | (1 << COL3) | (1 << COL2) | (1 << ROW1) | (1 << ROW2) | (1 << ROW3) | (0 << ROW4);
            __delay_us(100);
            if (!(COLUMNAS & (1 << COL1))){ valor = letras[3][0]; }  // '*'
            if (!(COLUMNAS & (1 << COL2))){ valor = letras[3][1]; }  // '0'
            if (!(COLUMNAS & (1 << COL3))){ valor = letras[3][2]; }  // '#'
            if (!(COLUMNAS & (1 << COL4))){ valor = letras[3][3]; }  // 'D'
        }
    }
    return valor;
}