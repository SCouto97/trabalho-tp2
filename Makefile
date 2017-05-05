CC = gcc
CFLAGS = -Wall -ansi
OBJ = *.o
DEPS = usuario.h


all: usuario clean

usuario: usuario.o
	$(CC) usuario.o -o usuario


usuario.o: usuario.c $(DEPS)
	$(CC) $(CFLAGS) usuario.c -c


clean: 
	rm -rf $(OBJ)