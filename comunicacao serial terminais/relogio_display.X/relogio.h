typedef struct{
    int dia;
    int mes;
    int ano;
}calendario;

typedef struct{
    int minuto;
    int segundo;
    int hora;
}relogio;

void inicializa_relogio();
void tratar_relogio(calendario *c, relogio *r);
void verifica_b(int ano);
void tratar_alarme(relogio *c);
int despertar();

