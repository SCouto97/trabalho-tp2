#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

#include "Topicos.c"
#include "Quiz.c"
#include "ListagemDeDisciplinas.c"

void adicionar_suite(void);

void verifica_ponteiro_lista(void);
void verifica_insercao(void);
void teste_CriaLista(void);
void teste_InsereLista(void);
void teste_CriaListaDisciplina(void);
void teste_InsereListaDisciplina(void);

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
	InsereDisciplina(&lista,infosdisciplina);
	CU_ASSERT_PTR_NOT_NULL(lista.primeiro->prox);
	CU_ASSERT_PTR_NULL(lista.primeiro->prox->prox);
}

void verifica_ponteiro_lista(void) {

	tipoListaTopico lista;
	CriaListaTopico(&lista);
	CU_ASSERT_PTR_NOT_NULL(lista.primeiro);
	CU_ASSERT_PTR_NULL(lista.primeiro->prox);
}

void verifica_insercao(void) {

	tipoListaTopico lista;
	tipoTopico top1;
	CriaListaTopico(&lista);
	InsereTopico(&lista, top1);
	CU_ASSERT_PTR_NOT_NULL(lista.primeiro->prox);
	CU_ASSERT_PTR_NULL(lista.primeiro->prox->prox);
}

void adicionar_suite(void) {

	CU_pSuite suite;

	suite = CU_add_suite("Testes estruturais", NULL, NULL);

	CU_ADD_TEST(suite, verifica_ponteiro_lista);
	CU_ADD_TEST(suite, verifica_insercao);
	CU_ADD_TEST(suite, teste_CriaLista);
	CU_ADD_TEST(suite, teste_InsereLista);
	CU_ADD_TEST(suite, teste_CriaListaDisciplina);
	CU_ADD_TEST(suite, teste_InsereListaDisciplina);

}

int main() {

	if (CUE_SUCCESS != CU_initialize_registry())
    		return CU_get_error();

    adicionar_suite();
    CU_basic_set_mode(CU_BRM_VERBOSE);
    (void)CU_basic_run_tests();

    CU_cleanup_registry();

	return CU_get_error();


	return 0;
}
