//#include <plib/usart.h>
#include <p18f4550.h>
#include "UART.h"
#include "relogio.h"
#include "lcd.h"

#pragma CONFIG WTG=OFF // DESLIGA O WATCHDOG TIMER
#pragma config PBADEN = OFF // NECESS?RIO PARA USAR O DISPLAY.

void main(){ 
    inicializarUART();
    inicializa_relogio();
    maquina_estado();
    InitXLCD();
    inicializaTela1();
    
    while(1){
        
        
        if(flagDisplay == 1){
            atualiza_tela();
            flagDisplay = 0;
        }
        
        if(PORTDbits.RD0 == 1){ // botao para mudar tela
            __delay_ms(180);
            LCD_Clear();
            flagTela++;
            if(flagTela>2) flagTela = 1;
            while(PORTDbits.RD0==1){} 
        }
        
        if(PORTDbits.RD1 == 1){ // bot?o mover cursor
            __delay_ms(180);
            posCursor++;
            posCursorR++;
            if(posCursor > 2) posCursor = 0;
            if(posCursorR > 6) posCursorR = 0;
            while(PORTDbits.RD1==1){}
        }
        
        if(flagTela == 1) ajustarT1();
        if(flagTela == 2 && flagAlarme == 0) ajustarAlarme();  // so ajusto o alarme se estiver na tela 2 e ele nao estiver disparando
        if(despertar() == 1)  flagAlarme = 1; // se o horario do alarme coincidiu vou acionar a variavel de controle
        
        if(flagAlarme == 1) { // se a variavel de controle for acionada vou exibir o aviso na tela por 35 segundos
            if(tempoAlarme < 35){
                despertarAlarme();
            }else{
                flagAlarme = 0;
            }
                
        }
    }
}


void interrupt SerialRxPinInterrupt(){
    if(TMR0IF){  
        TMR0=2535;// RESETA CONTADOR PARA O VALOR ESTABELECIDO (AJUSTE PARA OS SEGUNDOS)
        INTCONbits.TMR0IF=0; //ZERA A FLAG DO TIMER0
        contador++;
    }
    if(contador>1){ // AJUSTE DE C?LCULO PARA OS SEGUNDOS
        if(flag_inicializacao == 1 ){ // garantindo que na primeira execu??o ser? exibido o segundo "zero"
            flag_inicializacao = -1;
        }else{
            tratar_relogio(&ca, &re); // FUN??O PARA O REL?GIO SE AJUSTAR
            flagDisplay = 1;
            contador=0;
        }              
    }
    
    //check if the interrupt is caused by RX pin
    if(PIR1bits.RCIF == 1){
        if(i<7){
        	while(!RCIF);                            // Wait until RCIF gets low
            	dado[i]= converte_char_hex(RCREG);                                 // Retrieve data from reception register
            	i++;  
        }else{
            PIR1bits.RCIF = 0; // clear rx flag
            i=0;
			ESTADO_COMUNICACAO = COMANDO_RECEBIDO;
        } 
    }
}