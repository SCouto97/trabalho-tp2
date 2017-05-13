CC = gcc
CFLAGS = -ansi -Wall 

#Caso exista a adição de algum módulo, modificar apenas essas variáveis
#Para a compilação (que deve ser feita independentemente) seguir os exemplos .o

DEPS = usuario.h GerenciaDisciplina.h Topicos.h GerenciamentoQuiz.h ListagemDeDisciplinas.c
OBJS = usuario.o GerenciaDisciplina.o Quiz.o Topicos.o GerenciamentoQuiz.o ListagemDeDisciplinas.o

all: usuario teste

usuario: $(OBJS)
	$(CC) $(OBJS) -o usuario

teste: moduloTeste.c
	$(CC) -I./CUnit -L./CUnit moduloTeste.c -lcunit -o teste

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
	rm -rf *.o *.gch usuario teste
