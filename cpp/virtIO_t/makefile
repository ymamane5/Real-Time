aprog: main.o asciiIO.o binIO.o virtIO.o
	g++ main.o asciiIO.o binIO.o virtIO.o -g

main.o: main.cpp
	g++ -c main.cpp

asciiIO.o: asciiIO.cpp asciiIO.h
	g++ -c asciiIO.cpp -g

binIO.o: binIO.cpp binIO.h
	g++ -c binIO.cpp -g

virtIO.o: virtIO.cpp virtIO.h
	g++ -c virtIO.cpp -g