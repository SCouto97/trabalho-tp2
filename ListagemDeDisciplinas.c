#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ListagemDeDisciplinas.h"
#include "Topicos.h"

void InsereDisciplina(/*@out@*/ tipoListaDisciplina *lista, /*@out@*/ tipoDisciplina infosDisciplina) {
    apontador2 aux;
    int checaExistencia = 0; /*Variavel de controle para indicar se a disciplina ja esta na lista*/
    aux = lista->primeiro->prox;
    while(aux != NULL) {	/*Checa se a disciplina ja esta na lista para evitar repeticao*/
        if(aux->disciplina.idDisciplina == infosDisciplina.idDisciplina) {
            checaExistencia = 1;
            break;
        }
        aux = aux->prox;
    }
    if(checaExistencia == 0) { /*Caso a disciplina nao esteja na lista, inserimos.*/
        lista->ultimo->prox = (apontador2)malloc(sizeof(celulaDisciplina));
        lista->ultimo = lista->ultimo->prox;
        lista->ultimo->disciplina = infosDisciplina;
        lista->ultimo->prox = NULL;
    }
}

void CriaListaDisciplina(/*@out@*/ tipoListaDisciplina *lista) {
    lista->primeiro = (apontador2)malloc(sizeof(celulaDisciplina));
    lista->ultimo = lista->primeiro;
    lista->ultimo->prox = NULL;
}

void DesalocarListaDisciplina(/*@out@*/ tipoListaDisciplina *lista) {
    apontador2 aux, aux2;
    aux = lista->primeiro;
    while(aux!=NULL) {
        aux2 = aux;
        aux = aux->prox;
        free(aux2);
        lista->primeiro = NULL;
    }
}

void ListarDisciplinas(int IDaux) {
    FILE *fp;
    tipoListaDisciplina listaDisciplina;
    char line[100];	/*Array de Char para capturar uma linha do arquivo (fgets)*/
    char *token;	/*token do strtok que sera utilizado*/
    char nomeDisciplina[25] = "discpone"; /*Array de Char para armazenar o nome da disciplina que passaremos 				como parametro para Listar os Topicos dessa disciplina.*/
    int opcao;  	/*Armazena Resposta do usuario ao menu apresentado*/
    int identificador;  	/*Armazena identificador da disciplina que sera listado os 					topicos*/
    tipoDisciplina disciplina;
    apontador2 aux; /*Apontador para lista de Disciplina*/

    if(fopen("disciplinas.txt", "r") == NULL) {	/*Trata nao existencia do arquivo de disciplina*/
        printf("Nao existem disciplinas cadastradas no sistema!\n");
        printf("Insira <ENTER> para retornar ao Menu.\n");
        getchar();
        getchar();
    }
    else {
        CriaListaDisciplina(&listaDisciplina);
        fp = fopen("disciplinas.txt", "r");

	/*captura a linha e, atraves do strtok, le ID,Nome e Topico da disciplina.*/
	/*Varre o arquivo, inserindo as disciplinas na lista*/
        while(fgets(line,90,fp) != NULL) {
            token = strtok(line,".");
            disciplina.idDisciplina = atoi(token);
            token = strtok(NULL,"|");
            token = strtok(NULL,"|");
            strcpy(disciplina.nomeDisciplina, token);
            InsereDisciplina(&listaDisciplina, disciplina);
        }
        aux = listaDisciplina.primeiro->prox;
	/*Impressao da Lista de Disciplinas*/
        printf("------------------------Lista de Disciplinas------------------------:\n");
        while(aux != NULL) {
            printf("ID: %d - Nome: %s\n", aux->disciplina.idDisciplina, aux->disciplina.nomeDisciplina);
            aux = aux->prox;
        }
        printf("--------------------------------------------------------------------:\n");

	/*Apresentacao do Menu de Opcoes */
        if(IDaux == 1){
            printf("1- Listar Topicos de uma Disciplina.\n");
            printf("2- Retornar ao Menu\n");
            printf("Opcao: ");
            scanf("%d", &opcao);
            if(opcao == 1) {
                printf("Insira o Identificador da Disciplina: ");
                scanf("%d", &identificador);
            }
            aux = listaDisciplina.primeiro->prox;
            while(aux != NULL) {	/*Pelo identificador, procuramos o nome da Disciplina*/
                if(aux->disciplina.idDisciplina == identificador) {
                    strcpy(nomeDisciplina,aux->disciplina.nomeDisciplina);
                    break;
                }
                aux = aux->prox;
            }
            switch(opcao) {
                case 1: ListarTopicos(nomeDisciplina); /*Chamamos ListarTopicos passando o nome da 							Disciplina da qual desejamos obter os topicos como 							parametro*/
                        break;
                case 2: printf("Insira <ENTER> para retornar ao Menu.\n");
                        getchar();
                        getchar();
                        break;
            }
        }
        DesalocarListaDisciplina(&listaDisciplina);
        fclose(fp);
    }
}

void ListarMinhasDisciplinas(char* usuario_sessao) {
    FILE *fp;
    char line[100], *token;
    if(fopen("cadastros.txt", "r") != NULL) {
        fp = fopen("cadastros.txt", "r");
        while(fgets(line,90,fp) != NULL) {
            if(strstr(line, usuario_sessao) != NULL) {
                token = strtok(line," ");
                token = strtok(NULL,"\n");
                printf("ID: %d\n", atoi(token));
            }
        }
    }
}
