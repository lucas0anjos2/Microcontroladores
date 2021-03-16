#include "UART.h"

int crc16(char *dados){
    return 1;
}


void tx_data(const char data) { // transmitir dados
    //O sinalizador TXIF é ativado quando TX REG está vazio
    while(TXIF==0); // Wait until RCIF gets low  
    TXREG = data;
}

unsigned char rx_data(void) { // receber dados
    while (!RCIF); // Wait until RCIF gets low - Espere até RCIF ficar baixo
    return RCREG; // Retrieve data from reception register - Recuperar dados do registro de recepção  
}

void UART_Write_Text (const char* str){ // escrever no terminal
   for (int j=0 ; str[j]!='\0'; j++) {
        tx_data(str[j]);
   }   
}

void inicializarUART(){
    i = 0;
    BRGH = 1;
    SPBRG = spbrg_value; // Fill the SPBRG register to set the Baud Rate
    RCSTAbits.SPEN=1;                                     // To activate Serial port (TX and RX pins)
    TXSTAbits.TXEN=1;                                     // To enable transmission
    RCSTAbits.CREN=1;                                     // To enable continuous reception

    RCSTA = 0b10010000; // 0x90 (SPEN RX9 SREN CREN ADEN FERR OERR RX9D)
    TXSTA = 0b00100000; // 0x20 (CSRC TX9 TXEN SYNC - BRGH TRMT TX9D)

    TRISCbits.RC6 = 0; //TX pin set as output
    TRISCbits.RC7 = 1; //RX pin set as input

    //compare with the table above
    RCIF = 0; //reset RX pin flag
    RCIP = 0; //Not high priority
    RCIE = 1; //Enable RX interrupt
    PEIE = 1; //Enable pheripheral interrupt (serial port is a pheripheral)
    
    //HABILITANDO INTERRUP??ES
    INTCONbits.GIEH=1; 
    INTCONbits.GIEL=1;
    
    ESTADO_COMUNICACAO = ESPERA_COMANDO;
}

char converte_char_hex(char dado){
    if(dado == 0x31) return 0x01;
    if(dado == 0x32) return 0x02;
    if(dado == 0x33) return 0x03;
    if(dado == 0x34) return 0x04;
    if(dado == 0x35) return 0x05;
    if(dado == 0x36) return 0x06;
    if(dado == 0x37) return 0x07;
    if(dado == 0x38) return 0x08;
    if(dado == 0x39) return 0x09;
}

void receber_comando(){ 
    serial_data = rx_data();    // Receive data from PC
    dado[i] = converte_char_hex(serial_data);
    i++;
    if(i == 7){
        UART_Write_Text(dado);
        i = 0;
        ESTADO_COMUNICACAO = COMANDO_RECEBIDO;
    }
}

void verifica_comando(){
	if(crc16(dado) == 1){
		ESTADO_COMUNICACAO = COMANDO_OK;
	}else{
		ESTADO_COMUNICACAO = COMANDO_NOK;
    }
}

void realizar_alteracoes(){
    switch(dado[1]){
        case HORA:
            re.hora = BUFFRESP[2];
            re.minuto = BUFFRESP[3];
            re.segundo = BUFFRESP[4];
        break;
        case DDATA:
            ca.dia = BUFFRESP[2];
            ca.mes = BUFFRESP[3];
            ca.ano = BUFFRESP[4];
        break;
        case ALARME:
            alarme.hora = BUFFRESP[2];
            alarme.minuto = BUFFRESP[3];
            alarme.segundo = BUFFRESP[4];
        break;                 
    }   
}

void montar_resposta(){
    BUFFRESP[0] = dado[0];
    BUFFRESP[1] = dado[1];
    BUFFRESP[5] = 0xFF;
    BUFFRESP[6] = 0xFF;
    switch(dado[1]){
        case HORA:
            BUFFRESP[2] = re.hora;
            BUFFRESP[3] = re.minuto;
            BUFFRESP[4] = re.segundo;
        break;
        case DDATA:
            BUFFRESP[2] = ca.dia;
            BUFFRESP[3] = ca.mes;
            BUFFRESP[4] = ca.ano;  
        break;
        case ALARME:
            BUFFRESP[2] = alarme.hora;
            BUFFRESP[3] = alarme.minuto;
            BUFFRESP[4] = alarme.segundo; 
        break;          
    }
}


void trata_comando(){
	switch(dado[0]){
		case COMANDO_LEITURA:
			switch(dado[1]){
				case HORA:
					montar_resposta();                    
					ESTADO_COMUNICACAO = ENVIA_RESPOSTA;					
				break;
				
                case DDATA:                  
                    montar_resposta();
					ESTADO_COMUNICACAO = ENVIA_RESPOSTA;	                   
                break;
                
                case ALARME:
                    montar_resposta();
                    ESTADO_COMUNICACAO = ENVIA_RESPOSTA;
                break;                                
			}
		break;

		case COMANDO_ALTERACAO:
            realizar_alteracoes();
		break;		

    }
}

void envia_respostaTX(){
	tx_data(BUFFRESP[0]);
	tx_data(BUFFRESP[1]);
	tx_data(BUFFRESP[2]);
	tx_data(BUFFRESP[3]);
	tx_data(BUFFRESP[4]);
    tx_data(BUFFRESP[5]);
    tx_data(BUFFRESP[6]);
}



void maquina_estado(){

	switch(ESTADO_COMUNICACAO){
		case COMANDO_RECEBIDO:
            //UART_Write_Text("COMANDO RECEBIDO\r\n");
			ESTADO_COMUNICACAO = VERIFICAR_COMANDO;
		break;

		case VERIFICAR_COMANDO:
           // UART_Write_Text("VERIFICAR COMANDO\r\n");
			verifica_comando();		
		break;
		
		case COMANDO_OK:
            //UART_Write_Text("COMANDO OK\r\n");
			trata_comando();
		break;

		case COMANDO_NOK:
            //UART_Write_Text("COMANDO NAO OK\r\n");
			ESTADO_COMUNICACAO = ESPERA_COMANDO;	
		break;


		case ENVIA_RESPOSTA:
            //UART_Write_Text("ENVIAR RESPOSTA\r\n");
			envia_respostaTX();
			ESTADO_COMUNICACAO = ESPERA_COMANDO;
		break;

		case ESPERA_COMANDO: // ler instrucao serial	
            //UART_Write_Text("ESPERANDO COMANDO\r\n");
			//receber_comando();
		break;
	};
}




