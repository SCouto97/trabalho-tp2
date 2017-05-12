#ifndef TAD_h_
#define TAD_h_


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

#endif
