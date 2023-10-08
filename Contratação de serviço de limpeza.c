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
} Faxineiro;

typedef struct
{
	char cpf[12];
	char nome[50];
	char dataNascimento[11];
	char endereco[100];
	char cep[9];
	char cidade[50];
	char emails[1][50];	   // Máximo de 3 emails por cliente
	char telefones[1][15]; // Máximo de 3 telefones cliente
} Cliente;

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
	for (i = 0; i < contadorFaxineiros; i++)
	{
		if (faxineiro[i].cpf == cpfFaxineiro)
		{
			return i;
		}
	}
	return -1;
}

int incluiFaxineiro(Faxineiro *faxineiro, int *contadorFaxineiros)
{
	int cpfFaxineiro, achou;
	printf("Informe o cpf do faxineiro: ");
	scanf("%d", &cpfFaxineiro);
	achou = verificarFaxineiro(faxineiro, cpfFaxineiro, *contadorFaxineiros);
	if (achou != -1)
	{
		return achou;
	}
	else
	{
		faxineiro[*contadorFaxineiros].cpf = cpfFaxineiro; // faxineiro é um ponteiro para uma estrutura Faxineiro
		(*contadorFaxineiros)++;
		return -1;
	}
}

void menuFaxineiros(Faxineiro *faxineiro, int *contadorFaxineiros)
{
	int opcao;
	system("cls");

	do
	{
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

		switch (opcao)
		{
		case 1:
		{
			system("cls");
			break;
		}
		case 2:
		{
			system("cls");
			break;
		}
		case 3:
		{
			system("cls");
			if (incluiFaxineiro(faxineiro, &(*contadorFaxineiros)) != -1)
			{
				printf("\nFaxineiro já cadastrado no sistema!\n");
			}
			else
			{
				printf("\nFaxineiro cadastrado com sucesso!\n");
			}
			break;
		}
		case 4:
		{
			system("cls");
			break;
		}
		case 5:
		{
			system("cls");
			break;
		}
		case 6:
		{
			system("cls");
			printf("Voltando para o menu principal...\n\n");
			break;
		}
		default:
		{
			system("cls");
			printf("Opção inválida, tente novamente!\n\n");
			break;
		}
		}
	} while (opcao != 6);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int verificarCliente(Cliente *cliente, int cpfCliente, int contadorClientes)
{
	int i;
	for (i = 0; i < contadorClientes; i++)
	{
		if (cliente[i].cpf == cpfCliente)
		{
			return i;
		}
	}
	return -1;
}

void listarClientes(Cliente *clientes, int contadorClientes)
{
	printf("\n");
	for (int i = 0; i < contadorClientes; i++)
	{
		printf("Cliente encontrado:\n");
		printf("CPF: %s\n", clientes[i].cpf);
		printf("Nome: %s\n", clientes[i].nome);
		printf("Data de Nascimento: %s\n", clientes[i].dataNascimento);
		printf("Endereço: %s\n", clientes[i].endereco);
		printf("CEP: %s\n", clientes[i].cep);
		printf("Cidade: %s\n", clientes[i].cidade);

		printf("Emails:\n");
		for (int j = 0; j < 3; j++)
		{
			if (strlen(clientes[i].emails[j]) > 0)
			{
				printf("  %d: %s\n", j + 1, clientes[i].emails[j]);
			}
		}

		printf("Telefones:\n");
		for (int k = 0; k < 3; k++)
		{
			if (strlen(clientes[i].telefones[k]) > 0)
			{
				printf("  %d: %s\n", k + 1, clientes[i].telefones[k]);
			}
		}
	}
}

void listarCliente(Cliente *clientes, int contadorClientes)
{
	printf("\n");
	char cpf[13];

	printf("Digite o CPF do cliente: ");
	fgets(cpf, sizeof(cpf), stdin);
	cpf[strlen(cpf) - 1] = '\0'; // Remove o'\n' capturado por fgets
	int achou = -1;
	achou = verificarCliente(clientes, atoi(cpf), contadorClientes); // Convertemos o CPF para int e usamos verificarCliente corretamente.

	if (achou == -1)
	{
		printf("CPF não consta no cadastro...");
	}
	else
	{
		printf("Cliente encontrado:\n");
		printf("CPF: %s\n", clientes[achou].cpf);
		printf("Nome: %s\n", clientes[achou].nome);
		printf("Data de Nascimento: %s\n", clientes[achou].dataNascimento);
		printf("Endereço: %s\n", clientes[achou].endereco);
		printf("CEP: %s\n", clientes[achou].cep);
		printf("Cidade: %s\n", clientes[achou].cidade);

		printf("Emails:\n");
		for (int j = 0; j < 3; j++)
		{
			if (strlen(clientes[achou].emails[j]) > 0)
			{
				printf("  %d: %s\n", j + 1, clientes[achou].emails[j]);
			}
		}

		printf("Telefones:\n");
		for (int k = 0; k < 3; k++)
		{
			if (strlen(clientes[achou].telefones[k]) > 0)
			{
				printf("  %d: %s\n", k + 1, clientes[achou].telefones[k]);
			}
		}
	}
}

void incluiCliente(Cliente *clientes, int *contadorClientes)
{

	Cliente novoCliente;
	char cpf[13];

	printf("Digite o CPF do cliente: ");
	gets(cpf);

	// Verifica se o CPF já está em uso
	int achou = -1;
	achou = verificarCliente(clientes, atoi(cpf), *contadorClientes);
	if (achou != -1)
	{
		printf("Cliente já cadastrado...");
	}
	else
	{

		printf("Digite o nome do cliente: ");
		scanf(" %49[^\n]", novoCliente.nome);

		printf("Digite a data de nascimento do cliente (DD/MM/AAAA): ");
		scanf("%s", novoCliente.dataNascimento);

		printf("Digite o endereço do cliente: ");
		scanf(" %99[^\n]", novoCliente.endereco);

		printf("Digite o CEP do cliente: ");
		scanf("%s", novoCliente.cep);

		printf("Digite a cidade do cliente: ");
		scanf(" %49[^\n]", novoCliente.cidade);

		printf("Digite o e-mail do cliente: ");
		scanf(" %49[^\n]", novoCliente.emails[0]);

		printf("Digite o telefone do cliente: ");
		scanf(" %14[^\n]", novoCliente.telefones[0]);

		/*
		// Coleta e armazena emails do cliente
		int j = 0;
		while (j < 3) {
			printf("Digite o e-mail %d do cliente (ou deixe em branco para parar): ", j + 1);
			scanf(" %49[^\n]", novoCliente.emails[j]);
			if (strlen(novoCliente.emails[j]) == 0) {
				break;
			}
			j++;
		}

		// Coleta e armazena telefones do cliente
		int k = 0;
		while (k < 3) {
			printf("Digite o telefone %d do cliente (ou deixe em branco para parar): ", k + 1);
			scanf(" %14[^\n]", novoCliente.telefones[k]);
			if (strlen(novoCliente.telefones[k]) == 0) {
				break;
			}
			k++;
		}
		*/

		strcpy(novoCliente.cpf, cpf);

		// Adiciona o novo cliente ao vetor
		clientes[*contadorClientes] = novoCliente;
		(*contadorClientes)++;

		printf("Cliente adicionado com sucesso!\n");
	}
}

void alterarCliente(Cliente *clientes, int *contadorClientes)
{
	char cpf[13];

	printf("Digite o CPF do cliente que deseja alterar: ");
	fgets(cpf, sizeof(cpf), stdin);
	cpf[strlen(cpf) - 1] = '\0'; // Remove o '\n' capturado por fgets

	int achou = -1;
	achou = verificarCliente(clientes, atoi(cpf), *contadorClientes);

	if (achou == -1)
	{
		printf("CPF não consta no cadastro...\n");
	}
	else
	{
		Cliente *clienteParaAlterar = &clientes[achou];

		printf("Cliente encontrado:\n");
		printf("CPF: %s\n", clienteParaAlterar->cpf);
		printf("Nome: %s\n", clienteParaAlterar->nome);
		printf("Data de Nascimento: %s\n", clienteParaAlterar->dataNascimento);
		printf("Endereço: %s\n", clienteParaAlterar->endereco);
		printf("CEP: %s\n", clienteParaAlterar->cep);
		printf("Cidade: %s\n", clienteParaAlterar->cidade);

		printf("Emails:\n");
		for (int j = 0; j < 3; j++)
		{
			if (strlen(clienteParaAlterar->emails[j]) > 0)
			{
				printf("  %d: %s\n", j + 1, clienteParaAlterar->emails[j]);
			}
		}

		printf("Telefones:\n");
		for (int k = 0; k < 3; k++)
		{
			if (strlen(clienteParaAlterar->telefones[k]) > 0)
			{
				printf("  %d: %s\n", k + 1, clienteParaAlterar->telefones[k]);
			}
		}

		char opcao[3];
		printf("Deseja alterar os dados deste cliente? (Sim/Não): ");
		fgets(opcao, sizeof(opcao), stdin);
		opcao[strlen(opcao) - 1] = '\0'; // Remove o '\n' capturado por fgets

		if (strcmp(opcao, "Sim") == 0 || strcmp(opcao, "sim") == 0 || strcmp(opcao, "SIM") == 0)
		{
			printf("Digite o novo nome do cliente (ou deixe em branco para manter o mesmo): ");
			fgets(clienteParaAlterar->nome, sizeof(clienteParaAlterar->nome), stdin);
			clienteParaAlterar->nome[strlen(clienteParaAlterar->nome) - 1] = '\0'; // Remove o '\n' capturado por fgets

			printf("Digite a nova data de nascimento do cliente (DD/MM/AAAA) (ou deixe em branco para manter a mesma): ");
			fgets(clienteParaAlterar->dataNascimento, sizeof(clienteParaAlterar->dataNascimento), stdin);
			clienteParaAlterar->dataNascimento[strlen(clienteParaAlterar->dataNascimento) - 1] = '\0'; // Remove o '\n' capturado por fgets

			printf("Digite o novo endereço do cliente (ou deixe em branco para manter o mesmo): ");
			fgets(clienteParaAlterar->endereco, sizeof(clienteParaAlterar->endereco), stdin);
			clienteParaAlterar->endereco[strlen(clienteParaAlterar->endereco) - 1] = '\0'; // Remove o '\n' capturado por fgets

			printf("Digite o novo CEP do cliente (ou deixe em branco para manter o mesmo): ");
			fgets(clienteParaAlterar->cep, sizeof(clienteParaAlterar->cep), stdin);
			clienteParaAlterar->cep[strlen(clienteParaAlterar->cep) - 1] = '\0'; // Remove o '\n' capturado por fgets

			printf("Digite a nova cidade do cliente (ou deixe em branco para manter a mesma): ");
			fgets(clienteParaAlterar->cidade, sizeof(clienteParaAlterar->cidade), stdin);
			clienteParaAlterar->cidade[strlen(clienteParaAlterar->cidade) - 1] = '\0'; // Remove o '\n' capturado por fgets

			// Alterar emails do cliente
			for (int j = 0; j < 3; j++)
			{
				printf("Deseja alterar o e-mail %d do cliente? (Sim/Não): ", j + 1);
				fgets(opcao, sizeof(opcao), stdin);
				opcao[strlen(opcao) - 1] = '\0'; // Remove o '\n' capturado por fgets
				if (strcmp(opcao, "Sim") == 0 || strcmp(opcao, "sim") == 0 || strcmp(opcao, "SIM") == 0)
				{
					printf("Digite o novo e-mail (ou deixe em branco para manter o mesmo): ");
					fgets(clienteParaAlterar->emails[j], sizeof(clienteParaAlterar->emails[j]), stdin);
					clienteParaAlterar->emails[j][strlen(clienteParaAlterar->emails[j]) - 1] = '\0'; // Remove o '\n' capturado por fgets
				}
			}

			// Alterar telefones do cliente
			for (int k = 0; k < 3; k++)
			{
				printf("Deseja alterar o telefone %d do cliente? (Sim/Não): ", k + 1);
				fgets(opcao, sizeof(opcao), stdin);
				opcao[strlen(opcao) - 1] = '\0'; // Remove o '\n' capturado por fgets
				if (strcmp(opcao, "Sim") == 0 || strcmp(opcao, "sim") == 0 || strcmp(opcao, "SIM") == 0)
				{
					printf("Digite o novo telefone (ou deixe em branco para manter o mesmo): ");
					fgets(clienteParaAlterar->telefones[k], sizeof(clienteParaAlterar->telefones[k]), stdin);
					clienteParaAlterar->telefones[k][strlen(clienteParaAlterar->telefones[k]) - 1] = '\0'; // Remove o '\n' capturado por fgets
				}
			}

			printf("Dados do cliente alterados com sucesso!\n");
		}
	}
}

void excluirCliente(Cliente *clientes, int *contadorClientes)
{
	char cpf[13];

	printf("Digite o CPF do cliente que deseja excluir: ");
	fgets(cpf, sizeof(cpf), stdin);
	cpf[strlen(cpf) - 1] = '\0'; // Remove o '\n' capturado por fgets

	int achou = -1;
	achou = verificarCliente(clientes, atoi(cpf), *contadorClientes);

	if (achou == -1)
	{
		printf("CPF não consta no cadastro...\n");
	}
	else
	{
		Cliente *clienteParaExcluir = &clientes[achou];

		printf("Cliente encontrado:\n");
		printf("CPF: %s\n", clienteParaExcluir->cpf);
		printf("Nome: %s\n", clienteParaExcluir->nome);

		char opcao[3];
		printf("Deseja excluir este cliente? (Sim/Não): ");
		fgets(opcao, sizeof(opcao), stdin);
		opcao[strlen(opcao) - 1] = '\0'; // Remove o '\n' capturado por fgets

		if (strcmp(opcao, "Sim") == 0 || strcmp(opcao, "sim") == 0 || strcmp(opcao, "SIM") == 0 || strcmp(opcao, "ss") == 0 || strcmp(opcao, "s") == 0 || strcmp(opcao, "SS") == 0 || strcmp(opcao, "S") == 0)
		{
			// Remova o cliente do cadastro
			for (int i = achou; i < *contadorClientes - 1; i++)
			{
				// Move os clientes subsequentes para preencher o espaço
				*clienteParaExcluir = clientes[i + 1];
			}
			(*contadorClientes)--;
			printf("Cliente excluído com sucesso!\n");
		}
		else
		{
			printf("Cliente não foi excluído.\n");
		}
	}
}

void menuClientes(struct Cliente *cliente, int contadorClientes)
{
	int opcao;
	system("cls");

	do
	{
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

		switch (opcao)
		{
		case 1:
		{
			system("cls");
			listarClientes(cliente, contadorClientes);
			break;
		}
		case 2:
		{
			system("cls");
			listarCliente(cliente, contadorClientes);
			break;
		}
		case 3:
		{
			system("cls");
			incluiCliente(cliente, contadorClientes);
			break;
		}
		case 4:
		{
			system("cls");
			alterarCliente(cliente, contadorClientes);
			break;
		}
		case 5:
		{
			system("cls");
			excluirCliente(cliente, contadorClientes);
			break;
		}
		case 6:
		{
			system("cls");
			printf("Voltando para o menu principal...\n\n");
			break;
		}
		default:
		{
			system("cls");
			printf("Opção inválida, tente novamente!\n\n");
			break;
		}
		}
	} while (opcao != 6);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void menuServicos()
{
	int opcao;
	system("cls");

	do
	{
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

		switch (opcao)
		{
		case 1:
		{
			system("cls");
			break;
		}
		case 2:
		{
			system("cls");
			break;
		}
		case 3:
		{
			system("cls");
			break;
		}
		case 4:
		{
			system("cls");
			break;
		}
		case 5:
		{
			system("cls");
			break;
		}
		case 6:
		{
			system("cls");
			printf("Voltando para o menu principal...\n\n");
			break;
		}
		default:
		{
			system("cls");
			printf("Opção inválida, tente novamente!\n\n");
			break;
		}
		}
	} while (opcao != 6);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
	setlocale(LC_ALL, "Portuguese");
	int op, limiteSistema = 100;
	int contadorFaxineiros = 0;											// contador para quantos faxineiros estão inseridos no sistema
	Faxineiro *faxineiro;												// crair o vetor dentro da main e mandar ele dps
	faxineiro = (Faxineiro *)malloc(sizeof(Faxineiro) * limiteSistema); // aloca dinamicamente na memória para um único objeto do tipo Faxineiro

	int contadorClientes = 0;
	Cliente *cliente;
	cliente = (int *)malloc(sizeof(Cliente) * limiteSistema);

	menuPrincipal(&op);

	do
	{
		switch (op)
		{
		case 1:
		{ // caso a opção digitada for 1
			menuFaxineiros(faxineiro, &contadorFaxineiros);
			menuPrincipal(&op);
			break;
		}

		case 2:
		{ // caso a opção digitada for 2
			printf("Abrindo Submenu de Clientes...\n");
			menuClientes(cliente, contadorClientes);
			menuPrincipal(&op);
			break;
		}

		case 3:
		{ // caso a opção digitada for 3
			printf("Abrindo Submenu de Serviços...\n");
			menuServicos();
			menuPrincipal(&op);
			break;
		}

		case 4:
		{ // caso a opção digitada for 4
			printf("Abrindo Submenu de Relatórios...\n");
			menuPrincipal(&op);
			break;
		}

		case 5:
		{ // caso a opção digitada for 5
			// sai do loop e finaliza o programa, pois não chama o Menu Principal novamente
			break;
		}

		default:
		{ // caso a opção digitada não está entre as opções disponíveis
			system("cls");
			printf("Opção inválida, tente novamente!\n\n");
			menuPrincipal(&op);
			break;
		}
		}
		if (op == 5)
		{
			printf("Finalizando o programa...");
		}
	} while (op != 5); // mantém o Menu Principal em loop até que op seja igual a 5
}
