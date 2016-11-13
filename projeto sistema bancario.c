#define _WIN32_WINNT 0x0601

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

/*Declaração de structs*/

typedef struct SUltimosSaques {
	
	float valor;
	int dia,mes,ano,hora,minuto,segundo; //Para Guardar a data, guardo cada valor em cada variável
	int estaIniciado;

} TUltimosSaques;	

typedef struct SUltimosDepositos {
	
	float valor;
	int dia,mes,ano,hora,minuto,segundo; //Para Guardar a data, guardo cada valor em cada variável
	int estaIniciado;
	
} TUltimosDepositos;

typedef struct STransferencias {
	
	float valor;
	int dia,mes,ano,hora,minuto,segundo; //Para Guardar a data, guardo cada valor em cada variável
	char nomePessoaRecebeu[70];
	int estaIniciado; 
	
} TUltimasTransferencias;

typedef struct Sconta{
	
    int agencia;
    int operacao;
    long numeroConta;
    long senha;
    float saldo;
    TUltimosSaques ultimosSaques[5];
    TUltimosDepositos ultimosDepositos[5];
    TUltimasTransferencias ultimasTransferencias[5];

} TConta;

typedef struct SPessoa{
    char nome[70];
    char cpf[15];
    char sexo[12];
    int idade;
    TConta conta;

} TPessoa;

/* Fim Declaração Structs */

//Declaração de váriaveis globais

TPessoa pessoas[2];
FILE *file;
int contador = 0;
TPessoa pessoaLogada;

int tamanhoArrayExtrato = 5;

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


/* Fim Declaração Funções */

//Main
int main(){
	

		
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


system("title SIMULADOR BANCO");
system("color 8f");
setlocale(LC_ALL, "Portuguese");
acessarSistema();

}
//Fim Main

//Implementação de Funções

//Função De Acesso Ao Sistema
void acessarSistema(){
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
switch(opc)
{
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
void loginSistema(){
    int numeroConta;
    int usuarioValido = 0;
    int numeroTentativas = 5;
     system("cls");
    system("color 3f");
    //Pegar Arquivo E Jogar Em Array
    int j;
    for (j = 0; j < numeroTentativas ; j++){
    printf("\n\n Número de tentativas: %i, Resta:  %i \n\n",(j),numeroTentativas - (j));
    printf("\n\nDigite Número Da Conta(só números): ");
    fflush(stdin);
    scanf("%i",&numeroConta);

    if (numeroConta != 0){

        int i;
        for (i = 0;i < 2 ; i++){

            if (pessoas[i].conta.numeroConta == numeroConta){
                pessoaLogada = pessoas[i];
                usuarioValido = 1;
            }

        }

        if (usuarioValido == 1){

        menuDeAcesso(pessoaLogada);


        }else {

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

    printf("\nQuantidade de tentativas Esgotadas, Tente Novamente Ou Faça O Cadastro \n");
    system("pause");
    acessarSistema();


}


//Função de Menu Com Opções do sistema
void menuDeAcesso(TPessoa pessoa){
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
switch(opc)
{
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

void menuMais(TPessoa pessoa){
system("color 3f");
system("cls");
int opc;
printf("\n---------------------------------------------------\n\n");
printf("1- Ver Informações Do Usuário");
printf("\n2- Editar Informações Do Usuário");
printf("\n3- Voltar ");
printf("\n\nDigite uma opção: ");
fflush(stdin);
scanf("%i",&opc);
switch(opc)
{
    case 1:
        verInformacoes(pessoa);
        break;
    case 2:
        editarUsuario(pessoa);
        break;
    case 3:
        menuDeAcesso(pessoa);
        break;
    default :
        printf("\n Opção Inválida, Digite uma das opções disponíveis\n");
    system("pause");
    menuMais(pessoa);
    break;
}

}//Fim Metodo

void sair(){

system("cls");
printf("\n\t\n Saindo Do Sistema\n");
printf("\n\t Até Breve \n\n");
exit(0);
system("pause");

}//Fim Metodo



void cadastrarUsuario(){

TPessoa pessoa;

system("cls");

if (contador < 2 ){


do {
printf("\n\n Digite O Nome Do Usuário : ");
fflush(stdin);
gets(pessoa.nome);

if (strlen(pessoa.nome) != 0){


}else {
    printf("\n Digite Algo Para Nome \n");
    system("pause");
    system("cls");
}

}while (strlen(pessoa.nome) == 0);


do {

printf("\n\n Digite O Número Do Cpf : ");
fflush(stdin);
gets(pessoa.cpf);

if (strlen(pessoa.cpf) != 0){

    if (strlen(pessoa.cpf) == 14){

    }else {
        printf("\n Digite apenas 14 digitos \n");
        system("pause");
        system("cls");
    }

}else {
    printf("\n Digite algo Para O CPF !! \n");
    system("pause");
    system("cls");



}

}while(strlen(pessoa.cpf) < 14);


printf("\n\n Escolha O Sexo M / F : ");
fflush(stdin);
gets(pessoa.sexo);

printf("\n\n Digite Sua Idade : ");
fflush(stdin);
scanf("%d",&pessoa.idade);


printf("\n\n Digite A Agencia : ");
fflush(stdin);
scanf("%d", &pessoa.conta.agencia);


printf("\n\n Digite A Operacao : ");
fflush(stdin);
scanf("%d", &pessoa.conta.operacao);


printf("\n\n Digite o número da conta : ");
fflush(stdin);
scanf("%d",&pessoa.conta.numeroConta);


printf("\n\n Digite A Senha : ");
fflush(stdin);
scanf("%i", &pessoa.conta.senha);

pessoa.conta.saldo = 100.0;

printf("\nUsuário Cadastrado com sucesso, Você já pode acessar o sistema\n");
pessoas[contador] = pessoa;
contador++;
}
system("pause");
acessarSistema();

} //Fim Metodo

void editarUsuario(TPessoa pessoa){
    int opcao;
    long senha;
    char cpfAux[15];
    char novoNome[70];
    char novoCpf[15];
    char novoSexo[1];
    int novaIdade;
    long novaSenha;



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

    switch(opcao){

    case 1:

        system("cls");

        printf("\nDigite Um Novo Nome : ");
        fflush(stdin);
        gets(novoNome);

        printf("\n Digite A Senha Para Confirmar : ");
        fflush(stdin);
        scanf("%i",&senha);

        if (pessoa.conta.senha == senha){

            int i;
            for (i = 0; i < 2 ; i++){

                if (pessoa.conta.senha == pessoas[i].conta.senha){
                    strcpy(pessoa.nome, novoNome);
                    strcpy(pessoas[i].nome, novoNome);
                    printf("\n Nome Atualizado \n");
                    printf("Novo Nome é: %s \n",pessoas[i].nome);
                    system("pause");
                    editarUsuario(pessoa);

                }

            }

        }else {
            printf("\n Senha Incorreta, Tente Novamente \n");
            system("pause");
            editarUsuario(pessoa);

        }

        break;

    case 2:

        system("cls");

        printf("\nDigite novo CPF : ");
        fflush(stdin);
        gets(novoCpf);

        printf("\n Digite A Senha Para Confirmar : ");
        fflush(stdin);
        scanf("%i",&senha);

        if (pessoa.conta.senha == senha){

            int i;
            for (i = 0; i < 2 ; i++){

                if (pessoa.conta.senha == pessoas[i].conta.senha){
                    strcpy(pessoa.cpf, novoCpf);
                    strcpy(pessoas[i].cpf, novoCpf);
                    printf("\n CPF Atualizado \n");
                    printf("Novo CPF é: %s \n",pessoas[i].cpf);
                    system("pause");
                    editarUsuario(pessoa);

                }

            }

        }else {
            printf("\n Senha Incorreta, Tente Novamente \n");
            system("pause");
            editarUsuario(pessoa);

        }

        break;

    case 3:

        system("cls");

        printf("\n Escolha O Sexo M / F : ");
        fflush(stdin);
        gets(novoSexo);

        printf("\n Digite A Senha Para Confirmar : ");
        fflush(stdin);
        scanf("%i",&senha);

        if (pessoa.conta.senha == senha){

            int i;
            for (i = 0; i < 2 ; i++){

                if (pessoa.conta.senha == pessoas[i].conta.senha){
                    strcpy(pessoa.sexo, novoSexo);
                    strcpy(pessoas[i].sexo, novoSexo);
                    printf("\n Sexo Atualizado \n");
                    system("pause");
                    editarUsuario(pessoa);

                }

            }

        }else {
            printf("\n Senha Incorreta, Tente Novamente \n");
            system("pause");
            editarUsuario(pessoa);

        }

        break;

    case 4:

        system("cls");

        printf("\n Digite A Nova Idade : ");
        fflush(stdin);
        scanf("%d",&novaIdade);

        printf("\n Digite A Senha Para Confirmar : ");
        fflush(stdin);
        scanf("%i",&senha);

        if (pessoa.conta.senha == senha){

            int i;
            for (i = 0; i < 2 ; i++){

                if (pessoa.conta.senha == pessoas[i].conta.senha){
                    pessoa.idade = novaIdade;
                    pessoas[i].idade = novaIdade;
                    printf("\n Idade Atualizada \n");
                    printf("Nova Idade é: %i \n",pessoas[i].idade);
                    system("pause");
                    editarUsuario(pessoa);

                }

            }

        }else {
            printf("\n Senha Incorreta, Tente Novamente \n");
            system("pause");
            editarUsuario(pessoa);

        }

        break;


    case 5:

        system("cls");
        printf("\nDigite Sua Senha Nova : ");
        fflush(stdin);
        scanf("%i", &novaSenha);

        printf("Digite Seu CPF para Confimar : ");
        fflush(stdin);
        gets(cpfAux);
        printf(cpfAux);
        printf(pessoa.cpf);

        if (strcmp(pessoa.cpf , cpfAux) == 0 ) {

               int i;
               for (i = 0; i < 2 ; i++){

                    if (pessoa.conta.numeroConta == pessoas[i].conta.numeroConta){
                        pessoa.conta.senha = novaSenha;
                        pessoas[i].conta.senha = novaSenha;

                        printf("\nSenha Atualizada Com Sucesso !\n");
                        system("pause");
                        editarUsuario(pessoa);
                    }

               }

        }else {

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

void verInformacoes(TPessoa pessoa){

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

void versaldo(TPessoa pessoa){

 int senha;

 system("cls");
 printf("\nDigite Sua Senha : ");
 scanf("%i",&senha);

 if (pessoa.conta.senha == senha){

    int i;
    for (i = 0;i < 2 ; i++)
    {
        if (pessoas[i].conta.senha == pessoa.conta.senha){

            printf("\n Seu Saldo é :  R$ %.2f\n",pessoas[i].conta.saldo);
            system("Pause");
            menuDeAcesso(pessoa);

        }

    }


 }else{

     printf("\nSenha Incorreta !!\n");
     system("pause");
     menuDeAcesso(pessoa);

 }

}//Fim Metodo


void saque(TPessoa pessoa){
	
TUltimosSaques ultimosSaque;

float valor;
int senha;

system("cls");
 printf("\nDigite O Valor A Ser Sacado : ");
 scanf("%f",&valor);

 if (valor <= 0 ){
    printf("\n O Valor Tem Que Ser Maior Que Zero \n");
    system("pause");
    saque(pessoa);
 }


 printf("\nDigite Sua Senha : ");
 scanf("%i",&senha);

 if (pessoa.conta.senha == senha){

    int i;
    for (i = 0; i <2; i++)
    {
        if (pessoa.conta.senha == pessoas[i].conta.senha){

                if (pessoas[i].conta.saldo > valor){

        printf("\nValor Sacado Com Sucesso\n");
        float valorNovo = pessoas[i].conta.saldo - valor;
        pessoas[i].conta.saldo = valorNovo;
        
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
		
		pessoas[i].conta.ultimosSaques[0] = ultimosSaque;

        printf("\nSeu Novo Saldo é :  R$ %.2f \n",pessoas[i].conta.saldo);
        system("pause");
        menuDeAcesso(pessoa);

    }else {

    printf("\n Saldo insuficiente para realizar o saque\n");
    printf("Seu Saldo é : R$ %.2f \n",pessoas[i].conta.saldo);
    system("pause");
    menuDeAcesso(pessoa);

    }

        }
    }



 }else{

     printf("\nSenha Incorreta !!\n");
     system("pause");
     menuDeAcesso(pessoa);

 }

}//Fim Metodo


void menuExtrato (TPessoa pessoa){
	int opcao;
	
	system("cls");
	
	printf("\n\n 1 - Últimos Depositos ");
	printf ("\n 2 - Últimos Saques ");
	printf("\n 3 - Últimas Transferências ");
	printf("\n 4 - Voltar");
	printf("\n Digite sua opção : ");
	fflush(stdin);
	scanf("%i",&opcao);
	
	switch(opcao){
		
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

void deposito(TPessoa pessoa){
TUltimosDepositos ultimoDeposito;
long numConta;
float valor;
float valorAux = 0;
int pegou = 0;

system("cls");

printf("\n Digite O Valor A Ser Depositado : ");
fflush(stdin);
scanf("%f", &valor);

if (valor <= 0){
    printf("\n O Valor Tem Que Ser Maior que zero \n");
    system("pause");
    deposito(pessoa);


}else {


int i;
for (i = 0;i < 2; i++){
    if (pessoas[i].conta.numeroConta == pessoa.conta.numeroConta){

        valorAux = pessoas[i].conta.saldo + valor;

        pessoas[i].conta.saldo = valorAux;
        
        pessoa.conta.saldo = valorAux ; 

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
		
		int j;
		for (j = 0;j < tamanhoArrayExtrato; j++){
			
			if(pessoas[i].conta.ultimosDepositos[j].estaIniciado == 0){
				pessoas[i].conta.ultimosDepositos[j] = ultimoDeposito;	
				break;	
			}
			
		}
		
        pegou = 1;
        break;
    }
}

if (pegou == 1){
    printf("\nDeposito Realizado Com Sucesso \n");
    printf("\n Seu novo Saldo é : %.2f \n", pessoa.conta.saldo);
    system("pause");
    menuDeAcesso(pessoa);

}else{

printf("\n Conta Não Tá Cadastrada No Sistema \n");
system("pause");
menuDeAcesso(pessoa);

}

}

}//Fim Metodo

void depositoAnonimo(){
	
long numConta;
float valor;
float valorAux = 0;
int pegou = 0;

system("cls");

printf("\n Digite O Valor A Ser Depositado : ");
fflush(stdin);
scanf("%f", &valor);

if (valor <= 0){
    printf("\n O Valor Tem Que Ser Maior que zero \n");
    system("pause");
    depositoAnonimo();


}else {

printf("\n Digite O Número Da Conta A Ser Depositada: ");
fflush(stdin);
scanf("%i", &numConta);
int i;
for (i = 0;i < 2; i++){
    if (pessoas[i].conta.numeroConta == numConta){

        valorAux = pessoas[i].conta.saldo + valor;


        pessoas[i].conta.saldo = valorAux;

        pegou = 1;
        break;
    }
}

if (pegou == 1){
    printf("\nDeposito Realizado Com Sucesso \n");
    system("pause");
    acessarSistema();

}else{

printf("\n Conta Não Tá Cadastrada No Sistema \n");
system("pause");
acessarSistema();

}
	
}

}//Fim Metodo

void transferencia(TPessoa pessoa){
TUltimasTransferencias ultimaTransferencia;

system("cls");
float valor;
long numConta;
long senha;
int pegou = 0;

printf("\n Digite O Valor A Ser Transferindo : ");
scanf("%f",&valor);

if (valor <= 0) {
    printf("\n Valor Tem Que Ser Maior Que Zero \n");
    system("pause");
    transferencia(pessoa);
}else {

printf("\n Digite A Conta Onde O Valor Será Transferido: ");
scanf("%i", &numConta);

if (numConta == pessoa.conta.numeroConta){
    printf("\n Não Pode Ser A Mesma Conta \n");
    system("pause");
    menuDeAcesso(pessoa);
}else {

    printf("\n Digite A Senha: ");
    scanf("%i", &senha);

    if (pessoa.conta.senha == senha){
        system("cls");
        int i;
        for (i = 0;i < 2; i++){

            if (pessoas[i].conta.senha == pessoa.conta.senha){

                if (pessoas[i].conta.saldo > valor){

                    int j;
                    for (j = 0;j < 2 ; j++){

                        if (pessoas[j].conta.numeroConta == numConta){

                           	pessoas[i].conta.saldo = pessoas[i].conta.saldo - valor;
                           	pessoas[j].conta.saldo = pessoas[j].conta.saldo + valor;
                           
                           	struct tm *local;
							time_t t;
		
							t= time(NULL);//Iniciando A Váriavel
							local=localtime(&t);
                           
	                        ultimaTransferencia.valor = valor;
	        				ultimaTransferencia.dia = local->tm_mday; 
							ultimaTransferencia.mes = local->tm_mon + 1;
			                ultimaTransferencia.ano = local->tm_year + 1900;
			                ultimaTransferencia.hora = local->tm_hour;
			                ultimaTransferencia.minuto = local->tm_min;
			                ultimaTransferencia.segundo = local->tm_sec;
			                strcpy(ultimaTransferencia.nomePessoaRecebeu , pessoas[j].nome);
							   
						   	pessoas[i].conta.ultimasTransferencias[0] = ultimaTransferencia;

                           pegou = 1;
						   break;
                        }

                    }

                    if (pegou == 1){
                          printf("\n A transferência foi realizada com sucesso \n");
                               system("pause");
                               menuDeAcesso(pessoa);
                    }else {

                        printf("\n Não Existe Essa Conta Cadastrada !! \n");
                        system("pause");
                        menuDeAcesso(pessoa);
                    }

                }else {

                    printf("\n Saldo Insuficiente \n");
                    printf("Seu Saldo é %.2f \n",pessoas[i].conta.saldo);
                    system("pause");
                    menuDeAcesso(pessoa);

                }

            }

        }

    }else {
        printf("\n Senha Incorreta!! \n");
        system("pause");
        menuDeAcesso(pessoa);
    }


}

}


}//Fim Metodo


void extratoDepositos(TPessoa pessoa){
	TUltimosDepositos aux;
	

	system("cls");
	
	printf("\n================== ÚLTIMOS DEPOSITOS ====================\n");
	
	int i;
	for (i = 0 ; i  < 2 ; i++){
		
		if (pessoas[i].conta.numeroConta == pessoa.conta.numeroConta){
			
			int j;
			for (j = 0; j < tamanhoArrayExtrato ; j++) {
				aux = pessoas[i].conta.ultimosDepositos[j];
							
				if (pessoas[i].conta.ultimosDepositos[j].estaIniciado != 0){
				
					printf ("\n Valor : %.2f  Data : %d/%d/%d    Hora : %d:%d:%d  teste : %i",aux.valor,aux.dia,aux.mes,aux.ano,aux.hora,aux.minuto,aux.segundo,aux.estaIniciado);
					
				}
			
			}				
	
			break;
		}
		
	}
	
	printf("\n\n========================================================\n");
	
	system("pause");
	menuExtrato(pessoa);
	
}//Fim Método

void extratoSaques(TPessoa pessoa){
	TUltimosSaques aux;
	

	system("cls");
	
	printf("\n================== ÚLTIMOS SAQUES ====================\n");
	
	int i;
	for (i = 0 ; i  < 2 ; i++){
		
		if (pessoas[i].conta.numeroConta == pessoa.conta.numeroConta){
			
			int j;
			
			for (j = 0; j < tamanhoArrayExtrato ; j++) {
				aux = pessoas[i].conta.ultimosSaques[j];
				
				
				
				if (aux.estaIniciado != 0 ){
				
				
				printf ("\n Valor : %.2f    Data : %d/%d/%d    Hora : %d:%d:%d",aux.valor,aux.dia,aux.mes,aux.ano,aux.hora,aux.minuto,aux.segundo);
				
				}
			
			}				
				
				
			break;
		}
		
	}
	
	printf("\n\n========================================================\n");
	
	system("pause");
	menuExtrato(pessoa);
	
}//Fim Método

void extratoTransferencias(TPessoa pessoa){
	TUltimasTransferencias aux;

	system("cls");
	
	printf("\n================== ÚLTIMAS TRANSFERÊNCIAS ====================\n");
	
	int i;
	for (i = 0 ; i  < 2 ; i++){
		
		if (pessoas[i].conta.numeroConta == pessoa.conta.numeroConta){
			
			int j;
			
			for (j = 0; j < tamanhoArrayExtrato ; j++) {
				aux = pessoas[i].conta.ultimasTransferencias[j];
				
				
				
				if ( aux.estaIniciado != 0 ){
				
				
				printf ("\n Valor : %.2f para: %s   Data : %d/%d/%d    Hora : %d:%d:%d",aux.valor,aux.nomePessoaRecebeu,aux.dia,aux.mes,aux.ano,aux.hora,aux.minuto,aux.segundo);
				
				}
			
			}				
				
				
			break;
		}
		
	}
	
	printf("\n\n======================================================\n");
	
	system("pause");
	menuExtrato(pessoa);
	
}//Fim Método





