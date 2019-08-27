CFLAGS = -g

aprog : main.o hash.o
	gcc -o aprog main.o hash.o

main.o : main.c hash.h
	gcc -c $(CFLAGS) main.c

hash.o : hash.c hash.h
	gcc -c $(CFLAGS) hash.c