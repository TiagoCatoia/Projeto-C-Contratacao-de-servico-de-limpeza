#include<stdio.h>
#include<locale.h>
#include<string.h>
#include<stdlib.h>

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
	int dataNascimento[3];
	char cpf[50], rg[50], telefone[50], nome[50], sexo[50];      //// TRANSFORMAR TELEFONES EM UMA MATRIZ DE TELEFONES
}Faxineiro;

typedef struct
{
	int dataServico[3], valorServico;
	char cpfFaxineiro[50], cpfCliente[50];
}Servico;

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
int verificarFaxineiro(Faxineiro *faxineiro, char cpfFaxineiro[], int contadorFaxineiros)
{
	int i, resultado;
	for (i=0; i<contadorFaxineiros; i++) {
		resultado = strcmp(faxineiro[i].cpf, cpfFaxineiro);
	    if (resultado == 0) {
	        return i;
	    }
	}
	return -1;
}

int listarTodosFaxineiros(Faxineiro *faxineiro, int *contadorFaxineiros)
{
	if (*contadorFaxineiros == 0) {
		return -1;
	}
	else {
		printf("Imprimindo todos os Faxineiros...\n\n");
		int i;
		for (i=0; i<*contadorFaxineiros; i++) {
			printf("Nome: %s\n", faxineiro[i].nome);
			printf("Sexo: %s\n", faxineiro[i].sexo);
			printf("Data de nascimento: ");
			printf("%d/%d/%d\n", faxineiro[i].dataNascimento[0], faxineiro[i].dataNascimento[1], faxineiro[i].dataNascimento[2]);
			printf("RG: %s\n", faxineiro[i].rg);
			printf("CPF: %s\n", faxineiro[i].cpf);
			printf("Telefone: %s\n", faxineiro[i].telefone);
			printf("\n");
		}
	}
}

int listarUmFaxineiro(Faxineiro *faxineiro, int *contadorFaxineiros)
{
	char cpfFaxineiro[50];
	int achou;
	
	printf("Informe o CPF do Faxineiro: ");
	fflush(stdin);
	gets(cpfFaxineiro);
	achou = verificarFaxineiro(faxineiro, cpfFaxineiro, *contadorFaxineiros); // chama a fun��o que verifica se j� existe um faxineiro com esse cpf
	if (achou == -1) {
		return -1;
	}
	else {
		printf("\nNome: %s\n", faxineiro[achou].nome);
		printf("Sexo: %s\n", faxineiro[achou].sexo);
		printf("Data de nascimento: %d/%d/%d\n", faxineiro[achou].dataNascimento[0], faxineiro[achou].dataNascimento[1], faxineiro[achou].dataNascimento[2]);
		printf("RG: %s\n", faxineiro[achou].rg);
		printf("CPF: %s\n", faxineiro[achou].cpf);
		printf("Telefone: %s\n", faxineiro[achou].telefone);
		printf("\n");
	}
}

int incluiFaxineiro(Faxineiro *faxineiro, int *contadorFaxineiros)
{	
	// Aqui voc� pode realocar o vetor, se necess�rio, para acomodar mais faxineiros, estopu usando o limite para 100
    // Por exemplo:
    // *faxineiro = (Faxineiro *)realloc(*faxineiro, (*contadorFaxineiros + 1) * sizeof(Faxineiro));
    // se usar o realloc verificar se a aloca��o foi bem-sucedida antes de usar o ponteiro realocado.
    
    if (*contadorFaxineiros ==  100) {
    	printf("O n�mero(100) m�ximo de Faxineiros no sistema foi atingido!\n");
	}
	else {
		char cpfFaxineiro[50];
		int achou;
		
		printf("Informe o CPF do Faxineiro: ");
		fflush(stdin);
		gets(cpfFaxineiro);
		
		achou = verificarFaxineiro(faxineiro, cpfFaxineiro, *contadorFaxineiros); // chama a fun��o que verifica se j� existe um faxineiro com esse cpf
		if (achou != -1) {
			return 1;
		}
		else {
			// Armazenando cpf
			strcpy(faxineiro[*contadorFaxineiros].cpf, cpfFaxineiro);
			// Armazenando nome
			printf("Informe o nome do Faxineiro: ");
			fflush(stdin);
			gets(faxineiro[*contadorFaxineiros].nome);
			// Armazenando sexo
			printf("Informe o sexo do Faxineiro: ");
			gets(faxineiro[*contadorFaxineiros].sexo);
			// Armazenando data de nascimento
			printf("Informe a data de nascimento: \n");
			printf("Dia: ");
			scanf("%d", &faxineiro[*contadorFaxineiros].dataNascimento[0]);
			printf("M�s: ");
			scanf("%d", &faxineiro[*contadorFaxineiros].dataNascimento[1]);
			printf("Ano: ");
			scanf("%d", &faxineiro[*contadorFaxineiros].dataNascimento[2]);
			// Armazena rg
			printf("Informe o RG do Faxineiro: ");
			fflush(stdin);
			gets(faxineiro[*contadorFaxineiros].rg);
			// Armazena telefone
			printf("Informe o telefone do Faxineiro: ");
			gets(faxineiro[*contadorFaxineiros].telefone);
			// Incrementa o contador de faxineiros
			(*contadorFaxineiros)++;
			return -1;
			// Retorna valores de acordo com a situa��o:
		    // return 1;  Faxineiro j� existe
		    // return -1; Inclus�o bem-sucedida
		}
	}
}

int alterarDadosFaxineiro(Faxineiro *faxineiro, int *contadorFaxineiros)
{
	char cpfFaxineiro[50];
	int achou;
	
	printf("Informe o CPF do Faxineiro: ");
	fflush(stdin);
	gets(cpfFaxineiro);
	achou = verificarFaxineiro(faxineiro, cpfFaxineiro, *contadorFaxineiros); // chama a fun��o que verifica se j� existe um faxineiro com esse cpf
	if (achou == -1) {
		return -1;
	}
	else {
		int opcao;
		printf("Se pretende alterar o CPF, tente excluir o Faxineiro do sistema e depois inserir novamente!\n");
		printf("Qual dos dados a seguir deseja alterar ?\n");
		printf("1. Nome\n");
		printf("2. Sexo\n");
		printf("3. Data de Nascimento\n");
		printf("4. RG\n");
		printf("5. Telefone\n");
		printf("6. Voltar para o Menu de Faxineiros\n");
		printf("Entre com a op��o: ");
		scanf("%d", &opcao);
		printf("\n");
		
		switch (opcao) {
			case 1: {
				printf("Nome Atual: %s\n", faxineiro[achou].nome);
				printf("Informe o novo Nome: ");
				fflush(stdin);
				gets(faxineiro[achou].nome);
				break;
			}
			case 2: {
				printf("Sexo Atual: %s\n", faxineiro[achou].sexo);
				printf("Informe o novo Sexo: ");
				fflush(stdin);
				gets(faxineiro[achou].sexo);
				break;
			}
			case 3: {
				printf("Data de Nascimento Atual: %d/%d/%d\n", faxineiro[achou].dataNascimento[0], faxineiro[achou].dataNascimento[1], faxineiro[achou].dataNascimento[2]);
				printf("Informe a nova Data de Nascimento: ");
				printf("Dia: ");
				scanf("%d", &faxineiro[achou].dataNascimento[0]);
				printf("M�s: ");
				scanf("%d", &faxineiro[achou].dataNascimento[1]);
				printf("Ano: ");
				scanf("%d", &faxineiro[achou].dataNascimento[2]);
				break;
			}
			case 4: {
				printf("RG Atual: %s\n", faxineiro[achou].rg);
				printf("Informe o novo RG: ");
				fflush(stdin);
				gets(faxineiro[achou].rg);
				break;
			}
			case 5: {
				printf("Telefone Atual: %s\n", faxineiro[achou].telefone);
				printf("Informe o novo Telefone: ");
				fflush(stdin);
				gets(faxineiro[achou].telefone);
				break;
			}
			case 6: {
				printf("Voltando para o Menu de Faxineiros\n");
				break;
			}
			default: {
			printf("Op��o inv�lida, tente novamente!\n\n");
			break;
			}
		}
		return 1;
	}
}

int excluirFaxineiro(Faxineiro *faxineiro, int *contadorFaxineiros)
{
	char cpfFaxineiro[50];
	int achou, i;
	
	printf("Informe o CPF do Faxineiro: ");
	fflush(stdin);
	gets(cpfFaxineiro);
	achou = verificarFaxineiro(faxineiro, cpfFaxineiro, *contadorFaxineiros); // chama a fun��o que verifica se j� existe um faxineiro com esse cpf
	if (achou == -1) {
		return -1;
	}
	else {
		printf("Dados do Faxineiro: \n");
		printf("Nome: %s\n", faxineiro[achou].nome);
		printf("Sexo: %s\n", faxineiro[achou].sexo);
		printf("Data de nascimento: \n");
		printf("%d/%d/%d\n", faxineiro[achou].dataNascimento[0], faxineiro[achou].dataNascimento[1], faxineiro[achou].dataNascimento[2]);
		printf("RG: %s\n", faxineiro[achou].rg);
		printf("Telefone: %s\n", faxineiro[achou].telefone);
		printf("CPF: %s\n", faxineiro[achou].cpf);
		printf("\nExcluindo do Sistema...\n");
		
		for (i = achou; i < *contadorFaxineiros - 1; i++) { // achou representa o �ndice do faxineiro que deseja excluir
			faxineiro[i] = faxineiro[i+1];
			achou++;
		}
		(*contadorFaxineiros)--;
		
		return 1;
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
				int resultado = listarTodosFaxineiros(faxineiro, &(*contadorFaxineiros));
				if (resultado == -1) {
					printf("N�o existe nenhum Faxineiro cadastrado no sistema!\n");
				}
				break;
			}
			case 2: {
				system("cls");
				int resultado = listarUmFaxineiro(faxineiro, &(*contadorFaxineiros));
				if (resultado == -1) {
					printf("N�o existe nenhum Faxineiro com esse CPF no sistema!\n");
				}
				break;
			}
			case 3: {
				system("cls");
				int resultado;
				resultado = incluiFaxineiro(faxineiro, &(*contadorFaxineiros));
				if (resultado == 1) {
					printf("\nEste Faxineiro j� estava cadastrado no sistema!\n");
				}
				else if(resultado == -1){
					printf("\nFaxineiro cadastrado com sucesso!\n");
				}
				break;
			}
			case 4: {
				system("cls");
				int resultado = alterarDadosFaxineiro(faxineiro, &(*contadorFaxineiros));
				if (resultado == -1) {
					printf("N�o existe nenhum Faxineiro com esse CPF no sistema!\n");
				}
				else {
					printf("\nDados alterados com sucesso!\n");
				}
				break;
			}
			case 5: {
				system("cls");
				int resultado = excluirFaxineiro(faxineiro, &(*contadorFaxineiros));
				if (resultado == -1) {
					printf("N�o existe nenhum Faxineiro com esse CPF no sistema!\n");
				}
				else {
					printf("\nFaxineiro excluido do sistema com sucesso!\n");
				}
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

int verificarServico(Servico *servico, char cpfFaxineiro[], char cpfCliente[], int dataServico[], int contadorServicos)
{
	int i, resultado;
	for (i=0; i<contadorServicos; i++) {
		// Comparamos o CPF do faxineiro atual (servico[i].cpfFaxineiro) com o CPF fornecido (cpfFaxineiro)
        // e tamb�m o CPF do cliente atual (servico[i].cpfCliente) com o CPF fornecido (cpfCliente).
        // Al�m disso, comparamos cada data de servi�o.
        
		if (strcmp(servico[i].cpfFaxineiro, cpfFaxineiro) == 0 && strcmp(servico[i].cpfCliente, cpfCliente) == 0 &&
            servico[i].dataServico[0] == dataServico[0] && servico[i].dataServico[1] == dataServico[1] && servico[i].dataServico[2] == dataServico[2]) {
			return i;
		}
	}
	return -1;
}	

int listarTodosServicos(Servico *servico, int *contadorServicos)
{
	if (*contadorServicos == 0) {
		return -1;
	}
	else {
		printf("Imprimindo todos os Servi�os...\n\n");
		int i;
		for (i=0; i<*contadorServicos; i++) {
			printf("Data do Servi�o: %d/%d/%d\n", servico[i].dataServico[0], servico[i].dataServico[1], servico[i].dataServico[2]);
			printf("CPF do Faxineiro: %s\n", servico[i].cpfFaxineiro);
			printf("CPF do Cliente: %s\n", servico[i].cpfCliente);
			printf("Valor do Servi�o: %d\n", servico[i].valorServico);
			printf("\n");
		}
	}
}

int listarUmServico(Servico *servico, int *contadorServicos)
{
	char cpfFaxineiro[50], cpfCliente[50];
	int achou, dataServico[3];
	
	printf("Informe a data do Servi�o: \n");
	printf("Dia: ");
	scanf("%d", &dataServico[0]);
	printf("M�s: ");
	scanf("%d", &dataServico[1]);
	printf("Ano: ");
	scanf("%d", &dataServico[2]);
	
	printf("Informe o CPF do Faxineiro do Servi�o: ");
	fflush(stdin);
	gets(cpfFaxineiro);
	
	printf("Informe o CPF do Cliente do Servi�o: ");
	gets(cpfCliente);
	
	achou = verificarServico(servico, cpfFaxineiro, cpfCliente, dataServico, *contadorServicos); // chama a fun��o que verifica se j� existe um servico cadastrado com o mesmo cpf do faxineiro/cliente na mesma data
	if (achou != -1) {
		printf("\nDados do Servi�o: \n");
		printf("Data do Servi�o: %d/%d/%d\n", servico[achou].dataServico[0], servico[achou].dataServico[1], servico[achou].dataServico[2]);
		printf("CPF do Faxineiro: %s\n", servico[achou].cpfFaxineiro);
		printf("CPF do Cliente: %s\n", servico[achou].cpfCliente);
		printf("Valor do Servi�o: %d\n", servico[achou].valorServico);
		printf("\n");
	}
	else {
		return -1;
	}
}

int incluiServico(Servico *servico, int *contadorServicos)
{
	// Aqui voc� pode realocar o vetor, se necess�rio, para acomodar mais faxineiros, estopu usando o limite para 100
    // Por exemplo:
    // *faxineiro = (Faxineiro *)realloc(*faxineiro, (*contadorFaxineiros + 1) * sizeof(Faxineiro));
    // se usar o realloc verificar se a aloca��o foi bem-sucedida antes de usar o ponteiro realocado.
    
    if (*contadorServicos ==  100) {
    	printf("O n�mero(100) m�ximo de Servi�os no sistema foi atingido!\n");
	}
	else {
		char cpfFaxineiro[50], cpfCliente[50];
		int achou, dataServico[3];
		
		printf("Informe a data do Servi�o: \n");
		printf("Dia: ");
		scanf("%d", &dataServico[0]);
		printf("M�s: ");
		scanf("%d", &dataServico[1]);
		printf("Ano: ");
		scanf("%d", &dataServico[2]);
		
		printf("Informe o CPF do Faxineiro do Servi�o: ");
		fflush(stdin);
		gets(cpfFaxineiro);
		
		printf("Informe o CPF do Cliente do Servi�o: ");
		gets(cpfCliente);
		
		achou = verificarServico(servico, cpfFaxineiro, cpfCliente, dataServico, *contadorServicos); // chama a fun��o que verifica se j� existe um servico cadastrado com o mesmo cpf do faxineiro/cliente na mesma data
		if (achou != -1) {
			return 1;
		}
		else {
			// Armazenando cpf do faxineiro
			strcpy(servico[*contadorServicos].cpfFaxineiro, cpfFaxineiro);
			// Armazenando cpf do cliente
			strcpy(servico[*contadorServicos].cpfCliente, cpfCliente);
			// Armazenando data do servi�o
			servico[*contadorServicos].dataServico[0] = dataServico[0];
			servico[*contadorServicos].dataServico[1] = dataServico[1];
			servico[*contadorServicos].dataServico[2] = dataServico[2];
			// Armazena o valor do servi�o
			printf("Informe o valor do Servi�o: ");
			scanf("%d", &servico[*contadorServicos].valorServico);
			// Incrementa o contador de servi�os
			(*contadorServicos)++;
			return -1;
			// Retorna valores de acordo com a situa��o:
		    // return 1;  Servico j� existe
		    // return -1; Inclus�o bem-sucedida	
		}
	}
}

int alterarDadosServicos(Servico *servico, int *contadorServicos)
{
	char cpfFaxineiro[50], cpfCliente[50];
	int achou, dataServico[3];
	
	printf("Informe a data do Servi�o: \n");
	printf("Dia: ");
	scanf("%d", &dataServico[0]);
	printf("M�s: ");
	scanf("%d", &dataServico[1]);
	printf("Ano: ");
	scanf("%d", &dataServico[2]);
	
	printf("Informe o CPF do Faxineiro do Servi�o: ");
	fflush(stdin);
	gets(cpfFaxineiro);
	
	printf("Informe o CPF do Cliente do Servi�o: ");
	gets(cpfCliente);
	
	achou = verificarServico(servico, cpfFaxineiro, cpfCliente, dataServico, *contadorServicos); // chama a fun��o que verifica se j� existe um servico cadastrado com o mesmo cpf do faxineiro/cliente na mesma data
	if (achou != -1) {
		int opcao;
		printf("\nSe pretende alterar algum CPF ou a Data, tente excluir o Servi�o do sistema e depois inserir novamente!\n");
		printf("\nValor Atual do Servi�o: %d\n", servico[achou].valorServico);
		printf("Digite o novo Valor do Servi�o: ");
		scanf("%d", &servico[achou].valorServico);
		printf("\n");
		return 1;
	}
	else {
		return -1;
	}
}

int excluirServico(Servico *servico, int *contadorServicos)
{
	char cpfFaxineiro[50], cpfCliente[50];
	int achou, dataServico[3];
	
	printf("Informe a data do Servi�o: \n");
	printf("Dia: ");
	scanf("%d", &dataServico[0]);
	printf("M�s: ");
	scanf("%d", &dataServico[1]);
	printf("Ano: ");
	scanf("%d", &dataServico[2]);
	
	printf("Informe o CPF do Faxineiro do Servi�o: ");
	fflush(stdin);
	gets(cpfFaxineiro);
	
	printf("Informe o CPF do Cliente do Servi�o: ");
	gets(cpfCliente);
	
	achou = verificarServico(servico, cpfFaxineiro, cpfCliente, dataServico, *contadorServicos); // chama a fun��o que verifica se j� existe um servico cadastrado com o mesmo cpf do faxineiro/cliente na mesma data
	if (achou == -1) {
		return -1;
	}
	else {
		printf("\nDados do Servi�o: \n");
		printf("Data do Servi�o: %d/%d/%d\n", servico[achou].dataServico[0], servico[achou].dataServico[1], servico[achou].dataServico[2]);
		printf("CPF do Faxineiro: %s\n", servico[achou].cpfFaxineiro);
		printf("CPF do Cliente: %s\n", servico[achou].cpfCliente);
		printf("Valor do Servi�o: %d\n", servico[achou].valorServico);
		printf("\nExcluindo do Sistema...\n");
		
		int i;
		for (i = achou; i < *contadorServicos - 1; i++) { // achou representa o �ndice do servi�o que deseja excluir
			servico[i] = servico[i+1];
			achou++;
		}
		(*contadorServicos)--;
		
		return 1;
	}
}

void menuServicos(Servico *servico, int *contadorServicos) 
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
				int resultado = listarTodosServicos(servico, &(*contadorServicos));
				if (resultado == -1) {
					printf("N�o existe nenhum Servi�o cadastrado no sistema!\n");
				}
				break;
			}
			case 2: {
				system("cls");
				int resultado = listarUmServico(servico, &(*contadorServicos));
				if (resultado == -1) {
					printf("\nN�o existe nenhum Servi�o cadastrado com esses dados no Sistema!\n");
				}
				break;
			}
			case 3: {
				system("cls");
				int resultado;
				resultado = incluiServico(servico, &(*contadorServicos));
				if (resultado == 1) {
					printf("\nEste Servi�o j� estava cadastrado no sistema!\n");
				}
				else if(resultado == -1){
					printf("\nServi�o cadastrado com sucesso!\n");
				}
				break;
			}
			case 4: {
				system("cls");
				int resultado = alterarDadosServicos(servico, &(*contadorServicos));         //    PODE ALTERAR O RESTO OU S� O VALOR???????????? 
				if (resultado == -1) {
					printf("\nN�o existe nenhum Servi�o com esses dados no Sistema!\n");
				}
				else {
					printf("\nDados alterados com sucesso!\n");
				}
				break;
			}
			case 5: {
				system("cls");
				int resultado = excluirServico(servico, &(*contadorServicos));  
				if (resultado == -1) {
					printf("\nN�o existe nenhum Servi�o com esses dados no Sistema!\n");
				}
				else {
					printf("\nServi�o excluido do sistema com sucesso!\n");
				}
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
	int contadorFaxineiros = 0, contadorServicos = 0; // contador para quantos faxineiros/clientes/servicos est�o inseridos no sistema
	
	Faxineiro *faxineiro;
	faxineiro = (Faxineiro *) malloc(limiteSistema * sizeof(Faxineiro)); // aloca dinamicamente na mem�ria para um vetor do tipo Servico
	Servico *servico;
	servico = (Servico *) malloc(limiteSistema * sizeof(Servico)); // aloca dinamicamente na mem�ria para um vetor do tipo Servico
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
				menuServicos(servico, &contadorServicos);
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
