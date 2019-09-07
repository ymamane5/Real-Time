CFLAGS = -g

aprog : main.o malloc.o
	gcc -o aprog main.o malloc.o

main.o : main.c 
	gcc -c $(CFLAGS) main.c

malloc.o : malloc.c malloc.h
	gcc -c $(CFLAGS) malloc.c