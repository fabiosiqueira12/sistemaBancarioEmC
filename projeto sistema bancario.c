#define _WIN32_WINNT 0x0601

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

/*Declaração de structs*/

typedef struct Sconta{
    int agencia;
    int operacao;
    long numeroConta;
    long senha;
    double saldo;
    double ultimosSaques[5];
    double ultimosDepositos[5];
    double ultimasTransferencias[5];

} TConta;

typedef struct SPessoa{
    char nome[70];
    char cpf[15];
    char sexo[1];
    int idade;
    TConta conta;

} TPessoa;
/* Fim Declaração Structs */

//Declaração de váriaveis globais
int numeroConta;
TPessoa pessoas[2];
FILE *file;
int contador = 0;
TPessoa pessoaLogada;
/* Fim Declaração váriaveis globais */



/* Declaração das Funções*/
/* Funções para gerar menus */

void acessarSistema();
void sair();
void menuDeAcesso(TPessoa pessoa);
void loginSistema();
//Função de CRUD

void cadastrarUsuario();
void editarUsuario(TPessoa pessoa);

//Funções Do Caixa

void versaldo(TPessoa pessoa);
void saque(TPessoa pessoa);
void extrato (TPessoa pessoa);
void deposito (TPessoa pessoa);
void transferencia(TPessoa pessoa);

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
printf("\n3- Sair ");
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

    printf("\nQuantidade de tentativas Esgotadas, Tente fazer o cadastro \n");
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
printf("\n6- Editar Informações");
printf("\n7- Sair Do Sistema\n");
printf("\n\nDigite uma opção: ");
fflush(stdin);
scanf("%i",&opc);
switch(opc)
{
    case 1:
        versaldo(pessoa);
        break;
    case 2:
        extrato(pessoa);
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
        editarUsuario( pessoa);
        break;

    case 7:
        sair();
        break;
    default:
        printf("Opção invalida!\n");
    system("pause");
    menuDeAcesso(pessoa);
    break;
}
}

void sair(){

system("cls");
printf("\n\t\n Saindo Do Sistema\n");
printf("\n\t Até Breve \n\n");
exit(0);
system("pause");

}



void cadastrarUsuario(){
TPessoa pessoa;

system("cls");

if (contador < 2 ){

printf("\n\n Digite O Nome Do Usuário : ");
fflush(stdin);
gets(pessoa.nome);

printf("\n\n Digite O Número Do Cpf : ");
fflush(stdin);
gets(pessoa.cpf);

printf("\n\n Escolha O Sexo M / F : ");
fflush(stdin);
scanf("%c",&pessoa.sexo);
if (pessoa.sexo != "m" || pessoa.sexo != "f"){
        printf("\n Opção Inválida Digite m ou f\n");
}

printf("\n\n Digite Sua Idade : ");
fflush(stdin);
scanf("%i",&pessoa.idade);

printf("\n\n Digite A Agencia : ");
fflush(stdin);
scanf("%i", &pessoa.conta.agencia);

printf("\n\n Digite A Operacao : ");
fflush(stdin);
scanf("%i", &pessoa.conta.operacao);

printf("\n\n Digite o número da conta : ");
fflush(stdin);
scanf("%i",&pessoa.conta.numeroConta);

printf("\n\n Digite A Senha : ");
fflush(stdin);
scanf("%i", &pessoa.conta.senha);

pessoa.conta.saldo = 100.0;

printf("%d",pessoa.conta.saldo);

printf("\nUsuário Cadastrado com sucesso, Você já pode acessar o sistema\n");
pessoas[contador] = pessoa;
contador++;
}
system("pause");
acessarSistema();

}

void editarUsuario(TPessoa pessoa){
    int opcao;

    system("cls");
    printf("\n\n\t\t\t Opcões De Edição \n");
    printf("\n1- Nome ");
    printf("\n2- CPF ");
    printf("\n3- Sexo  ");
    printf("\n4- Idade ");
    printf("\n5- Sair ");


    printf("\n\n Digite Uma Opção: ");
    fflush(stdin);

    scanf("%i", &opcao);

    switch(opcao){

    case 1:

        system("cls");
        system("pause");
        menuDeAcesso(pessoa);

        break;
    case 2:

        system("cls");
        system("pause");
        menuDeAcesso(pessoa);

        break;
    case 3:

        system("cls");
        system("pause");
        menuDeAcesso(pessoa);

        break;
    case 4:

        system("cls");
        system("pause");
        menuDeAcesso(pessoa);

        break;
    case 5:
        system("cls");
        menuDeAcesso(pessoa);
        break;
    default :
        printf("Opcão Inválida \n");
        system("pause");
        editarUsuario(pessoa);

    }



}

void versaldo(TPessoa pessoa){

 int senha;

 system("cls");
 printf("\nDigite Sua Senha : ");
 scanf("%i",&senha);

 if (pessoa.conta.senha == senha){
    printf("\n Seu Saldo é :  R$ %d\n",pessoa.conta.saldo);
    system("Pause");
    menuDeAcesso(pessoa);
 }else{

     printf("\nSenha Incorreta !!\n");
     system("pause");
     menuDeAcesso(pessoa);

 }

}


void saque(TPessoa pessoa){

double valor;
int senha;

system("cls");
 printf("\nDigite O Valor A Ser Sacado(casa de 10): ");
 scanf("%d",&valor);

 printf("\nDigite Sua Senha : ");
 scanf("%i",&senha);

 if (pessoa.conta.senha == senha){

    if (pessoa.conta.saldo > valor){

        printf("\nValor Sacado Com Sucesso\n");
        double valorNovo = pessoa.conta.saldo - valor;
        pessoa.conta.saldo = valorNovo;

        printf("\nSeu Novo Saldo é :  R$ %d \n",pessoa.conta.saldo);
        system("pause");
        menuDeAcesso(pessoa);

    }else {

    printf("\n Saldo insuficiente para realizar o saque\n");
    printf("Seu Saldo é : R$ %d \n",pessoa.conta.saldo);
    system("pause");
    menuDeAcesso(pessoa);

    }

 }else{

     printf("\nSenha Incorreta !!\n");
     system("pause");
     menuDeAcesso(pessoa);

 }

}


void extrato (TPessoa pessoa){

long senha;
int tamanhoUltimosSaques = sizeof(pessoa.conta.ultimosSaques) /sizeof(pessoa.conta.ultimosSaques[0]);
int tamanhoUltimasTransferencias = sizeof(pessoa.conta.ultimasTransferencias) /sizeof(pessoa.conta.ultimasTransferencias[0]);
int tamanhoUltimosDepositos  = sizeof(pessoa.conta.ultimosDepositos) /sizeof(pessoa.conta.ultimosDepositos[0]);


system("cls");
printf("\n Digite Sua Senha: ");
scanf("%i",&senha);

if (pessoa.conta.senha == senha){
    system("cls");
    printf("\n ----------------------------------- \n");
    if (tamanhoUltimosSaques != 0){
        printf("\n Últimos Saques \n");

        int i;
        for (i = 0; i < tamanhoUltimosSaques; i++){

        }

    }else {

        printf("\n Não Foi Feito Saques Ainda ");

    }

    printf("\n ----------------------------------- \n");
    if (tamanhoUltimasTransferencias != 0){
        printf("\n Últimas Transferências \n");

        int i;
        for (i = 0; i < tamanhoUltimasTransferencias; i++){

        }

    }else {

        printf("\n Não Foi Feito Transferências Ainda ");

    }

    printf("\n ----------------------------------- \n");
    if (tamanhoUltimosDepositos != 0){
        printf("\n Últimos Depositos \n");

        int i;
        for (i = 0; i < tamanhoUltimosDepositos; i++){

        }

    }else {

        printf("\n Não Foi Feito Depositos Ainda ");

    }
     printf("\n ----------------------------------- \n");
     system("pause");
     menuDeAcesso(pessoa);
}else{

    printf("\n Senha Incorreta \n");
    system("pause");
    menuDeAcesso(pessoa);

}


}

void deposito(TPessoa pessoa){
long numConta;
double valor;
int pegou = 0;

system("cls");

printf("\n Digite O Valor A Ser Depositado : ");
scanf("%d", valor);
printf("\n Digite O Número Da Conta A Ser Depositada: ");
scanf("%i", numConta);
int i;
for (i = 0;i < 2; i++){
    if (pessoas[i].conta.numeroConta == numConta){
        pessoas[i].conta.saldo = pessoas[i].conta.saldo + valor;
        pegou = 1;
    }
}

if (pegou == 1){
    printf("\nDeposito Realizado Com Sucesso \n");
    system("pause");
    menuDeAcesso(pessoa);

}else{

printf("\n Conta Não Tá Cadastrada No Sistema \n");
system("pause");
menuDeAcesso(pessoa);

}

}

void transferencia(TPessoa pessoa){
system("cls");
double valor;
long numConta;
long senha;
int pegou = 0;

printf("\n Digite O Valor A Ser Transferindo : ");
scanf("%d",&valor);
printf("\n Digite A Conta Onde O Valor Será Transferido: ");
scanf("%i", &numConta);

printf("\n Digite Sua Senha: ");
scanf("%i", &senha);

if (numConta == pessoa.conta.numeroConta){
    system("cls");
    printf("\n Conta Não Pode Ser Igual A Sua !!!\n");
    system("pause");
    menuDeAcesso(pessoa);
}else {

if (pessoa.conta.senha == senha ){

        if (pessoa.conta.saldo > valor){

            int i;
            for (i = 0; i < 2; i++){

                if (pessoas[i].conta.numeroConta == numConta){
                    double saldoFinal = pessoa.conta.saldo - valor;
                    pessoa.conta.saldo = saldoFinal;

                    pessoas[i].conta.saldo = pessoas[i].conta.saldo + valor;
                    pegou = 1;

                }

            }

            if (pegou == 1){
                printf("\n Transação Realizada Com Sucesso \n");
                system("pause");
                menuDeAcesso(pessoa);
            }else {
                printf("\n Número Da Conta Não foi Encontrada \n");
                system("pause");
                menuDeAcesso(pessoa);
            }

        }else {
            printf("\n Saldo Insuficiente Para Efetuar Ação \n");
            printf(" Seu Saldo é : R$ %d \n",pessoa.conta.saldo);
            system("pause");
            menuDeAcesso(pessoa);
        }

}else {
    printf("\n Senha Incorreta Tente Realizar Novamente \n");
    system("pause");
    menuDeAcesso(pessoa);
}

}

}



