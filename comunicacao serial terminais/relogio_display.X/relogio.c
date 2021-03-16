#include "relogio.h"
#include "var.h"
#include <xc.h>


void inicializa_relogio(){
    //inicializa??o das vari?veis do rel?gio
    ca.ano = 2004;
    ca.mes = 2;
    ca.dia = 28;
    re.hora=23;
    re.minuto=59;
    re.segundo=35;
    alarme.hora = 0;
    alarme.minuto = 0;
    alarme.segundo = 1;
    flagDisplay = 1;
    flag_inicializacao = 1;
    contador = 0;
    flagTela = 1;
    T1 = 0;
    T2 = 0;
    posCursor = 0;
    posCursorR = 0;
    tempoAlarme = 0;
    
    T0CONbits.TMR0ON=1; // HABILITA O TIMER 0;
    INTCONbits.TMR0IE=1; // HABILITA A FLAG DE INTERRUP??O.
    INTCONbits.TMR0IF=0; // LIMPA A FLAG.
    // C?LCULO DE CONTADOR DA INTERRUP??O:
    T0CONbits.T08BIT=0;
    T0CONbits.PSA=0;
    T0CONbits.T0PS0=1;
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS2=1;
    T0CONbits.T0CS=0; // UTILIZAR CLOCK INTERNO.
    
    TMR0=2535; // DE ONDE INICIA O CONTADOR. 
    
    T0CONbits.TMR0ON=1;// HABILITA O TIMER0
    
    TRISB = 0; // SETA TODAS AS PORTAS B COMO SA?DA
    TRISD = 1; // SETA TODAS AS PORTAS D COMO ENTRADA
    
    qtdDias_mes[0] = 31;
    qtdDias_mes[1] = 28;
    qtdDias_mes[2] = 31;
    qtdDias_mes[3] = 30;
    qtdDias_mes[4] = 31;
    qtdDias_mes[5] = 30;
    qtdDias_mes[6] = 31;
    qtdDias_mes[7] = 31;
    qtdDias_mes[8] = 30;
    qtdDias_mes[9] = 31;
    qtdDias_mes[10] = 30;
    qtdDias_mes[11] = 31;
}

void verifica_b(int ano){ // VERIFICAÇÃO E AJUSTE SE O ANO EM QUESTÃO É BISSEXTO OU NÃO
    if(ano%4==0){
        qtdDias_mes[1] = 29;
    }else{
        qtdDias_mes[1] = 28;
    }
}

void tratar_relogio(calendario *c, relogio *r){ // AJUSTE DO FUNCIONAMENTO DO RELÓGIO
    r->segundo++;
    verifica_b(c->ano);
    if(tempoAlarme < 35 && flagAlarme == 1){
        tempoAlarme++;
    }else{
        tempoAlarme = 0;
    }
        
    if(r->segundo > 59){
        r->minuto++;
        r->segundo = 0;
    }
    if(r->minuto > 59){
        r->hora++;
        r->minuto = 0;
    }    
    if(r->hora > 23){
        c->dia++;
        r->hora = 0;
    }    
    if(c->dia > qtdDias_mes[c->mes-1]){
        c->mes++;
        c->dia = 1;
    }    
    if(c->mes > 12){
        c->ano++;
        c->mes = 1;
        c->dia = 1;
        verifica_b(c->ano);
    } 
    if(c->dia < 1){
        c->dia = qtdDias_mes[c->mes -2];
        c->mes--;
    }
    if(c->mes < 1){
        c->mes = 12;
        c->ano--;
        verifica_b(c->ano);
    }
    
    if(c->ano < 0) c->ano = 0;
    
    if(r->hora < 0){
        c->dia--;
        r->hora = 23;
    }

    if(r->minuto < 0){
        r->minuto = 59;
        r->hora--;
    }
    
    if(r->segundo < 0){
        r->segundo = 59;
        r->minuto--;
    }   
}

void tratar_alarme(relogio *c){
    if(c->hora > 23) c->hora = 0;
    
    if(c->minuto > 59) c->minuto = 0;
    
    if(c->segundo > 59) c->segundo = 0;
    
    if(c->hora < 0) c->hora = 23;
    
    if(c->minuto < 0) c->minuto = 59;
    
    if(c->segundo < 0) c->segundo = 59;
    
}

int despertar(){
    if(re.hora == alarme.hora && re.minuto == alarme.minuto && re.segundo == alarme.segundo){
        return 1;
    }else{
        return 0;
    }   
}