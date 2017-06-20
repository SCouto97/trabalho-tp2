#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h> 
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

void DesalocarLista(tipoLista *lista) {
    apontador aux, aux2;
    aux = lista->primeiro;
    while(aux!=NULL) {
        aux2 = aux;
        aux = aux->prox;
        free(aux2);
    }
}

/*Funcao Responsavel pela Impressao da Lista de Quiz e pela leitura das respostas do usuario.
Tambem informa ao usuario, ao termino do quiz, quais perguntas ele errou.
Recebe a Lista de Quiz e o nome do topico sobre o qual esta sendo realizado o quiz como parametro
*/

void ImprimirPerguntas(tipoLista lista, char *nometopico) {
    apontador aux;
    int counter = 1, boolean = 0;
    char resposta, opcao = '0';
    tipoLista ListaErradas;
    aux = lista.primeiro->prox;
    struct timeval t1, t2, v2, v1;
    double elapsedTime;
    CriaLista(&ListaErradas);
    system("clear");
    #include <sys/time.h>
    printf("---------------- Quiz: %s ----------------", nometopico);
    printf("\n");
    gettimeofday(&v1, NULL); 
    while(aux!=NULL) {  /*Loop de Impressao da Pergunta e Leitura da Resposta*/
        if(aux->dadosquiz.tipoD == 0) {
            gettimeofday(&t1, NULL); 
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
            gettimeofday(&t2, NULL);
            elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      /*seg -> ms*/
            elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   /*us -> ms*/
            printf("Tempo de Resposta da Questao: %lf ms\n", elapsedTime);
        /*Caso a resposta do usuario esteja incorreta, adicionamos a pergunta a uma Lista que  contem os erros do usuario, para que ele seja informado ao termino do quiz.*/
            if(resposta != aux->dadosquiz.resposta) {
                aux->dadosquiz.respostaUser = resposta;
                InsereLista(aux->dadosquiz, &ListaErradas);
            }
            printf("------------------------------------------------------------------\n");
            aux = aux->prox;
            counter++;
            printf("\n");
        }
        else {
            gettimeofday(&t1, NULL); 
            printf("------------------------------------------------------------------\n");
            printf("%d - %s\n", counter, aux->dadosquiz.pergunta);
            printf("Opcao A: %s\n", aux->dadosquiz.opcaoA);
            printf("Opcao B: %s\n", aux->dadosquiz.opcaoB);
            printf("Opcao C: %s\n", aux->dadosquiz.opcaoC);
            printf("Opcao D: %s\n", aux->dadosquiz.opcaoD);
            getchar();
            printf("Insira A,B,C ou D: ");
            scanf("%c", &resposta);
            if(resposta == 'a' || resposta == 'A') {
                resposta = 'A';
            }
            else {
                if(resposta == 'b' || resposta == 'B') {
                    resposta = 'B';
                }
                else {
                    if(resposta == 'c' || resposta == 'C') {
                         resposta = 'C';
                    }
                    else {
                        if(resposta == 'd' || resposta == 'D') {
                            resposta = 'D';
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
                }
            }
            gettimeofday(&t2, NULL);
            elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      /*seg -> ms*/
            elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   /*us -> ms*/
            printf("Tempo de Resposta da Questao: %lf ms\n", elapsedTime);
            /*Caso a resposta do usuario esteja incorreta, adicionamos a pergunta a uma Lista que  contem os erros do usuario, para que ele seja informado ao termino do quiz.*/
            if(resposta != aux->dadosquiz.resposta) {
                aux->dadosquiz.respostaUser = resposta;
                InsereLista(aux->dadosquiz, &ListaErradas);
            }
            printf("------------------------------------------------------------------\n");
            aux = aux->prox;
            counter++;
            printf("\n");
        }
    }  
    gettimeofday(&v2, NULL);   
    elapsedTime = (v2.tv_sec - v1.tv_sec) * 1000.0;      /*seg -> ms*/
    elapsedTime += (v2.tv_usec - v1.tv_usec) / 1000.0;   /*us -> ms*/
    printf("Duracao do Quiz: %lf ms\n", elapsedTime);
    /*Caso nao haja erros, printa sucesso*/
    if(ListaErradas.primeiro->prox == NULL) {
        printf("Parabens, voce acertou todas as perguntas!\n");
        printf("Insira <ENTER> para retornar ao Menu.\n");
        getchar();
        getchar();
    }
    else {  /*Caso contrario, imprime perguntas respondidas incorretamente*/
        aux = ListaErradas.primeiro->prox;
        printf("\n\n");
        printf("1 - ITENS INCORRETOS\n");
        printf("2 - SAIR\n");
        printf("Opcao: ");
        getchar();
        scanf("%c", &opcao);
        switch(opcao) {
                case '1':   while(aux!=NULL) {
                                printf("------------------------------------------------------------------\n");
                                printf("%s\n", aux->dadosquiz.pergunta);
                                printf("Respondeu: %c\n", aux->dadosquiz.respostaUser);
                                printf("Resposta Correta: %c\n", aux->dadosquiz.resposta);
                                printf("------------------------------------------------------------------\n");
                                printf("\n");
                                aux = aux->prox;
                            }
                            break;
                case '2':   break;
        }
        printf("Insira <ENTER> para retornar ao Menu.\n");
        getchar();
        getchar();
        DesalocarLista(&lista);
        DesalocarLista(&ListaErradas);
    }
}

void acessarQuiz(char *usuario_sessao) {
    FILE *fp, *fp2;
    char line[100], line2[100], *token, *token2;
    char nomeTopico[25];
    if(fopen("cadastros.txt","r") != NULL && fopen("disciplinas.txt","r") != NULL) {
        fp = fopen("cadastros.txt","r");
        printf("---------------------------Topicos Disponiveis---------------------------\n");
        while(fgets(line,90,fp)!=NULL) {
            if(strstr(line,usuario_sessao) != NULL) {
                token = strtok(line," ");
                token = strtok(NULL,"\n");
                fp2 = fopen("disciplinas.txt","r");
                while(fgets(line2,90,fp2)!=NULL) {
                    token2 = strtok(line2,".");
                    if(strcmp(token,token2) == 0) {
                        token2 = strtok(NULL,"|");
                        token2 = strtok(NULL,"|");
                        token2 = strtok(NULL,"|");
                        printf("%s\n", token2);
                    }
                }
            }
        }
        printf("-------------------------------------------------------------------------\n");
        printf("Insira o nome do topico sobre o qual desejas realizar um quiz: ");
        scanf("%s", nomeTopico);
        ListaPerguntas("disciplinas.txt",nomeTopico);
        fclose(fp);
        fclose(fp2);
    }
}

/*Funcao responavel pela criacao da lista de perguntas do quiz do topico passado como parametro.
Para isso, vare o arrquivo de perguntas, e, atraves da comparacao dos identificadores, filtra apenas as perguntas que fazem parte do topico que esta sendo exercitado e acrescenta na lista.*/
void ListaPerguntas(char *nomearquivo,char *nometopico) {
    FILE *fp;
    int counter=0;
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
                    quiz.tipoD = 0;
                    InsereLista(quiz,&lista);
                }
                printf("%s\n", nometopico);
            }
            fclose(fp);
            if(fopen("perguntas2.txt","r") != NULL) {
                fp = fopen("perguntas2.txt","r");
                while(fgets(line,250,fp) != NULL) {
                    if(strstr(line,charaux) != NULL) {
                        counter++;
                        if(counter == 1) {
                            token = strtok(line,"|");
                            token = strtok(NULL,"|");
                            strcpy(quiz.pergunta,token);
                            token = strtok(NULL,"|");
                            quiz.resposta = *token;
                        }
                        else {
                            if(counter == 2) {
                                token = strtok(line,"|");
                                token = strtok(NULL,"|");
                                strcpy(quiz.opcaoA,token);
                            }
                            else {
                                if(counter == 3) {
                                    token = strtok(line,"|");
                                    token = strtok(NULL,"|");
                                    strcpy(quiz.opcaoB,token);
                                }
                                else {
                                    if(counter == 4) {
                                        token = strtok(line,"|");
                                        token = strtok(NULL,"|");
                                        strcpy(quiz.opcaoC,token);
                                    }
                                    else {
                                        if(counter == 5) {
                                            token = strtok(line,"|");
                                            token = strtok(NULL,"|");
                                            strcpy(quiz.opcaoD,token);
                                            quiz.tipoD = 1;
                                            InsereLista(quiz,&lista);
                                            counter = 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                fclose(fp);
            }
            ImprimirPerguntas(lista,nometopico);
        }
    }  
}
