#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Topicos.h"

/*Funcao para criar uma lista de topicos com cabeca */
void CriaListaTopico(/*@out@*/ tipoListaTopico *lista) {
    lista->primeiro = (apontador3)malloc(sizeof(celulaTopico));
    lista->ultimo = lista->primeiro;
    lista->ultimo->prox = NULL;
}

/*Funcao para inserir elemento(do tipoTopico) em uma lista com cabeca*/
void InsereTopico(/*@out@*/ tipoListaTopico *lista, /*@out@*/ tipoTopico infosTopico) {
    lista->ultimo->prox = (apontador3)malloc(sizeof(celulaTopico));
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->topico = infosTopico;
    lista->ultimo->prox = NULL;
}

void DesalocarListaTopico(/*@out@*/ tipoListaTopico *lista) {
    apontador3 aux, aux2;
    aux = lista->primeiro;
    while(aux!=NULL) {
        aux2 = aux;
        aux = aux->prox;
        free(aux2);
        lista->primeiro = NULL;
    }
}

/*Funcao responsavel por listar os topicos da disciplina passada como parametro*/
void ListarTopicos(char *nomeDisciplina) {
    apontador3 aux;
    FILE *fp;
    char line[100];
    char *token;
    tipoListaTopico listaTopico;
    tipoTopico topico;
    fp = fopen("disciplinas.txt","r");
    system("clear");
    CriaListaTopico(&listaTopico);
    while(fgets(line,90,fp) != NULL) {/*Varre arquivo, lendo com strtok e insere topico na lista*/
        if(strstr(line,nomeDisciplina) != NULL) {
            token = strtok(line,".");
            topico.idDisciplinaOrigem = atoi(token);
            token = strtok(NULL,"|");
            topico.idTopico = atoi(token);
            token = strtok(NULL,"|");
            token = strtok(NULL,"|");
            strcpy(topico.nomeTopico, token);
            InsereTopico(&listaTopico, topico);
        }
    }
    aux = listaTopico.primeiro->prox;
	/* Impressao da lista de topicos */
        printf("--------------------Lista de Topicos de: %s --------------------:\n", nomeDisciplina);
        while(aux != NULL) {
            printf("ID: %d - Nome: %s\n", aux->topico.idTopico, aux->topico.nomeTopico);
            aux = aux->prox;
        }
        printf("-----------------------------------------------------------------------:\n");
        printf("Insira <ENTER> para retornar ao Menu.\n");
        getchar();
        getchar();
    fclose(fp);
    DesalocarListaTopico(&listaTopico);

}
