#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TAD.h"

void CriaLista(tipoLista *lista) {
  lista->primeiro = (apontador) malloc(sizeof(celula));
  lista->ultimo = lista->primeiro;
  lista->primeiro->prox = NULL;
}

void InsereLista(tipoQuiz x,tipoLista *lista){
	  lista->ultimo->prox=(apontador)malloc(sizeof(celula));
	  lista->ultimo=lista->ultimo->prox;
	  lista->ultimo->dadosquiz = x;
	  lista->ultimo->prox=NULL;	
}

void ImprimirPerguntas(tipoLista lista, char *nometopico) {
    apontador aux;
    int counter = 1, boolean = 0;
    char resposta;
    tipoLista ListaErradas;
    aux = lista.primeiro->prox;
    CriaLista(&ListaErradas);
    system("clear");
    printf("---------------- Quiz: %s ----------------", nometopico);
    printf("\n");
    while(aux!=NULL) {
        printf("------------------------------------------------------------------\n");
        printf("%d - %s\n", counter, aux->dadosquiz.pergunta);
        getchar();
        printf("Insira V ou F: ");
        scanf("%c", &resposta);
        if(resposta == 'v' || resposta == 'V') {
            resposta = 'V';
        }
        else {
            if(resposta == 'f' || resposta == 'F') {
                resposta = 'F';
            }
            else {
                while(boolean == 0) {
                    getchar();
                    printf("\nInsira V ou F: ");
                    scanf("%c", &resposta);
                    if(resposta == 'v' || resposta == 'V' || resposta == 'f' || resposta == 'F') {
                        boolean = 1;
                    }
                }
                boolean = 0;
            }
        }

        if(resposta != aux->dadosquiz.resposta) {
            InsereLista(aux->dadosquiz, &ListaErradas);
        }
        printf("------------------------------------------------------------------\n");
        aux = aux->prox;
        counter++;
        printf("\n");
    }    
    if(ListaErradas.primeiro->prox == NULL) {
        printf("Parabens, voce acertou todas as perguntas!\n");
        printf("Insira <ENTER> para retornar ao Menu.\n");
        getchar();
        getchar();
    }
    else {
        aux = ListaErradas.primeiro->prox;
        printf("ITENS INCORRETOS:\n\n");
        while(aux!=NULL) {
            printf("------------------------------------------------------------------\n");
            printf("%s\n", aux->dadosquiz.pergunta);
            if(aux->dadosquiz.resposta == 'V') {
                printf("Respondeu: F\n");
                printf("Resposta Correta: %c\n", aux->dadosquiz.resposta);
            }
            else {
              printf("Respondeu: V\n");
              printf("Resposta Correta: %c\n", aux->dadosquiz.resposta);
            }
            printf("------------------------------------------------------------------\n");
            printf("\n\n");
            aux = aux->prox;
        }
        printf("Insira <ENTER> para retornar ao Menu.\n");
        getchar();
        getchar();
    }
}

void ListaPerguntas(char *nomearquivo,char *nometopico) {
    FILE *fp;
    int counter = 1;
    char line[100], *token, charaux[10];
    tipoLista lista;
    tipoQuiz quiz;
    apontador aux;

    if(fopen("perguntas.txt","r") == NULL) {
        printf("Nao existe uma lista de perguntas ainda!\n");
        printf("Insira <ENTER> para retornar ao Menu.\n");
        getchar();
        getchar();
    }
    else {
        CriaLista(&lista);
        if(fopen(nomearquivo,"r") != NULL) {
            fp = fopen(nomearquivo,"r");
            while(fgets(line,90,fp) != NULL) {
                if(strstr(line,nometopico) != NULL) {
                    token = strtok(line,"|");
                    strcpy(charaux,token);
                    break;
                }
            }
            fclose(fp);
            fp = fopen("perguntas.txt","r");
            while(fgets(line,90,fp) != NULL) {
                if(strstr(line,charaux) != NULL) {
                    token = strtok(line,"|");
                    token = strtok(NULL,"|");
                    strcpy(quiz.pergunta,token);
                    token = strtok(NULL,"|");
                    quiz.resposta = *token; 
                    InsereLista(quiz,&lista);
                }
            }
            fclose(fp);
            ImprimirPerguntas(lista,nometopico);
        }
    }  
}