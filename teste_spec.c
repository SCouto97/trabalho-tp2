#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "bdd-for-c.h"
#include <string.h>

#include "Usuario.c"
#include "Topicos.c"
#include "Quiz.c"
#include "ListagemDeDisciplinas.c"
#include "GerenciaDisciplina.c"
#include "GerenciamentoQuiz.c"

describe("Testes do modulo Usuario") {

	it("Teste da funcao ProcuraNomeUsuario") {
		char user[20], name[20], password[20];
		int resultado = 0;
		FILE *fp;
		if(fopen("usuarios.txt", "r") != NULL) {
			fp = fopen("usuarios.txt", "r");
			fscanf(fp,("%s %s %s"), name, user, password);
			resultado = ProcuraNomeUsuario(user,"usuarios.txt");
			check(resultado == 1);
		}
	}

	it("Teste valido da funcao ValidarDisciplina") {
		FILE *fp = fopen("disciplinas.txt", "r");
		float lixo;
		char disciplina[20];
		char topperco[20];
		char line[90];
		char *token;

		if(fp) {
			fgets(line, 90, fp);
			token = strtok(line, "|");
			token = strtok(NULL, "|");
			strcpy(disciplina, token);
			token = strtok(NULL, "|");
			strcpy(topperco, token);
			check(ValidarDisciplina(disciplina, topperco) == 1);
		}
		else 
			return;
		fclose(fp);
	}

	it("Teste invalido da funcao ValidarDisciplina") {
		char *disciplina = "BANANA";
		char *topico = "DISCIPLINA";

		check(ValidarDisciplina(disciplina, topico) == 0);
	}

	it("Teste sucesso da funcao TelaLogin") {
		char user[20], password[20], name[20];
		FILE *fp;
		int resultado;
		if(fopen("usuarios.txt", "r") != NULL) {
			fp = fopen("usuarios.txt", "r");
			fscanf(fp,("%s %s %s"), name, user, password);
			resultado = TelaLogin(user,password,"usuarios.txt",1);
			check(resultado == 1)
			fclose(fp);
		}
	}

	it("Teste cadastro invalido da funcao TelaLogin") {
		char user[20] = "azazazazazazaz";
		char password[20] = "azazazazazazaz";
		int resultado;
		FILE *fp;
		if(fopen("usuarios.txt", "r") != NULL) {
			fp = fopen("usuarios.txt", "r");
			resultado = TelaLogin(user,password,"usuarios.txt",1);
			check(resultado == 0);
			fclose(fp);
		}
	}

	it("Teste arquivo inexistente da funcao TelaLogin") {
		char user[20] = "azazazazazazaz";
		char password[20] = "azazazazazazaz";
		int resultado;
		resultado = TelaLogin(user,password,"usuariol.txt", 1);
		check(resultado == 0);
	}

	it("Ao cadastrar um usuario cria o arquivo de usuarios(caso nao exista)") {
		char user[20] = "adadadadad";
		char password[20] = "adadadadad";
		char nome[20] = "stallone";
		char nomearquivo[20] = "inexistent.txt";
		int resultado;
		resultado = TelaCadastro(nome,user,password,nomearquivo,1);
		check(resultado == 1);
	}

	it("Ao cadastrar um usuario incrementa o arquivo de usuarios ja existente") {
		char user[20] = "adadadadad";
		char password[20] = "adadadadad";
		char nome[20] = "stallone";
		char nomearquivo[20] = "usuarios.txt";
		int resultado;
		resultado = TelaCadastro(nome,user,password,nomearquivo,1);
		check(resultado == 2);
	}
	
}

