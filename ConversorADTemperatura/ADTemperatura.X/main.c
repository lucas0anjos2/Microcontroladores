//--Bibliotecas do sistema--//
#include <p18f4550.h>
#include <delays.h>
#include <adc.h>


//--Bibliotecas criadas--//
#include "AD.h"
#include "var.h"
#include "lcd.h"

#define _XTAL_FREQ = 12000000;

#pragma CONFIG WTG=OFF // DESLIGA O WATCHDOG TIMER
#pragma config PBADEN = OFF // NECESSÁRIO PARA USAR O DISPLAY.

void main(void) {
    TRISB = 0;//setando as portas B como saída
    voltage = 0; 
    temperatura = 0;
    ADCResult = 0;
    init_ADC(); // Call initialize ADC
    InitXLCD();
 
    while (1) {
        ADCResult = 0;
        SetChanADC(ADC_CH0); //ADCON0 = 0b00000000;  //Select a channel to sample (index i = 0 (first channel) when the loop
        //runs for the first time, i will be 1 then 2 for each successive runs)
        ConvertADC(); // Convert Analog to Digital
        while (BusyADC());
        ADCResult += (unsigned int) ReadADC(); //Read each channel
        voltage = ((ADCResult / 3)*5.0) / 1023; //convert 10-bit ADC data into voltage
        temperatura = (ADCResult*5.0)/10.24; //converte a temperatura de 10mv para celcius
        inicializaTela(converterTemperaturaString(temperatura));
        
        //--NAO ENTENDI POR QUE ESSE FOR DO EFREM--//
//        //---sample and convert---- 
//        for (unsigned char i = 0; i <= 2; i++) //Loop 3 times to sample and read each channel individually.
//        {
//            SetChanADC(ADC_CH0); //ADCON0 = 0b00000000;  //Select a channel to sample (index i = 0 (first channel) when the loop
//            //runs for the first time, i will be 1 then 2 for each successive runs)
//            ConvertADC(); // Convert Analog to Digital
//            while (BusyADC());
//            ADCResult += (unsigned int) ReadADC(); //Read each channel
//            voltage = ((ADCResult / 3)*5.0) / 1023; //convert 10-bit ADC data into voltage
//            temperatura = (ADCResult*5.0)/10.24; //converte a temperatura de 10mv para celcius
//            inicializaTela(converterTemperaturaString(temperatura));
//        }
        
    }
    return;
}
