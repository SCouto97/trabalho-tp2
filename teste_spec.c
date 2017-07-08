#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "bdd-for-c.h"
#include <string.h>

#include "Usuario.c"
#include "Quiz.c"
#include "Topicos.c"
#include "ListagemDeDisciplinas.c"
#include "GerenciaDisciplina.c"
#include "GerenciamentoQuiz.c"

describe("Testes Utilizando Specs") {

	/*! Diagrama da funcao ProcuraNomeUsuario
	* \image latex ProcuraNomeUsuario.eps "Fluxograma" width=15cm
	* Nessa função optamos por testar seguindo o critério de cobertura por decisões, onde
	* checamos se a funcao ProcuraNomeUsuario responde como esperado quando a entrada equivale a um usuario
	* já existente. A escolha de critério de cobertura ser por decisão foi basicamente devido ao fato de que 
	* os trechos críticos para o bom funcionamento está na forma que a entrada se relaciona com os condicionais, enquanto
	* o restante das instruções presentes basicamente realizam interface com o usuario.
	*/
	it("Teste da funcao ProcuraNomeUsuario") {
		char user[20], name[20], password[20];
		int resultado = 0;
		FILE *fp;
		if(fopen("usuarios.txt", "r") != NULL) {
			fp = fopen("usuarios.txt", "r");
			fscanf(fp,("%s %s %s"), name, user, password);
			resultado = ProcuraNomeUsuario(user,"usuarios.txt");
			check(resultado == 1);
		}
	}

	/*! Diagrama da funcao ValidarDisciplina
	* \image latex ValidarDisciplina.eps "Fluxograma" width=15cm
	* No teste dessa função também utilizamos o critério de cobertura de decisões, onde checamos o comportamento da função ValidarDisciplina quando
	* a entrada é composta de uma disciplina e um tópico ambos válidos, e também quando não são válidos. Assim, Avaliamos se a função realiza corretamente o seu 		* papel de determinar a validade/invalidade de uma dupla disciplina e tópico. A justificativa por trás da cobertura ser de decisão também é devido a falta de 		* necessidade de realizar uma cobertura de instruções, uma vez que o bom funcionamento da função está atrelada ao comportamento dos condicionais.
	*/
	it("Teste valido da funcao ValidarDisciplina") {
		FILE *fp = fopen("disciplinas.txt", "r");
		char disciplina[20];
		char topperco[20];
		char line[90];
		char *token;

		if(fp) {
			fgets(line, 90, fp);
			token = strtok(line, "|");
			token = strtok(NULL, "|");
			strcpy(disciplina, token);
			token = strtok(NULL, "|");
			strcpy(topperco, token);
			check(ValidarDisciplina(disciplina, topperco) == 1);
		}
		else 
			return;
		fclose(fp);
	}

	it("Teste invalido da funcao ValidarDisciplina") {
		char *disciplina = "BANANA";
		char *topico = "DISCIPLINA";

		check(ValidarDisciplina(disciplina, topico) == 0);
	}

	/*! Diagrama da funcao TelaLogin
	* \image latex TelaLogin.eps "Fluxograma" width=15cm
	* Pelo critério de cobertura de decisões, checamos se a função TelaLogin responde cada classe de entrada como deveria.
	* Assim, inserimos três classes de entrada para checarmos o funcionamento da função: entrada válida, entrada inválida quanto ao usuário, entrada inválida
	* quanto ao arquivo. 
	*/
	it("Teste sucesso da funcao TelaLogin") {
		char user[20], password[20], name[20];
		FILE *fp;
		int resultado;
		if(fopen("usuarios.txt", "r") != NULL) {
			fp = fopen("usuarios.txt", "r");
			fscanf(fp,("%s %s %s"), name, user, password);
			resultado = TelaLogin(user,password,"usuarios.txt",1);
			check(resultado == 1)
			fclose(fp);
		}
	}

	it("Teste cadastro invalido da funcao TelaLogin") {
		char user[20] = "azazazazazazaz";
		char password[20] = "azazazazazazaz";
		int resultado;
		FILE *fp;
		if(fopen("usuarios.txt", "r") != NULL) {
			fp = fopen("usuarios.txt", "r");
			resultado = TelaLogin(user,password,"usuarios.txt",1);
			check(resultado == 0);
			fclose(fp);
		}
	}

	it("Teste arquivo inexistente da funcao TelaLogin") {
		char user[20] = "azazazazazazaz";
		char password[20] = "azazazazazazaz";
		int resultado;
		resultado = TelaLogin(user,password,"usuariol.txt", 1);
		check(resultado == 0);
	}

	/*! Diagrama da funcao TelaCadastro
	* \image latex TelaCadastro.eps "Fluxograma" width=15cm
	* Seguindo o critério de cobertura por decisões, checamos se a função TelaCadastro realiza o cadastro de um usuário
	* corretamente quando o arquivo de usuários ainda nao existe, e também se ele incrementa o arquivo com o novo usuário quando o arquivo
	* já existe. Novamente, a cobertura por instruções seria desnecessária por demandar uma quantidade maior de recursos sendo que a avaliação
	* do desempenho das funções depende unicamente da corretude dos condicionais.
	*/
	it("Ao cadastrar um usuario cria o arquivo de usuarios(caso nao exista)") {
		char user[20] = "adadadadad";
		char password[20] = "adadadadad";
		char nome[20] = "stallone";
		char nomearquivo[20] = "inexistent.txt";
		int resultado;
		resultado = TelaCadastro(nome,user,password,nomearquivo,1);
		check(resultado == 1);
	}

	it("Ao cadastrar um usuario incrementa o arquivo de usuarios ja existente") {
		char user[20] = "adadadadad";
		char password[20] = "adadadadad";
		char nome[20] = "stallone";
		char nomearquivo[20] = "usuarios.txt";
		int resultado;
		resultado = TelaCadastro(nome,user,password,nomearquivo,1);
		check(resultado == 2);
	}

	/*! Diagrama da funcao TelaRecuperarSenha 
	* \image latex TelaRecuperarSenha.eps "Fluxograma" width=15cm
	* Também seguindo o critério de cobertura por decisões, checamos se a função TelaRecuperarSenha 
	* responde como esperado quando a entrada se trata de um usuario existente, bem como quando se trata de um usuario inexistente.
	* Novamente, é interessante trabalhar com classes válidas e inválidas para determinar a relação de corretude entre entradas e condicionais.
	*/
	it("Teste sucesso em recuperar a senha de um usuario") {
		char nome[20];
		char user[20];
		char line [100];
		char *token;
		int resultado;
		FILE *fp;
		if(fopen("usuarios.txt","r") != NULL) {
			fp = fopen("usuarios.txt", "r");
			fgets(line,90,fp);
			token = strtok(line," ");
			strcpy(nome,token);
			token = strtok(NULL," ");
			strcpy(user,token);
			resultado = TelaRecuperarSenha(nome,user,1);
			check(resultado == 1);
		}
	}


	it("Teste falha em recuperar a senha de um usuario") {
		char nome[20] = "adadadadad";
		char user[20] = "adxaxddasdas";
		int resultado;
		resultado = TelaRecuperarSenha(nome,user,1);
		check(resultado == 0);
	}

	/*! Diagrama da funcao InsereLista
	* \image latex InsereLista.eps "Fluxograma" width=4cm
	* Pelo critério de cobertura de instrções, checamos se todas as instruções da função InsereLista são exercitadas.
	*/
	it("Teste se o elemento eh inserido com sucesso numa lista") {
		int resultado;
		tipoQuiz quiz;
		tipoLista lista;
		CriaLista(&lista);
		strcpy(quiz.pergunta, "Pergunta");
		resultado = InsereLista(quiz, &lista);
		check(resultado == 0);
		DesalocarLista(&lista);
	}
	
	/*! Diagrama da função DesalocarLista
	* \image latex DesalocarLista.eps "Fluxograma" width=4cm
	* Pelo critério de cobertura de instruções, checamos se todas instruções de DesalocarLista são devidamente exercitadas
	*/
	it("Testa se a lista eh desalocada com sucesso") {

		int resultado;
		tipoLista lista;
		CriaLista(&lista);
		resultado =	DesalocarLista(&lista);
		check(resultado == 1);	
	}

	/*! Diagrama da funcao CriaLista
	* \image latex CriaLista.eps "Fluxograma" width=4cm
	* Pelo critério de cobertura de instruções, checamos se todas instruções de CriaLista são devidamente exercitadas
	*/
	it("Verifica se a lista eh criada com sucesso") {
		int resultado;
		tipoLista lista;
		resultado = CriaLista(&lista);
		check(resultado == 1);
		DesalocarLista(&lista);
	}

	it("Testa se a lista de disciplinas foi criada e preenchida") {
		int teste = 2;
		int resultado;
		resultado = ListarDisciplinas(teste);
		check(resultado == 1);
	}

	it("Testa se a lista de topicos de uma disciplina foi criada e preenchida") {
		int teste = 1;
		int resultado;
		char line[100];
		char *token;
		char nomeDisciplina[25];
		FILE *fp;
		if(fopen("disciplinas.txt","r") != NULL) {
			fp = fopen("disciplinas.txt","r");
			fgets(line,90,fp);
			token = strtok(line,"|");
			token = strtok(NULL,"|");
			strcpy(nomeDisciplina,token);
			resultado = ListarTopicos(nomeDisciplina,teste);
			check(resultado == 1);
		}
	}

/*aqui muda*/
	it("Teste se consegue criar uma lista de disciplinas") {
		tipoListaDisciplina lista;
		int resultado;
		resultado = CriaListaDisciplina(&lista);
		check(resultado == 1);
		DesalocarListaDisciplina(&lista);
	}
	
	/*! Diagrama da função DesalocarLista
	* \image latex DesalocarLista.eps "Fluxograma" width=4cm
	* Pelo critério de cobertura de instruções, checamos se todas instruções de DesalocarLista são devidamente exercitadas
	*/
	it("Testa se a lista de disciplinas eh desalocada com sucesso") {
		int resultado;
		tipoListaDisciplina lista;
		CriaListaDisciplina(&lista);
		resultado =	DesalocarListaDisciplina(&lista);
		check(resultado == 1);	
	}
	/*! Diagrama da funcao CriaLista
	* \image latex CriaLista.eps "Fluxograma" width=4cm
	* Pelo critério de cobertura de instruções, checamos se todas instruções de CriaLista são devidamente exercitadas
	*/
	it("Verifica se consegue inserir uma disciplina nao existente") {
		int resultado;
		tipoListaDisciplina lista;
		tipoDisciplina disciplina;
		CriaListaDisciplina(&lista);
		resultado = InsereDisciplina(&lista, disciplina);
		check(resultado == 0);
		DesalocarListaDisciplina(&lista);
	}
	
	it("Verifica se consegue inserir uma disciplina ja existente") {
		int resultado;
		tipoListaDisciplina lista;
		tipoDisciplina disciplina1;
		tipoDisciplina disciplina2 = disciplina1;
		CriaListaDisciplina(&lista);
		InsereDisciplina(&lista, disciplina1);		
		resultado = InsereDisciplina(&lista, disciplina2);
		check(resultado == 1);
		DesalocarListaDisciplina(&lista);
	}
	/*! Diagrama da funcao CriaLista
	* \image latex CriaLista.eps "Fluxograma" width=4cm
	* Pelo critério de cobertura de instruções, checamos se todas instruções de CriaLista são devidamente exercitadas
	*/
	it("Verifica se consegue inserir uma disciplina nao existente") {

		int resultado;
		tipoListaDisciplina lista;
		tipoDisciplina disciplina;
		CriaListaDisciplina(&lista);
		resultado = InsereDisciplina(&lista, disciplina);
		check(resultado == 0);
		DesalocarListaDisciplina(&lista);
	}

	it("Verifica se consegue inserir uma disciplina ja existente") {
		int resultado;
		tipoListaDisciplina lista;
		tipoDisciplina disciplina1;
		tipoDisciplina disciplina2 = disciplina1;
		CriaListaDisciplina(&lista);
		InsereDisciplina(&lista, disciplina1);		
		resultado = InsereDisciplina(&lista, disciplina2);
		check(resultado == 1);
		DesalocarListaDisciplina(&lista);
	}

	it("Checa se a funcao ListaPerguntas criou e preenchou a lista de perguntas"){
		char arquivo[20] = "disciplinas.txt";
		char *token;
		FILE *fp;
		char topico[20];
		char line[100];
		int resultado;
		if(fopen(arquivo,"r") != NULL) {
			fp = fopen(arquivo,"r");
			fgets(line,90,fp);
			token = strtok(line,"|");
			token = strtok(NULL,"|");
			token = strtok(NULL,"|");
			strcpy(topico,token);
			resultado = ListaPerguntas(arquivo,topico,1);
			check(resultado == 1);
		}
	}
}
