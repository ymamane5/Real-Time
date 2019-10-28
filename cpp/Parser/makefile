aprog: main.o parser.o tokenizer.o analizer.o
	g++ main.o parser.o tokenizer.o analizer.o -g

main.o: main.cpp
	g++ -c main.cpp

parser.o: parser.cpp parser.h
	g++ -c parser.cpp -g

tokenizer.o: tokenizer.cpp tokenizer.h
	g++ -c tokenizer.cpp -g

analizer.o: analizer.cpp analizer.h
	g++ -c analizer.cpp -g