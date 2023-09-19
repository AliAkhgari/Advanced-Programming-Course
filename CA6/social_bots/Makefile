CC := g++ -std=c++11

all: 2.out

2.out: main.o SocialBots.o Bot.o Channel.o EchoBot.o LoggerBot.o FredBot.o LibrarianBot.o SameSrcDest.o ChannelAlreadyExist.o ChannelDoesntExist.o
	$(CC) main.o SocialBots.o Bot.o Channel.o EchoBot.o LoggerBot.o FredBot.o LibrarianBot.o SameSrcDest.o ChannelAlreadyExist.o ChannelDoesntExist.o -o 2.out

main.o: main.cpp SocialBots.hpp
	$(CC) -c main.cpp

SocialBots.o: SocialBots.cpp Bot.hpp Channel.hpp EchoBot.hpp LoggerBot.hpp FredBot.hpp LibrarianBot.hpp ChannelAlreadyExist.hpp ChannelDoesntExist.hpp SameSrcDest.hpp
	$(CC) -c SocialBots.cpp

Bot.o: Bot.cpp 
	$(CC) -c Bot.cpp

Channel.o: Channel.cpp Bot.hpp
	$(CC) -c Channel.cpp

EchoBot.o: EchoBot.cpp Bot.hpp Channel.hpp
	$(CC) -c EchoBot.cpp

LoggerBot.o: LoggerBot.cpp Bot.hpp Channel.hpp
	$(CC) -c LoggerBot.cpp

FredBot.o: FredBot.cpp Bot.hpp Channel.hpp
	$(CC) -c FredBot.cpp

LibrarianBot.o: LibrarianBot.cpp Bot.hpp Channel.hpp
	$(CC) -c LibrarianBot.cpp

SameSrcDest.o: SameSrcDest.cpp	
	$(CC) -c SameSrcDest.cpp

ChannelAlreadyExist.o: ChannelAlreadyExist.cpp
	$(CC) -c ChannelAlreadyExist.cpp

ChannelDoesntExist.o: ChannelDoesntExist.cpp	
	$(CC) -c ChannelDoesntExist.cpp

clean:
	rm *.o
	rm 2.out