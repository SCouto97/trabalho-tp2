#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"
#include <string.h>

/*Função responsável por apresentar a tela de Login ao cliente. Pede que seja inserido usuário e senha e
Informa se o Login foi realizado com sucesso. */
void TelaLogin() {
	FILE *fp;
	int loginfound = 0;
	char user[20], password[20], name[20], user_read[20], password_read[20], nomearquivo[20] = "usuarios.txt";
	system("clear");
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Tela de Login: %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("%%%%%%%%%%%%%% Usuario: ");
	scanf("%s", user);
	printf("%%%%%%%%%%%%%% Senha: ");
	scanf("%s", password);

	if(fopen(nomearquivo, "r") == NULL) {
		printf("Nao existem usuarios cadastrados!\n");
		printf("Insira <QUALQUER TECLA> para retornar ao menu inicial.");
		getchar();
		getchar();

	}
	else {
		fp = fopen(nomearquivo, "r");
		while(fscanf(fp,("%s %s %s"), name, user_read, password_read) == 3) {
			if(strcmp(user_read,user) == 0 && strcmp(password_read,password) == 0) {
				printf("Login Efetuado com Sucesso!\n");
				printf("Seja Bem-Vindo, %s\n", name);
				getchar();
				getchar();
				loginfound = 1;
				break;
			}
		}
		if(loginfound == 0) {
			printf("Usuario e/ou Senha Incorretos.\n");
			printf("Insira <QUALQUER TECLA> para retornar ao menu inicial.");
			getchar();
			getchar();
			system("clear");
		}
		fclose(fp);
	}
}

/*Função responsável por checar se um nome de usuário já existe. Para isso, lê o arquivo e compara com o nome
inserido pelo usuário. Caso já exista um igual, retorna 1. Caso contrário, retorna 0.*/
int ProcuraNomeUsuario(char username[20], char nomearquivo[20]) {
	char user_read[20], name_read[20], password_read[20];
	FILE *fp;
	if(fopen(nomearquivo, "r") == NULL) {
		return 0;
	}
	else {
		fp = fopen(nomearquivo,"r");
		while(fscanf(fp,("%s %s %s"), name_read, user_read, password_read) == 3) {
			if(strcmp(user_read,username) == 0) {
				printf("Este usuario ja existe. Insira outro. \n");
				return 1;
			}
		}
		return 0;
	}
}

/*Função responsável por realizar o cadastro de novos usuários. São solicitados a princípio: Nome, Usuário e Senha.
Checa se o usuario está disponível para uso. Se não estiver, o cadastro é realizado. Se estiver, então o cliente deverá
optar por outro nome de usuário*/
void TelaCadastro() {
	char nome[20], login[20], senha[20], nomearquivo[20] = "usuarios.txt";
	FILE *fp;
	int usuarioexiste = 1;
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Cadastro %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
	printf("%%%%%%%%%%%%%% Primeiro Nome: ");
	scanf("%s", nome);
	while(usuarioexiste == 1) {
		printf("%%%%%%%%%%%%%% Usuario: ");
		scanf("%s", login);
		usuarioexiste = ProcuraNomeUsuario(login,nomearquivo);
	}
	printf("%%%%%%%%%%%%%% Senha: ");
	scanf("%s", senha);
	if(fopen(nomearquivo,"r") == NULL) {
		fp = fopen(nomearquivo, "w");
		fprintf(fp,"%s %s %s\n", nome, login, senha);
		printf("Cadastro realizado com sucesso.\n");
		printf("Insira <QUALQUER TECLA> para retornar ao menu inicial e fazer seu Login.\n");
		getchar();
		getchar();
		system("clear");
		fclose(fp);
	}
	else {
		fp = fopen(nomearquivo, "a");
		fprintf(fp,"%s %s %s\n", nome, login, senha);
		printf("Cadastro realizado com sucesso.\n");
		printf("Insira <QUALQUER TECLA> para retornar ao menu inicial e fazer seu Login.\n");
		getchar();
		getchar();
		system("clear");
		fclose(fp);
	}
}

/*Função responsável por procurar no arquivo de cadastros o usuario inserido. Para solicitar a senha é necessario
informar o nome e o usuario. Com ambas informações, é realizada uma busca no arquivo e, se existir algum cadastro
que possua o Nome e o Usuário informados, entao pegamos essa senha e informamos ao cliente.*/
void TelaRecuperarSenha() {
	FILE *fp;
	char nomearquivo[20] = "usuarios.txt", nome[20], usuario[20], senha[20], nome_read[20], usuario_read[20];
	int loginfound = 0;
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Recuperacao de Senha %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");	
	printf("%%%%%%%%%%%%%% Insira seu primeiro nome: ");
	scanf("%s", nome);
	printf("%%%%%%%%%%%%%% Insira seu usuario: ");
	scanf("%s", usuario);
	if (fopen(nomearquivo, "r") == NULL) {	/*checa existencia do arquivo de cadastros*/
		printf("Nao existe nenhum usuario cadastrado!\n");
		printf("Insira <QUALQUER TECLA> para retornar ao menu inicial.");
		getchar();
		getchar();		
	}
	else {
		fp = fopen(nomearquivo, "r");
		while(fscanf(fp,("%s %s %s"), nome_read, usuario_read, senha) == 3) {
			if(strcmp(nome_read,nome) == 0 && strcmp(usuario_read,usuario) == 0) { /*Compara dados lido do arquivo com dados inserido pelo usuario*/
				loginfound = 1;
				printf("Sua senha: %s\n", senha);
				printf("Insira <QUALQUER TECLA> para retornar ao menu inicial e fazer seu Login.\n");
				getchar();
				getchar();
				fclose(fp);
				break;
			}
		}
		if(loginfound == 0) {	/*nenhum usuario foi encontrado durante a pesquisa. */
			printf("Nenhum usuario como o inserido foi encontrado.\n");
			printf("Insira <QUALQUER TECLA> para retornar ao menu inicial.\n");
			getchar();
			getchar();
			fclose(fp);
		}	
	}
}

/* Externar uma mensagem de saida para o usuario */
void TelaSaida(int *opcao) {
	printf("Obrigado por utilizar o QuizTime!\n");
	printf("Insira <QUALQUER TECLA> para encerrar.\n");
	*opcao = 4;
	getchar();
	getchar();
}

/*Tela Inicial do nosso QuizTime. A Mesma informara ao usuario as opcoes que ele pode utilizar.*/
void TelaInicial() {
	int opcao = 0;
	while(opcao != 4) {
		system("clear");		
		printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Seja Bem-Vindo ao QuizTime %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
		printf("Opcoes: \n");
		printf("1 - Fazer Login\n");
		printf("2 - Cadastrar\n");
		printf("3 - Esqueci Minha Senha\n");
		printf("4 - Sair\n");
		printf("Opcao Desejada: ");
		scanf("%d", &opcao);
		switch(opcao) {
			case 1: TelaLogin();
					break;
			case 2: TelaCadastro();
					break;
			case 3: TelaRecuperarSenha();
					break;
			case 4: TelaSaida(&opcao);
					break;
		}
	}	
}	


int main () {
	TelaInicial();
	return 0;
}