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

/**Funcao responsavel pela criacao da lista de perguntas do quiz do topico passado como parametro.
*Para isso, vare o arrquivo de perguntas, e, atraves da comparacao dos identificadores, 
*filtra apenas as perguntas que fazem parte do topico que esta sendo exercitado e acrescenta na lista.
*/
void ListaPerguntas(char *nomearquivo, char *nometopico);

/**Funcao Responsavel pela Impressao da Lista de Quiz e pela leitura das respostas do usuario.
*Tambem informa ao usuario, ao termino do quiz, quais perguntas ele errou.
*Recebe a Lista de Quiz e o nome do topico sobre o qual esta sendo realizado o quiz como parametro
*/
void ImprimirPerguntas(tipoLista lista, char *nometopico);


/**
* Funcao para criar uma lista com cabeca com perguntas de um quiz
*/
void CriaLista(tipoLista *lista);


/**
*Funcao para inserir elemento(do tipoQuiz) em uma lista com cabeca
*/
int InsereLista(tipoQuiz x, tipoLista *lista);

void DesalocarLista(tipoLista *lista);

void acessarQuiz(char *usuario_sessao);

#endif