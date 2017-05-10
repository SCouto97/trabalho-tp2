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

void AdicionaDisciplina(ListaDisciplinas *lista2, float codigo, char *nome) {

	Disciplinas *aux = lista2->ultimo;
	aux->proximo = (Disciplinas*)malloc(sizeof(Disciplinas));
	aux->proximo->codigo = codigo;
	strcpy(aux->proximo->nomeDisciplina, nome);
	aux->proximo->visitado = 1;
/*	CriaListaTopicos(lt);
	ListaTopicos *lt;
	AdicionaTopico(lt)
*/
	return;
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

/*	FILE *fp = fopen("disciplinas.txt", "r");

	ListaDisciplinas *l1;

	if(fp) {

		AdicionaDisciplina(l1);				
		system("clear");
		printf("------------------------------------------------------------------\n");
		printf("Codigo: %f\nMateria: %s\nTopicos: \n", l1->ultimo->codigo, l1->ultimo->nomeDisciplina);
		MostraTopicos(l1->ultimo->listadetopicos);

		fclose(fp);
	} else
		printf("nao foi possivel abrir o arquivo\n\n");

	return;
*/
}

/*
int main() {

	FILE *fp = fopen("disciplinas.txt", "r");
	
	if(fp) {

			float codigo;
			char *nome, *token, *linha_atual;
	
			const char sep[2] = "|";

			fgets(linha_atual, 100, fp);
			token = strtok(linha_atual, sep);
			codigo = atof(token);
			
			Disciplinas *aux = lista2->ultimo;
			aux->proximo = (Disciplinas*)malloc(sizeof(Disciplinas));
			
			aux->proximo->codigo = codigo;

			CriaListaTopicos(aux->listadetopicos);
			
			int i = 0;

			while(token != NULL) {

				token = strtok(NULL, sep);

				if(i == 0)
					strcpy(nome, token);
				if(i == 1)
					AdicionaTopico(aux->listadetopicos, token);

				strcpy(aux->proximo->nomeDisciplina, nome);

				lista2->ultimo = aux->proximo;
				++i;
			}
	
	
	
			fclose(fp);
	} else
		printf("O arquivo nao pode ser acessado\n");
	
	return;


	return 0;
}

*/