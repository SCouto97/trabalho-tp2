#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Quiz.h"

/*Funcao para criar uma lista com cabeca com perguntas de um quiz*/
void CriaLista(tipoLista *lista) {
  lista->primeiro = (apontador) malloc(sizeof(celula));
  lista->ultimo = lista->primeiro;
  lista->primeiro->prox = NULL;
}

/*Funcao para inserir elemento(do tipoQuiz) em uma lista com cabeca*/
void InsereLista(tipoQuiz x,tipoLista *lista){
      lista->ultimo->prox=(apontador)malloc(sizeof(celula));
      lista->ultimo=lista->ultimo->prox;
      lista->ultimo->dadosquiz = x;
      lista->ultimo->prox=NULL; 
}

/*Funcao Responsavel pela Impressao da Lista de Quiz e pela leitura das respostas do usuario.
Tambem informa ao usuario, ao termino do quiz, quais perguntas ele errou.
Recebe a Lista de Quiz e o nome do topico sobre o qual esta sendo realizado o quiz como parametro
*/

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
    while(aux!=NULL) {  /*Loop de Impressao da Pergunta e Leitura da Resposta*/
        printf("------------------------------------------------------------------\n");
        printf("%d - %s\n", counter, aux->dadosquiz.pergunta);
        getchar();
        printf("Insira V ou F: ");
        scanf("%c", &resposta);
    /*Valida se a Resposta Inserida foi V ou F, apenas*/
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
    /*Caso a resposta do usuario esteja incorreta, adicionamos a pergunta a uma Lista que  contem os erros do usuario, para que ele seja informado ao termino do quiz.*/
        if(resposta != aux->dadosquiz.resposta) {
            InsereLista(aux->dadosquiz, &ListaErradas);
        }
        printf("------------------------------------------------------------------\n");
        aux = aux->prox;
        counter++;
        printf("\n");
    }    
    /*Caso nao haja erros, printa sucesso*/
    if(ListaErradas.primeiro->prox == NULL) {
        printf("Parabens, voce acertou todas as perguntas!\n");
        printf("Insira <ENTER> para retornar ao Menu.\n");
        getchar();
        getchar();
    }
    else {  /*Caso contrario, imprime perguntas respondidas incorretamente*/
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

/*Funcao responavel pela criacao da lista de perguntas do quiz do topico passado como parametro.
Para isso, vare o arrquivo de perguntas, e, atraves da comparacao dos identificadores, filtra apenas as perguntas que fazem parte do topico que esta sendo exercitado e acrescenta na lista.*/
void ListaPerguntas(char *nomearquivo,char *nometopico) {
    FILE *fp;

    char line[260]; /*Array de char para armazenar uma linha do arquivo capturada*/
    char *token;    /*Token do strtok que sera utilizado*/
    char charaux[10];  /* Array de char para armazenar o identificador de um topico*/
    tipoLista lista;
    tipoQuiz quiz;

    if(fopen("perguntas.txt","r") == NULL) { /*Trata nao existencia do arquivo*/
        printf("Nao existe uma lista de perguntas ainda!\n");
        printf("Insira <ENTER> para retornar ao Menu.\n");
        getchar();
        getchar();
    }
    else {
        CriaLista(&lista);  
        if(fopen(nomearquivo,"r") != NULL) {
            fp = fopen(nomearquivo,"r");
            while(fgets(line,90,fp) != NULL) {  /*Captura linhas, compara identificadores*/
                if(strstr(line,nometopico) != NULL) { /*Procura a string "nometopico" na string
                                                         "line" (Linha do Arquivo que foi capturada)*/
                    token = strtok(line,"|");   
                    strcpy(charaux,token);
                    break;
                }
            }
            fclose(fp);
            fp = fopen("perguntas.txt","r");
        /*Filtra perguntas do topico passado como parametro*/
            while(fgets(line,250,fp) != NULL) { 
                if(strstr(line,charaux) != NULL) {
                    token = strtok(line,"|");
                    token = strtok(NULL,"|");
                    strcpy(quiz.pergunta,token);
                    token = strtok(NULL,"|");
                    quiz.resposta = *token; 
                    InsereLista(quiz,&lista);
                }
                printf("%s\n", nometopico);
            }
            fclose(fp);
            ImprimirPerguntas(lista,nometopico);
        }
    }  
}
