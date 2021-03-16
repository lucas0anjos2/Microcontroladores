#include "AD.h"
#include "var.h"
#include <adc.h>

void init_ADC(void)        //Configure ADC with 3 analog channels
{

OpenADC(ADC_FOSC_64 &              // ADC_FOSC_64:      Clock de convers�o do A/D igual a
                        //               FAD = FOSC/64 = 48MHz/64 = 750kHz
                        //               Desta Forma, TAD=1/FAD = 1,33us.
         ADC_RIGHT_JUST &            // ADC_RIGHT_JUST:    Resultado da convers�o ocupar� os
                        //               bits menos significativos dos regis-
                        //               tradores ADRESH e ADRESL.
         ADC_12_TAD,               // ADC_12_TAD:              Determina o tempo de convers�o de uma
                        //               palavra de 10-bits. Neste caso ser�
                        //               igual a 12*TAD = 12*1,33us = 16us.
         
         ADC_CH0 &          // ADC_CH0:         Atua sobre os bits CHS3:CHS0 do ADCON0
                        //               para selecionar o canal no qual ser�
                        //               realizada a convers�o. Neste caso o AN0.
         ADC_INT_OFF &       // ADC_INT_OFF:      Habilita ou Desabilita a interrup��o de t�rminio de
                        //               convers�o.
         ADC_REF_VDD_VSS,    //ADC reference voltage from VDD & VSS
         ADC_1ANA);         // BITs PCFG3:PCFG0:        Configura os pinos  AN1(RA1) e AN0(RA0) como Entradas Anal�gicas
}
