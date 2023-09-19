CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: A7-810198341/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: A7-810198341/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: A7-810198341/main.cpp A7-810198341/CSVReader.hpp A7-810198341/UTRIP.hpp A7-810198341/GET.hpp A7-810198341/POST.hpp A7-810198341/DELETE.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/CSVReader.o: A7-810198341/CSVReader.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/CSVReader.cpp -o $(BUILD_DIR)/CSVReader.o

$(BUILD_DIR)/UTRIP.o: A7-810198341/UTRIP.cpp A7-810198341/Hotel.hpp A7-810198341/User.hpp A7-810198341/Room.hpp A7-810198341/ExceptionHandling.hpp A7-810198341/Filter.hpp A7-810198341/PriceFilter.hpp A7-810198341/CityFilter.hpp A7-810198341/RoomFilter.hpp A7-810198341/StarFilter.hpp A7-810198341/DefaultPriceFilter.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/UTRIP.cpp -o $(BUILD_DIR)/UTRIP.o

$(BUILD_DIR)/Hotel.o: A7-810198341/Hotel.cpp A7-810198341/Room.hpp A7-810198341/ExceptionHandling.hpp A7-810198341/Rating.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/Hotel.cpp -o $(BUILD_DIR)/Hotel.o

$(BUILD_DIR)/Rating.o: A7-810198341/Rating.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/Rating.cpp -o $(BUILD_DIR)/Rating.o

$(BUILD_DIR)/Room.o: A7-810198341/Room.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/Room.cpp -o $(BUILD_DIR)/Room.o

$(BUILD_DIR)/User.o: A7-810198341/User.cpp A7-810198341/Reserve.hpp A7-810198341/ExceptionHandling.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Reserve.o: A7-810198341/Reserve.cpp A7-810198341/Room.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/Reserve.cpp -o $(BUILD_DIR)/Reserve.o

$(BUILD_DIR)/Filter.o: A7-810198341/Filter.cpp A7-810198341/Hotel.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/Filter.cpp -o $(BUILD_DIR)/Filter.o

$(BUILD_DIR)/CityFilter.o: A7-810198341/CityFilter.cpp A7-810198341/Filter.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/CityFilter.cpp -o $(BUILD_DIR)/CityFilter.o

$(BUILD_DIR)/StarFilter.o: A7-810198341/StarFilter.cpp A7-810198341/Filter.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/StarFilter.cpp -o $(BUILD_DIR)/StarFilter.o

$(BUILD_DIR)/RoomFilter.o: A7-810198341/RoomFilter.cpp A7-810198341/Filter.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/RoomFilter.cpp -o $(BUILD_DIR)/RoomFilter.o

$(BUILD_DIR)/PriceFilter.o: A7-810198341/PriceFilter.cpp A7-810198341/Filter.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/PriceFilter.cpp -o $(BUILD_DIR)/PriceFilter.o

$(BUILD_DIR)/DefaultPriceFilter.o: A7-810198341/DefaultPriceFilter.cpp A7-810198341/Filter.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/DefaultPriceFilter.cpp -o $(BUILD_DIR)/DefaultPriceFilter.o

$(BUILD_DIR)/POST.o: A7-810198341/POST.cpp A7-810198341/UTRIP.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/POST.cpp -o $(BUILD_DIR)/POST.o

$(BUILD_DIR)/GET.o: A7-810198341/GET.cpp A7-810198341/UTRIP.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/GET.cpp -o $(BUILD_DIR)/GET.o

$(BUILD_DIR)/DELETE.o: A7-810198341/DELETE.cpp A7-810198341/UTRIP.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/DELETE.cpp -o $(BUILD_DIR)/DELETE.o

$(BUILD_DIR)/ExceptionHandling.o: A7-810198341/ExceptionHandling.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c A7-810198341/ExceptionHandling.cpp -o $(BUILD_DIR)/ExceptionHandling.o

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/CSVReader.o $(BUILD_DIR)/UTRIP.o $(BUILD_DIR)/Hotel.o $(BUILD_DIR)/Rating.o $(BUILD_DIR)/Room.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Reserve.o $(BUILD_DIR)/Filter.o $(BUILD_DIR)/CityFilter.o $(BUILD_DIR)/StarFilter.o $(BUILD_DIR)/RoomFilter.o $(BUILD_DIR)/PriceFilter.o $(BUILD_DIR)/DefaultPriceFilter.o $(BUILD_DIR)/POST.o $(BUILD_DIR)/GET.o $(BUILD_DIR)/DELETE.o $(BUILD_DIR)/ExceptionHandling.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/CSVReader.o $(BUILD_DIR)/UTRIP.o $(BUILD_DIR)/Hotel.o $(BUILD_DIR)/Rating.o $(BUILD_DIR)/Room.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Reserve.o $(BUILD_DIR)/Filter.o $(BUILD_DIR)/CityFilter.o $(BUILD_DIR)/StarFilter.o $(BUILD_DIR)/RoomFilter.o $(BUILD_DIR)/PriceFilter.o $(BUILD_DIR)/DefaultPriceFilter.o $(BUILD_DIR)/POST.o $(BUILD_DIR)/GET.o $(BUILD_DIR)/DELETE.o $(BUILD_DIR)/ExceptionHandling.o  -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null
