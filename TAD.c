#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TAD.h"

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

/*Funcao para criar uma lista de disciplina com cabeca */
void CriaListaDisciplina(tipoListaDisciplina *lista) {
    lista->primeiro = (apontador2)malloc(sizeof(celulaDisciplina));
    lista->ultimo = lista->primeiro;
    lista->ultimo->prox = NULL;
}
/*Funcao para inserir elemento(do tipoDisciplina) em uma lista com cabeca*/
void InsereDisciplina(tipoListaDisciplina *lista, tipoDisciplina infosDisciplina) {
    apontador2 aux;
    aux = lista->primeiro->prox;
    int checaExistencia = 0; /*Variavel de controle para indicar se a disciplina ja esta na lista*/
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

/*Funcao responsavel por listar as disciplinas que estao cadastradas no sistema*/
void ListarDisciplinas() { 
    FILE *fp;
    tipoListaDisciplina listaDisciplina;
    char line[100];	/*Array de Char para capturar uma linha do arquivo (fgets)*/
    char *token;	/*token do strtok que sera utilizado*/
    char nomeDisciplina[25]; /*Array de Char para armazenar o nome da disciplina que passaremos 				como parametro para Listar os Topicos dessa disciplina.*/
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
        fclose(fp);
    }
}



/*Funcao para criar uma lista de topicos com cabeca */
void CriaListaTopico(tipoListaTopico *lista) {
    lista->primeiro = (apontador3)malloc(sizeof(celulaTopico));
    lista->ultimo = lista->primeiro;
    lista->ultimo->prox = NULL;
}

/*Funcao para inserir elemento(do tipoTopico) em uma lista com cabeca*/
void InsereTopico(tipoListaTopico *lista, tipoTopico infosTopico) {
    lista->ultimo->prox = (apontador3)malloc(sizeof(celulaTopico));
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->topico = infosTopico; 
    lista->ultimo->prox = NULL;
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
    while(aux!=NULL) {	/*Loop de Impressao da Pergunta e Leitura da Resposta*/
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
	/*Caso a resposta do usuario esteja incorreta, adicionamos a pergunta a uma Lista que 		contem os erros do usuario, para que ele seja informado ao termino do quiz.*/
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

    char line[100]; /*Array de char para armazenar uma linha do arquivo capturada*/
    char *token;	/*Token do strtok que sera utilizado*/
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
            while(fgets(line,90,fp) != NULL) {	/*Captura linhas, compara identificadores*/
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
