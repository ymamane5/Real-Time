
CFLAGS = -g -lcrypto -lpthread

findDup : findDup.o hash.o wQueue.o
	gcc -o aprog main.c findDup.o hash.o wQueue.o $(CFLAGS)

findDup.o : findDup.c findDup.h
	gcc -c $(CFLAGS) findDup.c

hash.o : hash.c hash.h
	gcc -c $(CFLAGS) hash.c

wQueue.o: wQueue.c wQueue.h
	gcc -c $(CFLAGS) wQueue.c