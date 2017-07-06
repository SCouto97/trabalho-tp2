
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
}

