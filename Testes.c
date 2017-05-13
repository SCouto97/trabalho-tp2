#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "Quiz.c"
#include "ListagemDeDisciplinas.c"

void teste_CriaLista(void) {
	tipoLista lista;
	CriaLista(&lista);
	CU_ASSERT_PTR_NOT_NULL(lista.primeiro);
	CU_ASSERT_PTR_NULL(lista.primeiro->prox);
}

void teste_InsereLista(void) {
	tipoLista lista;
	tipoQuiz quiz;
	CriaLista(&lista);
	InsereLista(quiz,&lista);
	CU_ASSERT_PTR_NOT_NULL(lista.primeiro->prox);
	CU_ASSERT_PTR_NULL(lista.primeiro->prox->prox);
}

void teste_CriaListaDisciplina(void) {
	tipoListaDisciplina lista;
	CriaListaDisciplina(&lista);
	CU_ASSERT_PTR_NOT_NULL(lista.primeiro);
	CU_ASSERT_PTR_NULL(lista.primeiro->prox);
}

void teste_InsereListaDisciplina(void) {
	tipoListaDisciplina lista;
	tipoDisciplina infosdisciplina;
	CriaListaDisciplina(&lista);
	InsereListaDisciplina(&lista,infosdisciplina);
	CU_ASSERT_PTR_NOT_NULL(lista.primeiro->prox);
	CU_ASSERT_PTR_NULL(lista.primeiro->prox->prox);
}

int main () {
	return 0;
}