/* ENTREGA FINAL */

#include "hotel.h"

int main()
{
	int andar,quarto;

	int option;
	hosp hotel[ANDARES][QUARTOS];

	char options[8][100] = 
	{
	"Check-in de hospede", 
	"Check-out de hospede", 
	"Reservar apartamento",
	"Cancelar uma reserva", 
	"Mapa de ocupacao e reservas do hotel", 
	"Informacoes do hospede",
	"Taxas de ocupacao e reservas do hotel", 
	"Sair do programa"
	};
	
	for(andar = 0; andar < ANDARES; andar++){
		for(quarto = 0; quarto < QUARTOS; quarto++){
			hotel[andar][quarto].status = '.';
		}
	}
	
	do
	{	
		//exibi todas as opções disponiveis
		for(int i = 1;i <= 8; i++)
			printf("(%d) - %s\n", i, options[i - 1]);
		
		printf("\nEscolha uma opcao: ");
		scanf("%d", &option);

		//Verifica se a opção informada é válida
		if(option < 1 || option > 8){
			printf("Opcao invalida, digite uma opcao de 1 a 8\n\n");
			continue;
		}
			
		switch(option)
		{
			case 1:
			    check_in(hotel);
				break;
			case 2:
				check_out(hotel);
				break;
			case 3: 
				reservar(hotel);
				break;
			case 4:
				cancelar_reserva(hotel);
				break;
			case 5: 
				mapa_hotel(hotel);
				break;
			case 6:
				recebe_andar_apt(&andar , &quarto);
				mostra_info_hospede(hotel, andar - 1, quarto - 1);
				break;
			case 7:
				ocupation(hotel);
				break;
			case 8: break;
		}
				
	}while(option != 8);
	

	return 0;
}
void fclear()
{
	//Realiza a limpeza do buffer
	char carac;
	while( (carac = fgetc(stdin)) != EOF && carac != '\n'){}
	
}

int for_andar_valido(int andar, int apt)
{
	//Verifica se o numero do andar e do quarto,de fato, existem
	if((andar < 1 || andar > 20) || (apt < 1 || apt > 14)){
		return 0;
	}
	return 1;
}

void recebe_andar_apt(int *andar, int *apt)
{
	//Recebe o numero do andar e do quarto
	printf("Informe o numero do andar: ");
	scanf("%d", andar);
	
	printf("Informe o numero do apartamento: ");
	scanf("%d", apt);
}
void mapa_hotel(hosp hotel[ANDARES][QUARTOS])
{
	//Exibe o mapa atualizado do hotel
	printf("\nApto - >\t");
	for(int apt = 1; apt <= 14; apt++){
		printf("%2d  ", apt);
	}
	printf("\n\n");
	for(int andar = 19; andar >= 0; andar --)
	{
		printf("Andar %02d\t ", andar + 1);
		for(int apt = 0; apt < 14; apt++){
			printf("%c   ",hotel[andar][apt].status);
		}
		printf("\n");
	}
	printf("\n");
}

void reservar(hosp hotel[ANDARES][QUARTOS])
{
	//Faz uma reserva
	int andar, apt;
	
	printf("-- Reservar quarto\n");
	recebe_andar_apt(&andar, &apt);
	
	if(!for_andar_valido(andar,apt)){
		printf("\nNumero do andar e/ou apartamento nao existem\n\n");
		return;
	}

	if(hotel[andar-1][apt-1].status == 'R' || hotel[andar-1][apt-1].status == 'O'){
		printf("\nApartamento ja reservado ou ocupado :( \n\n");
	}
	else{
		hotel[andar-1][apt-1].status = 'R';
		printf("\nReservado com sucesso !\n\n");
	}
	
}

void cancelar_reserva(hosp hotel[ANDARES][QUARTOS])
{
	//Cancela uma reserva
	int andar, apt;

	printf("-- Cancelar reserva de quarto\n");
	recebe_andar_apt(&andar, &apt);

	if(!for_andar_valido(andar,apt)){
		printf("\nNumero do andar e/ou apartamento nao existem\n\n");
		return;
	}

	switch (hotel[andar-1][apt-1].status)
	{
		case('R'):
			hotel[andar-1][apt-1].status = '.';
			printf("\nReserva cancelada com sucesso.\n\n");
			break;
		case('O'):
			printf("\nApartamento ja ocupado\n\n");
			break;
		default:
			printf("\nApartamento ja desocupado\n\n");
			break;
	}
	
}

void check_in(hosp hotel[ANDARES][QUARTOS])
{
	//Realiza o check-in de um quarto
	int andar, apt;

    printf("-- Check-in de quarto\n");
	recebe_andar_apt(&andar, &apt);

	if(!for_andar_valido(andar,apt)){
		printf("\nNumero do andar e/ou apartamento nao existem\n\n");
		return;
	}

	if(hotel[andar-1][apt-1].status == 'O'){
		printf("\nApartamento ja ocupado\n\n");
		return;
	}

	hotel[andar-1][apt-1].status = 'O';
	recebe_info_hospede(hotel, andar - 1, apt - 1);
	printf("\nCheck-in realizado com sucesso\n\n");

}

void check_out(hosp hotel[ANDARES][QUARTOS])
{
	//Realiza o check-out do quarto
	int andar, apt;

	printf("-- Check-out de quarto\n");
	recebe_andar_apt(&andar, &apt);

	if(!for_andar_valido(andar,apt)){
		printf("\nNumero do andar e/ou apartamento nao existem\n\n");
		return;
	}

	switch (hotel[andar-1][apt-1].status)
	{
		case('O'):
			hotel[andar-1][apt-1].status = '.';
			printf("\nCheck-out realizado com sucesso.\n\n");
			break;
		case('R'):
			printf("\nAinda nao foi realizado o check-in.\n\n");
			break;
		case ('.'):
			printf("\nApartamento ja esta desocupado.\n\n");
			break;		
	}
}

void ocupation(hosp hotel[ANDARES][QUARTOS])
{
	//Exibe a taxa de ocupaçao e de reserva do hotel
	int ctOc = 0, ctR = 0; 
	int andar, quarto;
	float tx_ocupados, tx_reservados, total;

	for(andar = 0;  andar < ANDARES; andar++){
		for(quarto = 0; quarto < QUARTOS; quarto++){
			switch (hotel[andar][quarto].status)
			{
				case 'R':
					ctR ++;
					break;
				case 'O':
					ctOc ++;
					break;
				default:
					break;
			}
		}
	}
    tx_ocupados = (ctOc / (TOTAL * 1.0)) * 100;
	tx_reservados = (ctR / (ANDARES * QUARTOS * 1.0)) * 100;
	printf("\nTaxa de ocupacao do hotel (%d de %d quartos): %.2f %%\n", ctOc,TOTAL,tx_ocupados);
	printf("\nTaxa de reserva do hotel (%d de %d quartos): %.2f %%\n\n", ctR, TOTAL,tx_reservados);
}


void recebe_info_hospede(hosp hotel[ANDARES][QUARTOS], int andar, int quarto)
{
	//Recebe os dados necessários para a realização do check-in
	printf("\nInforme o seu nome: ");
	fclear();
	gets(hotel[andar][quarto].nome);
	
	//enquanto o cpf nao for valido, continua pedindo
	do
	{
		printf("\nInforme o seu CPF (xxxxxxxxx-xx):  ");
		gets( hotel[andar][quarto].CPF);

		if(!for_cpf_valido(hotel[andar][quarto].CPF)){
			printf("Cpf invalido, por favor digite um cpf valido\n");
		}
		
	}while(!for_cpf_valido(hotel[andar][quarto].CPF));


	printf("\nInforme o seu endereco (ex: Rua Domingo de Goes 280): ");
	gets(hotel[andar][quarto].end);

	printf("\nInforme o seu telefone (xx) xxxxx-xxxx: ");
	gets(hotel[andar][quarto].tel);

	printf("\nInforme o seu email(user@email.com): ");
	gets(hotel[andar][quarto].email);
}

void mostra_info_hospede(hosp hotel[ANDARES][QUARTOS], int andar, int quarto)
{
	//Mostra os dados do hospede do quarto ocupado
	switch(hotel[andar][quarto].status)
	{
		case '.':
			printf("\nQuarto desocupado\n\n");
			break;
		case 'R':
			printf("\nQuarto reservado\n\n");
			break;
		default:
			printf("\nInfos do hospede: \n");
			printf("\tNome: %s\n", hotel[andar][quarto].nome);
			printf("\tCPF: %s\n", hotel[andar][quarto].CPF);
			printf("\tEndereco: %s\n", hotel[andar][quarto].end);
			printf("\tTelefone: %s\n", hotel[andar][quarto].tel);
			printf("\tEmail: %s\n\n", hotel[andar][quarto].email);
	}
}

int for_cpf_valido(char cpf[13])
{
	//Verifica se o cpf informado é válido
    int d[12];
    int soma1 = 0, soma2 = 0;
    int index,cont;
    int d10_verd, d11_verd;

	if(strlen(cpf) != 12 || cpf[9] != '-'){
		return 0;
	}
    /*realiza a conversão de string de 
    caracteres para números*/
    for(int i=0; i < 12; i++){

        if(cpf[i] == '-'){
            continue;
        }
        d[i] = cpf[i] - '0';
    }

    cont = 10, index = 0;

    //realiza o algoritmo da soma1
    while(index <= 8)
    {
        soma1 += cont*d[index];
        cont --;
        index ++;
    }

    //calcula o d10 verdadeiro
    if(soma1 % 11 < 2){
        d10_verd = 0;
    }
    else{
        d10_verd = 11 - soma1%11;
    }

    //se os digitos não baterem, retorna Falso
    if(d[10] != d10_verd){
        return 0;
    }

    cont = 11, index = 0;

    //realiza o algoritmo da soma2
    while(index <= 8)
    {
        soma2 += cont*d[index];
        cont --;
        index ++;
    }

    //calcula o d11 verdadeiro
    if(((soma2 + 2*d[10]) % 11) < 2){
        d11_verd = 0;
    }
    else{
        d11_verd = 11 - ((soma2 + 2*d[10]) % 11);
    }

    //se os digitos não baterem, retorna Falso
    if(d[11] != d11_verd){
        return 0;
    }
 
    /*se passar por todos os testes, é porque 
    os digitos são iguais*/
    return 1;
}