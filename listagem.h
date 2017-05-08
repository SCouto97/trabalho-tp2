/*TADs utilizados para o armazenamento e listagem das matérias e seus tópicos
  São estruturados em Lista                                                   */

typedef struct _topicos {
	
	struct _topicos *proximo;
	char *nomeTopico;

} Topicos;

typedef struct _listadetopicos {

	Topicos *primeiro, *ultimo;

} ListaTopicos;

typedef struct _disciplinas {

	struct _disciplinas *proximo;
	int codigo;
	char *nomeDisciplina;
	ListaTopicos *listadetopicos;

} Disciplinas;

typedef struct {

	Disciplinas *primeiro, *ultimo;

} ListaDisciplinas;

/*Funções para criação/modificação desses TADs e impressão*/

void CriaListaTopicos(ListaTopicos *lista1);
void AdicionaTopico(ListaTopicos *lista1, char *topico);
void MostraTopicos(ListaTopicos *lista1);
void DesalocaListaTopicos(ListaTopicos *lista1);
void CriaListaDisciplinas(ListaDisciplinas *lista2);
void AdicionaDisciplina(ListaDisciplinas *lista2, int codigo, char *disciplina);
void DesalocaListaDisciplinas(ListaDisciplinas *lista2);
void MostraDisciplinas();
