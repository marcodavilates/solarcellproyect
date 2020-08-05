/*
 * File:   ADC.c
 * Author: Marco PIC16F1519
 *
 * Created on 3 de agosto de 2020, 12:56
 */


#include <xc.h>
#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
#define _XTAL_FREQ 8000000
//#define TMR2PRESCALE 16
//long PWM_freq = 5000;
#include <xc.h>
#include <stdio.h>
#include "lcd.h"
/*
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF
 */
void ACD_initialize(){
    ADCON0 = 0b00000001;
    ADCON1 = 0b11010000;
}
unsigned int ADC_Read(unsigned int channel){
    ADCON0 &= 0b10000011;
    ADCON0 |= channel << 2;
    __delay_ms(2);
    GO_nDONE = 1;
    while(GO_nDONE);
    return((ADRESH << 8)+ ADRESL);
}
/*void PWM_initialize(){
    PR2 = (_XTAL_FREQ/(PWM_freq*4*TMR2PRESCALE))-1;
    CCP1M3 = 1;
    CCP1M2 = 1;
    T2CKPS0 = 1;
    T2CKPS1 = 0;
    TMR2ON = 1;
    TRISC2 = 0; 
}

void PWM_Duty(unsigned int duty){
    if(duty<1023){
        duty = ((float)duty/1023)*(_XTAL_FREQ/(PWM_freq*TMR2PRESCALE));
        CCP1X = (duty & 2)>>1;
        CCP1Y = duty & 1;
        CCPR1L = duty >> 2;
        
    }
}
*/
void main(void) {
    int adc;
    float v = 0;
    int flag = 0;
    char s[30];
    //Puertos
    TRISD = 0x00;
    TRISAbits.TRISA0 = 1; 
    ANSELAbits.ANSA0 = 1;
    //Iniciar ADC
    ACD_initialize();
    Lcd_Init();
    //PWM_initialize();
    while(1){
        if(flag>=100){
            adc = (ADC_Read(0));
            v = adc/1023;
            Lcd_Clear();
            flag = 0;
            //PWM_Duty(adc);
            __delay_ms(10);
        }
        flag++;
        sprintf(s,"Res: %d",adc);
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String(s);
        sprintf(s,"D is: %f",v);
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String(s);
    }
    return;
}