CC = g++ -Iinc -std=c++11

__start__: prog
	./obj/prog.out

prog: obj/main.o obj/board.o
	$(CC) obj/main.o obj/board.o -o obj/prog.out

obj/main.o: src/main.cpp inc/board.hh
	$(CC) -c -o obj/main.o src/main.cpp 

obj/board.o: src/board.cpp inc/board.hh
	$(CC) -c -o obj/board.o src/board.cpp

clean:
	rm -r obj/*.o