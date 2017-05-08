#include <stdio.h>
#include <stdlib.h>
#include "GerenciaDisciplina.h"
#include <string.h>


/*Funcao responsavel por permitir modificacoes no arquivo de disciplinas (apenas o administrador pode fazer isto) 
O Administrador podera: criar um arquivo ( se ainda nao existir ), inserir Disciplina e Topicos.
Ao inserir topicos, checa se já existe. Caso exista, informa o administrador. Caso contrário, cria o topico.*/
void ModificarArquivo(char *nomearquivo, char *usuario_sessao) {
	FILE *fp;
	char nomedisciplina[25], nometopico[25], line[100], *token;
	int flag = 0, counter=0, numerodisciplina, maiornumero = 0;

	system("clear");
	printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%% Sessao Ativa - %s %%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", usuario_sessao);
	printf("Perfil: Administrador\n");
	if(fopen(nomearquivo,"r") == NULL) { /*Checa existencia do arquivo. Caso nao exista, cria.*/
		fp = fopen(nomearquivo, "w");
		printf("Insira Disciplina: ");
		scanf(" %[^\n]s", nomedisciplina);
		printf("Topico a ser adicionado: ");
		scanf(" %[^\n]s", nometopico);
		fputs("00.1|", fp);
		fprintf(fp, "%s|%s|{Quiz 1}\n", nomedisciplina, nometopico);
		fclose(fp);
	}
	else {
		printf("Insira Disciplina: ");
		scanf(" %[^\n]s", nomedisciplina);
		printf("Topico a ser adicionado: ");
		scanf(" %[^\n]s", nometopico);
		fp = fopen(nomearquivo,"r");
		while(fgets(line,90,fp) != NULL) {
			if(strstr(line,nometopico) != NULL) {
				printf("Topico %s ja existente!\n", nometopico);
				printf("Insira <ENTER> para retornar ao MENU de Administrador.\n");
				getchar();
				getchar();
				flag = 1;
				break;
			}
		}
		fclose(fp);
		if(flag == 0) {
			fp = fopen(nomearquivo,"r");
			while(fgets(line,90,fp) != NULL) {
				if(strstr(line,nomedisciplina) != NULL) {
					token = strtok(line,".");
					numerodisciplina = atoi(token);
					counter++;
				}
				else {
					token = strtok(line,".");
					if(maiornumero < atoi(token)) {
						maiornumero = atoi(token);
					}
				}
			}
			if(counter == 0) {
				numerodisciplina = maiornumero+1;
			}
			fclose(fp);
			fp = fopen(nomearquivo,"a");
			fprintf(fp, "%d.%d|%s|%s|{Quiz 1}\n", numerodisciplina, counter+1, nomedisciplina, nometopico);
			printf("Topico adicionado com sucesso!\n");
			printf("Insira <ENTER> para retornar ao MENU de Administrador.\n");
			getchar();
			getchar();
			fclose(fp);
		}
	}
}