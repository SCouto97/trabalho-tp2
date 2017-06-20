#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GerenciamentoQuiz.h"

/*Funcao responsavel por checar existencia da disciplina e topico recebida como parametro
Retorna 1 se a disciplina e o topico inseridos existirem, 0 caso contrario*/
int ValidarDisciplina(char *nomeDisciplina, char *nomeTopico) {
	FILE *fp;	
	char line[100]; /*Array de Char para armazenar linha do arquivo capturada*/
	char *token;
	if(fopen("disciplinas.txt","r") == NULL) {
		printf("Essa Disciplina nao existe!");
		return 0;
	}
	else {
		fp = fopen("disciplinas.txt", "r");
		while(fgets(line,90,fp) != NULL) {
			if(strstr(line,nomeDisciplina) != NULL) {
				token = strtok(line,"|");
				token = strtok(NULL,"|");
				token = strtok(NULL,"|");
				if(strcmp(nomeTopico,token) == 0) {
					return 1;
				}
			}
		}
		return 0;
	}
	fclose(fp);
}


void gerenciaPerguntas(char* nomearquivo, char* usuario_sessao){
    FILE* arq;
    float num;
    char pergunta[250], nomedisciplina[25], topico[25], resposta, line[100], *token, opcao;
    char opcaoA[50];
    char opcaoB[50];
    char opcaoC[50];
    char opcaoD[50];
    arq = fopen(nomearquivo,"r");
    int boolean = 0;
    int boolean2 = 0;
    system("clear");
    printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Sessao Ativa - %s %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", usuario_sessao);
    printf("Perfil: Administrador\n");
    printf("1- Inserir Pergunta do Tipo A (V ou F)\n");
    printf("2- Inserir Pergunta do Tipo D (Multipla Escolha)\n");
    printf("Opcao: ");
    getchar();
    scanf("%c", &opcao);
    if(opcao == '1') {
        printf("\n\n~>Adicione sua pergunta<~\n");
        getchar();
        printf("Digite o nome da disciplina: ");
        scanf("%[^\n]s",nomedisciplina);
        printf("Digite o nome do topico: ");
        scanf(" %[^\n]s",topico);
        while(boolean2 == 0) {
        	boolean2 = ValidarDisciplina(nomedisciplina, topico);
        	if(boolean2 == 0) {
        		printf("Disciplina e/ou Topico incorretos.\n");
        		getchar();
        		printf("Insira novamente a Disciplina: ");
        		scanf("%[^\n]s", nomedisciplina);
        		printf("Insira novamente o Topico: ");
           		scanf(" %[^\n]s",topico);
        	}
        }
        while(fgets(line,90,arq) != NULL) {
            if(strstr(line,topico) != NULL) {
                token = strtok(line,"|");
                num = atof(token);
                break;
            }
        }
        fclose(arq);
        arq = fopen("perguntas.txt","a");
        printf("Digite sua pergunta: ");
        scanf(" %[^\n]s", pergunta);
        getchar();
        printf("Insira a resposta (V ou F): ");
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
                }
            }


        fprintf(arq,"%.1f|%s|%c|\n",num,pergunta,resposta);
        fclose(arq);
    }
    else {
        if(opcao == '2') {
            printf("\n\n~>Adicione sua pergunta<~\n");
            getchar();
            printf("Digite o nome da disciplina: ");
            scanf("%[^\n]s",nomedisciplina);
            printf("Digite o nome do topico: ");
            scanf(" %[^\n]s",topico);
            while(boolean2 == 0) {
                boolean2 = ValidarDisciplina(nomedisciplina, topico);
                if(boolean2 == 0) {
                    printf("Disciplina e/ou Topico incorretos.\n");
                    getchar();
                    printf("Insira novamente a Disciplina: ");
                    scanf("%[^\n]s", nomedisciplina);
                    printf("Insira novamente o Topico: ");
                    scanf(" %[^\n]s",topico);
                }
            }
            while(fgets(line,90,arq) != NULL) {
                if(strstr(line,topico) != NULL) {
                    token = strtok(line,"|");
                    num = atof(token);
                    break;
                }
            }
            fclose(arq);
            arq = fopen("perguntas2.txt","a");
            printf("Digite sua pergunta: ");
            scanf(" %[^\n]s", pergunta);
            getchar();
            printf("Insira a Opcao A: ");
            scanf("%[^\n]s", opcaoA);
            printf("Insira a Opcao B: ");
            getchar();
            scanf("%[^\n]s", opcaoB);
            printf("Insira a Opcao C: ");
            getchar();
            scanf("%[^\n]s", opcaoC);
            printf("Insira a Opcao D: ");
            getchar();
            scanf("%[^\n]s", opcaoD);
            getchar();
            printf("Insira a resposta (A, B, C ou D): ");
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
                                printf("\nInsira A, B, C ou D: ");
                                scanf("%c", &resposta);
                                if(resposta == 'a' || resposta == 'A' || resposta == 'b' || resposta == 'B' || resposta == 'c' || resposta == 'C' || resposta == 'd' || resposta == 'D') {
                                    boolean = 1;
                                }
                            }
                        }
                    }
                }
            }
            fprintf(arq,"%.1f|%s|%c|\n",num,pergunta,resposta);
            fprintf(arq,"%.1f|%s|\n",num,opcaoA);
            fprintf(arq,"%.1f|%s|\n",num,opcaoB);
            fprintf(arq,"%.1f|%s|\n",num,opcaoC);
            fprintf(arq,"%.1f|%s|\n",num,opcaoD);
            fclose(arq);
        }
    }
}
