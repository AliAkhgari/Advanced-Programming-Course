all: Goodreads.out

Goodreads.out: main.o Goodreads.o User.o Author.o Book.o Review.o Functions.o FollowEdge.o 
	g++ -std=c++11 -o Goodreads.out main.o Goodreads.o User.o Author.o Book.o Review.o Functions.o FollowEdge.o 

main.o: main.cpp Goodreads.hpp Functions.hpp
	g++ -std=c++11 -c main.cpp

Goodreads.o: Goodreads.cpp User.hpp Author.hpp Book.hpp Review.hpp FollowEdge.hpp Functions.hpp
	g++ -std=c++11 -c Goodreads.cpp

User.o: User.cpp User.hpp Functions.hpp
	g++ -std=c++11 -c User.cpp

Author.o: Author.cpp Functions.hpp
	g++ -std=c++11 -c Author.cpp

Book.o: Book.cpp Functions.hpp Author.hpp
	g++ -std=c++11 -c Book.cpp 

Review.o: Review.cpp Functions.hpp
	g++ -std=c++11 -c Review.cpp

Functions.o: Functions.cpp User.hpp Author.hpp Book.hpp Review.hpp FollowEdge.hpp Functions.hpp
	g++ -std=c++11 -c Functions.cpp

FollowEdge.o: FollowEdge.cpp Functions.hpp
	g++ -std=c++11 -c FollowEdge.cpp

clean:
	rm *.o
	rm Goodreads.out