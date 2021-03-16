#ifndef TRABMICRO_H_INCLUDED
#define TRABMICRO_H_INCLUDED


// definição do tipo
typedef struct
{
    int numero;
    double saldo;
} trabmicro;
// cabeçalho das funções

void Inicializa(trabmicro * conta, int numero, double saldo);
void Deposito (trabmicro * conta, double valor);
void Saque (trabmicro * conta, double valor);
void Imprime (trabmicro * conta);


#endif // TRABMICRO_H_INCLUDED
