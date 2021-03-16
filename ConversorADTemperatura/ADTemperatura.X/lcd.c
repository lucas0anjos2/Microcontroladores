#include "lcd.h"

void DelayFor18TCY(void){
    Delay10TCYx(120);
}

void DelayPORXLCD(void){
    Delay1KTCYx(180);
    return;
} 

void DelayXLCD(void){
    Delay1KTCYx(60);
    return;
}

void InitXLCD(void){
    OpenXLCD(FOUR_BIT & LINES_5X7);
    while(BusyXLCD());
    WriteCmdXLCD(0x06);
    WriteCmdXLCD(0x0C);
}

void LCD_Clear(){
    while(BusyXLCD());
    WriteCmdXLCD(0x01);
}

void inicializaTela(char *t)
{
    SetDDRamAddr(0x0);//move o cursor para o inicio
    putrsXLCD(t);//escreve uma string no lcd
}

char *converterTemperaturaString(float temp)
{
    static char buf[6];
    sprintf(buf,"temp:%f", temp);
    return buf;
}

char *converterVoltagemString(float v)
{
    static char buf[6];
    sprintf(buf,"volt:%f", v);
    return buf;
}