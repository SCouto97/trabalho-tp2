#ifndef ListagemDedDisciplinas_h_
#define ListagemDedDisciplinas_h_

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


/**\brief Funcao responsavel por listar as disciplinas que estao cadastradas no sistema.

*/
int ListarDisciplinas(int IDaux);

void ListarMinhasDisciplinas(char* usuario_sessao);

/**\brief Funcao para criar uma lista de disciplina com cabeca. 

*/
int CriaListaDisciplina(tipoListaDisciplina *lista);

int DesalocarListaDisciplina(tipoListaDisciplina *lista);


/**\brief Funcao para inserir elemento(do tipoDisciplina) em uma lista com cabeca.

*/
int InsereDisciplina(tipoListaDisciplina *lista, tipoDisciplina infosDisciplina);

#endif
