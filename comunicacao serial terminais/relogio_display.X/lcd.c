#include "lcd.h"
#include "var.h"

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
   // WriteCmdXLCD(0x06); // Move cursor right, dont shift display
   // WriteCmdXLCD(0x0C); // liga o cursor
}

void LCD_Clear(){
    while(BusyXLCD());
    WriteCmdXLCD(0x01);
}

void controlaCursor(){ // controla o cursor na tela 2
    switch(posCursor){
        case 0:
            SetDDRamAddr(0x41);
            break;
        case 1:
            SetDDRamAddr(0x44);
            break;
        case 2:
            SetDDRamAddr(0x47);
            break;
        default:
            return;
            
    }
}

void controlaCursorR(){ // controla o cursor na tela 1
    switch(posCursorR){
        case 0:
            WriteCmdXLCD(0x0F); // liga cursor piscando
            break;
        case 1:
            SetDDRamAddr(0x07);
            break;
        case 2:
            SetDDRamAddr(0x0A);
            break;
        case 3:
            SetDDRamAddr(0x0D);
            break;
        case 4:
            SetDDRamAddr(0x47);
            break;
        case 5:
            SetDDRamAddr(0x4A);
            break;
        case 6:
            SetDDRamAddr(0x4F);
            break;
        case 7:
            WriteCmdXLCD(0x0C); // desliga o cursor
            break;
        default:
            return;     
    }
}

char *exibirData(int dia, int mes, int ano){
    static char *string;
    if(dia >= 10 && mes >= 10){ //d e m > 10
        sprintf(string, "DATA: %i/%i/%i", dia, mes, ano);
    }
    if(dia >= 10 && mes < 10){ //d  > 10
        sprintf(string, "DATA: %i/0%i/%i", dia, mes, ano);
    }
    if(dia < 10 && mes >= 10){ //m  > 10
        sprintf(string, "DATA: 0%i/%i/%i", dia, mes, ano);
    }if(dia < 10 && mes < 10){ //d e m  < 10
        sprintf(string, "DATA: 0%i/0%i/%i", dia, mes, ano);
    }
    return string;
}

char *exibirHora(int h, int m, int s){
    static char *string;
    //adicionando zero à esquerda quando necessário
    if(h >= 10 && m >= 10 && s >= 10){  // todos > 10
        sprintf(string, "HORA: %i:%i:%i", h, m, s);
    }
    if(h >= 10 && m >= 10 && s < 10){ // h e m > 10
        sprintf(string, "HORA: %i:%i:0%i", h, m, s);
    }
    if(h >= 10 && m < 10 && s >= 10){  // h e s > 10
        sprintf(string, "HORA: %i:0%i:%i", h, m, s);
    }if(h >= 10 && m < 10 && s < 10){  // h > 10
        sprintf(string, "HORA: %i:0%i:0%i", h, m, s);
    }
    if(h < 10 && m >= 10 && s >= 10){ // m e s > 10
        sprintf(string, "HORA: 0%i:%i:%i", h, m, s);
    }
    if(h < 10 && m >= 10 && s < 10){ // m > 10
        sprintf(string, "HORA: 0%i:%i:0%i", h, m, s);
    }
    if(h < 10 && m < 10 && s >= 10){ // s > 10
        sprintf(string, "HORA: 0%i:0%i:%i", h, m, s);
    }
    if(h < 10 && m < 10 && s < 10){ // todos < 10
        sprintf(string, "HORA: 0%i:0%i:0%i", h, m, s);
    }
    return string;
}

char *exibirAlarme(int h, int m, int s){
    static char *string;
    //adicionando zero à esquerda quando necessário
    if(h >= 10 && m >= 10 && s >= 10){  // todos > 10
        sprintf(string, "%i:%i:%i", h, m, s);
    }
    if(h >= 10 && m >= 10 && s < 10){ // h e m > 10
        sprintf(string, "%i:%i:0%i", h, m, s);
    }
    if(h >= 10 && m < 10 && s >= 10){  // h e s > 10
        sprintf(string, "%i:0%i:%i", h, m, s);
    }if(h >= 10 && m < 10 && s < 10){  // h > 10
        sprintf(string, "%i:0%i:0%i", h, m, s);
    }
    if(h < 10 && m >= 10 && s >= 10){ // m e s > 10
        sprintf(string, "0%i:%i:%i", h, m, s);
    }
    if(h < 10 && m >= 10 && s < 10){ // m > 10
        sprintf(string, "0%i:%i:0%i", h, m, s);
    }
    if(h < 10 && m < 10 && s >= 10){ // s > 10
        sprintf(string, "0%i:0%i:%i", h, m, s);
    }
    if(h < 10 && m < 10 && s < 10){ // todos < 10
        sprintf(string, "0%i:0%i:0%i", h, m, s);
    }
    return string;
}

void inicializaTela1(){
    if(T1 == 0){
        WriteCmdXLCD(0x0C); // desliga cursor
        T1 = 1;
        T2 = 0;
    }else{
        SetDDRamAddr(0x0);//move o cursor para o inicio
        putrsXLCD(exibirHora(re.hora, re.minuto, re.segundo));//escreve uma string no lcd
        SetDDRamAddr(0x40);//move o cursor para a segunda linha
        putrsXLCD(exibirData(ca.dia, ca.mes, ca.ano));
        controlaCursorR(); 
    }
}

void inicializaTela2(){
    if(T2 == 0){
        if(flagAlarme == 0){ // so ligo o cursor se o alarme nao estiver disparando
            WriteCmdXLCD(0x0F); // liga cursor piscando
        }
        T2 = 1;
        T1 = 0;
    }else{
        SetDDRamAddr(0x0);
        putsXLCD("ALARME: ");
        SetDDRamAddr(0x40);
        putrsXLCD(exibirAlarme(alarme.hora, alarme.minuto, alarme.segundo));
        controlaCursor(); 
    }
}

void atualiza_tela(){
    switch(flagTela){
        case 1:
            inicializaTela1();
            break;
        case 2:
            inicializaTela2();
            break;
            
        default:
            return; 
    }
}


void ajustarRelogio(){}



void ajustarAlarme(){
    if(PORTDbits.RD2 == 1){ // botão incrementar
        __delay_ms(180);
        if(posCursor == 0){
            alarme.hora++;
        }
        if(posCursor == 1){
            alarme.minuto++;
        }
        if(posCursor == 2){
            alarme.segundo++;
        }
        while(PORTDbits.RD2 == 1) {}
    }
    
    if(PORTDbits.RD3 == 1){ // botão decrementar
        __delay_ms(180);
        if(posCursor == 0){
            alarme.hora--;
        }
        if(posCursor == 1){
            alarme.minuto--;
        }
        if(posCursor == 2){
            alarme.segundo--;
        }
        while(PORTDbits.RD3 == 1) {}
    }
    tratar_alarme(&alarme);
}

int setarAlarme(){
    switch(posCursor){
        case 0:
            return 1;
            break;
        case 1:
            break;
        case 2:
            break;
        default:
            return;
    }
    return 0;
}


void despertarAlarme(){
    WriteCmdXLCD(0x0C);
    SetDDRamAddr(0x0F);
    putsXLCD("A");
    SetDDRamAddr(0x0F);
    putsXLCD(" ");
}

void ajustarT1(){
    if(PORTDbits.RD2 == 1){ // botão incrementar
        __delay_ms(180);
        if(posCursorR == 1){
            re.hora++;
        }
        if(posCursorR == 2){
            re.minuto++;
        }
        if(posCursorR == 3){
            re.segundo++;
        }
        if(posCursorR == 4){
            ca.dia++;
        }
        if(posCursorR == 5){
            ca.mes++;
        }
        if(posCursorR == 6){
            ca.ano++;
        }
        while(PORTDbits.RD2 == 1) {}
    }
    
    if(PORTDbits.RD3 == 1){ // botão decrementar
        __delay_ms(180);
        if(posCursorR == 1){
            re.hora--;
        }
        if(posCursorR == 2){
            re.minuto--;
        }
        if(posCursorR == 3){
            re.segundo--;
        }
        if(posCursorR == 4){
            ca.dia--;
        }
        if(posCursorR == 5){
            ca.mes--;
        }
        if(posCursorR == 6){
            ca.ano--;
        }
        while(PORTDbits.RD3 == 1) {}
    }
    
}