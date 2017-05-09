
CC = gcc
CFLAGS = -ansi -Wall

#Caso exista a adição de algum módulo, modificar apenas essas variáveis
#Para a compilação (que deve ser feita independentemente) seguir os exemplos .o

DEPS = usuario.h GerenciaDisciplina.h listagem.h TAD.h
OBJS = usuario.o GerenciaDisciplina.o listagem.o quiz.o TAD.o

all: usuario

usuario: $(OBJS) 
	$(CC) $(OBJS) -o usuario

usuario.o: usuario.c $(DEPS)
	$(CC) $(CFLAGS) usuario.c -c

GerenciaDisciplina.o: GerenciaDisciplina.c GerenciaDisciplina.h
	$(CC) $(CFLAGS) GerenciaDisciplina.c -c

listagem.o: listagem.c
	$(CC) $(CFLAGS) listagem.c -c

quiz.o: quiz.c TAD.h
	$(CC) $(CFLAGS) quiz.c -c

TAD.o: TAD.c TAD.h
	$(CC) $(CFLAGS) TAD.c -c

clean: 
	rm -rf *.o *.gch usuario
