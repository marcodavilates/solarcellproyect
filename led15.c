/*
 * File:   led.c
 * Author: user
 *
 * Created on 1 de agosto de 2020, 22:47
 */

#define _XTAL_FREQ 8000000

#include <xc.h>

#pragma config FOSC = HS
#pragma config WDTE = ON
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

void main(void) {
    TRISB0 = 0;
    while(1)
    {
       RB0 = 1;  
       __delay_ms(1000); 
       RB0 = 0;
       __delay_ms(1000);
    }   
    return;
}