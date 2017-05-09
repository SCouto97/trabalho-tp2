#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listagem.h"

void CriaListaTopicos(ListaTopicos *lista1) {

	if(lista1 != NULL) {

		lista1->primeiro = (Topicos*)malloc(sizeof(Topicos));
		lista1->ultimo = lista1->primeiro;
		lista1->ultimo->proximo = NULL;
	} else
		printf("Esse ponteiro nao existe\n");

	return;
}

void AdicionaTopico(ListaTopicos *lista1, char *topico) {

	Topicos *aux = lista1->ultimo;
	aux->proximo = (Topicos*)malloc(sizeof(Topicos));
	strcpy(aux->proximo->nomeTopico, topico);
	lista1->ultimo = aux->proximo;
}

void MostraTopicos(ListaTopicos *lista1) {

	Topicos *aux = lista1->primeiro->proximo;

	while(aux != NULL) {

		printf("Os topicos sao:\n");
		fputs(aux->nomeTopico, stdout);
		aux = aux->proximo;
	}
	return;
}

void DesalocaListaTopicos(ListaTopicos *lista1) {

	Topicos *aux1, *aux2;
	aux1 = lista1->primeiro;
	aux2 = NULL;

	while(aux1) {

		aux2 = aux1;
		aux1 = aux1->proximo;
		free(aux2);
	}
	free(lista1);
}

void CriaListaDisciplinas(ListaDisciplinas *lista2) {

	if(lista2 != NULL) {

		lista2->primeiro = (Disciplinas*)malloc(sizeof(Disciplinas));
		lista2->ultimo = lista2->primeiro;
		lista2->ultimo->proximo = NULL;
	} else
		printf("Esse ponteiro nao existe\n");

	return;
}

void AdicionaDisciplina(ListaDisciplinas *lista2, int codigo, char *disciplina) {

	Disciplinas *aux = lista2->ultimo;
	aux->proximo = (Disciplinas*)malloc(sizeof(Disciplinas));
	strcpy(aux->proximo->nomeDisciplina, disciplina);
	aux->proximo->codigo = codigo;
	lista2->ultimo = aux->proximo;
}

void DesalocaListaDisciplinas(ListaDisciplinas *lista2) {

	Disciplinas *aux1, *aux2;
	aux1 = lista2->primeiro;
	aux2 = NULL;

	while(aux1) {

		aux2 = aux1;
		aux1 = aux1->proximo;
		free(aux2);
	}
	free(lista2);
}


void MostraDisciplinas() {

	FILE *fp = fopen("disciplinas.txt", "r");

	if(fp) {

		fclose(fp);
	} else
		printf("nao foi possivel abrir o arquivo\n\n");

	return;
}
