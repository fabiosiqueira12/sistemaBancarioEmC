#define _WIN32_WINNT 0x0601

#include<stdio.h> //Lib básica
#include<stdlib.h> //Lib Básica
#include<locale.h> //Setar o local para português
#include<string.h> //Lib básica
#include<windows.h> //Lib para pegar funcões e menu do windows
#include<time.h> //Lib para manipular data e hora
#define tamanhoArrayExtrato 5 //Variavel para acessar arrays de extrato dentro de pessoa


/*Declaração de structs*/
typedef struct SUltimosSaques {

	float valor;
	int dia,mes,ano,hora,minuto,segundo; //Para Guardar a data, guardo cada valor em cada variável
	int estaIniciado; //Variável auxiliar para pecorrer nos arrays dentro da struct pessoa

} TUltimosSaques;

typedef struct SUltimosDepositos {

	float valor;
	int dia,mes,ano,hora,minuto,segundo; //Para Guardar a data, guardo cada valor em cada variável
	int estaIniciado; //Variável auxiliar para pecorrer nos arrays dentro da struct pessoa

} TUltimosDepositos;

typedef struct STransferencias {

	float valor;
	int dia,mes,ano,hora,minuto,segundo; //Para Guardar a data, guardo cada valor em cada variável
	char nomePessoaRecebeu[70];
	int estaIniciado; //Variável auxiliar para pecorrer nos arrays dentro da struct pessoa

} TUltimasTransferencias;

typedef struct Sconta {

	int agencia;
	int operacao;
	long numeroConta;
	long senha;
	float saldo;
	TUltimosSaques ultimosSaques[6];
	TUltimosDepositos ultimosDepositos[6];
	TUltimasTransferencias ultimasTransferencias[6];

} TConta;

typedef struct SPessoa {
	char nome[70];
	char cpf[15];
	char sexo[12];
	int idade;
	TConta conta;

} TPessoa;

/* Fim Declaração Structs */

//Declaração de váriaveis globais

FILE *file;
TPessoa pessoaLogada;


/* Fim Declaração váriaveis globais */



/* Declaração das Funções*/
/* Funções para gerar menus */

void acessarSistema();
void sair();
void menuDeAcesso(TPessoa pessoa);
void loginSistema();
void menuMais(TPessoa pessoa);

//Função de CRUD

void cadastrarUsuario();
void editarUsuario(TPessoa pessoa);
void verInformacoes(TPessoa pessoa);
void verInformacoesConta(TPessoa pessoa);

//Funções Do Caixa

void versaldo(TPessoa pessoa);
void saque(TPessoa pessoa);
void menuExtrato (TPessoa pessoa);
void deposito (TPessoa pessoa);
void depositoAnonimo();
void transferencia(TPessoa pessoa);
void extratoDepositos(TPessoa pessoa);
void extratoTransferencias(TPessoa pessoa);
void extratoSaques(TPessoa pessoa);

//Funções para manipular arquivos

/*
	Função Para manipular os dados,
	char modo = caracter pra representar modo de abertura de arquivo
	opções => 'w' = w+b,'r' = 'rb', 'a' = 'ab', f = 'r+b'
  */
FILE* abreArquivo(char modo);

void fecharArquivo(FILE *arquivo); //Função Para Fechar arquivo

/* Fim Declaração Funções */

//Main
int main() {

	//trecho de código para desabilitar o botão fechar do cmd

	HWND hnd;
	HMENU menu;
	int i, j, cont;
	LPTSTR buffer;

	// Recebe o handle do console
	hnd = GetConsoleWindow();

	// Recebe o handle para o menu do sistema
	menu = GetSystemMenu(hnd, 0);

	// Recebe quantos itens tem no menu
	cont = GetMenuItemCount(menu);

	j = -1;

	// Alocando espaço para receber a string que "não sabemos" o tamanho
	buffer = (TCHAR*) malloc (256 *sizeof(TCHAR));

	for (i=0; i<cont; i++) {
		// Recebe a string do menu, na posição "i" e a coloca no buffer
		GetMenuString(menu, i, buffer, 255, MF_BYPOSITION);
		//Compara se a string do menu é igual a string "Fechar"
		if (!strcmp(buffer, "&Fechar")) {
			j = i;
			break;
		}
	}
	// Se a string "Fechar" for encontrada, remove do menu
	if (j >= 0)
		RemoveMenu(menu, j, MF_BYPOSITION);

	//trecho de código para desabilitar o botão fechar do cmd

	system("title SIMULADOR BANCO");
	system("color 8f");
	setlocale(LC_ALL, "Portuguese");
	acessarSistema();

}
//Fim Main

//Implementação de Funções

//Função De Acesso Ao Sistema
void acessarSistema() {
	system("color 8f");
	system("cls");
	int opc;
	printf("\n\t\t\tSimulador de Sistema Bancário \n");
	printf("\n---------------------------------------------------\n");
	printf("\n\n\t\t\t MENU\n\n");
	printf("\n---------------------------------------------------\n");
	printf("1- Acesso do usuário");
	printf("\n2- Cadastrar Novo Usuário");
	printf("\n3- Depositar ");
	printf("\n4- Sair ");
	printf("\n\nDigite uma opção: ");
	fflush(stdin);
	scanf("%i",&opc);
	switch(opc) {
		case 1:
			loginSistema();
			break;
		case 2:
			cadastrarUsuario();
			break;
		case 3:
			depositoAnonimo();
			break;
		case 4:
			sair();
			break;
		default :
			printf("\n Opção Inválida, Digite uma das opções disponíveis\n");
			system("pause");
			acessarSistema();
			break;
	}

}

//Função Para Verificar Se Conta Existe
void loginSistema() {
	TPessoa aux;
	int numeroConta;
	int usuarioValido = 0;
	int numeroTentativas = 5;
	system("cls");
	system("color 3f");
	//Pegar Arquivo E Jogar Em Array
	int j;
	for (j = 0; j < numeroTentativas ; j++) {
		printf("\n\n Número de tentativas: %i, Resta:  %i \n\n",(j),numeroTentativas - (j));
		printf("\n\nDigite Número Da Conta(só números): ");
		fflush(stdin);
		scanf("%i",&numeroConta);

		file = abreArquivo('r');
		if (numeroConta != 0) {



			while( fread(&aux,sizeof(TPessoa),1,file) == 1) {

				if (aux.conta.numeroConta == numeroConta) {
					pessoaLogada = aux;
					usuarioValido = 1;
				}

			}

			if (usuarioValido == 1) {
				fecharArquivo(file);
				menuDeAcesso(pessoaLogada);
				break;

			} else {

				printf("\n Usuário Não Existe No Sistema\n");
				system("pause");
				system("cls");
			}

		} else {
			printf("\n Digite Só Números!\n");
			system("pause");
			system("cls");
		}

	}

	fecharArquivo(file);

	printf("\nQuantidade de tentativas Esgotadas, Tente Novamente Ou Faça O Cadastro \n");
	system("pause");
	acessarSistema();


}


//Função de Menu Com Opções do sistema
void menuDeAcesso(TPessoa pessoa) {
	int opc;
	system("cls");
	system("color 3f");
	printf("\n\t\t\tSimulador De Sistema Bancário\n");
	printf("\n---------------------------------------------------\n");

	printf("\n Bem Vindo %s \n",pessoa.nome);

	printf("\n---------------------------------------------------\n");

	printf("\n\n\t\t\t MENU\n\n");
	printf("1- Ver Saldo");
	printf("\n2- Extrato");
	printf("\n3- Saque");
	printf("\n4- Depósito");
	printf("\n5- Transferência");
	printf("\n6- Mais");
	printf("\n7- Menu Principal ");
	printf("\n8- Sair Do Sistema\n");
	printf("\n\nDigite uma opção: ");
	fflush(stdin);
	scanf("%i",&opc);
	switch(opc) {
		case 1:
			versaldo(pessoa);
			break;
		case 2:
			menuExtrato(pessoa);
			break;
		case 3:
			saque(pessoa);
			break;
		case 4:
			deposito(pessoa);
			break;
		case 5:
			transferencia(pessoa);
			break;
		case 6:
			menuMais(pessoa);
			break;

		case 7:
			acessarSistema();

			break;

		case 8:
			sair();
			break;

		default:
			printf("Opção invalida!\n");
			system("pause");
			menuDeAcesso(pessoa);
			break;
	}

}

void menuMais(TPessoa pessoa) {
	system("color 3f");
	system("cls");
	int opc;
	printf("\n---------------------------------------------------\n\n");
	printf("1- Ver Informações Do Usuário");
	printf("\n2- Ver informações da conta");
	printf("\n3- Editar Informações Do Usuário");
	printf("\n4- Voltar ");
	printf("\n\nDigite uma opção: ");
	fflush(stdin);
	scanf("%i",&opc);
	switch(opc) {
		case 1:
			verInformacoes(pessoa);
			break;
		case 2:
			verInformacoesConta(pessoa);
			break;
		case 3:
			editarUsuario(pessoa);
			break;
		case 4:
			menuDeAcesso(pessoa);
			break;
		default :
			printf("\n Opção Inválida, Digite uma das opções disponíveis\n");
			system("pause");
			menuMais(pessoa);
			break;
	}

}//Fim Metodo

void sair() {

	system("cls");
	printf("\n\t\n Saindo Do Sistema\n");
	printf("\n\t Até Breve \n\n");
	exit(0);
	system("pause");

}//Fim Metodo



void cadastrarUsuario() {

	TPessoa pessoa;
	TPessoa aux;
	int escolhaSexo;
	int numerocontaValidar = 0;
	int achouConta = 0;

	system("cls");


	do {
		printf("\n\n Digite O Nome Do Usuário : ");
		fflush(stdin);
		gets(pessoa.nome);

		if (strlen(pessoa.nome) != 0) {


		} else {
			printf("\n Digite Algo Para Nome \n");
			system("pause");
			system("cls");
		}

	} while (strlen(pessoa.nome) == 0);


	do {

		printf("\n\n Digite O Número Do Cpf : ");
		fflush(stdin);
		gets(pessoa.cpf);

		if (strlen(pessoa.cpf) != 0) {

			if (strlen(pessoa.cpf) == 14) {

			} else {
				printf("\n Digite apenas 14 digitos \n");
				system("pause");
				system("cls");
			}

		} else {
			printf("\n Digite algo Para O CPF !! \n");
			system("pause");
			system("cls");



		}

	} while(strlen(pessoa.cpf) < 14);

	do {

		printf("\n\n Escolha O Sexo : 1- masculino / 2- feminino : ");
		fflush(stdin);
		scanf("%i",&escolhaSexo);
		switch(escolhaSexo) {

			case  1:
				strcpy(pessoa.sexo,"masculino");
				break;
			case  2:
				strcpy(pessoa.sexo,"feminino");
				break;
			default :
				printf("\nOpção Inválida\n");
				system("pause");
				system("cls");
				break;

		}

	} while (escolhaSexo != 1 && escolhaSexo != 2);

	do {
		printf("\n\n Digite Sua Idade : ");
		fflush(stdin);
		scanf("%d",&pessoa.idade);

		if (pessoa.idade < 16) {
			printf("\n Usuário tem que ser maior que 16 anos \n");
			system("pause");
			system("cls");
		}

	} while(pessoa.idade < 16);


	do {
		printf("\n\n Digite A Agencia : ");
		fflush(stdin);
		scanf("%d", &pessoa.conta.agencia);

		if (pessoa.conta.agencia <= 0) {
			printf("\n Digite um valor válido, número ou valor maior que zero\n");
			system("pause");
			system("cls");
		}

	} while (pessoa.conta.agencia <= 0);



	do {
		printf("\n\n Digite a operação : ");
		fflush(stdin);
		scanf("%d", &pessoa.conta.operacao);

		if (pessoa.conta.operacao <= 0) {
			printf("\n Digite um valor válido, número ou valor maior que zero\n");
			system("pause");
			system("cls");
		}

	} while (pessoa.conta.operacao <= 0);

	do {
		printf("\n\n Digite o número da conta : ");
		fflush(stdin);
		scanf("%d",&pessoa.conta.numeroConta);

		if (pessoa.conta.numeroConta <= 0) {
			printf("\n Digite um valor maior que zero \n");
			system("pause");
			system("cls");

		} else {

			file = fopen("dados.txt","rb");

			if (file != NULL) {

				while( fread(&aux,sizeof(TPessoa),1,file) == 1) {

					if (aux.conta.numeroConta == pessoa.conta.numeroConta) {
						printf("\n Esse número de conta já existe \n");
						system("pause");
						system("cls");
						achouConta = 1;
						break;
					} else {
						achouConta = 0;
					}

				}

				if (achouConta == 0 ) {
					printf("\n");
					numerocontaValidar = 1;
				}




			} else {
				numerocontaValidar = 1;
			}

			fclose(file);

		}


	} while(numerocontaValidar == 0);


	do {

		printf("\n\n Digite A Senha : ");
		fflush(stdin);
		scanf("%i", &pessoa.conta.senha);

		if (pessoa.conta.senha <= 0) {
			printf("\n Digite um valor válido, número ou valor maior que zero\n");
			system("pause");
			system("cls");
		}

	} while(pessoa.conta.senha <= 0);


	pessoa.conta.saldo = 100.0;

	printf("\nUsuário Cadastrado com sucesso, Você já pode acessar o sistema\n");
	pessoa;

	int f;
	for (f = 0; f < tamanhoArrayExtrato; f++) {

		pessoa.conta.ultimosDepositos[f].estaIniciado = 0;
		pessoa.conta.ultimosSaques[f].estaIniciado = 0;
		pessoa.conta.ultimasTransferencias[f].estaIniciado = 0;
	}

	file = abreArquivo('a');

	fwrite(&pessoa,sizeof(TPessoa),1,file);

	fecharArquivo(file);


	system("pause");
	acessarSistema();

} //Fim Metodo

void editarUsuario(TPessoa pessoa) {
	TPessoa aux;
	int opcao;
	long senha;
	char cpfAux[15];
	char novoNome[70];
	char novoCpf[15];
	char novoSexo[12];
	int novaIdade;
	long novaSenha;
	int posicao = 0;
	int pegou = 0;
	int escolhaSexo = 0;


	system("cls");
	printf("\n\n\t\t\t Opcões De Edição \n");
	printf("\n1- Nome ");
	printf("\n2- CPF ");
	printf("\n3- Sexo  ");
	printf("\n4- Idade ");
	printf("\n5- Senha ");
	printf("\n6- Voltar ");


	printf("\n\n Digite Uma Opção: ");
	fflush(stdin);

	scanf("%i", &opcao);

	switch(opcao) {

		case 1:

			system("cls");
			do {
				printf("\nDigite Um Novo Nome : ");
				fflush(stdin);
				gets(novoNome);

				if (strlen(novoNome) <= 0) {
					printf("\n Digite algo para o nome \n");
					system("pause");
					system("cls");
				} else {



					printf("\n Digite A Senha Para Confirmar : ");
					fflush(stdin);
					scanf("%i",&senha);


					if (pessoa.conta.senha == senha) {

						file = abreArquivo('f');


						fseek(file,posicao,SEEK_SET);

						while( fread(&aux,sizeof(TPessoa),1,file) == 1) {

							if (aux.conta.numeroConta == pessoa.conta.numeroConta) {

								strcpy(aux.nome,novoNome);

								strcpy(pessoa.nome,novoNome);

								fseek(file,posicao, SEEK_SET);
								fwrite(&aux,sizeof(TPessoa),1,file);

								pegou = 1;
								break;
							}

							posicao = posicao + sizeof(TPessoa);

						}

						fecharArquivo(file);

						if (pegou == 1) {
							printf("\n Nome atualizado com sucesso \n");
							system("pause");
							editarUsuario(pessoa);
							break;
						} else {
							printf("\n Erro ao tentar salvar nome, tente novamente !!! \n");
							system("pause");
							editarUsuario(pessoa);
							break;
						}

					} else {
						printf("\n Senha Incorreta, Tente Novamente \n");
						system("pause");
						editarUsuario(pessoa);
						break;

					}

				}

			} while(strlen(novoNome) <= 0);


			break;

		case 2:

			system("cls");
			do {
				printf("\n Digite Um Novo CPF : ");
				fflush(stdin);
				gets(novoCpf);

				if (strlen(novoCpf) <= 0) {
					printf("\n Digite algo para o CPF \n");
					system("pause");
					system("cls");
				} else if (strlen(novoCpf) < 14) {
					printf("\n Digite 14 digitos para o CPF \n");
					system("pause");
					system("cls");
				} else if (strlen(novoCpf) > 14) {
					printf("\n Digite 14 digitos para o CPF \n");
					system("pause");
					system("cls");
				} else {

					printf("\n Digite A Senha Para Confirmar : ");
					fflush(stdin);
					scanf("%i",&senha);


					if (pessoa.conta.senha == senha) {

						file = abreArquivo('f');


						fseek(file,posicao,SEEK_SET);

						while( fread(&aux,sizeof(TPessoa),1,file) == 1) {

							if (aux.conta.numeroConta == pessoa.conta.numeroConta) {

								strcpy(aux.cpf,novoCpf);

								strcpy(pessoa.cpf,novoCpf);

								fseek(file,posicao, SEEK_SET);
								fwrite(&aux,sizeof(TPessoa),1,file);

								pegou = 1;
								break;
							}

							posicao = posicao + sizeof(TPessoa);

						}

						fecharArquivo(file);

						if (pegou == 1) {
							printf("\n CPF atualizado com sucesso \n");
							system("pause");
							editarUsuario(pessoa);
							break;
						} else {
							printf("\n Erro ao tentar salvar CPF, tente novamente !!! \n");
							system("pause");
							editarUsuario(pessoa);
							break;
						}

					} else {
						printf("\n Senha Incorreta, Tente Novamente \n");
						system("pause");
						editarUsuario(pessoa);
						break;

					}

				}

			} while(strlen(novoCpf) != 14);

			break;

		case 3:

			system("cls");

			do {

				printf("\n\n Escolha O Sexo : 1- masculino / 2- feminino : ");
				fflush(stdin);
				scanf("%i",&escolhaSexo);
				switch(escolhaSexo) {

					case  1:
						strcpy(novoSexo,"masculino");
						break;
					case  2:
						strcpy(novoSexo,"feminino");
						break;
					default :
						printf("\nOpção Inválida\n");
						system("pause");
						system("cls");
						break;

				}

			} while (escolhaSexo != 1 && escolhaSexo != 2);

			system("cls");
			printf("\n Tem certeza dessa operacão ? 1- sim / 2- não ");
			scanf("%i",&pegou);

			if (pegou == 1) {

				file = abreArquivo('f');


				fseek(file,posicao,SEEK_SET);

				while( fread(&aux,sizeof(TPessoa),1,file) == 1) {

					if (aux.conta.numeroConta == pessoa.conta.numeroConta) {

						strcpy(aux.sexo,novoSexo);

						strcpy(pessoa.sexo,novoSexo);

						fseek(file,posicao, SEEK_SET);
						fwrite(&aux,sizeof(TPessoa),1,file);

						pegou = 1;
						break;
					}

					posicao = posicao + sizeof(TPessoa);

				}

				fecharArquivo(file);

				printf("\n Sexo atualizado com sucesso \n");
				system("pause");
				editarUsuario(pessoa);


			} else if (pegou = 2) {

				printf("\n Operação cancelada \n");
				system("pause");
				editarUsuario(pessoa);

			} else {

				printf("\n Opção inválida \n");
				system("pause");
				editarUsuario(pessoa);

			}

			break;

		case 4:

			system("cls");

			do {

				printf("Digite a nova idade : ");
				scanf("%i",&novaIdade);

				if (novaIdade < 16) {
					printf("\n Idade tem que ser maior do que 16 anos \n");
					system("pause");
					system("cls");

				}

			} while (novaIdade < 16);



			printf("\n Digite A Senha Para Confirmar : ");
			fflush(stdin);
			scanf("%i",&senha);

			if (pessoa.conta.senha == senha) {

				file = abreArquivo('f');


				fseek(file,posicao,SEEK_SET);

				while( fread(&aux,sizeof(TPessoa),1,file) == 1) {

					if (aux.conta.numeroConta == pessoa.conta.numeroConta) {

						aux.idade = novaIdade;

						pessoa.idade = novaIdade;

						fseek(file,posicao, SEEK_SET);
						fwrite(&aux,sizeof(TPessoa),1,file);

						pegou = 1;
						break;
					}

					posicao = posicao + sizeof(TPessoa);

				}

				fecharArquivo(file);

				if (pegou == 1) {
					printf("\n Idade atualizada com sucesso \n");
					system("pause");
					editarUsuario(pessoa);
				} else {
					printf("\n Erro ao tentar atualizar idade, tente novamente !!! \n");
					system("pause");
					editarUsuario(pessoa);

				}

			} else {
				printf("\n Senha Incorreta, Tente Novamente \n");
				system("pause");
				editarUsuario(pessoa);

			}

			break;


		case 5:

			system("cls");

			do {
				printf("\nDigite Sua Senha Nova : ");
				fflush(stdin);
				scanf("%i", &novaSenha);

				if (novaSenha <= 0) {
					printf("\n Digite um valor válido, número ou valor maior que zero\n");
					system("pause");
					system("cls");
				}

			} while(novaSenha <= 0);

			do {

				printf("Digite Seu CPF para Confimar : ");
				fflush(stdin);
				gets(cpfAux);

				if (strlen(cpfAux) < 14 || strlen(cpfAux) > 14) {
					printf("\n Digite 14 digitos para o CPF \n");
					system("pause");
					system("cls");
				}

			} while (strlen(cpfAux) != 14);


			if (strcmp(pessoa.cpf, cpfAux) == 0 ) {

				file = abreArquivo('f');


				fseek(file,posicao,SEEK_SET);

				while( fread(&aux,sizeof(TPessoa),1,file) == 1) {

					if (aux.conta.numeroConta == pessoa.conta.numeroConta) {

						aux.conta.senha  = novaSenha;

						pessoa.conta.senha = novaSenha;

						fseek(file,posicao, SEEK_SET);
						fwrite(&aux,sizeof(TPessoa),1,file);

						pegou = 1;
						break;
					}

					posicao = posicao + sizeof(TPessoa);

				}

				fecharArquivo(file);

				if (pegou == 1) {
					printf("\n Senha atualizada com sucesso \n");
					system("pause");
					editarUsuario(pessoa);
				} else {
					printf("\n Erro ao tentar atualizar senha, tente novamente !!! \n");
					system("pause");
					editarUsuario(pessoa);

				}


			} else {

				printf("\nCpf Incorreto , Tente Novamente !!!\n");
				system("pause");
				editarUsuario(pessoa);

			}

			break;

		case 6:
			system("cls");
			menuMais(pessoa);

		default :
			printf("Opcão Inválida \n");
			system("pause");
			editarUsuario(pessoa);

	}



}//Fim Metodo

void verInformacoes(TPessoa pessoa) {

	system("cls");

	printf("\n Informações Do Usuário \n");
	printf("\n---------------------------------------------------\n\n");
	printf ("\t\t Nome : %s", pessoa.nome);
	printf("\n\t\t CPF : %s", pessoa.cpf);
	printf("\n\t\t Sexo : %s", pessoa.sexo);
	printf("\n\t\t Idade : %d Anos", pessoa.idade);
	printf("\n---------------------------------------------------\n\n");
	system("pause");

	menuMais(pessoa);

}//Fim Metodo

void versaldo(TPessoa pessoa) {
	TPessoa aux;
	int senha;

	system("cls");
	printf("\nDigite Sua Senha : ");
	scanf("%i",&senha);

	if (pessoa.conta.senha == senha) {

		file = abreArquivo('r');

		while( fread(&aux,sizeof(TPessoa),1,file) == 1) {

			if (aux.conta.senha == pessoa.conta.senha) {
				printf("\n Seu Saldo é :  R$ %.2f\n",aux.conta.saldo);
				system("Pause");
				menuDeAcesso(pessoa);
				fecharArquivo(file);
			}

		}


	} else {

		printf("\nSenha Incorreta !!\n");
		system("pause");
		menuDeAcesso(pessoa);

	}

}//Fim Metodo


void saque(TPessoa pessoa) {
	TUltimosSaques auxSaque;
	TUltimosSaques ultimosSaque;
	TPessoa aux;
	int pegou = 0;
	int posicao = 0;
	float valor;
	int senha;

	system("cls");
	printf("\nDigite O Valor A Ser Sacado : ");
	scanf("%f",&valor);

	if (valor <= 0 ) {
		printf("\n O Valor Tem Que Ser Maior Que Zero \n");
		system("pause");
		saque(pessoa);
	}


	printf("\nDigite Sua Senha : ");
	scanf("%i",&senha);

	if (pessoa.conta.senha == senha) {

		file = abreArquivo('f');

		fseek(file,posicao,SEEK_SET);

		while( fread(&aux,sizeof(TPessoa),1,file) == 1) {

			if (aux.conta.numeroConta == pessoa.conta.numeroConta) {
				if (aux.conta.saldo < valor) {
					printf("\n Saldo insuficiente para realizar o saque\n");
					system("pause");
					menuDeAcesso(pessoa);
					fecharArquivo(file);
					break;
				} else {



					aux.conta.saldo = aux.conta.saldo - valor;

					pessoa.conta.saldo = pessoa.conta.saldo - valor;

					struct tm *local;
					time_t t;

					t= time(NULL);//Iniciando A Váriavel
					local=localtime(&t);

					ultimosSaque.valor = valor;
					ultimosSaque.dia = local->tm_mday;
					ultimosSaque.mes = local->tm_mon + 1;
					ultimosSaque.ano = local->tm_year + 1900;
					ultimosSaque.hora = local->tm_hour;
					ultimosSaque.minuto = local->tm_min;
					ultimosSaque.segundo = local->tm_sec;
					ultimosSaque.estaIniciado = 1;

					int f;
					for (f = 0; f < tamanhoArrayExtrato; f++) {

						if ( f == (tamanhoArrayExtrato - 1)) {

							int k;
							for (k = 0 ; k < tamanhoArrayExtrato; k++) {
								if (k == (tamanhoArrayExtrato -1) ) {
									aux.conta.ultimosSaques[k] = ultimosSaque;
								} else {

									auxSaque = aux.conta.ultimosSaques[k + 1];
									aux.conta.ultimosSaques[k] = auxSaque;

								}
							}
						} else {

							if (aux.conta.ultimosSaques[f].estaIniciado == 0) {
								aux.conta.ultimosSaques[f] = ultimosSaque;
								break;
							}

						}

					}


					fseek(file,posicao,SEEK_SET);

					fwrite(&aux,sizeof(TPessoa),1,file);

				}

				pegou = 1;
				break;
			}
			posicao = posicao + sizeof(TPessoa);
		}

		fecharArquivo(file);

		if (pegou == 1) {
			printf("\n Saque Realizado Com Sucesso \n");
			printf("\n Seu novo Saldo é : %.2f \n", pessoa.conta.saldo);
			system("pause");
			menuDeAcesso(pessoa);

		} else {

			printf("\n Conta Não Tá Cadastrada No Sistema \n");
			system("pause");
			menuDeAcesso(pessoa);

		}

	} else {

		printf("\nSenha Incorreta !!\n");
		system("pause");
		menuDeAcesso(pessoa);

	}

}//Fim Metodo


void menuExtrato (TPessoa pessoa) {
	int opcao;

	system("cls");

	printf("\n\n 1 - Últimos Depositos ");
	printf ("\n 2 - Últimos Saques ");
	printf("\n 3 - Últimas Transferências ");
	printf("\n 4 - Voltar");
	printf("\n Digite sua opção : ");
	fflush(stdin);
	scanf("%i",&opcao);

	switch(opcao) {

		case 1:
			extratoDepositos(pessoa);
			break;
		case 2:
			extratoSaques(pessoa);
			break;
		case 3:
			extratoTransferencias(pessoa);
			break;
		case 4:
			menuDeAcesso(pessoa);
			break;
		default:
			printf("\n Opção Inválida \n");
			system("pause");
			menuExtrato(pessoa);
	}


}//Fim Metodo

void deposito(TPessoa pessoa) {
	TUltimosDepositos auxDeposito;//Para reposicionar array quando tiver cheio
	TUltimosDepositos ultimoDeposito;
	TPessoa aux;
	long numConta;
	float valor;
	float valorAux = 0;
	int pegou = 0;
	int posicao = 0;

	system("cls");

	printf("\n Digite O Valor A Ser Depositado : ");
	fflush(stdin);
	scanf("%f", &valor);

	if (valor <= 0) {
		printf("\n O Valor Tem Que Ser Maior que zero \n");
		system("pause");
		deposito(pessoa);


	} else {

		file = abreArquivo('f');

		fseek(file,posicao,SEEK_SET);

		while( fread(&aux,sizeof(TPessoa),1,file) == 1) {

			if (aux.conta.numeroConta == pessoa.conta.numeroConta) {
				valorAux = aux.conta.saldo + valor;

				aux.conta.saldo = valorAux;

				pessoa.conta.saldo = valorAux;

				struct tm *local;
				time_t t;

				t= time(NULL);//Iniciando A Váriavel
				local=localtime(&t);

				ultimoDeposito.valor = valor;
				ultimoDeposito.dia = local->tm_mday;
				ultimoDeposito.mes = local->tm_mon + 1;
				ultimoDeposito.ano = local->tm_year + 1900;
				ultimoDeposito.hora = local->tm_hour;
				ultimoDeposito.minuto = local->tm_min;
				ultimoDeposito.segundo = local->tm_sec;
				ultimoDeposito.estaIniciado = 1;

				int f;
				for (f = 0; f < tamanhoArrayExtrato; f++) {

					if ( f == (tamanhoArrayExtrato - 1)) {

						int k;
						for (k = 0 ; k < tamanhoArrayExtrato; k++) {
							if (k == (tamanhoArrayExtrato -1) ) {
								aux.conta.ultimosDepositos[k] = ultimoDeposito;
							} else {

								auxDeposito = aux.conta.ultimosDepositos[k + 1];
								aux.conta.ultimosDepositos[k] = auxDeposito;

							}
						}

						break;
					} else {

						if (aux.conta.ultimosDepositos[f].estaIniciado == 0) {
							aux.conta.ultimosDepositos[f] = ultimoDeposito;
							break;
						}

					}

				}


				fseek(file,posicao, SEEK_SET);

				fwrite(&aux,sizeof(TPessoa),1,file);

				pegou = 1;
				break;
			}

			posicao = posicao + sizeof(TPessoa);

		}

		fecharArquivo(file);


		if (pegou == 1) {

			printf("\nDeposito Realizado Com Sucesso \n");
			printf("\n Seu novo Saldo é : %.2f \n", pessoa.conta.saldo);
			system("pause");
			menuDeAcesso(pessoa);

		} else {

			printf("\n Conta Não Tá Cadastrada No Sistema \n");
			system("pause");
			menuDeAcesso(pessoa);

		}

	}

}//Fim Metodo

void depositoAnonimo() {
	TPessoa aux;
	long numConta;
	float valor;
	float valorAux = 0;
	int pegou = 0;
	int posicao = 0;

	system("cls");

	printf("\n Digite O Valor A Ser Depositado : ");
	fflush(stdin);
	scanf("%f", &valor);

	if (valor <= 0) {
		printf("\n O Valor Tem Que Ser Maior que zero \n");
		system("pause");
		depositoAnonimo();


	} else {


		printf("\n Digite O Número Da Conta A Ser Depositada: ");
		fflush(stdin);
		scanf("%i", &numConta);

		file = abreArquivo('f');


		fseek(file,posicao,SEEK_SET);

		while( fread(&aux,sizeof(TPessoa),1,file) == 1) {

			if (aux.conta.numeroConta == numConta) {
				valorAux = aux.conta.saldo + valor;

				aux.conta.saldo = valorAux;


				fseek(file,posicao, SEEK_SET);
				fwrite(&aux,sizeof(TPessoa),1,file);

				pegou = 1;
				break;
			}

			posicao = posicao + sizeof(TPessoa);

		}




		fecharArquivo(file);


		if (pegou == 1) {
			printf("\nDeposito Realizado Com Sucesso \n");
			system("pause");
			acessarSistema();

		} else {

			printf("\n Conta Não Tá Cadastrada No Sistema \n");
			system("pause");
			acessarSistema();

		}

	}

}//Fim Metodo

void transferencia(TPessoa pessoa) {
	TUltimasTransferencias ultimaTransferencia;
	char nomeQuemRecebeu[70]; //Para Guardar O Nome de quem recebeu
	TPessoa aux;
	system("cls");
	float valor;
	long numConta;
	long senha;
	int pegou = 0;
	int posicaoPrimeiro = 0; //Primeira pessoa a ter os campos alterados
	int posicaoSegundo = 0; //Segunda Pessoa a ter os campos alterados

	printf("\n Digite O Valor A Ser Transferindo : ");
	scanf("%f",&valor);

	if (valor <= 0) {
		printf("\n Valor Tem Que Ser Maior Que Zero \n");
		system("pause");
		transferencia(pessoa);
	} else {

		printf("\n Digite A Conta Onde O Valor Será Transferido: ");
		scanf("%i", &numConta);

		if (numConta == pessoa.conta.numeroConta) {
			printf("\n Não Pode Ser A Mesma Conta \n");
			system("pause");
			menuDeAcesso(pessoa);
		} else {

			printf("\n Digite A Senha: ");
			scanf("%i", &senha);

			if (pessoa.conta.senha == senha) {
				system("cls");
				if (pessoa.conta.saldo >= valor) {

					file = abreArquivo('f');


					fseek(file,posicaoPrimeiro,SEEK_SET);

					while( fread(&aux,sizeof(TPessoa),1,file) == 1) {

						if (aux.conta.numeroConta == numConta) {


							aux.conta.saldo = aux.conta.saldo + valor;

							strcpy(nomeQuemRecebeu, aux.nome);

							fseek(file,posicaoPrimeiro,SEEK_SET);

							fwrite(&aux,sizeof(TPessoa),1,file);

							pegou = 1;
							break;
						}
						posicaoPrimeiro = posicaoPrimeiro + sizeof(TPessoa);
					}

					fecharArquivo(file);

					if (pegou == 1) { //Atualizando o objeto atual

						file = abreArquivo('f');


						fseek(file,posicaoSegundo,SEEK_SET);

						while( fread(&aux,sizeof(TPessoa),1,file) == 1) {

							if (aux.conta.numeroConta == pessoa.conta.numeroConta) {


								aux.conta.saldo = aux.conta.saldo - valor;

								pessoa.conta.saldo = pessoa.conta.saldo - valor;

								struct tm *local;
								time_t t;

								t= time(NULL);//Iniciando A Váriavel
								local=localtime(&t);

								ultimaTransferencia.valor = valor;
								strcpy(ultimaTransferencia.nomePessoaRecebeu,nomeQuemRecebeu);
								ultimaTransferencia.dia = local->tm_mday;
								ultimaTransferencia.mes = local->tm_mon + 1;
								ultimaTransferencia.ano = local->tm_year + 1900;
								ultimaTransferencia.hora = local->tm_hour;
								ultimaTransferencia.minuto = local->tm_min;
								ultimaTransferencia.segundo = local->tm_sec;
								ultimaTransferencia.estaIniciado = 1;

								int f;
								for (f = 0; f < tamanhoArrayExtrato; f++) {

									if ( f == (tamanhoArrayExtrato - 1)) {

										aux.conta.ultimasTransferencias[4]= ultimaTransferencia;
										break;
									} else {

										if (aux.conta.ultimasTransferencias[f].estaIniciado == 0) {
											aux.conta.ultimasTransferencias[f] = ultimaTransferencia;
											break;
										}

									}

								}


								fseek(file,posicaoSegundo,SEEK_SET);

								fwrite(&aux,sizeof(TPessoa),1,file);

								break;
							}
							posicaoSegundo = posicaoSegundo + sizeof(TPessoa);
						}

						fecharArquivo(file);

						printf ("\n Transferência realizada com sucesso !! \n");
						printf ("Seu Saldo Atual é : %.2f\n", pessoa.conta.saldo);
						system("pause");
						menuDeAcesso(pessoa);

					} else {
						printf("\n Conta não está cadastrada no sistema !!! \n");
						system("pause");
						menuDeAcesso(pessoa);
					}

				} else {

					printf("\n Saldo Insuficiente \n");
					printf("Seu Saldo é %.2f \n",pessoa.conta.saldo);
					system("pause");
					menuDeAcesso(pessoa);

				}





			} else {
				printf("\n Senha Incorreta!! \n");
				system("pause");
				menuDeAcesso(pessoa);
			}


		}

	}


}//Fim Metodo


void extratoDepositos(TPessoa pessoa) {
	TUltimosDepositos ultimoDeposito;
	TPessoa pessoaAux;
	file = abreArquivo('r');
	system("cls");

	printf("\n================== ÚLTIMOS DEPOSITOS ====================\n");

	while( fread(&pessoaAux,sizeof(TPessoa),1,file) == 1) {

		if (pessoaAux.conta.numeroConta == pessoa.conta.numeroConta) {

			int i;
			for (i = tamanhoArrayExtrato -1 ; i >= 0; i-- ) {

				ultimoDeposito = pessoaAux.conta.ultimosDepositos[i];

				if (ultimoDeposito.estaIniciado > 0) {
					printf ("\n Valor : %.2f    Data : %d/%d/%d    Hora : %d:%d:%d",ultimoDeposito.valor,ultimoDeposito.dia,ultimoDeposito.mes,ultimoDeposito.ano,ultimoDeposito.hora,ultimoDeposito.minuto,ultimoDeposito.segundo);

				}

			}


		}

	}

	printf("\n\n========================================================\n");
	fecharArquivo(file);

	system("pause");
	menuExtrato(pessoa);

}//Fim Método

void extratoSaques(TPessoa pessoa) {
	TUltimosSaques ultimoSaque;
	TPessoa pessoaAux;
	file = abreArquivo('r');
	system("cls");

	printf("\n================== ÚLTIMOS SAQUES ====================\n");

	while( fread(&pessoaAux,sizeof(TPessoa),1,file) == 1) {

		if (pessoaAux.conta.numeroConta == pessoa.conta.numeroConta) {

			int i;
			for (i = tamanhoArrayExtrato -1 ; i >= 0; i-- ) {

				ultimoSaque = pessoaAux.conta.ultimosSaques[i];

				if (ultimoSaque.estaIniciado > 0) {
					printf ("\n Valor : %.2f    Data : %d/%d/%d    Hora : %d:%d:%d",ultimoSaque.valor,ultimoSaque.dia,ultimoSaque.mes,ultimoSaque.ano,ultimoSaque.hora,ultimoSaque.minuto,ultimoSaque.segundo);
				}

			}


		}

	}

	printf("\n\n========================================================\n");
	fecharArquivo(file);

	system("pause");
	menuExtrato(pessoa);

}//Fim Método

void extratoTransferencias(TPessoa pessoa) {
	TUltimasTransferencias ultimasTransferencias;
	TPessoa pessoaAux;
	file = abreArquivo('r');
	system("cls");

	printf("\n================== ÚLTIMAS TRANSFERÊNCIAS ====================\n");

	while( fread(&pessoaAux,sizeof(TPessoa),1,file) == 1) {

		if (pessoaAux.conta.numeroConta == pessoa.conta.numeroConta) {

			int i;
			for (i = tamanhoArrayExtrato -1 ; i >= 0; i-- ) {

				ultimasTransferencias = pessoaAux.conta.ultimasTransferencias[i];

				if (ultimasTransferencias.estaIniciado > 0) {
					printf ("\n Valor : %.2f Para : %s   Data : %d/%d/%d    Hora : %d:%d:%d",ultimasTransferencias.valor,ultimasTransferencias.nomePessoaRecebeu,ultimasTransferencias.dia,ultimasTransferencias.mes,ultimasTransferencias.ano,ultimasTransferencias.hora,ultimasTransferencias.minuto,ultimasTransferencias.segundo);
				}

			}


		}

	}

	printf("\n\n========================================================\n");
	fecharArquivo(file);
	system("pause");
	menuExtrato(pessoa);

}//Fim Método

void verInformacoesConta(TPessoa pessoa) {
	system("cls");

	printf("\n==============================");
	printf("\n Número da conta : %i",pessoa.conta.numeroConta);
	printf("\n Agência : %i", pessoa.conta.agencia);
	printf("\n Operador : %i", pessoa.conta.operacao);
	printf("\n================================\n");
	system("pause");
	menuMais(pessoa);

}//Fim Método

//Helpers

FILE* abreArquivo(char modo) {
	FILE *arquivo;
	char caminho [30] = "dados.txt";
	switch (modo) {

		case 'w'://Escrever
			arquivo = fopen(caminho,"wb");
			break;
		case 'r'://Ler
			arquivo = fopen(caminho,"rb");
			break;
		case 'a'://Append
			arquivo = fopen(caminho,"ab");
			break;
		case 'f':
			arquivo = fopen(caminho, "r+b");
			break;
		default:
			arquivo = NULL;
			break;

	}

	if (arquivo == NULL) {
		system("cls");
		printf("\n Não foi possível abrir o arquivo, tente novamente \n");
		system("pause");
		acessarSistema();
	}

	return arquivo;

}

void fecharArquivo(FILE *arquivo) {
	fclose(arquivo);
}


