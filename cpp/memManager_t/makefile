aprog: main.cpp memManager.o memPool.o memPage.o
	g++ main.cpp memManager.o memPool.o memPage.o -g

memManager.o: memManager.cpp memManager.h
	g++ -c memManager.cpp -g

memPool.o: memPool.cpp memPool.h
	g++ -c memPool.cpp -g

memPage.o: memPage.cpp memPage.h
	g++ -c memPage.cpp -g