CC =gcc
CFLAGS = -ansi -Wall
DEPS = usuario.h GerenciaDisciplina.h
OBJ = *.o

all: usuario clean

usuario: usuario.o
	$(CC) -c usuario.o

usuario.o: usuario.c $(DEPS)
	$(CC) $(CFLAGS) $(DEPS) usuario.c -c

GerenciaDisciplina.o: GerenciaDisciplina.c $(DEPS)
	$(CC) $(CFLAGS) $(DEPS) GerenciaDisciplina.c -c


clean: $(OBJ)
	rm -rf $(OBJ)