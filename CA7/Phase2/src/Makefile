all: utrip.out

utrip.out: main.o CSVReader.o UTRIP.o Hotel.o Room.o User.o POST.o GET.o DELETE.o Filter.o CityFilter.o StarFilter.o RoomFilter.o PriceFilter.o ExceptionHandling.o Reserve.o DefaultPriceFilter.o Rating.o
	g++ -std=c++11 -o utrip.out main.o CSVReader.o UTRIP.o Hotel.o Room.o User.o POST.o GET.o DELETE.o Filter.o CityFilter.o StarFilter.o RoomFilter.o PriceFilter.o ExceptionHandling.o Reserve.o DefaultPriceFilter.o Rating.o

main.o: main.cpp CSVReader.hpp UTRIP.hpp GET.hpp POST.hpp DELETE.hpp
	g++ -std=c++11 -c main.cpp

CSVReader.o: CSVReader.cpp
	g++ -std=c++11 -c CSVReader.cpp

UTRIP.o: UTRIP.cpp Hotel.hpp User.hpp Room.hpp ExceptionHandling.hpp Filter.hpp CityFilter.hpp PriceFilter.hpp RoomFilter.hpp StarFilter.hpp DefaultPriceFilter.hpp
	g++ -std=c++11 -c UTRIP.cpp

Hotel.o: Hotel.cpp Room.hpp ExceptionHandling.hpp Rating.hpp
	g++ -std=c++11 -c Hotel.cpp

Rating.o: Rating.cpp
	g++ -std=c++11 -c Rating.cpp

Room.o: Room.cpp 
	g++ -std=c++11 -c Room.cpp

User.o: User.cpp Reserve.hpp ExceptionHandling.hpp
	g++ -std=c++11 -c User.cpp

Reserve.o: Reserve.cpp Room.hpp
	g++ -std=c++11 -c Reserve.cpp

Filter.o: Filter.cpp Hotel.hpp
	g++ -std=c++11 -c Filter.cpp

CityFilter.o: CityFilter.cpp Filter.hpp
	g++ -std=c++11 -c CityFilter.cpp

StarFilter.o: StarFilter.cpp Filter.hpp
	g++ -std=c++11 -c StarFilter.cpp

RoomFilter.o: RoomFilter.cpp Filter.hpp
	g++ -std=c++11 -c RoomFilter.cpp

PriceFilter.o: PriceFilter.cpp Filter.hpp
	g++ -std=c++11 -c PriceFilter.cpp

DefaultPriceFilter.o: DefaultPriceFilter.cpp
	g++ -std=c++11 -c DefaultPriceFilter.cpp

POST.o: POST.cpp UTRIP.hpp
	g++ -std=c++11 -c POST.cpp

GET.o: GET.cpp UTRIP.hpp
	g++ -std=c++11 -c GET.cpp

DELETE.o: DELETE.cpp UTRIP.hpp
	g++ -std=c++11 -c DELETE.cpp

ExceptionHandling.o: ExceptionHandling.cpp
	g++ -std=c++11 -c ExceptionHandling.cpp
	
clean:
	rm *.o
	rm utrip.out