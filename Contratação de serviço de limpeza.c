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
	int cpf, rg, telefone, *dataNascimento; // * armazenaria o endereço de memória onde um valor pode ser encontrado para criar os vetores dinamicamente
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
	// Aqui você pode realocar o vetor, se necessário, para acomodar mais faxineiros
    // Por exemplo:
    // *faxineiro = (Faxineiro *)realloc(*faxineiro, (*contadorFaxineiros + 1) * sizeof(Faxineiro));
    // se usar o realloc verificar se a alocação foi bem-sucedida antes de usar o ponteiro realocado.
    
    if (*contadorFaxineiros ==  100) {
    	printf("O número(100) máximo de faxineiros no sistema foi atingido!\n");
	}
	else {
		int cpfFaxineiro, achou;
		printf("Informe o cpf do faxineiro: ");
		scanf("%d", &cpfFaxineiro);
		achou = verificarFaxineiro(faxineiro, cpfFaxineiro, *contadorFaxineiros); // chama a função que verifica se já existe um faxineiro com esse cpf
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
			faxineiro[*contadorFaxineiros].dataNascimento = (int *) malloc(3 * sizeof(int)); // dataNascimento[0] = dia dataNascimento[1] = mês dataNascimento[2] = Ano
			
			// VOU MUDAR dataNascimento para string
			
			// Armazena rg
			// Armazena telefone
			(*contadorFaxineiros)++;
			return -1;
			// Retorna valores de acordo com a situação:
		    // return 1;  Faxineiro já existe
		    // return -1; Inclusão bem-sucedida
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
				int result;
				result = incluiFaxineiro(faxineiro, &(*contadorFaxineiros));
				if (result == 1) {
					printf("\nFaxineiro já cadastrado no sistema!\n");
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
				printf("Opção inválida, tente novamente!\n\n");
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
	int op, limiteSistema = 100; 
	int contadorFaxineiros = 0; // contador para quantos faxineiros estão inseridos no sistema
	Faxineiro *faxineiro; // crair o vetor dentro da main e mandar ele dps
	faxineiro = (Faxineiro *) malloc(limiteSistema * sizeof(Faxineiro)); // aloca dinamicamente na memória para um único objeto do tipo Faxineiro
	// faxineiro é um ponteiro para uma estrutura/vetor Faxineiro

	menuPrincipal(&op);
	
	do {
		switch (op) {
			case 1: { // caso a opção digitada for 1
				menuFaxineiros(faxineiro, &contadorFaxineiros);
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


/* 
TALVEZ PRECISE:

malloc pode retornar NULL se não houver memória disponível.
if (faxineiro == NULL) {
    printf("Erro na alocação de memória.\n");
    exit(1); // Ou tome alguma outra ação apropriada em caso de erro.
    
    

case 5: {
    // Liberar a memória alocada para o vetor de Faxineiros antes de sair
    for (int i = 0; i < contadorFaxineiros; i++) {
        free(faxineiro[i].nome); // Liberar memória alocada para o nome de cada Faxineiro
        free(faxineiro[i].sexo); // Liberar memória alocada para o sexo de cada Faxineiro
        free(faxineiro[i].dataNascimento); // Liberar memória alocada para a dataNascimento de cada Faxineiro
    }
    free(faxineiro); // Liberar a memória alocada para o vetor de Faxineiros
    printf("Finalizando o programa...\n");
    break;
}*/
