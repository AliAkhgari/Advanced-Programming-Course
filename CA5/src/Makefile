CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: FieldRunners.out

FieldRunners.out: main.o rsdl.o FieldRunners.o Enemy.o file.o Tower.o bullet.o player.o missile.o gattling.o tesla.o data.o
	$(CC) main.o FieldRunners.o rsdl.o Enemy.o file.o Tower.o bullet.o player.o missile.o gattling.o tesla.o data.o $(CCFLAGS) -o FieldRunners.out

rsdl.o: rsdl.cpp
	$(CC) -c rsdl.cpp

main.o: main.cpp rsdl.hpp FieldRunners.hpp file.hpp
	$(CC) -c main.cpp

FieldRunners.o: FieldRunners.cpp rsdl.hpp Enemy.hpp Tower.hpp player.hpp data.hpp tesla.hpp missile.hpp gattling.hpp bullet.hpp file.hpp
	$(CC) -c FieldRunners.cpp

file.o: file.cpp Enemy.hpp
	$(CC) -c file.cpp

data.o: data.cpp Enemy.hpp
	$(CC) -c data.cpp

Enemy.o: Enemy.cpp rsdl.hpp file.hpp
	$(CC) -c Enemy.cpp

Tower.o: Tower.cpp rsdl.hpp file.hpp bullet.hpp
	$(CC) -c Tower.cpp

bullet.o: bullet.cpp file.hpp rsdl.hpp
	$(CC) -c bullet.cpp

player.o: player.cpp rsdl.hpp 
	$(CC) -c player.cpp

missile.o: missile.cpp Tower.hpp
	$(CC) -c missile.cpp

tesla.o: tesla.cpp Tower.hpp
	$(CC) -c tesla.cpp

gattling.o: gattling.cpp Tower.hpp
	$(CC) -c gattling.cpp

clean:
	rm *.o
	rm FieldRunners.out