CC = gcc
CFLAGS = -Wall -ansi
OBJ = *.o


all: usuario clean

usuario: usuario.o
	$(CC) usuario.o -o usuario


usuario.o: usuario.c
	$(CC) $(CFLAGS) usuario.c -c


clean: 
	rm -rf $(OBJ)