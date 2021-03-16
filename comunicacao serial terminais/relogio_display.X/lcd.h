#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <xlcd.h>
#include <string.h>
#include <delays.h>

#define _XTAL_FREQ 12000000

void LCD_Clear();
char *exibirData(int dia, int mes, int ano);
char *exibirHora(int h, int m, int s);
void inicializaTela1();
void inicializaTela2();
void atualiza_tela();
void controlaCursor();
void ajustarAlarme();
int setarAlarme();
char *exibirAlarme(int h, int m, int s);
void despertarAlarme();
void controlaCursorR();
void ajustarRelogio();