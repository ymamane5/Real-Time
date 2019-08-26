﻿CFLAGS = -g

aprog : darray_test.o darray_int.o
	gcc -o aprog darray_test.o darray_int.o

darray_test.o : darray_test.c darray_int.h
	gcc -c $(CFLAGS) main.c

darray_int.o : darray_int.c darray_int.h
	gcc -c $(CFLAGS) vector.c