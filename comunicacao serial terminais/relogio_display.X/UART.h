#include "var.h"
#include <plib/usart.h>
#include <stdio.h>


void tx_data(const char data);
unsigned char rx_data(void);
void UART_Write_Text (const char* str);
void inicializarUART();
void verifica_comando();
int crc16(char *dados);
void receber_comando();
char converte_char_hex(char dado);
void envia_respostaTX();