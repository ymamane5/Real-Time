prog: progA.o progB.o libN.so
	gcc -o prog progA.o progB.o -lN -L.

progA.o : progA.c
	gcc -c progA.c

progB.o : progB.c
	gcc -c progB.c

libN.so : lib1.o lib2.o lib3.o
	gcc -o libN.so -shared lib1.o lib2.o lib3.o

lib1.o : lib1.c
	gcc -c -fPIC lib1.c

lib2.o : lib2.c
	gcc -c -fPIC lib2.c

lib3.o : lib3.c
	gcc -c -fPIC lib3.c	
