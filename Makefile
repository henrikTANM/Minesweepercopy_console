CC = g++

CFLAGS = -std=c++20 -Wall -Werror -Wpedantic

main: main.o game.o tile.o
	${CC} ${CFLAGS} main.o game.o tile.o -o main

main.o: main.cpp
	${CC} -c ${CFLAGS} main.cpp -o main.o

game.o: game.cpp
	${CC} -c ${CFLAGS} game.cpp -o game.o

tile.o: tile.cpp
	${CC} -c ${CFLAGS} tile.cpp -o tile.o

clean:
	rm *.o main.exe