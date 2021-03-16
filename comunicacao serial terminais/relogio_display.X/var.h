#include "relogio.h"

//Definicoes para parametros do pic
#define _XTAL_FREQ 12000000 //The speed of your internal(or)external oscillator
#define POLY 0x8408
#define FREQ 12000000    // Frequency = 12MHz
#define baud 9600
#define spbrg_value (((FREQ/64)/baud)-1)    // Refer to the formula for Baud rate calculation in Description tab

//parametros para protocolo UART
#define ESPERA_COMANDO      0x00
#define COMANDO_RECEBIDO    0x01
#define VERIFICAR_COMANDO   0x02
#define COMANDO_OK          0x03
#define COMANDO_NOK         0x04
#define ENVIA_RESPOSTA      0x05
#define COMANDO_LEITURA     0x01
#define COMANDO_ALTERACAO   0x02
#define HORA                0x01
#define DDATA               0x02
#define ALARME              0x03

//variaveis protocolo UART
unsigned char ESTADO_COMUNICACAO;
unsigned char serial_data;
unsigned int i ;
unsigned char dado[7];
unsigned char BUFFRESP[7];


//variaveis relogio
calendario ca;
relogio re;
relogio alarme;
int flagDisplay; // controla a atualiza??o da hora no display
int flag_inicializacao; // garante que a primeira contagem inicie no 0
int contador; // ajusta o c?lculo para contagem dos segundos
int qtdDias_mes[12]; // dias para cada m?s do ano
int flagTela; // controle de qual tela exibir
int T1, T2; // controle de inicializa??es das telas
int posCursor; // controla a posicao do cursor para a tela de alarme
int posCursorR; // controla a posicao do cursor para a tela do relogio
int flagAlarme;// controla se o alarme deve ser acionado ou nao
int tempoAlarme;// control o tempo que o alarme permanesce acionado