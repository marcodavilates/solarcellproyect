/*
 * File:   MPPT.c
 * Author: user
 *
 * Created on 9 de agosto de 2020, 11:08
 */
/*
 * File:   mppt.c
 * Author: user
 *
 * Created on 9 de agosto de 2020, 11:01
 */

#define _XTAL_FREQ 8000000
#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
#define TMR2PRESCALE 1

#include <xc.h>
#include <stdio.h>
#include "lcd.h"

long FPWM = 30000;
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

void ACD_initialize(){
    ADCON0 = 0b00000001;
    ADCON1 = 0b11010000;
}
unsigned int ADC_Read(unsigned int channel){
    ADCON0 &= 0b10000011;
    ADCON0 |= (channel << 2);
    __delay_ms(3);
    GO_nDONE = 1;
    while(GO_nDONE);
    return((ADRESH << 8)+ ADRESL);
}
void PWM_initialize(){
    TRISC2 = 0;
    T2CON = 0b00000100;
    CCP1CON =0b00001100;
    PR2 = 64;
}
void PWM_Duty(unsigned int duty){
    if(duty<1023){
        duty =((float)duty/1023)*4*(PR2+1);
        CCPR1L = duty >> 2;
        DC1B1 = (duty & 2)>>1;
        DC1B0 = duty & 1;
        TRISC2=0;
    }
}
void main(void) {
   int adc;
   float d;
   char s[16];
//  PUERTOS
    ANSA0 = 1;
    TRISA0 = 1;
    ANSC2 = 0;
    ANSELD = 0x00;
    TRISD = 0x00;
// CONFIGURACIONES
    OSCCON = 0b01110000;
// VALORES  
   PWM_initialize();
   ACD_initialize();
   Lcd_Init();
    while(1){
       adc = ADC_Read(0); 
       PWM_Duty(adc);
       __delay_ms(100);
       d = ((float)adc/1023);
       Lcd_Clear();
       __delay_ms(200);
       Lcd_Set_Cursor(1,1);
       sprintf(s,"D is: %f",d);
       __delay_us(20);
       Lcd_Write_String(s);
    };
    return;
}
