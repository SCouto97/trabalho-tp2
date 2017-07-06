
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "bdd-for-c.h"

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




}
