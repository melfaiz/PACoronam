CC=g++
CFLAGS=-c -Wall -std=c++11 
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

SOURCES=$(wildcard source/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=pacoronam



all: make run

make: $(SOURCES) $(EXECUTABLE) 

run: 
	./$(EXECUTABLE)
        
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LIBFLAGS)

clean:
	rm -rf source/*.o
	rm -f $(EXECUTABLE)

