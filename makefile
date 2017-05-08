CC = gcc
CFLAGS = -ansi -Wall
DEPS = usuario.h GerenciaDisciplina.h listagem.h
OBJS = usuario.o GerenciaDisciplina.o listagem.o

all: usuario

usuario: $(OBJS)
	$(CC) $(OBJS) -o usuario

usuario.o: usuario.c $(DEPS)
	$(CC) $(CFLAGS) usuario.c $(DEPS) -c

GerenciaDisciplina.o: GerenciaDisciplina.c GerenciaDisciplina.h
	$(CC) $(CFLAGS) GerenciaDisciplina.c -c

listagem.o: listagem.c
	$(CC) $(CFLAGS) listagem.c -c

clean: 
	rm -rf *.o *.gch usuario
