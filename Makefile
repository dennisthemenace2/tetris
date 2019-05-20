CC = gcc
LD = ld

prog: main.o render.o
	$(CC) -o prog main.o render.o -lGL -lGLU -lglut -std=c99

main.o: main.c
	$(CC) -c main.c 

render.o: render.c
	$(CC) -c render.c render.h -std=c99
