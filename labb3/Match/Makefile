CC=g++
CFLAGS=-c -Wall -std=c++11 -O3
SOURCES:=*.cpp
OBJECTS:=$(SOURCES:.cpp=.o)
EXECUTABLE=match

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	-rm -rf *.o $(EXECUTABLE)
