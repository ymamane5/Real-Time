CFLAGS = -g

findDup : findDup.o hash.o
	gcc -o aprog testFindDup.c findDup.o hash.o

findDup.o : findDup.c findDup.h
	gcc -c $(CFLAGS) findDup.c

hash.o : hash.c hash.h
	gcc -c $(CFLAGS) hash.c