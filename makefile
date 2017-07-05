CC = gcc
CFLAGS = -ansi -Wall 

#Caso exista a adição de algum módulo, modificar apenas essas variáveis
#Para a compilação (que deve ser feita independentemente) seguir os exemplos .o

DEPS = Usuario.h GerenciaDisciplina.h Topicos.h GerenciamentoQuiz.h ListagemDeDisciplinas.c
OBJS = Usuario.o GerenciaDisciplina.o Quiz.o Topicos.o GerenciamentoQuiz.o ListagemDeDisciplinas.o main.o

all: main teste teste_spec

main: $(OBJS)
	$(CC) $(OBJS) -o TP1

main.o: main.c
	$(CC) main.c -c

teste: moduloTeste.c
	$(CC) -I./CUnit -L./CUnit moduloTeste.c -lcunit -o TESTE

teste_spec: teste_spec.c
	$(CC) -std=c99 teste_spec.c -o teste_spec

usuario.o: usuario.c $(DEPS)
	$(CC) $(CFLAGS) usuario.c -c

GerenciaDisciplina.o: GerenciaDisciplina.c GerenciaDisciplina.h
	$(CC) $(CFLAGS) GerenciaDisciplina.c -c

Quiz.o: Quiz.c Topicos.h
	$(CC) $(CFLAGS) Quiz.c -c

Topicos.o: Topicos.c Topicos.h
	$(CC) $(CFLAGS) Topicos.c -c

GerenciamentoQuiz.o: GerenciamentoQuiz.c GerenciamentoQuiz.h
	$(CC) $(CFLAGS) GerenciamentoQuiz.c -c

ListagemDeDisciplinas.o: ListagemDeDisciplinas.c ListagemDeDisciplinas.h
	$(CC) $(CFLAGS) ListagemDeDisciplinas.c -c

clean:
	rm -rf *.o *.gch TP1 TESTE
