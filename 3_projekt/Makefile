CC = g++ -std=c++11 

all: main.o board.o
	$(CC) main.o board.o -o a.out
	./a.out

main.o: main.cpp board.o:
	$(CC) main.cpp -c -o main.o

board.o: board.cpp board.hh minmax.o:
	$(CC) board.cpp -c -o board.o

minmax.o: minmax.cpp minmax.hh:
	$(CC) minmax.cpp -c -o minmax.o