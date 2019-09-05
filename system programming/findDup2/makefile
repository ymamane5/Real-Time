CFLAGS = -g -lcrypto

findDup : findDup.o hash.o
	gcc -o aprog testFindDup.c findDup.o hash.o -lcrypto

findDup.o : findDup.c findDup.h
	gcc -c $(CFLAGS) findDup.c

hash.o : hash.c hash.h
	gcc -c $(CFLAGS) hash.c