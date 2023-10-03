#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

/*
Um sistema para uma prestadora de serviço de limpeza (faxinas) precisa gerenciar os 
dados sobre cada faxineiro(a) e os clientes que contratam os seus serviços. Os dados a serem 
armazenados sobre cada entidade são apresentados a seguir: 
Faxineiro = (CPF, RG, nome, sexo, data de nascimento, telefones) 
Cliente = (CPF, nome, data de nascimento, endereço, CEP, cidade, e-mails, telefones) 
Serviço = (CPF faxineiro, CPF cliente, data, valor) 
Atenção: os atributos grifados são chaves e você NÃO deve permitir a inclusão de mais 
de um cadastro com os mesmos valores para os atributos chaves. 
Utilizando os conhecimentos aprendidos sobre Vetores, Strings, Registros e Funções 
desenvolva um programa em C que apresente o seguinte menu de opções para o usuário e 
implemente cada operação usando função. Escolha a estrutura de dados mais apropriada para 
armazenar os dados de cada entidade descrita anteriormente.

Menu Principal: 
1. Submenu de Faxineiros 
2. Submenu de Clientes 
3. Submenu de Serviços 
4. Submenu Relatórios 
5. Sair 

Cada Submenu deverá oferecer as opções: Listar todos, Listar um, Incluir (sem 
repetição), Alterar e Excluir (após confirmação dos dados) um elemento do conjunto. O 
Submenu Relatórios deverá ter uma opção para cada um dos relatórios solicitados abaixo. 
Relatórios: 
a) Mostrar o nome, os e-mails e telefones de todos(as) os(as) clientes que contrataram 
o serviço de determinado(a) faxineiro(a) entre as datas X e Y. O CPF do(a) 
faxineiro(a) e as datas deverão ser fornecidos pelo usuário;

b) Mostrar os dados de todos os serviços contratados para uma data específica a ser 
fornecida pelo usuário. Apresente também o nome do(a) faxineiro(a) e do(a) cliente; 
c) Mostrar os dados de todos os serviços realizados por determinado(a) faxineiro(a),
cujo CPF será fornecido pelo usuário.

A aplicação deverá utilizar Arquivos para a persistência dos dados. Em outras palavras, cada 
registro de Faxineiro, Cliente e Serviço deverá ser armazenado em um arquivo binário
específico, que conterá apenas registros daquele mesmo tipo de entidade. Para os relatórios 
você deverá usar arquivos textos. Utilize estruturas dinâmicas como vetores e registros 
alocados dinamicamente para o armazenamento temporário dos dados (ou seja, antes de serem 
gravados em arquivos). 
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	int cpf, rg, telefone, *dataNascimento;
	char *nome, *sexo;
}Faxineiro;

void menuPrincipal(int *op) 
{	
	printf("Menu principal\n");
	printf("1. Submenu de Faxineiros\n");
	printf("2. Submenu de Clientes\n");
	printf("3. Submenu de Serviços\n");
	printf("4. Submenu de Relatórios\n");
	printf("5. Sair\n");
	printf("Entre com a opção: ");
	scanf("%d", &(*op));
	printf("\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void menuFaxineiros(struct Faxineiro *faxineiro, int contadorFaxineiros) 
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
		printf("Entre com a opção: ");
		scanf("%d", &opcao);
		printf("\n");
		
		switch (opcao) {
			case 1: {
				incluiFaxineiro(faxineiro, contadorFaxineiros);
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
				printf("Opção inválida, tente novamente!\n\n");
				break;
			}
		}
	}while (opcao != 6);
}

void incluiFaxineiro(struct Faxineiro *faxineiro, int contadorFaxineiros)
{
	
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
		printf("Entre com a opção: ");
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
				printf("Opção inválida, tente novamente!\n\n");
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
		printf("Abrindo Submenu de Serviços...\n");
		printf("\nMenu de Serviços: \n");
		printf("1. Listar todos Serviços\n");
		printf("2. Listar um Serviço\n");
		printf("3. Incluir Serviço no sistema\n");
		printf("4. Alterar dados de um Serviço\n");
		printf("5. Excluir Serviço do sistema\n");
		printf("6. Voltar para o Menu Principal\n");
		printf("Entre com a opção: ");
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
				printf("Opção inválida, tente novamente!\n\n");
				break;
			}
		}
	}while (opcao != 6);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
main () {
	setlocale(LC_ALL, "Portuguese"); 
	int op; 
	int contadorFaxineiros = 0; // contador para quantos faxineiros estão inseridos no sistema
	Faxineiro *faxineiro; // crair o vetor dentro da main e mandar ele dps
	int limite = 100; // limite de faxineiros, clientes e serviços inseridos no sistema
	faxineiro = (int *) malloc(sizeof(Faxineiro)*limite);

	menuPrincipal(&op);
	
	do {
		switch (op) {
			case 1: { // caso a opção digitada for 1
				menuFaxineiros(faxineiro, contadorFaxineiros);
				menuPrincipal(&op);
				break;
			}
			
			case 2: { // caso a opção digitada for 2
				printf("Abrindo Submenu de Clientes...\n");
				menuClientes();
				menuPrincipal(&op);
				break;
			}
			
			case 3: { // caso a opção digitada for 3
				printf("Abrindo Submenu de Serviços...\n");
				menuServicos();
				menuPrincipal(&op);
				break;
			}
			
			case 4: { // caso a opção digitada for 4
				printf("Abrindo Submenu de Relatórios...\n");
				menuPrincipal(&op);
				break;
			}
			
			case 5: { // caso a opção digitada for 5
				// sai do loop e finaliza o programa, pois não chama o Menu Principal novamente
				break;
			}
			
			default: {	// caso a opção digitada não está entre as opções disponíveis
				system("cls");
				printf("Opção inválida, tente novamente!\n\n");
				menuPrincipal(&op);
				break;
			}
		}
		if (op == 5) {
			printf("Finalizando o programa...");
		}
	}while (op != 5); // mantém o Menu Principal em loop até que op seja igual a 5
}
