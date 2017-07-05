
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
}
