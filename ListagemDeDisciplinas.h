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


/*Função usada para listar as disciplinas ao usuário*/

void ListarDisciplinas(int IDaux);

void ListarMinhasDisciplinas(char* usuario_sessao);

void CriaListaDisciplina(tipoListaDisciplina *lista);

void DesalocarListaDisciplina(tipoListaDisciplina *lista);

void InsereDisciplina(tipoListaDisciplina *lista, tipoDisciplina infosDisciplina);

#endif
