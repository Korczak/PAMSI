CC = g++ -Iinc -std=c++11

__start__: prog
	./obj/prog.out

prog: obj/main.o obj/plansza.o
	$(CC) obj/main.o obj/plansza.o -o obj/prog.out

obj/main.o: src/main.cpp inc/plansza.hh
	$(CC) -c -o obj/main.o src/main.cpp 

obj/plansza.o: src/plansza.cpp inc/plansza.hh
	$(CC) -c -o obj/plansza.o src/plansza.cpp


clean:
	rm -r obj/*.o