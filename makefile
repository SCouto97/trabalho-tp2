CC=gcc
CFLAGS=-I.
DEPS = usuario.h GerenciaDisciplina.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: usuario.o GerenciaDisciplina.o
	gcc -o usuario usuario.o GerenciaDisciplina.o -I.
