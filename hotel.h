#include <stdio.h>
#include <string.h>

#define ANDARES 20
#define QUARTOS 14
#define TOTAL ANDARES * QUARTOS

typedef struct{
	char status;
	char CPF[14];
	char nome[100];
	char end[100];
	char tel[20];
	char email[50];
	
}hosp;

void fclear();
int for_cpf_valido(char cpf[14]);
int for_andar_valido(int andar, int apt);
void recebe_andar_apt(int *andar, int *apt);
void check_in(hosp hotel[ANDARES][QUARTOS]);
void check_out(hosp hotel[ANDARES][QUARTOS]);
void reservar(hosp hotel[ANDARES][QUARTOS]);
void cancelar_reserva(hosp hotel[ANDARES][QUARTOS]);
void mapa_hotel(hosp hotel[ANDARES][QUARTOS]);
void ocupation(hosp hotel[ANDARES][QUARTOS]);
void recebe_info_hospede(hosp hotel[ANDARES][QUARTOS], int andar, int quarto);
void mostra_info_hospede(hosp hotel[ANDARES][QUARTOS], int andar, int quarto);