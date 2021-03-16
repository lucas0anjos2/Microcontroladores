#include <xc.h>
#include <delays.h>

#pragma CONFIG WTG=OFF
#define _XTAL_FREQ 4000000 // define a frequencia
#define POLY 0x8408

// métodos neccessários para usar o delay
void DelayFor18TCY(void){
    Delay10TCYx(120);
}

void DelayPORXLCD(void){
    Delay1KTCYx(180);
    return;
} 

void main(void) {
    
    // configurando as portas
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD0 = 0;
    
    while(1){
        // debouncing
        if(PORTDbits.RD6 == 1){
            __delay_ms(180);
            PORTDbits.RD0 = 1;
            __delay_ms(500);
            PORTDbits.RD0 = 0;
            while(PORTDbits.RD6==1){} 
        }
        
    }
    
    return;
}
