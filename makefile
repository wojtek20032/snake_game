all: game

game: winsys.o screen.o 
	g++ -g -Wall -pedantic $^ -o $@ -lncurses

winsys.o:snake.cpp snake.h winsys.h screen.h cpoint.h
	g++ -g -c -Wall -pedantic $< -o $@

screen.o: screen.cpp screen.h
	g++ -g -c -Wall -pedantic $< -o $@

.PHONY: clean

clean:
	-rm game winsys.o screen.o
