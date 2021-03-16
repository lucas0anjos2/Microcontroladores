#include<stdio.h>
#include "trabmicro.h"

void Inicializa(trabmicro * conta, int numero, double saldo)
{
    conta->numero = numero;
    conta->saldo = saldo;
}
void Deposito (trabmicro * conta, double valor)
{
    conta->saldo += valor;
}
void Saque (trabmicro * conta, double valor)
{
    conta->saldo -= valor;
}
void Imprime (trabmicro *conta)
{
    printf("Numero: %d\n", conta->numero);
    printf("Saldo: %f\n", conta->saldo);
}
