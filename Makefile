Project2: main.o
	g++ -o Project2 main.o

main.o: main.cpp linearlist.h linearlist-implementation.h
	g++ -c main.cpp