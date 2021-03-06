#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Topicos.h"
#include "Usuario.h"
#include "GerenciaDisciplina.h"
#include "GerenciamentoQuiz.h"
#include "ListagemDeDisciplinas.h"
#include "Quiz.h"



void LerDadosLogin() {
	char user[20], password[20];
	system("clear");
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Tela de Login: %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("%%%%%%%%%%%%%% Usuario: ");
	scanf("%s", user);
	printf("%%%%%%%%%%%%%% Senha: ");
	scanf("%s", password);
	TelaLogin(user,password,"usuarios.txt",0);
}

/*Função responsável por apresentar a tela de Login ao cliente. Pede que seja inserido usuário e senha e
Informa se o Login foi realizado com sucesso. */
int TelaLogin(char *user, char *password, char *nomearquivo, int test) {
	FILE *fp;
	int loginfound = 0; /*Variavel para controle de login. So sera settada para "1" se o login 				    existir.*/
	char name[20] = "usrone", user_read[20] = "usrone", password_read[20] = "usrone";
	if(fopen(nomearquivo, "r") == NULL) {	/*Trata Possibilidade do Arquivo Nao Existir*/
		if(test == 1) {
			return loginfound;
		}
		printf("Nao existem usuarios cadastrados!\n");
		printf("Insira <ENTER> para retornar ao menu inicial.");
		getchar();
		getchar();
	}
	else {
		fp = fopen(nomearquivo, "r");
		while(fscanf(fp,("%s %s %s"), name, user_read, password_read) == 3) {
			if(strcmp(user_read,user) == 0 && strcmp(password_read,password) == 0) {
				loginfound = 1;
				if(test == 1) {
					return loginfound;
				}
				printf("Login Efetuado com Sucesso!\n");
				printf("Seja Bem-Vindo, %s\n", name);
				printf("Insira <ENTER> para ir para a entrada do sistema.\n");
				getchar();
				getchar();
				TelaEntradaSistema(user_read); /*Chama funcao que apresenta Tela 									de Entrada (Login Efetuado)*/
				break;
			}
		}
		if(loginfound == 0) { /*Informa falha de login*/
			if(test == 1) {
				return loginfound;
			}
			printf("Usuario e/ou Senha Incorretos.\n");
			printf("Insira <ENTER> para retornar ao menu inicial.");
			getchar();
			getchar();
			system("clear");
		}
		fclose(fp);
	}
	return 0;
}

/*Função responsável por checar se um nome de usuário já existe. Para isso, lê o arquivo e compara com o nome
inserido pelo usuário. Caso já exista um igual, retorna 1. Caso contrário, retorna 0.

Parametros da funcao: "username" - Nome do usuario que queremos checar existencia.
"nomearquivo" - Nome do arquivo no qual procuraremos o usuario inserido.*/

int ProcuraNomeUsuario(char *username, char *nomearquivo) {
	char user_read[20] = "usrone", name_read[20], password_read[20];
	FILE *fp;

	if(fopen(nomearquivo, "r") == NULL) {	/*Trata Possibilidade do Arquivo Nao Existir*/
		return 0;
	}
	else {
		fp = fopen(nomearquivo,"r");	/*Efetivamente procura pelo usuario no arquivo*/
		while(fscanf(fp,("%s %s %s"), name_read, user_read, password_read) == 3) {
			if(strcmp(user_read,username) == 0) {
				printf("Este usuario ja existe. Insira outro. \n");
				return 1;
			}
		}
		fclose(fp);
		return 0;
	}
}

/*Função responsável por realizar o cadastro de novos usuários. São solicitados a princípio: Nome, Usuário e Senha.
Checa se o usuario está disponível para uso. Se não estiver, o cadastro é realizado. Se estiver, então o cliente sera informado e devera optar por outro nome de usuário*/

void LerDadosCadastro() {
	char nome[20], login[20] = "usrone", senha[20], nomearquivo[20] = "usuarios.txt";
	int usuarioexiste = 1;
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Cadastro %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("%%%%%%%%%%%%%% Primeiro Nome: ");
	scanf("%s", nome);
	while(usuarioexiste == 1) {  /*Loop para Garantir a unicidade do usuario a ser cadastrado*/
		printf("%%%%%%%%%%%%%% Usuario: ");
		scanf("%s", login);
		usuarioexiste = ProcuraNomeUsuario(login,nomearquivo); /*Retorno 0 ou 1*/
	}
	printf("%%%%%%%%%%%%%% Senha: ");
	scanf("%s", senha);
	TelaCadastro(nome,login,senha, nomearquivo, 0);
}


int TelaCadastro(char *nome, char *login, char *senha, char *nomearquivo, int test) {
	FILE *fp;
	if(fopen(nomearquivo,"r") == NULL) { /*Caso ainda nao exista arquivo de usuarios*/
		if(test == 1) {
			return 1;
		}
		fp = fopen(nomearquivo, "w");
		fprintf(fp,"%s %s %s\n", nome, login, senha);
		printf("Cadastro realizado com sucesso.\n");
		printf("Insira <ENTER> para retornar ao menu inicial e fazer seu Login.\n");
		getchar();
		getchar();
		system("clear");
		fclose(fp);
	}
	else {	/* Caso ja exista, acrescenta ao final os dados do novo usuario */
		if(test == 1) {
			return 2;
		}
		fp = fopen(nomearquivo, "a");
		fprintf(fp,"%s %s %s\n", nome, login, senha);
		printf("Cadastro realizado com sucesso.\n");
		printf("Insira <ENTER> para retornar ao menu inicial e fazer seu Login.\n");
		getchar();
		getchar();
		system("clear");
		fclose(fp);
	}
	return 0;
}

/*Função responsável por procurar no arquivo de cadastros o usuario inserido. Para solicitar a senha é necessario
informar o nome e o usuario. Com ambas informações, é realizada uma busca no arquivo e, se existir algum cadastro
que possua o Nome e o Usuário informados, entao  essa senha e informada ao cliente.*/

void LerDadosRecuperarSenha() {
	char nome[20], usuario[20];
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Recuperacao de Senha %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("%%%%%%%%%%%%%% Insira seu primeiro nome: ");
	scanf("%s", nome);
	printf("%%%%%%%%%%%%%% Insira seu usuario: ");
	scanf("%s", usuario);
	TelaRecuperarSenha(nome,usuario,0);
}


int TelaRecuperarSenha(char *nome, char *usuario, int test) {
	FILE *fp;
	char nomearquivo[20] = "usuarios.txt", senha[20], nome_read[20] = "usrone", usuario_read[20] = "usrone";
	int loginfound = 0; /*Variavel para controle de login. So sera settada para "1" se o 				    usuario for encontrado no cadastro.*/
	if (fopen(nomearquivo, "r") == NULL) {	/*checa existencia do arquivo de cadastros*/
		printf("Nao existe nenhum usuario cadastrado!\n");
		printf("Insira <ENTER> para retornar ao menu inicial.");
		getchar();
		getchar();
	}
	else {
		fp = fopen(nomearquivo, "r");
		while(fscanf(fp,("%s %s %s"), nome_read, usuario_read, senha) == 3) {
			if(strcmp(nome_read,nome) == 0 && strcmp(usuario_read,usuario) == 0) { /*Compara dados lido do arquivo com dados inserido pelo usuario*/
				loginfound = 1;
				if(test == 1) {
					return loginfound;
				}
				printf("Sua senha: %s\n", senha);
				printf("Insira <ENTER> para retornar ao menu inicial e fazer seu Login.\n");
				getchar();
				getchar();
				fclose(fp);
				break;
			}
		}
		if(loginfound == 0) {	/*nenhum usuario foi encontrado durante a pesquisa. */
			if(test == 1) {
				return loginfound;
			}
			printf("Nenhum usuario como o inserido foi encontrado.\n");
			printf("Insira <ENTER> para retornar ao menu inicial.\n");
			getchar();
			getchar();
			fclose(fp);
		}
	}
	return 0;
}

/* Externar uma mensagem de saida para o usuario ao optar pelo encerramento da aplicacao */
void TelaSaida(char *opcao) {
	printf("Obrigado por utilizar o QuizTime!\n");
	printf("Insira <ENTER> para encerrar.\n");
	*opcao = '4';
	getchar();
	getchar();
}

/* Funcao responsavel por externar uma mensagem de LogOut*/
void TelaFinalizarSessao(char opcao) {
	printf("Sessao finalizada com sucesso.\n");
	printf("Insira <ENTER> para retornar ao Menu Inicial.\n");
	getchar();
	getchar();
}

void LerDadosCadastroAdmin() {
	char opcao;
	system("clear");
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Cadastro em Disciplina %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	ListarDisciplinas(0);
	printf("Insira o ID da Disciplina que desejas se cadastrar: ");
	getchar();
	scanf("%c", &opcao);
}


void cadastrarUsuario(char* usuario_sessao){
	FILE *fp;
	char line[100];
	char opcao;
	char *token;
	int flag = 0;
	system("clear");
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Cadastro em Disciplina %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	ListarDisciplinas(0);
	printf("Insira o ID da Disciplina que desejas se cadastrar: ");
	getchar();
	scanf("%c", &opcao);
	while(opcao == '\n') {
		printf("Insira o ID da Disciplina que desejas se cadastrar: ");
		scanf("%c", &opcao);
	}
	if(fopen("cadastros.txt","r") != NULL) {
		fp = fopen("cadastros.txt", "r");
		while(fgets(line,90,fp) != NULL) {
			if(strstr(line,usuario_sessao) != NULL) {
				token = strtok(line," ");
				token = strtok(NULL,"\n");
				if(*token == opcao) {
					flag = 1;
					printf("Usuario ja cadastrado nesta disciplina.\n");
					printf("Insira <ENTER> para retornar ao Menu.\n");
					getchar();
					getchar();
					break;
				}
			}
		}
		fclose(fp);
	}
	if(flag == 0) {
		fp = fopen("cadastros.txt","a");
		fprintf(fp,"%s %c\n", usuario_sessao, opcao);
		fclose(fp);
	}
}

/* Funcao responsavel por manifestar a tela de entrada do usuario no sistema (apos login ser realizado). Caso o usuario seja identificado como administrador, seu Menu de opcoes apresentado sera diferente caso o usuario possua perfil de estudante. */

void TelaEntradaSistema(char *usuario_sessao) {
	char opcao = '1';
	char nomearquivo[] = "disciplinas.txt";
	if(strcmp(usuario_sessao,"admin") != 0) { /*Menu de usuario estudante*/
		while(opcao != '4') {
			system("clear");
			printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Sessao Ativa - %s %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", usuario_sessao);
			printf("Perfil: Estudante\n");
			printf("---------------------------Meu Caderno---------------------------\n");
			ListarMinhasDisciplinas(usuario_sessao);
			printf("------------------------------------------------------------------------\n");

			printf("Opcoes: \n");
			printf("1 - Cadastrar Nova Disciplina ao Seu Caderno\n");
			printf("2 - Listar Disciplinas do Sistema\n");
			printf("3 - Acessar Quiz de uma Disciplina\n");
			printf("4 - Encerrar Sessao e retornar para o Menu Inicial\n");
			printf("Opcao Desejada: ");
			scanf("%c", &opcao);
			printf("\n");
			switch(opcao) {
				case '1': cadastrarUsuario(usuario_sessao);

					break; /*CadastrarDisciplina(usuario_sessao,nomearquivo);*/
				case '2': ListarDisciplinas(1);
						  break;
				case '3': acessarQuiz(usuario_sessao);
						  break;
				case '4': TelaFinalizarSessao(opcao);
						  break;
			}
		}
	}
	else {	/*Menu de usuario administrador*/
		while(opcao != '4') {
			system("clear");
			printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Sessao Ativa - %s %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", usuario_sessao);
			printf("Perfil: Administrador\n");
			printf("Opcoes: \n");
				printf("1 - Cadastrar Novo Usuario\n");
				printf("2 - Criar Disciplina\n");
				printf("3 - Adicionar Perguntas de um determinado topico\n");
				printf("4 - Encerrar Sessao e retornar para o Menu Inicial\n");
				printf("Opcao Desejada: ");
				scanf("%c", &opcao);
				switch(opcao) {
					case '1': LerDadosCadastro();
							break;
					case '2': ModificarArquivo(nomearquivo,usuario_sessao);
							break;
					case '3': gerenciaPerguntas(nomearquivo,usuario_sessao);
							break;
					case '4': TelaFinalizarSessao(opcao);
							break;
				}
			}
		}
}




/*Tela Inicial do nosso QuizTime. A Mesma informara ao usuario as opcoes que ele pode utilizar.*/
void TelaInicial() {
	char opcao = '0';
	while(opcao != '4') {
		system("clear");
		printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Seja Bem-Vindo ao QuizTime %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
		printf("Opcoes: \n");
		printf("1 - Fazer Login\n");
		printf("2 - Cadastrar\n");
		printf("3 - Esqueci Minha Senha\n");
		printf("4 - Sair\n");
		printf("Opcao Desejada: ");
		scanf("%c", &opcao);
		switch(opcao) {
			case '1': LerDadosLogin();
					break;
			case '2': LerDadosCadastro();
					break;
			case '3': LerDadosRecuperarSenha();
					break;
			case '4': TelaSaida(&opcao);
					break;
		}
	}
}
