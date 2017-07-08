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

void DesalocarListaTopico(tipoListaTopico *lista);

/**\brief Funcao para criar uma lista de topicos com cabeca. 

*/
void CriaListaTopico(tipoListaTopico *lista);

/**\brief Funcao para inserir elemento(do tipoTopico) em uma lista com cabeca.

*/
void InsereTopico(tipoListaTopico *lista, tipoTopico infosTopico);

/**\brief Funcao responsavel por listar os topicos da disciplina passada como parametro.

*/
int ListarTopicos(char *nomeDisciplina, int test);

#endif
