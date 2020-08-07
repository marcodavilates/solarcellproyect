/*
 * File:   lcd15.c
 * Author: user
 *
 * Created on 1 de agosto de 2020, 22:47
 */

#define _XTAL_FREQ 8000000
#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

#include <xc.h>
#include "lcd.h"

#pragma config FOSC = HS
#pragma config WDTE = ON
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

void main(void) {
    unsigned int a;
    OSCCON = 0b01110000;
    TRISB0 = 0;
    TRISB1 = 0;
    TRISD = 0b00000000;
    Lcd_Init();
    __delay_ms(5); 
    RB1 = 1;
    while(1)
    {
       RB0 = 0;
       RD1 = 0;
       __delay_ms(1000); 
       RB0 = 1;
       RD1 = 1;
       __delay_ms(1000);
       Lcd_Clear();
       Lcd_Set_Cursor(1,1);
       Lcd_Write_String("Te quiero");
       Lcd_Set_Cursor(2,1);
       Lcd_Write_String("Gabriela Granda");
       __delay_ms(1000);
    }   
    return;
}