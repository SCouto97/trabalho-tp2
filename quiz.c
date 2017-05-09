#include <stdio.h>
#include <stdlib.h>
#include "TAD.h"
#include <string.h>



void gerenciaPerguntas(char* nomearquivo, char* usuario_sessao){
    FILE* arq;
    float num;
    char pergunta[150], nomedisciplina[25], topico[25], resposta, line[100], *token;
    arq = fopen(nomearquivo,"r");
    int boolean = 0;
    system("clear");
    printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Sessao Ativa - %s %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", usuario_sessao);
    printf("Perfil: Administrador\n");
    printf("\n\n~>Adicione sua pergunta<~\n");
    getchar();
    printf("Digite o nome da disciplina: ");
    scanf("%[^\n]s",nomedisciplina);
    printf("Digite o nome do topico: ");
    scanf(" %[^\n]s",topico);
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
          printf("%c", resposta);
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
