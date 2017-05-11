#ifndef TAD_h_
#define TAD_h_

typedef struct celula_str *apontador;

typedef struct {
	char pergunta[60], resposta;
	int respondida;
}tipoQuiz;

typedef struct {
	apontador primeiro, ultimo;
}tipoLista;

typedef struct celula_str {
	tipoQuiz dadosquiz;
	apontador prox;
}celula;



typedef struct celula_str2 *apontador2;

typedef struct {
	char nomeDisciplina[25];
	int idDisciplina;
}tipoDisciplina;

typedef struct celula_str2 {
	tipoDisciplina disciplina;
	apontador2 prox;	
}celulaDisciplina;

typedef struct {
	apontador2 primeiro,ultimo;
}tipoListaDisciplina;



typedef struct celula_str3 *apontador3;

typedef struct {
	char nomeTopico[25];
	int idTopico, idDisciplinaOrigem;
}tipoTopico;

typedef struct celula_str3 {
	tipoTopico topico;
	apontador3 prox;
}celulaTopico;

typedef struct {
	apontador3 primeiro,ultimo;
}tipoListaTopico;


void CriaListaTopico(tipoListaTopico *lista);

void InsereTopico(tipoListaTopico *lista, tipoTopico infosTopico);

void ListarTopicos(char *nomeDisciplina);

void ListarDisciplinas();

void CriaLista(tipoLista *lista);

void InsereLista(tipoQuiz x, tipoLista *lista);

void ListaPerguntas(char *nomearquivo, char *nometopico);

void ImprimirPerguntas(tipoLista lista, char *nometopico);

void gerenciaPerguntas(char* nomearquivo, char* usuario_sessao);

#endif
