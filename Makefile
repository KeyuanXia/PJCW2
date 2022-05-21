main: main.o Array.o Initial.o MakeLife.o utility.o ViewDraw.o
	gcc -o $@ $^ -lSDL2
main.o: main.c Initial.h Array.h utility.h ViewDraw.h
	gcc -c $<
Array.o: Array.c Array.h Initial.h
	gcc -c $<
Initial.o: Initial.c Initial.c utility.h
	gcc -c $<
MakeLife.o: MakeLife.c MakeLife.h
	gcc -c $<
utility.o: utility.c Array.h
	gcc -c $<
ViewDraw.o: ViewDraw.c ViewDraw.h Array.h utility.h MakeLife.h Initial.h
	gcc -c $<
clean:
	rm -rf *.o main
