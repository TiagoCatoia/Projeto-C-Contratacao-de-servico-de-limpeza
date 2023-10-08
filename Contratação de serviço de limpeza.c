#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

/*
Um sistema para uma prestadora de servi�o de limpeza (faxinas) precisa gerenciar os 
dados sobre cada faxineiro(a) e os clientes que contratam os seus servi�os. Os dados a serem 
armazenados sobre cada entidade s�o apresentados a seguir: 
Faxineiro = (CPF, RG, nome, sexo, data de nascimento, telefones) 
Cliente = (CPF, nome, data de nascimento, endere�o, CEP, cidade, e-mails, telefones) 
Servi�o = (CPF faxineiro, CPF cliente, data, valor) 
Aten��o: os atributos grifados s�o chaves e voc� N�O deve permitir a inclus�o de mais 
de um cadastro com os mesmos valores para os atributos chaves. 
Utilizando os conhecimentos aprendidos sobre Vetores, Strings, Registros e Fun��es 
desenvolva um programa em C que apresente o seguinte menu de op��es para o usu�rio e 
implemente cada opera��o usando fun��o. Escolha a estrutura de dados mais apropriada para 
armazenar os dados de cada entidade descrita anteriormente.

Menu Principal: 
1. Submenu de Faxineiros 
2. Submenu de Clientes 
3. Submenu de Servi�os 
4. Submenu Relat�rios 
5. Sair 

Cada Submenu dever� oferecer as op��es: Listar todos, Listar um, Incluir (sem 
repeti��o), Alterar e Excluir (ap�s confirma��o dos dados) um elemento do conjunto. O 
Submenu Relat�rios dever� ter uma op��o para cada um dos relat�rios solicitados abaixo. 
Relat�rios: 
a) Mostrar o nome, os e-mails e telefones de todos(as) os(as) clientes que contrataram 
o servi�o de determinado(a) faxineiro(a) entre as datas X e Y. O CPF do(a) 
faxineiro(a) e as datas dever�o ser fornecidos pelo usu�rio;

b) Mostrar os dados de todos os servi�os contratados para uma data espec�fica a ser 
fornecida pelo usu�rio. Apresente tamb�m o nome do(a) faxineiro(a) e do(a) cliente; 
c) Mostrar os dados de todos os servi�os realizados por determinado(a) faxineiro(a),
cujo CPF ser� fornecido pelo usu�rio.

A aplica��o dever� utilizar Arquivos para a persist�ncia dos dados. Em outras palavras, cada 
registro de Faxineiro, Cliente e Servi�o dever� ser armazenado em um arquivo bin�rio
espec�fico, que conter� apenas registros daquele mesmo tipo de entidade. Para os relat�rios 
voc� dever� usar arquivos textos. Utilize estruturas din�micas como vetores e registros 
alocados dinamicamente para o armazenamento tempor�rio dos dados (ou seja, antes de serem 
gravados em arquivos). 
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	int cpf, rg, telefone, *dataNascimento; // * armazenaria o endere�o de mem�ria onde um valor pode ser encontrado para criar os vetores dinamicamente
	char *nome, *sexo;
}Faxineiro;

void menuPrincipal(int *op) 
{	
	printf("Menu principal\n");
	printf("1. Submenu de Faxineiros\n");
	printf("2. Submenu de Clientes\n");
	printf("3. Submenu de Servi�os\n");
	printf("4. Submenu de Relat�rios\n");
	printf("5. Sair\n");
	printf("Entre com a op��o: ");
	scanf("%d", &(*op));
	printf("\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int verificarFaxineiro(Faxineiro *faxineiro, int cpfFaxineiro, int contadorFaxineiros)
{
	int i;
	for (i=0; i<contadorFaxineiros; i++) {
		if (faxineiro[i].cpf == cpfFaxineiro) {
			return i;
		}
	}
	return -1;
}

int incluiFaxineiro(Faxineiro *faxineiro, int *contadorFaxineiros)
{	
	// Aqui voc� pode realocar o vetor, se necess�rio, para acomodar mais faxineiros
    // Por exemplo:
    // *faxineiro = (Faxineiro *)realloc(*faxineiro, (*contadorFaxineiros + 1) * sizeof(Faxineiro));
    // se usar o realloc verificar se a aloca��o foi bem-sucedida antes de usar o ponteiro realocado.
    
    if (*contadorFaxineiros ==  100) {
    	printf("O n�mero(100) m�ximo de faxineiros no sistema foi atingido!\n");
	}
	else {
		int cpfFaxineiro, achou;
		printf("Informe o cpf do faxineiro: ");
		scanf("%d", &cpfFaxineiro);
		achou = verificarFaxineiro(faxineiro, cpfFaxineiro, *contadorFaxineiros); // chama a fun��o que verifica se j� existe um faxineiro com esse cpf
		if (achou != -1) {
			return 1;
		}
		else {
			char nome[50], sexo[50];
			int rgFaxineiro, telefoneFaxineiro, i;
			// Armazenando cpf
			faxineiro[*contadorFaxineiros].cpf = cpfFaxineiro;
			// Armazenando nome
			faxineiro[*contadorFaxineiros].nome = (char *) malloc(50 * sizeof(char));
			printf("Informe o nome do faxineiro: ");
			fflush(stdin);
			gets(nome);
			strcpy(faxineiro[*contadorFaxineiros].nome, nome); // sem o strcpy deveria acessar cada indice do vetor faxineiro[*contadorFaxineiros].nome[i] e armazenar cada char de nome
			// Armazenando sexo
			faxineiro[*contadorFaxineiros].sexo = (char *) malloc(sizeof(char));
			printf("Informe o sexo do faxineiro: ");
			gets(sexo);
			strcpy(faxineiro[*contadorFaxineiros].sexo, sexo);
			// Armazenando data de nascimento
			faxineiro[*contadorFaxineiros].dataNascimento = (int *) malloc(3 * sizeof(int)); // dataNascimento[0] = dia dataNascimento[1] = m�s dataNascimento[2] = Ano
			
			// VOU MUDAR dataNascimento para string
			
			// Armazena rg
			// Armazena telefone
			(*contadorFaxineiros)++;
			return -1;
			// Retorna valores de acordo com a situa��o:
		    // return 1;  Faxineiro j� existe
		    // return -1; Inclus�o bem-sucedida
		}
	}
}

void menuFaxineiros(Faxineiro *faxineiro, int *contadorFaxineiros) 
{
	int opcao;
	system("cls");
	
	do {
		printf("Abrindo Submenu de Faxineiros...\n");
		printf("\nMenu de Faxineiros: \n");
		printf("1. Listar todos Faxineiros\n");
		printf("2. Listar um Faxineiro\n");
		printf("3. Incluir Faxineiro no sistema\n");
		printf("4. Alterar dados de um Faxineiro\n");
		printf("5. Excluir Faxineiro do sistema\n");
		printf("6. Voltar para o Menu Principal\n");
		printf("Entre com a op��o: ");
		scanf("%d", &opcao);
		printf("\n");
		
		switch (opcao) {
			case 1: {
				system("cls");
				break;
			}
			case 2: {
				system("cls");
				break;
			}
			case 3: {
				system("cls");
				int result;
				result = incluiFaxineiro(faxineiro, &(*contadorFaxineiros));
				if (result == 1) {
					printf("\nFaxineiro j� cadastrado no sistema!\n");
				}
				else if(result == -1){
					printf("\nFaxineiro cadastrado com sucesso!\n");
				}
				break;
			}
			case 4: {
				system("cls");
				break;
			}
			case 5: {
				system("cls");
				break;
			}
			case 6: {
				system("cls");
				printf("Voltando para o menu principal...\n\n");
				break;
			}
			default: {
				system("cls");
				printf("Op��o inv�lida, tente novamente!\n\n");
				break;
			}
		}
	}while (opcao != 6);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void menuClientes() 
{
	int opcao;
	system("cls");
	
	do {
		printf("Abrindo Submenu de Clientes...\n");
		printf("\nMenu de Clientes: \n");
		printf("1. Listar todos Clientes\n");
		printf("2. Listar um Cliente\n");
		printf("3. Incluir Cliente no sistema\n");
		printf("4. Alterar dados de um Cliente\n");
		printf("5. Excluir Cliente do sistema\n");
		printf("6. Voltar para o Menu Principal\n");
		printf("Entre com a op��o: ");
		scanf("%d", &opcao);
		printf("\n");
		
		switch (opcao) {
			case 1: {
				system("cls");
				break;
			}
			case 2: {
				system("cls");
				break;
			}
			case 3: {
				system("cls");
				break;
			}
			case 4: {
				system("cls");
				break;
			}
			case 5: {
				system("cls");
				break;
			}
			case 6: {
				system("cls");
				printf("Voltando para o menu principal...\n\n");
				break;
			}
			default: {
				system("cls");
				printf("Op��o inv�lida, tente novamente!\n\n");
				break;
			}
		}
	}while (opcao != 6);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void menuServicos() 
{
	int opcao;
	system("cls");
	
	do {
		printf("Abrindo Submenu de Servi�os...\n");
		printf("\nMenu de Servi�os: \n");
		printf("1. Listar todos Servi�os\n");
		printf("2. Listar um Servi�o\n");
		printf("3. Incluir Servi�o no sistema\n");
		printf("4. Alterar dados de um Servi�o\n");
		printf("5. Excluir Servi�o do sistema\n");
		printf("6. Voltar para o Menu Principal\n");
		printf("Entre com a op��o: ");
		scanf("%d", &opcao);
		printf("\n");
		
		switch (opcao) {
			case 1: {
				system("cls");
				break;
			}
			case 2: {
				system("cls");
				break;
			}
			case 3: {
				system("cls");
				break;
			}
			case 4: {
				system("cls");
				break;
			}
			case 5: {
				system("cls");
				break;
			}
			case 6: {
				system("cls");
				printf("Voltando para o menu principal...\n\n");
				break;
			}
			default: {
				system("cls");
				printf("Op��o inv�lida, tente novamente!\n\n");
				break;
			}
		}
	}while (opcao != 6);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
main () {
	setlocale(LC_ALL, "Portuguese"); 
	int op, limiteSistema = 100; 
	int contadorFaxineiros = 0; // contador para quantos faxineiros est�o inseridos no sistema
	Faxineiro *faxineiro; // crair o vetor dentro da main e mandar ele dps
	faxineiro = (Faxineiro *) malloc(limiteSistema * sizeof(Faxineiro)); // aloca dinamicamente na mem�ria para um �nico objeto do tipo Faxineiro
	// faxineiro � um ponteiro para uma estrutura/vetor Faxineiro

	menuPrincipal(&op);
	
	do {
		switch (op) {
			case 1: { // caso a op��o digitada for 1
				menuFaxineiros(faxineiro, &contadorFaxineiros);
				menuPrincipal(&op);
				break;
			}
			
			case 2: { // caso a op��o digitada for 2
				printf("Abrindo Submenu de Clientes...\n");
				menuClientes();
				menuPrincipal(&op);
				break;
			}
			
			case 3: { // caso a op��o digitada for 3
				printf("Abrindo Submenu de Servi�os...\n");
				menuServicos();
				menuPrincipal(&op);
				break;
			}
			
			case 4: { // caso a op��o digitada for 4
				printf("Abrindo Submenu de Relat�rios...\n");
				menuPrincipal(&op);
				break;
			}
			
			case 5: { // caso a op��o digitada for 5
				// sai do loop e finaliza o programa, pois n�o chama o Menu Principal novamente
				break;
			}
			
			default: {	// caso a op��o digitada n�o est� entre as op��es dispon�veis
				system("cls");
				printf("Op��o inv�lida, tente novamente!\n\n");
				menuPrincipal(&op);
				break;
			}
		}
		if (op == 5) {
			printf("Finalizando o programa...");
		}
	}while (op != 5); // mant�m o Menu Principal em loop at� que op seja igual a 5
}


/* 
TALVEZ PRECISE:

malloc pode retornar NULL se n�o houver mem�ria dispon�vel.
if (faxineiro == NULL) {
    printf("Erro na aloca��o de mem�ria.\n");
    exit(1); // Ou tome alguma outra a��o apropriada em caso de erro.
    
    

case 5: {
    // Liberar a mem�ria alocada para o vetor de Faxineiros antes de sair
    for (int i = 0; i < contadorFaxineiros; i++) {
        free(faxineiro[i].nome); // Liberar mem�ria alocada para o nome de cada Faxineiro
        free(faxineiro[i].sexo); // Liberar mem�ria alocada para o sexo de cada Faxineiro
        free(faxineiro[i].dataNascimento); // Liberar mem�ria alocada para a dataNascimento de cada Faxineiro
    }
    free(faxineiro); // Liberar a mem�ria alocada para o vetor de Faxineiros
    printf("Finalizando o programa...\n");
    break;
}*/
