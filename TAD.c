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

void CriaListaDisciplina(tipoListaDisciplina *lista) {
    lista->primeiro = (apontador2)malloc(sizeof(celulaDisciplina));
    lista->ultimo = lista->primeiro;
    lista->ultimo->prox = NULL;
}

void InsereDisciplina(tipoListaDisciplina *lista, tipoDisciplina infosDisciplina) {
    apontador2 aux;
    aux = lista->primeiro->prox;
    int checaExistencia = 0;
    while(aux != NULL) {
        if(aux->disciplina.idDisciplina == infosDisciplina.idDisciplina) {
            checaExistencia = 1;
            break;
        }         
        aux = aux->prox;    
    }
    if(checaExistencia == 0) {
        lista->ultimo->prox = (apontador2)malloc(sizeof(celulaDisciplina));
        lista->ultimo = lista->ultimo->prox;
        lista->ultimo->disciplina = infosDisciplina; 
        lista->ultimo->prox = NULL;
    }
}

void ListarDisciplinas() { 
    FILE *fp;
    tipoListaDisciplina listaDisciplina;
    char line[100];
    char *token;
    char nomeDisciplina[25];
    int opcao, identificador;
    tipoDisciplina disciplina;
    apontador2 aux;

    if(fopen("disciplinas.txt", "r") == NULL) {
        printf("Nao existem disciplinas cadastradas no sistema!\n");
        printf("Insira <ENTER> para retornar ao Menu.\n");
        getchar();
        getchar();
    }
    else {
        CriaListaDisciplina(&listaDisciplina);
        fp = fopen("disciplinas.txt", "r");
        

        while(fgets(line,90,fp) != NULL) {
            token = strtok(line,".");
            disciplina.idDisciplina = atoi(token);
            token = strtok(NULL,"|");
            token = strtok(NULL,"|");
            strcpy(disciplina.nomeDisciplina, token);
            InsereDisciplina(&listaDisciplina, disciplina);
        }
        aux = listaDisciplina.primeiro->prox;
        printf("------------------------Lista de Disciplinas------------------------:\n");
        while(aux != NULL) {
            printf("ID: %d - Nome: %s\n", aux->disciplina.idDisciplina, aux->disciplina.nomeDisciplina);
            aux = aux->prox;
        }
        printf("--------------------------------------------------------------------:\n");
        printf("1- Listar Topicos de uma Disciplina.\n");
        printf("2- Retornar ao Menu\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        if(opcao == 1) {
            printf("Insira o Identificador da Disciplina: ");
            scanf("%d", &identificador);
        }
        aux = listaDisciplina.primeiro->prox;
        while(aux != NULL) {
            if(aux->disciplina.idDisciplina == identificador) {
                strcpy(nomeDisciplina,aux->disciplina.nomeDisciplina);
                break;
            }
            aux = aux->prox;
        }
        switch(opcao) {
            case 1: ListarTopicos(nomeDisciplina);
                    break;
            case 2: printf("Insira <ENTER> para retornar ao Menu.\n");
                    getchar();
                    getchar();
                    break;
        }
        fclose(fp);
    }
}




void CriaListaTopico(tipoListaTopico *lista) {
    lista->primeiro = (apontador3)malloc(sizeof(celulaTopico));
    lista->ultimo = lista->primeiro;
    lista->ultimo->prox = NULL;
}

void InsereTopico(tipoListaTopico *lista, tipoTopico infosTopico) {
    lista->ultimo->prox = (apontador3)malloc(sizeof(celulaTopico));
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->topico = infosTopico; 
    lista->ultimo->prox = NULL;
}

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
    while(fgets(line,90,fp) != NULL) {
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

    char line[100], *token, charaux[10];
    tipoLista lista;
    tipoQuiz quiz;

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