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
	char cpf[50], rg[50], telefone[50][50], nome[50], sexo[50];
}Faxineiro;

typedef struct
{
	int dataNascimento[3];
	char cpf[50], nome[50], cep[50], cidade[50], endereco[50], email[50], telefone[50]; //// TRANSFORMAR E-MAILS E TELEFONES EM UMA MATRIZ
} Cliente;

typedef struct
{
	int dataServico[3];
	float valorServico;
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
		int i, y = 0;
		for (i=0; i<*contadorFaxineiros; i++) {
			printf("Nome: %s\n", faxineiro[i].nome);
			printf("Sexo: %s\n", faxineiro[i].sexo);
			printf("Data de nascimento: ");
			printf("%d/%d/%d\n", faxineiro[i].dataNascimento[0], faxineiro[i].dataNascimento[1], faxineiro[i].dataNascimento[2]);
			printf("RG: %s\n", faxineiro[i].rg);
			printf("CPF: %s\n", faxineiro[i].cpf);
			printf("Telefones: | ");
			for (y=0; y<50; y++) {
				if (faxineiro[i].telefone[y][0] != '\0') {
        			printf("%s | ", faxineiro[i].telefone[y]);
    			}
			}
			printf("\n\n");
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
		int i = 0;
		printf("\nNome: %s\n", faxineiro[achou].nome);
		printf("Sexo: %s\n", faxineiro[achou].sexo);
		printf("Data de nascimento: %d/%d/%d\n", faxineiro[achou].dataNascimento[0], faxineiro[achou].dataNascimento[1], faxineiro[achou].dataNascimento[2]);
		printf("RG: %s\n", faxineiro[achou].rg);
		printf("CPF: %s\n", faxineiro[achou].cpf);
		printf("Telefones: | ");
		for (i=0; i<50; i++) {
			if (faxineiro[achou].telefone[i][0] != '\0') {
        		printf("%s | ", faxineiro[achou].telefone[i]);
    		}
		}
		printf("\n\n");
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
			int maisTelefone = 1, contadorTelefones = 0;
			do {
				if (contadorTelefones == 50) {
					printf("N�mero m�ximo de telefones atingido!\n");
				}
				else if (maisTelefone == 1) {
					printf("Informe o telefone do Faxineiro: ");
					fflush(stdin);
					gets(faxineiro[*contadorFaxineiros].telefone[contadorTelefones]);
					contadorTelefones++;
				}
				printf("Deseja adicionar outro telefone? (1 para Sim e 0 para N�o) :");
				scanf("%d", &maisTelefone);
			} while (maisTelefone == 1);
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
				printf("Informe a nova Data de Nascimento: \n");
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
				int i = 0;
				char telefoneAlterar[50];
				
				printf("Telefones Atuais: | ");
				for (i=0; i<50; i++) {
					if (faxineiro[achou].telefone[i][0] != '\0') {
	        			printf("%s | ", faxineiro[achou].telefone[i]);
	    			}
				}
				printf("\nDigite o Telefone que deseja alterar: ");
				fflush(stdin);
				gets(telefoneAlterar);
				for (i=0; i<50; i++) {
					if (faxineiro[achou].telefone[i][0] != '\0') {
	        			if (strcmp(faxineiro[achou].telefone[i], telefoneAlterar) == 0) {
	        				printf("Informe o novo Telefone: ");
	        				gets(faxineiro[achou].telefone[i]);
	        				return 1;
						}
	    			}
				}
				printf("\nO Faxineiro n�o possui esse telefone!\n");
				return -2;
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
		printf("Telefones: | ");
		for (i=0; i<50; i++) {
			if (faxineiro[achou].telefone[i][0] != '\0') {
        		printf("%s | ", faxineiro[achou].telefone[i]);
    		}
		}
		printf("\nCPF: %s\n", faxineiro[achou].cpf);
		printf("\nExcluindo do Sistema...\n");
		
		for (i = achou; i < *contadorFaxineiros - 1; i++) { // achou representa o �ndice do faxineiro que deseja excluir
			faxineiro[i] = faxineiro[i+1];
		}
		(*contadorFaxineiros)--;
		
		return 1;
	}
}

void menuFaxineiros(Faxineiro *faxineiro, int *contadorFaxineiros) 
{
	// Crinado um ponteiro para o Arquivo de Faxineiros
	FILE *arquivoFaxineiros;
	
	// Abre o Arquivo Bin�rio no modo de Escrita e Leitura
	arquivoFaxineiros = fopen("dados_faxineiros", "rb+");
	// Verifica se o Arquivo  Existe ou est� Vazio
	// Caso o Arquivo n�o exista ou est� vazio, ent�o o vetor Faxineiro e o contador s�o utilizados como vazio assim como definidos na main
	// Caso o arquivo exista os dados s�o carregados para o vetor e o contador
	if (arquivoFaxineiros != NULL) {
		*contadorFaxineiros = fread(faxineiro, sizeof(Faxineiro), 100, arquivoFaxineiros); // 100 representa o Tamanho M�ximo do vetor faxineiro
	}
	// Trata o caso de erro durante a leitura do Arquivo
	if (ferror(arquivoFaxineiros)) {
        perror("Erro ao ler do arquivo");
    }
	// Posiciona o ponteiro no in�cio do arquivo para substituir os dados j� carregados (SEEK_SET)
	fseek(arquivoFaxineiros, 0, SEEK_SET);
	
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
				else if (resultado == -2){
					printf("\nN�o foi poss�vel alterar os dados!\n");
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
					printf("\nFaxineiro exclu�do do sistema com sucesso!\n");
				}
				break;
			}
			case 6: {
				system("cls");
				printf("Voltando para o menu principal...\n\n");
				
				// Gravando os Dados dos Faxineiros no Arquivo Bin�rio
				fwrite(faxineiro, sizeof(Faxineiro), *contadorFaxineiros, arquivoFaxineiros); // o contadorFaxineiros representa quantos faxineiros est�o sendo gravados
				fclose(arquivoFaxineiros);
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

int verificarCliente(Cliente *cliente, char cpfCliente[], int contadorClientes)
{
	int i, resultado;
	for (i = 0; i < contadorClientes; i++)
	{
		resultado = strcmp(cliente[i].cpf, cpfCliente);
		if (resultado == 0)
		{
			return i;
		}
	}
	return -1;
}

int listarTodosClientes(Cliente *cliente, int *contadorClientes)
{
	if (*contadorClientes == 0)
	{
		return -1;
	}
	else
	{
		printf("Imprimindo todos os Clientes...\n\n");
		int i;
		for (i = 0; i < *contadorClientes; i++)
		{
			printf("Nome: %s\n", cliente[i].nome);
			printf("Data de nascimento: ");
			printf("%d/%d/%d\n", cliente[i].dataNascimento[0], cliente[i].dataNascimento[1], cliente[i].dataNascimento[2]);
			printf("Endere�o: %s\n", cliente[i].endereco);
			printf("CPF: %s\n", cliente[i].cpf);
			printf("CEP: %s\n", cliente[i].cep);
			printf("Cidade: %s\n", cliente[i].cidade);
			printf("E-mail: %s\n", cliente[i].email);
			printf("Telefone: %s\n", cliente[i].telefone);
			printf("\n");
		}
	}
}

int listarUmCliente(Cliente *cliente, int *contadorClientes)
{
	char cpfCliente[50];
	int achou;

	printf("Informe o CPF do Cliente: ");
	fflush(stdin);
	gets(cpfCliente);
	achou = verificarCliente(cliente, cpfCliente, *contadorClientes); // chama a fun��o que verifica se j� existe um faxineiro com esse cpf
	if (achou == -1)
	{
		return -1;
	}
	else
	{
		printf("Nome: %s\n", cliente[achou].nome);
		printf("Data de nascimento: ");
		printf("%d/%d/%d\n", cliente[achou].dataNascimento[0], cliente[achou].dataNascimento[1], cliente[achou].dataNascimento[2]);
		printf("Endere�o: %s\n", cliente[achou].endereco);
		printf("CPF: %s\n", cliente[achou].cpf);
		printf("CEP: %s\n", cliente[achou].cep);
		printf("Cidade: %s\n", cliente[achou].cidade);
		printf("E-mail: %s\n", cliente[achou].email);
		printf("Telefone: %s\n", cliente[achou].telefone);
		printf("\n");
	}
}

int incluiCliente(Cliente *cliente, int *contadorClientes)
{
	// Aqui voc� pode realocar o vetor, se necess�rio, para acomodar mais clientes, estou usando o limite para 100
	// Por exemplo:
	// *cliente = (Cliente *)realloc(*cliente, (*contadorClientes + 1) * sizeof(Cliente));
	// Se usar o realloc, verifique se a aloca��o foi bem-sucedida antes de usar o ponteiro realocado.

	if (*contadorClientes == 100)
	{
		printf("O n�mero m�ximo (100) de clientes no sistema foi atingido!\n");
	}
	else
	{
		char cpfCliente[50];
		int achou;

		printf("Informe o CPF do Cliente: ");
		fflush(stdin);
		gets(cpfCliente);

		achou = verificarCliente(cliente, cpfCliente, *contadorClientes); // chama a fun��o que verifica se j� existe um cliente com esse CPF
		if (achou != -1)
		{
			return 1;
		}
		else
		{
			// Armazenando CPF
			strcpy(cliente[*contadorClientes].cpf, cpfCliente);
			// Armazenando nome
			printf("Informe o nome do Cliente: ");
			fflush(stdin);
			gets(cliente[*contadorClientes].nome);
			// Armazenando data de nascimento
			printf("Informe a data de nascimento: \n");
			printf("Dia: ");
			scanf("%d", &cliente[*contadorClientes].dataNascimento[0]);
			printf("M�s: ");
			scanf("%d", &cliente[*contadorClientes].dataNascimento[1]);
			printf("Ano: ");
			scanf("%d", &cliente[*contadorClientes].dataNascimento[2]);
			// Armazenar endere�o
			printf("Informe o Endere�o do Cliente: ");
			fflush(stdin);
			gets(cliente[*contadorClientes].endereco);
			// Armazenar CEP
			printf("Informe o CEP do Cliente: ");
			fflush(stdin);
			gets(cliente[*contadorClientes].cep);
			// Armazenar cidade
			printf("Informe a Cidade do Cliente: ");
			fflush(stdin);
			gets(cliente[*contadorClientes].cidade);
			// Armazenar email
			printf("Informe o E-mail do Cliente: ");
			fflush(stdin);
			gets(cliente[*contadorClientes].email);
			// Armazenar telefone
			printf("Informe o telefone do Cliente: ");
			gets(cliente[*contadorClientes].telefone);
			// Incrementar o contador de clientes
			(*contadorClientes)++;
			return -1;
			// Retorna valores de acordo com a situa��o:
			// return 1;  Cliente j� existe
			// return -1; Inclus�o bem-sucedida
		}
	}
}

int alterarDadosCliente(Cliente *cliente, int *contadorClientes)
{
	char cpfCliente[50];
	int achou;

	printf("Informe o CPF do Cliente: ");
	fflush(stdin);
	gets(cpfCliente);
	achou = verificarCliente(cliente, cpfCliente, *contadorClientes); // chama a fun��o que verifica se j� existe um cliente com esse cpf
	if (achou == -1)
	{
		return -1;
	}
	else
	{
		int opcao;
		printf("Se pretende alterar o CPF, tente excluir o Cliente do sistema e depois inserir novamente!\n");
		printf("Qual dos dados a seguir deseja alterar ?\n");
		printf("1. Nome\n");
		printf("2. Data de Nascimento\n");
		printf("3. Endere�o\n");
		printf("4. CEP\n");
		printf("5. Cidade\n");
		printf("6. E-mails\n");
		printf("7. Telefone\n");
		printf("8. Voltar para o Menu de Faxineiros\n");
		printf("Entre com a op��o: ");
		scanf("%d", &opcao);
		printf("\n");

		switch (opcao)
		{
		case 1:
		{
			printf("Nome Atual: %s\n", cliente[achou].nome);
			printf("Informe o novo Nome: ");
			fflush(stdin);
			gets(cliente[achou].nome);
			break;
		}
		case 2:
		{
			printf("Data de Nascimento Atual: %d/%d/%d\n", cliente[achou].dataNascimento[0], cliente[achou].dataNascimento[1], cliente[achou].dataNascimento[2]);
			printf("Informe a nova Data de Nascimento: \n");
			printf("Dia: ");
			scanf("%d", &cliente[achou].dataNascimento[0]);
			printf("M�s: ");
			scanf("%d", &cliente[achou].dataNascimento[1]);
			printf("Ano: ");
			scanf("%d", &cliente[achou].dataNascimento[2]);
			break;
		}
		case 3:
		{
			printf("Endere�o Atual: %s\n", cliente[achou].endereco);
			printf("Informe o novo Endere�o: ");
			fflush(stdin);
			gets(cliente[achou].endereco);
			break;
		}
		case 4:
		{
			printf("CEP Atual: %s\n", cliente[achou].cep);
			printf("Informe o novo CEP: ");
			fflush(stdin);
			gets(cliente[achou].cep);
			break;
		}
		case 5:
		{
			printf("Cidade Atual: %s\n", cliente[achou].cidade);
			printf("Informe a nova Cidade: ");
			fflush(stdin);
			gets(cliente[achou].cidade);
			break;
		}
		case 6:
		{
			printf("E-mail Atual: %s\n", cliente[achou].email);
			printf("Informe o novo E-mail: ");
			fflush(stdin);
			gets(cliente[achou].email);
			break;
		}
		case 7:
		{
			printf("Telefone Atual: %s\n", cliente[achou].telefone);
			printf("Informe o novo Telefone: ");
			fflush(stdin);
			gets(cliente[achou].telefone);
			break;
		}
		default:
		{
			printf("Op��o inv�lida, tente novamente!\n\n");
			break;
		}
		}
		return 1;
	}
}

int excluirCliente(Cliente *cliente, int *contadorClientes)
{
	char cpfCliente[50];
	int achou, i;

	printf("Informe o CPF do Cliente: ");
	fflush(stdin);
	gets(cpfCliente);
	achou = verificarCliente(cliente, cpfCliente, *contadorClientes); // chama a fun��o que verifica se j� existe um cliente com esse cpf
	if (achou == -1)
	{
		return -1;
	}
	else
	{
		printf("Dados do Cliente: \n");
		printf("Nome: %s\n", cliente[achou].nome);
		printf("Data de nascimento: ");
		printf("%d/%d/%d\n", cliente[achou].dataNascimento[0], cliente[achou].dataNascimento[1], cliente[achou].dataNascimento[2]);
		printf("Endere�o: %s\n", cliente[achou].endereco);
		printf("CEP: %s\n", cliente[achou].cep);
		printf("Cidade: %s\n", cliente[achou].cidade);
		printf("E-mail: %s\n", cliente[achou].email);
		printf("Telefone: %s\n", cliente[achou].telefone);
		printf("\n");
		printf("\nExcluindo do Sistema...\n");

		for (i = achou; i < *contadorClientes - 1; i++)
		{ // achou representa o �ndice do cliente que deseja excluir
			cliente[i] = cliente[i + 1];
		}
		(*contadorClientes)--;

		return 1;
	}
}

void menuClientes(Cliente *cliente, int *contadorClientes) 
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
				int resultado = listarTodosClientes(cliente, &(*contadorClientes));
				if (resultado == -1)
				{
					printf("N�o existe nenhum Cliente cadastrado no sistema!\n");
				}
				break;
			}
			case 2: {
				system("cls");
				int resultado = listarUmCliente(cliente, &(*contadorClientes));
				if (resultado == -1)
				{
					printf("N�o existe nenhum Cliente com esse CPF no sistema!\n");
				}
				break;
			}
			case 3: {
				system("cls");
				int resultado;
				resultado = incluiCliente(cliente, &(*contadorClientes));
				if (resultado == 1)
				{
					printf("\nEste Cliente j� estava cadastrado no sistema!\n");
				}
				else if (resultado == -1)
				{
					printf("\nCliente cadastrado com sucesso!\n");
				}
				break;
			}
			case 4: {
				system("cls");
				int resultado = alterarDadosCliente(cliente, &(*contadorClientes));
				if (resultado == -1)
				{
					printf("N�o existe nenhum Cliente com esse CPF no sistema!\n");
				}
				else
				{
					printf("\nDados alterados com sucesso!\n");
				}
				break;
			}
			case 5: {
				system("cls");
				int resultado = excluirCliente(cliente, &(*contadorClientes));
				if (resultado == -1)
				{
					printf("N�o existe nenhum Cliente com esse CPF no sistema!\n");
				}
				else
				{
					printf("\nCliente exclu�do do sistema com sucesso!\n");
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
			printf("Valor do Servi�o: %.2f\n", servico[i].valorServico);
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
		printf("Valor do Servi�o: %.2f\n", servico[achou].valorServico);
		printf("\n");
	}
	else {
		return -1;
	}
}

int incluiServico(Servico *servico, int *contadorServicos, Faxineiro *faxineiro, int *contadorFaxineiros, Cliente *cliente, int *contadorClientes)
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
		int achouServico, achouFaxineiro, achouCliente, dataServico[3];
		
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
		
		achouServico = verificarServico(servico, cpfFaxineiro, cpfCliente, dataServico, *contadorServicos); // Chama a fun��o que verifica se j� existe um Servico Cadastrado com o mesmo CPF do Faxineiro/Cliente na mesma Data
		if (achouServico != -1) {
			return 1;
		}
		else {
			achouFaxineiro = verificarFaxineiro(faxineiro, cpfFaxineiro, *contadorFaxineiros); // Chama a fun��o que verifica se j� existe um Faxineiro com esse CPF no Sistema
			if (achouFaxineiro == -1) {
				return 2;
			}
			achouCliente = verificarCliente(cliente, cpfCliente, *contadorClientes); // Chama a fun��o que verifica se j� existe um Cliente com esse CPF no Sistema
			if (achouCliente == -1) {
				return 3;
			}
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
			scanf("%f", &servico[*contadorServicos].valorServico);
			// Incrementa o contador de servi�os
			(*contadorServicos)++;
			return -1;
			// Retorna valores de acordo com a situa��o:
		    // return 1;  Servico j� existe
		    // return -1; Inclus�o bem-sucedida
			// return 2; N�o foi poss�vel realizar o cadastro, pois o CPF do Faxineiro N�o est� Cadastrado no sistema	
			// return 3; N�o foi poss�vel realizar o cadastro, pois o CPF do Cliente N�o est� Cadastrado no sistema	
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
		printf("\nValor Atual do Servi�o: %.2f\n", servico[achou].valorServico);
		printf("Digite o novo Valor do Servi�o: ");
		scanf("%f", &servico[achou].valorServico);
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
		printf("Valor do Servi�o: %.2f\n", servico[achou].valorServico);
		printf("\nExcluindo do Sistema...\n");
		
		int i;
		for (i = achou; i < *contadorServicos - 1; i++) { // achou representa o �ndice do servi�o que deseja excluir
			servico[i] = servico[i+1];
		}
		(*contadorServicos)--;
		
		return 1;
	}
}

void menuServicos(Servico *servico, int *contadorServicos, Faxineiro *faxineiro, int *contadorFaxineiros, Cliente *cliente, int *contadorClientes) 
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
				resultado = incluiServico(servico, &(*contadorServicos), faxineiro, &(*contadorFaxineiros), cliente, &(*contadorClientes));
				if (resultado == 1) {
					printf("\nEste Servi�o j� estava cadastrado no sistema!\n");
				}
				else if (resultado == -1){
					printf("\nServi�o cadastrado com sucesso!\n");
				}
				else if (resultado == 2) {
					printf("\nN�o foi poss�vel cadastrar o Servi�o pois n�o existe nenhum Faxineiro com esse CPF no Sistema!\n");
				}
				else if (resultado == 3) {
					printf("\nN�o foi poss�vel cadastrar o Servi�o pois n�o existe nenhum Cliente com esse CPF no Sistema!\n");
				}
				break;
			}
			case 4: {
				system("cls");
				int resultado = alterarDadosServicos(servico, &(*contadorServicos));
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
					printf("\nServi�o exclu�do do sistema com sucesso!\n");
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
	int contadorFaxineiros = 0, contadorClientes = 0, contadorServicos = 0; // contador para quantos faxineiros/clientes/servicos est�o inseridos no sistema
	
	// faxineiro � um ponteiro para uma vetor que armazena registros Faxineiro
	Faxineiro *faxineiro;
	faxineiro = (Faxineiro *) malloc(limiteSistema * sizeof(Faxineiro)); // aloca dinamicamente na mem�ria para um vetor do tipo Servico
	// cliente � um ponteiro para uma vetor que armazena registros Cliente
	Cliente *cliente;
	cliente = (Cliente *)malloc(limiteSistema * sizeof(Cliente));
	// servico � um ponteiro para uma vetor que armazena registros Servico
	Servico *servico;
	servico = (Servico *) malloc(limiteSistema * sizeof(Servico)); // aloca dinamicamente na mem�ria para um vetor do tipo Servico

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
				menuClientes(cliente, &contadorClientes);
				menuPrincipal(&op);
				break;
			}
			
			case 3: { // caso a op��o digitada for 3
				printf("Abrindo Submenu de Servi�os...\n");
				menuServicos(servico, &contadorServicos, faxineiro, &contadorFaxineiros, cliente, &contadorClientes);
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
