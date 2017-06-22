#ifndef Quiz_h_
#define Quiz_h_

typedef struct celula_str *apontador;

typedef struct {
	char pergunta[250], resposta, respostaUser;
	char opcaoA[50];
	char opcaoB[50];
	char opcaoC[50];
	char opcaoD[50];
	int respondida, tipoD;
} tipoQuiz;

typedef struct {
	apontador primeiro, ultimo;
} tipoLista;

typedef struct celula_str {
	tipoQuiz dadosquiz;
	apontador prox;
} celula;

typedef struct topicosId {
	char topico[25];
}topicosId;

void ListaPerguntas(char *nomearquivo, char *nometopico);

void ImprimirPerguntas(tipoLista lista, char *nometopico);

void gerenciaPerguntas(char* nomearquivo, char* usuario_sessao);

void CriaLista(tipoLista *lista);

void InsereLista(tipoQuiz x, tipoLista *lista);

void DesalocarLista(tipoLista *lista);

void acessarQuiz(char *usuario_sessao);

#endif