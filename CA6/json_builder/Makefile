CC := g++ -std=c++11

all: 1.out

1.out: main.o JsonBuilder.o Container.o Object.o Data.o KeyString.o KeyInt.o Array.o
	$(CC) main.o JsonBuilder.o Container.o Object.o Data.o KeyString.o KeyInt.o Array.o -o 1.out

main.o: main.cpp JsonBuilder.hpp
	$(CC) -c main.cpp

JsonBuilder.o: JsonBuilder.cpp Container.hpp
	$(CC) -c JsonBuilder.cpp

Container.o: Container.cpp Object.hpp Array.hpp Data.hpp
	$(CC) -c Container.cpp

Object.o: Object.cpp Data.hpp KeyInt.hpp KeyString.hpp
	$(CC) -c Object.cpp

Data.o: Data.cpp
	$(CC) -c Data.cpp

KeyString.o: KeyString.cpp Data.hpp
	$(CC) -c KeyString.cpp

KeyInt.o: KeyInt.cpp Data.hpp
	$(CC) -c KeyInt.cpp

Array.o: Array.cpp Data.hpp String.hpp Int.hpp
	$(CC) -c Array.cpp

String.o: String.cpp Data.hpp
	$(CC) -c String.cpp

Int.o: Int.cpp Data.hpp
	$(CC) -c Int.cpp

clean:
	rm *.o
	rm 1.out