#include <stdio.h>
#include <stdlib.h>
//#include "quiz.h"
#include <string.h>

void gerenciaPerguntas(char* nomearquivo, char* usuario_sessao){
    FILE* arq;
    float num;
    char pergunta[150], nomedisciplina[25], topico[25], boolean, line[100], *token;
    arq = fopen(nomearquivo,"r");
    system("clear");
    printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Sessao Ativa - %s %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", usuario_sessao);
    printf("Perfil: Administrador\n");
    printf("\n\n~>Adicione sua pergunta<~\n");
    printf("Digite o nome da disciplina: ");
    scanf("%s",nomedisciplina);
    printf("Digite o nome do topico: ");
    scanf("%s",topico);
    while(fgets(line,90,arq) != NULL) {
        if(strstr(line,topico) != NULL) {
            token = strtok(line,"|");
            num = atof(token);
            break;
        }
    }
    printf("%f\n", num);
    fclose(arq);
    arq = fopen("perguntas.txt","a");
    printf("Digite sua pergunta: ");
    scanf(" %[^\n]s", pergunta);
    getchar();
    printf("Insira a resposta (V ou F): ");
    scanf("%c", &boolean);


    fprintf(arq,"%.1f|%s|%c|\n",num,pergunta,boolean);
    fclose(arq);
}

int main(int argc, char *argv[]) {
    char nice[20] = "admin";
    char nomearquivo[20] = "disciplinas.txt";
    gerenciaPerguntas(nomearquivo,nice);
    return 0;
}
