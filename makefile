CC = gcc
CFLAGS = -ansi -Wall -std=c99
DEPS = usuario.h GerenciaDisciplina.h listagem.h TAD.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

usuario: usuario.o GerenciaDisciplina.o listagem.o TAD.o quiz.o
	gcc -o $@ $^ $(CFLAGS)
