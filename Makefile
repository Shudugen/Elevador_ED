# -*- Makefile -*-
 
elevador: main.o Fila.h
	gcc main.o -o elevador
main.o: main.c Fila.h
	gcc -c main.c
clean: 
	rm *.o elevador
