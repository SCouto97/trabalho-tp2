#ifndef Quiz_h_
#define Quiz_h_

typedef struct celula_str *apontador;

typedef struct {
	char pergunta[250], resposta;
	int respondida;
} tipoQuiz;

typedef struct {
	apontador primeiro, ultimo;
} tipoLista;

typedef struct celula_str {
	tipoQuiz dadosquiz;
	apontador prox;
} celula;

void ListaPerguntas(char *nomearquivo, char *nometopico);

void ImprimirPerguntas(tipoLista lista, char *nometopico);

void gerenciaPerguntas(char* nomearquivo, char* usuario_sessao);

void CriaLista(tipoLista *lista);

void InsereLista(tipoQuiz x, tipoLista *lista);

void DesalocarLista(tipoLista *lista);

void acessarQuiz(char *usuario_sessao);

#endif